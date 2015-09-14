/*
  ==============================================================================

    LookAndFeel.h
    Created: 25 Aug 2015 8:13:38am
    Author:  Joel

  ==============================================================================
*/

#ifndef LOOKANDFEEL_H_INCLUDED
#define LOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

namespace Gui {

	class DefaultLookAndFeel : public LookAndFeel_V3 {

	public:

		DefaultLookAndFeel() {}
		~DefaultLookAndFeel() {}

		void drawRotarySlider(Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &) override;

		void drawLinearSlider(Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, Slider::SliderStyle const, Slider& sl) override;

		Typeface::Ptr getTypefaceForFont(const Font &) override;
	};

	class TuningKnobLookAndFeel : public DefaultLookAndFeel {
	public:
		TuningKnobLookAndFeel() {}
		~TuningKnobLookAndFeel() {}

		void drawRotarySlider(Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &) override;
	};

	class FreqKnobLookAndFeel : public DefaultLookAndFeel {
	public:
		FreqKnobLookAndFeel() {}
		~FreqKnobLookAndFeel() {}
	};

} // namespace Gui

#endif  // LOOKANDFEEL_H_INCLUDED
