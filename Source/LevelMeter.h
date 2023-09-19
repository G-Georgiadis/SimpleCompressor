#pragma once


#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PeakIndicator.h"

using namespace juce;


class LevelMeter : public Component, Timer
{
public:
	LevelMeter(std::function<float()>&& valueFunction, std::function<void()>&& resetMaxFunction);
	~LevelMeter();

	void paint(Graphics& g) override;
	void resized() override;
private:
	std::function<float()> valueSuplier;
	ColourGradient gradient{};

	void drawGrill(Graphics& g);

	float lastMaxValue;

	PeakIndicator peakIndicator;

	// Inherited via Timer
	void timerCallback() override;
};
