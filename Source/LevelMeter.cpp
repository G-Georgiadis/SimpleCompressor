#include "LevelMeter.h"

LevelMeter::LevelMeter(std::function<float()>&& valueFunction) 
	: valueSuplier(std::move(valueFunction)),
	gradient(), lastMaxValue(0)
{
	startTimer(60);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint(Graphics& g)
{
	auto maxValue = valueSuplier();

	if (maxValue < lastMaxValue) maxValue = lastMaxValue * 0.85;

	auto bounds = getLocalBounds().reduced(10, 0).toFloat();

	g.setColour(Colours::black);
	g.fillRect(bounds);

	g.setGradientFill(gradient);
	const auto scaledY = jmap(maxValue, 0.f, 1.f, 0.f, static_cast<float>(getHeight()));
	
	g.fillRoundedRectangle(bounds.removeFromBottom(scaledY), 5);

	lastMaxValue = maxValue;

	drawGrill(g);
}

void LevelMeter::resized()
{
	const auto bounds = getLocalBounds().toFloat();

	gradient = ColourGradient
	{
		Colours::green,
		bounds.getBottomLeft(),
		Colours::red,
		bounds.getTopLeft(),
		false
	};
	gradient.addColour(0.5, Colours::yellow);
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
