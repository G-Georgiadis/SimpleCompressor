#include "ResponseDisplay.h"


ResponseDisplay::ResponseDisplay(AudioProcessorValueTreeState& apvts)
	: threshold(apvts.getParameterAsValue("Threshold").getValue()),
	ratio(apvts.getParameterAsValue("Ratio").getValue())
{
	apvts.addParameterListener("Threshold", this);
	apvts.addParameterListener("Ratio", this);
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
