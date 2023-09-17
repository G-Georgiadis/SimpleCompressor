#include "ResponseDisplay.h"


ResponseDisplay::ResponseDisplay(AudioProcessorValueTreeState& apvts, std::function<float()>&& valueFunction)
	: threshold(apvts.getParameterAsValue("Threshold").getValue()),
	ratio(apvts.getParameterAsValue("Ratio").getValue()),
	valueSuplier(std::move(valueFunction)),
	lastMaxValue(0)
{
	apvts.addParameterListener("Threshold", this);
	apvts.addParameterListener("Ratio", this);

	startTimerHz(60);
}

void ResponseDisplay::paint(Graphics& g)
{
	g.setColour(Colours::darkgrey.darker(0.99f));
	g.fillRoundedRectangle(getLocalBounds().toFloat(), 3);

	auto localBounds = getLocalBounds();

	auto x = localBounds.getX();
	auto y = localBounds.getY();
	auto width = localBounds.getWidth();
	auto height = localBounds.getHeight();

	/** Draw threshold (horizontal) line */
	auto thresholdY = jmap(threshold, -70.f, 0.f, static_cast<float>(height), static_cast<float>(y));
	auto thresholdX = jmap(threshold, -70.f, 0.f, static_cast<float>(x), static_cast<float>(width));
	g.setColour(Colours::grey);
	g.drawLine(x, thresholdY, width, thresholdY);

	g.setColour(Colours::darkorange);
	
	Point<float> bottomLeft(x, height);
	Point<float> thresholdXY(thresholdX, thresholdY);
	Point<float> compressedTopRight(width, thresholdY - (thresholdY / ratio));

	Line<float> part1(bottomLeft, thresholdXY);
	Line<float> part2(thresholdXY, compressedTopRight);

	g.drawLine(part1);
	g.drawLine(part2);

	auto maxValue = valueSuplier();

	/** Smoothing the level drop */
	if (maxValue < lastMaxValue) maxValue = lastMaxValue * 0.85;

	auto maxValueScalled = jmap(maxValue, 0.f, 1.f, static_cast<float>(height), static_cast<float>(y));
	g.setColour(Colours::whitesmoke);
	g.drawLine(x, maxValueScalled, width, maxValueScalled);

	lastMaxValue = maxValue;
}

void ResponseDisplay::resized()
{

}

void ResponseDisplay::parameterChanged(const String& parameterID, float newValue)
{
	if (parameterID == "Threshold") threshold = newValue;
	if (parameterID == "Ratio") ratio = newValue;

	const MessageManagerLock mmLock;	
	this->repaint();
}

void ResponseDisplay::timerCallback()
{
	this->repaint();
}
