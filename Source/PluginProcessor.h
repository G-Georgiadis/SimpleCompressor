/*****************************************************************//**
 * \file   PluginProcessor.h
 * \brief  Header file for the Simple Compressor plugin processor.
 * 
 * \author George Georgiadis
 * \date   September 2023
 *********************************************************************/

#pragma once

#include <JuceHeader.h>


/**
 * Processes audio.
 */
class SimpleCompressorAudioProcessor  : public juce::AudioProcessor, juce::AudioProcessorValueTreeState::Listener
{
public:
    /**
     * Constructor and deconstructor.
     * Nothing special here.
     */

    /** SimpleCompressorAudioProcessor Constructor */
    SimpleCompressorAudioProcessor();
    /** SimpleCompressorAudioProcessor Deconstructor */
    ~SimpleCompressorAudioProcessor() override;

    /** A good place to initialize anything that wasn't available during construction. */
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    /** Called after playback has stopped, to let the object free up any resources it no longer needs. */
    void releaseResources() override;
    /** Renders the next block of audio */
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    /** Creates the GUI */
    juce::AudioProcessorEditor* createEditor() override;
    /** Returns true since there is a GUI */
    bool hasEditor() const override;

    /** Returns the name of this plugin. */
    const juce::String getName() const override;

    /** Returns false since we don't need MIDI for the compressor. */
    bool acceptsMidi() const override;
    /** Returns false since the compressor doesn't produce MIDI. */
    bool producesMidi() const override;
    /** Returns false since the compressor does not process MIDI. */
    bool isMidiEffect() const override;
    /** Returns 0. */
    double getTailLengthSeconds() const override;

    /** Returns 1 for compatibility. Consider adding presets later. */
    int getNumPrograms() override;
    /** Returns 0. This may change if presets are implemented. */
    int getCurrentProgram() override;
    /** Sets the current program number. To be used if presets are implemented. */
    void setCurrentProgram (int index) override;
    /** Returns the name of the current program. */
    const juce::String getProgramName (int index) override;
    /** Sets the name for this preset. */
    void changeProgramName (int index, const juce::String& newName) override;

    /**
     * The host will call this method when it wants to save the processor's internal state.
     * To be used for saving presets.
     * 
     * Consider implementing getCurrentProgramStateInformation() which only stores the current program if presets will not be implemented.
     * 
     * \param destData The block provided by the host so that it can save the current state.
     */
    void getStateInformation (juce::MemoryBlock& destData) override;
    /** This must restore the processor's state from a block of data previously created using getStateInformation(). */
    void setStateInformation (const void* data, int sizeInBytes) override;

    /** Generates the parameter layout for the compressor */
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    /** The value tree state of the compressor. Holds parameters and interfaces between GUI controls and processor logic */
    juce::AudioProcessorValueTreeState apvts{ *this, &undoManager, "Simple Compressor Parameters", createParameterLayout() };

    float maxValueAfterInputGainL;
    float maxValueAfterInputGainR;

    float maxValueAfterOutputGainL;
    float maxValueAfterOutputGainR;

    /** The signal value post input gain (L) */
    float sampleAfterInputGainL;
    /** The signal value post input gain (R) */
    float sampleAfterInputGainR;

    /** The signal value post input gain (L) */
    float sampleAfterOutputGainL;
    /** The signal value post input gain (R) */
    float sampleAfterOutputGainR;

    /** The amplitude above the threshold. (= signal amplitude - threshold). Only updated if the signal amplitude is above the threshold. */
    float amplitudeToCompress;

    float getMaxValueAfterInputGain(int channelNo);
    float getMaxValueAfterOutputGain(int channelNo);

    /** Fetches the amplitude of the signal post input gain. Used for the level meter */
    float getPostGainInputValue(int channelNo);

    /** Fetches the amplitude of the signal post input gain. Used for the level meter */
    float getPostGainOutputValue(int channelNo);
    
private:
    /** Manages undo states. Currently created but not implemented. */
    juce::UndoManager undoManager;

    /** The "Input Gain" parameter controlled by the Input Gain knob. */
    float inputGainDecibels;
    /** The "Threshold" parameter conttrolled by the Threshold knob. */
    float thresholdDb;
    /** The "Ratio" paremeter controlled by the Ratio knob. */
    float ratio;
    /** The "Output Gain" parameter controlled by the Output Gain knob. */
    float outputGainDecibels;


    /** The Input Gain. Amplifies the signal before compression. */
    juce::dsp::Gain<float> inputGain;
    /** The part of the signal above the threshold which needs to be attenuated by the ratio amount. */
    juce::dsp::Gain<float> compressorGain;
    /** The Output Gain. Amplifies the signal after compression. */
    juce::dsp::Gain<float> outputGain;


    // Inherited via Listener
    /** Called when a parameter is tweaked on the GUI. Sets the parameter values used for remdering the output. */
    void parameterChanged(const juce::String& parameterID, float newValue) override;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleCompressorAudioProcessor)        
};
