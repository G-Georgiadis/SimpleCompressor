#include "LevelMeter.h"

LevelMeter::LevelMeter(std::function<float()>&& valueFunction, std::function<void()>&& resetMaxFunction)
	: valueSuplier(std::move(valueFunction)),
	gradient(), lastMaxValue(0),
	peakIndicator(std::move(resetMaxFunction))
{
	addAndMakeVisible(peakIndicator);

	startTimerHz(60);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint(Graphics& g)
{
	auto maxValue = valueSuplier();

	/** Check if the signal has clipped and if so, set the indicator */
	if (maxValue >= 1.f)
	{
		peakIndicator.set();
	}

	/** Smoothing the level drop */
	if (maxValue < lastMaxValue) maxValue = lastMaxValue * 0.85;

	auto bounds = getLocalBounds().reduced(10, 0).toFloat();

	g.setColour(Colours::black.brighter(0.1f));
	g.fillRect(bounds);

	g.setGradientFill(gradient);
	const auto scaledY = jmap(maxValue, 0.f, 1.f, 0.f, static_cast<float>(getHeight()));
	
	g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5);

	drawGrill(g);

	lastMaxValue = maxValue;
}

void LevelMeter::resized()
{
	const auto bounds = getLocalBounds().reduced(10, 0).toFloat();

	gradient = ColourGradient
	{
		Colours::green,
		bounds.getBottomLeft(),
		Colours::red,
		bounds.getTopLeft(),
		false
	};
	gradient.addColour(0.5, Colours::yellow);

	peakIndicator.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), (bounds.getHeight() / 24.f) +2.f);
}

void LevelMeter::drawGrill(Graphics& g)
{
	
	auto localBounds = getLocalBounds().reduced(10, 0);
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

void LevelMeter::timerCallback()
{
	this->repaint();
}
