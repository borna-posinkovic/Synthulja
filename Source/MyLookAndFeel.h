/*
  ==============================================================================

    MyLookAndFeel.h
    Created: 27 Feb 2019 8:46:27pm
    Author:  Borna

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class MyLookAndFeel : public LookAndFeel_V4 {

public:
	MyLookAndFeel() {

		setColour(Slider::thumbColourId, Colours::darkturquoise);
		setColour(Slider::backgroundColourId, Colours::darkgrey);
		setColour(Slider::trackColourId, Colours::darkslategrey);

		setColour(ComboBox::backgroundColourId, Colours::darkgrey);
		setColour(ComboBox::outlineColourId, Colours::darkseagreen);

	}

	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		auto radius = jmin(width / 2, height / 2) - 4.0f;
		auto centreX = x + width * 0.5f;
		auto centreY = y + height * 0.5f;
		auto rx = centreX - radius;
		auto ry = centreY - radius;
		auto rw = radius * 2.0f;
		auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

		// fill
		g.setColour(Colours::darkgrey);
		g.fillEllipse(rx, ry, rw, rw);
		// outline
		g.setColour(Colours::darkseagreen);
		g.drawEllipse(rx, ry, rw, rw, 2.0f);

		Path p;
		auto pointerLength = radius * 0.7f;
		auto pointerThickness = 3.0f;
		//p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
		p.addRoundedRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength, 1.0f);
		p.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));

		// pointer
		g.setColour(Colours::darkturquoise);
		g.fillPath(p);
	}

private:

};