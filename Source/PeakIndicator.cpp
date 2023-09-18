#include "PeakIndicator.h"

PeakIndicator::PeakIndicator(std::function<void()>&& resetMaxFunction)
	: Button("PeakIndicator"),
	resetMaxValue(std::move(resetMaxFunction)),
	hasPeaked(false)
{
}

void PeakIndicator::set()
{
	hasPeaked = true;
}

void PeakIndicator::clicked()
{
	hasPeaked = false;
	resetMaxValue();
}

void PeakIndicator::paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	g.fillAll(Colours::black);
	g.setColour((hasPeaked) ? Colours::red : Colours::darkred.darker(0.9));
	g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 5);
}
