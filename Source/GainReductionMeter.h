#pragma once


#include <JuceHeader.h>


using namespace juce;


class GainReductionMeter : public Component, Timer
{
public:
	GainReductionMeter(std::function<float()>&& valueFunction);

	void paint(Graphics& g) override;
private:
	std::function<float()> valueSuplier;
	float lastMaxValue;

	void drawGrill(Graphics& g);

	// Inherited via Timer
	void timerCallback() override;
};