/*
  ==============================================================================

    Shapes.h
    Created: 7 Apr 2023 7:25:12pm
    Author:  G

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

//==============================================================================
/*
Class to make and store shapes used in the GUI
*/
class Shapes  : public Component
{
public:
    //Transport bar button shapes
    static Path getOpenButtonPath();
    static Path getSkipToStartButtonPath();
    static Path getRewindButtonPath();
    static Path getStopButtonPath();
    static Path getPlayButtonPath();
    static Path getPauseButtonPath();
    static Path getFastForwardButtonPath();
    static Path getSkipToEndButtonPath();

    //Waveform shapes
    static Path getSawtoothPath(Rectangle<float>&& buttonBounds);
    static Path getPulsePath(Rectangle<float>&& buttonBounds);
    static Path getTrianglePath(Rectangle<float>&& buttonBounds);
    static Path getSinewavePath(Rectangle<float>&& buttonBounds);
    static Path getNoisePath(Rectangle<float>&& buttonBounds);

    // Slider and knob shapes
    static Path getGearShapedPath(int numberOfSides, float totalDiameter, float totalCenterX, float totalCenterY, float knobGearInnerDiameter);
private:
    static const Rectangle<int> localBounds;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Shapes)
};
