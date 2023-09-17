/*****************************************************************//**
 * \file   PluginEditor.h
 * \brief  Header file for the GUI of the Simple Compressor plugin processor.
 * 
 * \author George Georgiadis
 * \date   September 2023
 *********************************************************************/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "RotaryKnob_GearShaped_LookAndFeel.h"
#include "RotaryKnob_GearShaped.h"
#include "LevelMeter.h"
#include "ResponseDisplay.h"

/**
 * Controls the GUI.
 */
class SimpleCompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    /** Constructor */
    SimpleCompressorAudioProcessorEditor (SimpleCompressorAudioProcessor&);
    /** Deconstructor */
    ~SimpleCompressorAudioProcessorEditor() override;

    /** Draws the GUI */
    void paint (juce::Graphics&) override;
    /** Called each time the plugin window is resized. */
    void resized() override;

private:
    /**
     * This reference is provided as a quick way for your editor
     * to access the processor object that created it.
     */
    SimpleCompressorAudioProcessor& audioProcessor;
    /** The knob that sets the input gain */
    RotaryKnob_GearShaped inputGain_Knob;
    /** The knob that controls the threshold. */
    RotaryKnob_GearShaped threshold_Knob;
    /** The knob that controls the ratio. */
    RotaryKnob_GearShaped ratio_Knob;
    /** The knob that controls the output gain. */
    RotaryKnob_GearShaped outputGain_Knob;

    /** The post input gain level meter (L) */
    LevelMeter input_LevelMeterL;
    /** The post input gain level meter (R) */
    LevelMeter input_LevelMeterR;

    ResponseDisplay responseDisplay;

    /** The post output gain level meter (L) */
    LevelMeter output_LevelMeterL;
    /** The post output gain level meter (R) */
    LevelMeter output_LevelMeterR;

    /** Attaches the input gain knob to the input gain parameter in the audio processor value tree state. */
    juce::AudioProcessorValueTreeState::SliderAttachment inputGain_Attachment;
    /** Attaches the threshold knob to the threshold parameter in the audio processor value tree state. */
    juce::AudioProcessorValueTreeState::SliderAttachment threshold_Attachment;
    /** Attaches the ratio to the ratio parameter in the audio processor value tree state. */
    juce::AudioProcessorValueTreeState::SliderAttachment ratio_Attachment;
    /** Attaches the output gain to the output gain parameter in the audio processor value tree state. */
    juce::AudioProcessorValueTreeState::SliderAttachment outputGain_Attachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleCompressorAudioProcessorEditor)
};
