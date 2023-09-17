#pragma once
#include "JuceHeader.h"

using namespace juce;

class ResponseDisplay : public Component, private AudioProcessorValueTreeState::Listener
{
public:
	ResponseDisplay(AudioProcessorValueTreeState& apvts);

	void paint(Graphics& g) override;
	void resized() override;
private:
	float threshold, ratio;

	// Inherited via Listener
	void parameterChanged(const String& parameterID, float newValue) override;
};