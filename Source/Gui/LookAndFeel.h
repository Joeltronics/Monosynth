/*
  ==============================================================================

    LookAndFeel.h
    Created: 25 Aug 2015 8:13:38am
    Author:  Joel Geddert

  ==============================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

		void drawRotarySlider(
			juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &)
			override;
	};

} // namespace Gui

#endif  // LOOKANDFEEL_H_INCLUDED
