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

	/** Indicates that the channel has passed the max level (0dB FS) */
	bool hasPeaked;

	TextButton peakIndicator;

	/** Resets the peaked flag */
	void resetPeaked();


	// Inherited via Timer
	void timerCallback() override;
};
