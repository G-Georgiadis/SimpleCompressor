#pragma once


#include "JuceHeader.h"
#include "PluginProcessor.h"

using namespace juce;


class LevelMeter : public Component, Timer
{
public:
	LevelMeter(std::function<float()>&& valueFunction);
	~LevelMeter();

	void paint(Graphics& g) override;
	void resized() override;
private:
	std::function<float()> valueSuplier;
	Rectangle<int> repaintBounds;
	ColourGradient gradient{};

	void drawGrill(Graphics& g);

	float lastMaxValue;
	// Inherited via Timer
	void timerCallback() override;
};
