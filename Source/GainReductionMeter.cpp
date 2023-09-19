#include "GainReductionMeter.h"

GainReductionMeter::GainReductionMeter(std::function<float()>&& valueFunction)
	: valueSuplier(std::move(valueFunction)), lastMaxValue(0)
{
	startTimerHz(60);
}

void GainReductionMeter::paint(Graphics& g)
{
	auto maxValue = valueSuplier();
	//maxValue = Decibels::gainToDecibels(maxValue);

	/** Smoothing the level drop */
	if (maxValue < lastMaxValue) maxValue = lastMaxValue * 0.92;

	auto bounds = getLocalBounds().toFloat();

	g.setColour(Colours::black.brighter(0.1f));
	g.fillRect(bounds);

	g.setColour(Colours::darkgrey);
	const auto scaledY = jmap(maxValue, 0.f, 1.f, 0.f, static_cast<float>(getHeight()));

	g.fillRoundedRectangle(bounds.removeFromTop(scaledY), 5);

	drawGrill(g);

	lastMaxValue = maxValue;
}

void GainReductionMeter::drawGrill(Graphics& g)
{
	auto localBounds = getLocalBounds();
	g.setColour(Colours::black);
	g.drawRoundedRectangle(localBounds.toFloat(), 5, 2);

	auto x = localBounds.getX();
	auto y = localBounds.getY();
	auto width = localBounds.getWidth();
	auto height = localBounds.getHeight();

	auto holeHeight = height / 24.f;
	for (int numberOfHoles = 0; numberOfHoles < 24; numberOfHoles++)
	{
		g.drawRoundedRectangle(x, y + numberOfHoles * holeHeight, width, holeHeight, 5, 2);
	}
}

void GainReductionMeter::timerCallback()
{
	repaint();
}
