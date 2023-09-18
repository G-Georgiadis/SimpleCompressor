#pragma once


#include "JuceHeader.h"
#include "RotaryKnob_GearShaped_LookAndFeel.h"


using namespace juce;


class RotaryKnob_GearShaped : public Slider
{
public:
	RotaryKnob_GearShaped();
	~RotaryKnob_GearShaped();
private:
	RotaryKnob_GearShaped_LookAndFeel rotaryKnob_GearShaped_LookAndFeel;	
};
