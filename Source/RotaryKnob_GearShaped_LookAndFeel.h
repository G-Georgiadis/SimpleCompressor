#pragma once


#include "JuceHeader.h"
#include "Shapes.h"


using namespace juce;

class RotaryKnob_GearShaped_LookAndFeel : public LookAndFeel_V4
{
public:
	/**
	 * Defines the bounds for the slider and the text box.
	 * 
	 * \param slider A slider. Used to access it's bounds and derive the slider and text box areas.
	 * \return A Slider::SliderLayout
	 */
	Slider::SliderLayout getSliderLayout(Slider& slider) override
	{
		Slider::SliderLayout layout;

		Rectangle<int> localBounds = slider.getLocalBounds();
		layout.sliderBounds = localBounds.removeFromTop(localBounds.getHeight() * 0.75f);
		//localBounds.removeFromBottom(localBounds.getHeight() * 0.6f);	// Space between slider and textbox
		layout.textBoxBounds = localBounds.removeFromBottom(localBounds.getHeight() * 0.6f);

		return layout;
	}


	/**
	 * Draws the rotary slider.
	 */
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height,
		float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
	{
		constexpr int numberOfSides = 8;
		constexpr float numberOfRadiansPerSide = 2 * MathConstants<float>::pi / numberOfSides;

		/** Using the smallest dimension as the totalDiameter to ensure that the knob fits the bounds. */
		int totalDiameter = (width < height) ? width : height;
		float totalRadius = totalDiameter / 2.f;
		float totalCenterX = x + width / 2.f;
		float totalCenterY = y + height / 2.f;

		float angle = rotaryStartAngle + (sliderPosProportional * (rotaryEndAngle - rotaryStartAngle));

		/** Knob outer circle. The outer gear shape edges should touch this circle. */
		float knobGearOuterDiameter = 0.9f * totalDiameter;
		float knobGearOuterRadius = knobGearOuterDiameter / 2.f;

		/** Knob inner circle. The inner gear shape edges should touch this circle. */
		float knobGearInnerDiameter = 0.75 * totalDiameter;


		/**
		 * Min-Max lines.
		 */
		Path minMaxLines;
		minMaxLines.addArc(totalCenterX - totalRadius, totalCenterY - totalRadius,
			totalDiameter, totalDiameter,
			rotaryStartAngle, rotaryEndAngle, true);

		PathStrokeType strokeType = PathStrokeType::PathStrokeType(1.f);
		g.setColour(Colours::beige);
		g.strokePath(minMaxLines, strokeType);

		/** Minimum line */
		Line<float> minLine = Line<float>(totalCenterX, totalCenterY - totalRadius, totalCenterX, totalCenterY - totalRadius + totalRadius / 6.f);
		minLine.applyTransform(AffineTransform::rotation(rotaryStartAngle, totalCenterX, totalCenterY));
		g.drawLine(minLine, 1.f);

		/** Minimum line */
		Line<float> maxLine = Line<float>(totalCenterX, totalCenterY - totalRadius, totalCenterX, totalCenterY - totalRadius + totalRadius / 6.f);
		maxLine.applyTransform(AffineTransform::rotation(rotaryEndAngle, totalCenterX, totalCenterY));
		g.drawLine(maxLine, 1.f);

		/** Min label */
		g.drawFittedText("Min", totalCenterX - totalRadius, totalCenterY + totalRadius,
			totalRadius / 2.f, totalRadius / 6.f, Justification::centred, 1);
		/** Max label */
		g.drawFittedText("Max", totalCenterX + totalRadius / 2.f, totalCenterY + totalRadius,
			totalRadius / 2.f, totalRadius / 6.f, Justification::centred, 1);


		/****************************************************************************
		 * Disk at the bottom of the knob.
		 */
		 /** Base colour */
		g.setColour(Colours::black.brighter(0.03));
		g.fillEllipse
		(
			totalCenterX - knobGearOuterRadius,
			totalCenterY - knobGearOuterRadius,
			knobGearOuterDiameter,
			knobGearOuterDiameter
		);
		/** Light reflection. */
		ColourGradient backDiskGradient = ColourGradient(
			Colours::white.withAlpha(0.15f), totalCenterX + knobGearOuterRadius / 2.f, totalCenterY - knobGearOuterRadius,
			Colours::black.withAlpha(0.1f), totalCenterX - knobGearOuterRadius / 2.f, totalCenterY + knobGearOuterRadius,
			true);
		g.setGradientFill(backDiskGradient);
		g.fillEllipse
		(
			totalCenterX - knobGearOuterRadius,
			totalCenterY - knobGearOuterRadius,
			knobGearOuterDiameter,
			knobGearOuterDiameter
		);


		/****************************************************************************
		 * Pointer.
		 */
		Path knobPointerPath;
		knobPointerPath.startNewSubPath(totalCenterX, totalCenterY - totalRadius + (totalDiameter - knobGearOuterDiameter - 10.f) / 2.f);
		knobPointerPath.lineTo(totalCenterX + 0.2f * (knobGearOuterDiameter - knobGearInnerDiameter) / 2, totalCenterY - totalRadius + (knobGearOuterDiameter - knobGearInnerDiameter));
		knobPointerPath.lineTo(totalCenterX - 0.2f * (knobGearOuterDiameter - knobGearInnerDiameter) / 2, totalCenterY - totalRadius + (knobGearOuterDiameter - knobGearInnerDiameter));
		knobPointerPath.closeSubPath();
		knobPointerPath = knobPointerPath.createPathWithRoundedCorners(5.f);

		knobPointerPath.applyTransform(AffineTransform::rotation(
			angle,
			totalCenterX,
			totalCenterY)
		);

		g.setColour(Colours::beige.darker(0.8));
		g.fillPath(knobPointerPath);


		/****************************************************************************
		 * Gear shaped knob.
		 */
		Path gearShapedKnobPath = Shapes::getGearShapedPath(numberOfSides, totalDiameter, totalCenterX, totalCenterY, knobGearInnerDiameter);
		
		/** Rotate the knob depending on value (angle) */
		gearShapedKnobPath.applyTransform(AffineTransform::rotation(
			angle,
			totalCenterX,
			totalCenterY));
		
		DropShadow gearShadow = DropShadow(juce::Colours::black.withAlpha(0.5f), 20, juce::Point(-20, 20));
		gearShadow.drawForPath(g, gearShapedKnobPath);
		
		/** Knob base colour */
		g.setColour(Colours::black.brighter(0.05));
		g.fillPath(gearShapedKnobPath);

		/** Gradient for light reflection effect. */
		ColourGradient gearTopGradient = ColourGradient(
			Colours::white.withAlpha(0.15f), totalCenterX + knobGearOuterRadius / 2.f, totalCenterY - knobGearOuterRadius,
			Colours::black.withAlpha(0.1f), totalCenterX - knobGearOuterRadius / 2.f, totalCenterY + knobGearOuterRadius,
			true);
		g.setGradientFill(gearTopGradient);
		g.fillPath(gearShapedKnobPath);

	}

	/** Draws the text box of the rotary knob. */
	Label* createSliderTextBox(Slider& slider) override
	{
		juce::Label* sliderTextBoxPtr = LookAndFeel_V4::createSliderTextBox(slider);

		sliderTextBoxPtr->setColour(juce::Label::textColourId, juce::Colours::beige);
		sliderTextBoxPtr->setColour(juce::Label::backgroundColourId, juce::Colours::transparentBlack);
		sliderTextBoxPtr->setColour(juce::Label::outlineColourId, juce::Colours::transparentBlack);
		sliderTextBoxPtr->setColour(juce::Label::textWhenEditingColourId, juce::Colours::beige);
		sliderTextBoxPtr->setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::black);
		sliderTextBoxPtr->setColour(juce::Label::outlineWhenEditingColourId, juce::Colours::beige);

		// ToDo: Fix text box justification when editing the value

		return sliderTextBoxPtr;
	}

	
private:
	static constexpr int numberOfDecimalPlaces = 2;
};
