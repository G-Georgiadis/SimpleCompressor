/*****************************************************************//**
 * \file   PluginProcessor.cpp
 * \brief  Implementation file for the Simple Compressor plugin processor.
 * 
 * \author George Georgiadis
 * \date   September 2023
 *********************************************************************/

#include "PluginProcessor.h"
#include "PluginEditor.h"


#pragma region Constructor & Deconstructor
SimpleCompressorAudioProcessor::SimpleCompressorAudioProcessor()
    : undoManager(),
    inputGainDecibels(apvts.getParameterAsValue("Input Gain").getValue()),
    thresholdDb(apvts.getParameterAsValue("Threshold").getValue()),
    ratio(apvts.getParameterAsValue("Ratio").getValue()),
    outputGainDecibels(apvts.getParameterAsValue("Output Gain").getValue()),
    amplitudeToCompress(0),
    maxValueAfterInputGainL(0),
    maxValueAfterInputGainR(0)
{
    apvts.addParameterListener("Input Gain", this);
    apvts.addParameterListener("Threshold", this);
    apvts.addParameterListener("Ratio", this);
    apvts.addParameterListener("Output Gain", this);
}

SimpleCompressorAudioProcessor::~SimpleCompressorAudioProcessor()
{
}
#pragma endregion Constructor & Deconstructor


#pragma region Default stuff
const juce::String SimpleCompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleCompressorAudioProcessor::acceptsMidi() const
{
    return false;
}

bool SimpleCompressorAudioProcessor::producesMidi() const
{
    return false;
}

bool SimpleCompressorAudioProcessor::isMidiEffect() const
{
    return false;
}

double SimpleCompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleCompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleCompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleCompressorAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String SimpleCompressorAudioProcessor::getProgramName(int index)
{
    return {};
}

void SimpleCompressorAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}
#pragma endregion


#pragma region Processing logic
void SimpleCompressorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec{ sampleRate, samplesPerBlock , jmax<float>(this->getTotalNumInputChannels(), this->getTotalNumOutputChannels()) };

    inputGain.prepare(spec);
    inputGain.setGainDecibels(inputGainDecibels);

    compressorGain.prepare(spec);
    compressorGain.setGainLinear(1 / ratio);

    outputGain.prepare(spec);
    outputGain.setGainDecibels(outputGainDecibels);
}

void SimpleCompressorAudioProcessor::releaseResources()
{

}

void SimpleCompressorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    ScopedNoDenormals noDenormals;

    

    int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {

        for (int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
        {
            /** The current amplitude value [-1.f to 1.f] */
            auto sample = buffer.getSample(channel, sampleIndex);
            auto thresholdValue = juce::Decibels::decibelsToGain(thresholdDb);

            // Apply input gain
            sample = inputGain.processSample(sample);

            if (channel == 0) if (abs(sample) > maxValueAfterInputGainL) maxValueAfterInputGainL = sample;
            if (channel == 1) if (abs(sample) > maxValueAfterInputGainR) maxValueAfterInputGainR = sample;
            //if (channel == 0) sumInputGainL += sample * sample;  // For use with input meter. 
            //else if (channel == 1) sumInputGainR = sample * sample;
            
            amplitudeToCompress = abs(sample) - thresholdValue;

            // Compress
            if (sample > thresholdValue)
            {
                sample = thresholdValue + compressorGain.processSample(amplitudeToCompress);
            }
            else if (sample < -thresholdValue)
            {
                sample = -thresholdValue - compressorGain.processSample(amplitudeToCompress);
            }

            // Apply output gain
            sample = outputGain.processSample(sample);

            if (channel == 0) if (abs(sample) > maxValueAfterOutputGainL) maxValueAfterOutputGainL = sample;
            if (channel == 1) if (abs(sample) > maxValueAfterOutputGainR) maxValueAfterOutputGainR = sample;

            //if (channel == 0) sumOutputGainL += sample * sample;  // For use with input meter. 
            //else if (channel == 1) sumOutputGainR += sample * sample;

            // Write processed sample to buffer
            buffer.setSample(channel, sampleIndex, sample);
        }
    }
}

