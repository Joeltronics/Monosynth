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

	class DefaultLookAndFeel : public juce::LookAndFeel_V3 {

	public:

		DefaultLookAndFeel() {}
		~DefaultLookAndFeel() {}

		virtual void drawRotarySlider(
			juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &)
			override;

		virtual void drawLinearSlider(
			juce::Graphics&, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, juce::Slider::SliderStyle const, juce::Slider& sl)
			override;

		juce::Typeface::Ptr getTypefaceForFont(const juce::Font &) override;
	};

	class TuningKnobLookAndFeel : public DefaultLookAndFeel {
	public:
		TuningKnobLookAndFeel() {}
		~TuningKnobLookAndFeel() {}

		void drawRotarySlider(
			juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &)
			override;
	};

	class FreqKnobLookAndFeel : public DefaultLookAndFeel {
	public:
		FreqKnobLookAndFeel() {}
		~FreqKnobLookAndFeel() {}
	};

} // namespace Gui

#endif  // LOOKANDFEEL_H_INCLUDED
