#pragma once


#include "JuceHeader.h"
#include "RotaryKnob_GearShaped.h"


RotaryKnob_GearShaped::RotaryKnob_GearShaped()
{
	this->setLookAndFeel(&rotaryKnob_GearShaped_LookAndFeel);

	this->setSliderStyle(Slider::RotaryVerticalDrag);

	this->setNumDecimalPlacesToDisplay(2);
}

RotaryKnob_GearShaped::~RotaryKnob_GearShaped()
{
	this->setLookAndFeel(nullptr);
}