//void SimpleCompressorAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
//{
//    ScopedNoDenormals noDenormals;
//
//    double sumInputGainL = 0.0;
//    double sumInputGainR = 0.0;
//
//    double sumOutputGainL = 0.0;
//    double sumOutputGainR = 0.0;
//
//    int numSamples = buffer.getNumSamples();
//
//    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
//    {
//
//        for (int sampleIndex = 0; sampleIndex < numSamples; sampleIndex++)
//        {
//            /** The current amplitude value [-1.f to 1.f] */
//            auto sample = buffer.getSample(channel, sampleIndex);
//            auto thresholdValue = juce::Decibels::decibelsToGain(thresholdDb);
//
//            // Apply input gain
//            sample = inputGain.processSample(sample);
//
//            if (channel == 0) sumInputGainL += sample * sample;  // For use with input meter. 
//            else if (channel == 1) sumInputGainR = sample * sample;
//
//            amplitudeToCompress = abs(sample) - thresholdValue;
//
//            // Compress
//            if (sample > thresholdValue)
//            {
//                sample = thresholdValue + compressorGain.processSample(amplitudeToCompress);
//            }
//            else if (sample < -thresholdValue)
//            {
//                sample = -thresholdValue - compressorGain.processSample(amplitudeToCompress);
//            }
//
//            // Apply output gain
//            sample = outputGain.processSample(sample);
//
//            if (channel == 0) sumOutputGainL += sample * sample;  // For use with input meter. 
//            else if (channel == 1) sumOutputGainR += sample * sample;
//
//            // Write processed sample to buffer
//            buffer.setSample(channel, sampleIndex, sample);
//        }
//    }
//    sampleAfterInputGainL = std::sqrt(sumInputGainL / numSamples);
//    sampleAfterInputGainR = std::sqrt(sumInputGainR / numSamples);
//
//    sampleAfterOutputGainL = std::sqrt(sumOutputGainL / numSamples);
//    sampleAfterOutputGainR = std::sqrt(sumOutputGainR / numSamples);
//}
#pragma endregion Processing logic


#pragma region Host, state and GUI related logic
//========================= GUI ================================================
bool SimpleCompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SimpleCompressorAudioProcessor::createEditor()
{
    return new SimpleCompressorAudioProcessorEditor(*this);
    //return new juce::GenericAudioProcessorEditor(*this);
}

//========================= State information ==================================
void SimpleCompressorAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleCompressorAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//========================= Parameter layout ====================================
juce::AudioProcessorValueTreeState::ParameterLayout SimpleCompressorAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

    std::unique_ptr<juce::AudioParameterFloat> inputGain = std::make_unique<juce::AudioParameterFloat>("Input Gain", "Input Gain", 0.f, 24.f, 0.f);
    std::unique_ptr<juce::AudioParameterFloat> threshold = std::make_unique<juce::AudioParameterFloat>("Threshold", "Threshold", -70.f, 0.f, 0.f);
    std::unique_ptr<juce::AudioParameterFloat> ratio = std::make_unique<juce::AudioParameterFloat>("Ratio", "Ratio", 1.f, 10.f, 2.f);
    std::unique_ptr<juce::AudioParameterFloat> outputGain = std::make_unique<juce::AudioParameterFloat>("Output Gain", "Output Gain", 0.f, 36.f, 0.f);

    layout.add<juce::AudioParameterFloat>(std::move(inputGain));
    layout.add<juce::AudioParameterFloat>(std::move(threshold));
    layout.add<juce::AudioParameterFloat>(std::move(ratio));
    layout.add<juce::AudioParameterFloat>(std::move(outputGain));

    return layout;
}
#pragma endregion Host, state and GUI related logic

float SimpleCompressorAudioProcessor::getMaxValueAfterInputGain(int channelNo)
{
    jassert(channelNo >= -1 || channelNo == 1);
    if (channelNo == -1) return (maxValueAfterInputGainL > maxValueAfterInputGainR) ? maxValueAfterInputGainL : maxValueAfterInputGainR;
    if (channelNo == 0)
    {
        auto max = maxValueAfterInputGainL;
        maxValueAfterInputGainL = 0;
        return max;
    }
    else
    {
        auto max = maxValueAfterInputGainR;
        maxValueAfterInputGainR = 0;
        return max;
    }
}

float SimpleCompressorAudioProcessor::getMaxValueAfterOutputGain(int channelNo)
{
    jassert(channelNo == 0 || channelNo == 1);
    if (channelNo == 0)
    {
        auto max = maxValueAfterOutputGainL;
        maxValueAfterOutputGainL = 0;
        return max;
    }
    else
    {
        auto max = maxValueAfterOutputGainR;
        maxValueAfterOutputGainR = 0;
        return max;
    }
}

float SimpleCompressorAudioProcessor::getPostGainInputValue(int channelNo)
 {
    jassert(channelNo == 0 || channelNo == 1);
    switch (channelNo)
    {
    case 0:
        return sampleAfterInputGainL;
    case 1:
        return sampleAfterInputGainR;
    }
}

float SimpleCompressorAudioProcessor::getPostGainOutputValue(int channelNo)
{
    jassert(channelNo == 0 || channelNo == 1);
    switch (channelNo)
    {
    case 0:
        return sampleAfterOutputGainL;
    case 1:
        return sampleAfterOutputGainR;
    }
}


void SimpleCompressorAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "Input Gain") inputGain.setGainDecibels(newValue);
    if (parameterID == "Threshold") thresholdDb = newValue;
    if (parameterID == "Ratio") compressorGain.setGainLinear(1/ newValue);
    if (parameterID == "Output Gain") outputGain.setGainDecibels(newValue);
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleCompressorAudioProcessor();
}
