#pragma once
#include "JuceHeader.h"

using namespace juce;

class ResponseDisplay : public Component, private AudioProcessorValueTreeState::Listener, Timer
{
public:

	void paint(Graphics& g) override;
	void resized() override;
private:
	float threshold, ratio;

	// Inherited via Listener
	void parameterChanged(const String& parameterID, float newValue) override;
	
	std::function<float()> valueSuplier;
	float lastMaxValue;
	// Inherited via Timer
	void timerCallback() override;
};