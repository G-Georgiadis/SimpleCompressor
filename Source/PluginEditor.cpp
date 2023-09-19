/*****************************************************************//**
 * \file   PluginEditor.cpp
 * \brief  Implementation file for the GUI of the Simple Compressor plugin processor.
 * 
 * \author George Georgiadis
 * \date   September 2023
 *********************************************************************/

#include "PluginProcessor.h"
#include "PluginEditor.h"


#pragma region Constructor & Deconstructor
SimpleCompressorAudioProcessorEditor::SimpleCompressorAudioProcessorEditor(SimpleCompressorAudioProcessor& p)
    : AudioProcessorEditor(&p),
    audioProcessor(p),
    inputGain_Attachment(p.apvts, "InputGain", inputGain_Knob),
    threshold_Attachment(p.apvts, "Threshold", threshold_Knob),
    ratio_Attachment(p.apvts, "Ratio", ratio_Knob),
    outputGain_Attachment(p.apvts, "OutputGain", outputGain_Knob),
    input_LevelMeterL([&]() { return audioProcessor.getMaxValueAfterInputGain(0); },
        [&]() { return audioProcessor.resetPostInputGainMaxValue(0); }),
    input_LevelMeterR([&]() { return audioProcessor.getMaxValueAfterInputGain(1); },
        [&]() { return audioProcessor.resetPostInputGainMaxValue(1); }),
    responseDisplay(p.apvts, [&]() { return audioProcessor.getMaxValueAfterInputGain(-1); }),
    gainReductionMeterL([&]() { return audioProcessor.getGainReduction(0); }),
    gainReductionMeterR([&]() { return audioProcessor.getGainReduction(1); }),
    output_LevelMeterL([&]() { return audioProcessor.getMaxValueAfterOutputGain(0); },
        [&]() { return audioProcessor.resetPostOutputGainMaxValue(0); }),
    output_LevelMeterR([&]() { return audioProcessor.getMaxValueAfterOutputGain(1); },
        [&]() { return audioProcessor.resetPostOutputGainMaxValue(1); })

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    addAndMakeVisible(input_LevelMeterL);
    addAndMakeVisible(input_LevelMeterR);

    addAndMakeVisible(responseDisplay);

    addAndMakeVisible(gainReductionMeterL);
    addAndMakeVisible(gainReductionMeterR);

    addAndMakeVisible(output_LevelMeterL);
    addAndMakeVisible(output_LevelMeterR);

    addAndMakeVisible(inputGain_Knob);
    inputGain_Knob.setTextValueSuffix(" dB");

    addAndMakeVisible(threshold_Knob);
    threshold_Knob.setTextValueSuffix(" dB");

    addAndMakeVisible(ratio_Knob);
    ratio_Knob.setNumDecimalPlacesToDisplay(0);
    ratio_Knob.setTextValueSuffix(":1");
    
    addAndMakeVisible(outputGain_Knob);
    outputGain_Knob.setTextValueSuffix(" dB");

    this->setResizable(false, false);
    this->setBufferedToImage(true);
}

SimpleCompressorAudioProcessorEditor::~SimpleCompressorAudioProcessorEditor()
{
}
#pragma endregion Constructor & Deconstructor


void SimpleCompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkkhaki.darker(0.91));
}

void SimpleCompressorAudioProcessorEditor::resized()
{
    auto localBounds = getLocalBounds();

    auto topPart = localBounds.removeFromTop(200);
    topPart.reduce(0, 20);  // Margin

    topPart.removeFromLeft(20); // Margin
    auto inputMeterBounds = topPart.removeFromLeft(70);
    topPart.removeFromLeft(20); // Margin
    auto responseCurveBounds = topPart.removeFromLeft(180);
    topPart.removeFromLeft(20); // Margin
    auto outputMeterBounds = topPart.removeFromLeft(70);


    input_LevelMeterL.setBounds(inputMeterBounds.removeFromLeft(inputMeterBounds.getWidth() / 2));
    input_LevelMeterR.setBounds(inputMeterBounds);

    responseDisplay.setBounds(responseCurveBounds.removeFromLeft(responseCurveBounds.getWidth() - 30));
    responseCurveBounds.removeFromLeft(5); 
    gainReductionMeterL.setBounds(responseCurveBounds.removeFromLeft(10));
    responseCurveBounds.removeFromLeft(5);
    gainReductionMeterR.setBounds(responseCurveBounds.removeFromLeft(10));

    output_LevelMeterL.setBounds(outputMeterBounds.removeFromLeft(outputMeterBounds.getWidth() / 2));
    output_LevelMeterR.setBounds(outputMeterBounds);


    localBounds.removeFromLeft(20); // Margin
    auto inputGainBounds = localBounds.removeFromLeft(70);
    localBounds.removeFromLeft(20); // Margin
    auto thresholdBounds = localBounds.removeFromLeft(80);
    localBounds.removeFromLeft(20); // Margin
    auto ratioBounds = localBounds.removeFromLeft(80);
    localBounds.removeFromLeft(20); // Margin
    auto outputGainBounds = localBounds.removeFromLeft(70);

    

    inputGain_Knob.setBounds(inputGainBounds);
    threshold_Knob.setBounds(thresholdBounds);
    ratio_Knob.setBounds(ratioBounds);
    outputGain_Knob.setBounds(outputGainBounds);

}
