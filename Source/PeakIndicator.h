#pragma once

#include "JuceHeader.h"

using namespace juce;


class PeakIndicator : public Button
{
public:
	PeakIndicator(std::function<void()>&& resetMaxFunction);

	void set();
	void clicked();
private:
	std::function<void()> resetMaxValue;

	/** Indicates that the channel has passed the max level (0dB FS) */
	bool hasPeaked;	

	// Inherited via Button
	void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};
