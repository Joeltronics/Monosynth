/*
  ==============================================================================

    LookAndFeel.cpp
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

#include "LookAndFeel.h"

#include "JuceHeader.h"

#include "Utils/DspUtils.h"
#include "Utils/ApproxEqual.h"

#include <cmath>
#include <vector>

using namespace juce;

namespace Gui {

	static inline int ToInt(float f) { return Utils::RoundTo<int>(f); }
	static inline int ToInt(double d) { return Utils::RoundTo<int>(d); }

	static inline float GetX_(float centerX, float radius, float angle) {
		return centerX + radius*cosf(angle);
	}

	static inline float GetY_(float centerY, float radius, float angle) {
		return centerY - radius*sinf(angle);
	}

	static inline void DrawTick_(Graphics& g, float cx, float cy, float r1, float r2, float angle, float width = 1.0f) {
		g.drawLine(GetX_(cx, r1, angle),
			GetY_(cy, r1, angle),
			GetX_(cx, r2, angle),
			GetY_(cy, r2, angle),
			width);
	}

	static inline float AngleToCartesian_(float angle) {
		return float(M_PI_2) - angle;
	}

	// r1 = start of knob indicator
	// r2 = end of knob indicator
	// r3 = edge of knob (or slightly less)
	// For some knobs, r2 = r3
	static Image GetKnobImage_(bool bBigKnobStyle, uint32_t dim, float& r1 /*out*/, float& r2 /*out*/, float& r3 /*out*/) {
		float rOuter = dim / 2.0f;
		if (bBigKnobStyle) {
			r3 = rOuter * 2.0f/3.0f;
			r2 = rOuter * 0.42f;
			r1 = r2 * 0.25f;
			return ImageCache::getFromMemory(BinaryData::bigknob88_png, BinaryData::bigknob88_pngSize);
		}
		else if (dim >= 32) {
			r3 = rOuter * 0.5f;
			r2 = r3;
			r1 = r2 * 0.25f;
			return ImageCache::getFromMemory(BinaryData::knob32_png, BinaryData::knob32_pngSize);
		}
		else {
			r3 = rOuter * 0.5f;
			r2 = r3;
			r1 = r2 * 0.25f;
			return ImageCache::getFromMemory(BinaryData::knob24_png, BinaryData::knob24_pngSize);
		}
	}

	static void DrawImageCentered_(
		Graphics& g,
		Image const& img,
		float const cx, float const cy,
		int const maxw, int const maxh)
	{
		int const imgw = img.getWidth();
		int const imgh = img.getHeight();

		float scale;
		
		if (maxw > 0 && maxh > 0)
			scale = std::min(float(maxw) / float(imgw), float(maxh) / float(imgh));
		else if(maxw > 0)
			scale = float(maxw) / float(imgw);
		else if(maxh > 0)
			scale = float(maxh) / float(imgh);
		else
			scale = 1.0f;

		int outw = ToInt(imgw * scale);
		int outh = ToInt(imgh * scale);

		int outx = ToInt(cx - float(outw) / 2.0f);
		int outy = ToInt(cy - float(outh) / 2.0f);

		g.drawImage(img, outx, outy, outw, outh, 0, 0, imgw, imgh);
	}

	// ***** Knob drawing functions *****

	static void DrawKnob_(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const sliderPosProportional,
		float rotaryStartAngle, float rotaryEndAngle,
		Slider& sl,
		Image& knobImg,
		std::vector<float> ticks, std::vector<float> miniTicks,
		float r1, float r2, float r3,
		float tickWidth)
	{
		// Angles passed in are clockwise - convert to cartesian
		rotaryStartAngle = AngleToCartesian_(rotaryStartAngle);
		rotaryEndAngle = AngleToCartesian_(rotaryEndAngle);

		// Center coords
		float cx = x + (w / 2.0f);
		float cy = y + (h / 2.0f);

		// Mouseover
		bool const bIsMouseOver = sl.isEnabled() && sl.isMouseOverOrDragging();

		// TODO: use mouseover value

		// Max Radius
		int minDim = std::min(w, h);
		float rOuter = minDim / 2.0f;
		float rMiniTick = r3 + 0.55f*(rOuter - r3);

		// Draw ticks
		g.setColour(Colours::whitesmoke);

		for (std::vector<float>::const_iterator it = miniTicks.begin(); it != miniTicks.end(); ++it) {
			float tickAngle = Utils::Interp<float>(rotaryStartAngle, rotaryEndAngle, *it);
			DrawTick_(g, cx, cy, r3, rMiniTick, tickAngle);
		}

		for (std::vector<float>::const_iterator it = ticks.begin(); it != ticks.end(); ++it) {
			float tickAngle = Utils::Interp<float>(rotaryStartAngle, rotaryEndAngle, *it);
			DrawTick_(g, cx, cy, r3, rOuter, tickAngle);
		}

		// Draw knob image
		DrawImageCentered_(g, knobImg, cx, cy, w, h);

		// Draw knob indicator
		float angle = Utils::Interp(rotaryStartAngle, rotaryEndAngle, sliderPosProportional);
		g.setColour(Colours::whitesmoke);
		DrawTick_(g, cx, cy, r1, r2, angle, tickWidth);
	}

	void DefaultLookAndFeel::drawRotarySlider(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const sliderPosProportional,
		float rotaryStartAngle,
		float rotaryEndAngle,
		Slider& sl)
	{
		int minDim = std::min(w, h);
		
		float minVal = float(sl.getMinimum());
		float maxVal = float(sl.getMaximum());
		int32_t intMinVal = int32_t(std::ceil(minVal));
		int32_t intMaxVal = int32_t(std::floor(maxVal));

		float r1, r2, r3, tickWidth;
		Image knobImg = GetKnobImage_((minDim >= 48), minDim, r1, r2, r3);
		std::vector<float> ticks;
		std::vector<float> miniTicks; // this one ends up staying empty here
		
		if (minDim >= 48) {
			tickWidth = (minDim >= 88) ? 3.0f : 2.0f;

			if (Utils::ApproxEqual(minVal, 0.0f) && Utils::ApproxEqual(maxVal, 1.0f) && sl.getInterval() == 0.0f) {
				// Draw 10 ticks
				for (int32_t n = 0; n <= 10; ++n)
					ticks.push_back(float(sl.valueToProportionOfLength(n/10.0)));
			}
			else {
				// Draw all ticks
				for (int32_t n = intMinVal; n <= intMaxVal; ++n)
					ticks.push_back(float(sl.valueToProportionOfLength(n)));

				if (!Utils::ApproxEqual(minVal, 0.0f)) ticks.push_back(0.0f);
				if (!Utils::ApproxEqual(maxVal, 1.0f)) ticks.push_back(1.0f);
			}
		}
		else if (minDim >= 32) {
			tickWidth = 2.0f;

			// Draw start & end, and zero point if bipolar
			ticks.push_back(0.0f);
			if (minVal < 0.0f)
				ticks.push_back(float(sl.valueToProportionOfLength(0.0)));
			ticks.push_back(1.0f);
		}
		else {
			tickWidth = 1.0f;
		}

		DrawKnob_(
			g, x, y, w, h,
			sliderPosProportional, rotaryStartAngle, rotaryEndAngle, sl,
			knobImg, ticks, miniTicks,
			r1, r2, r3, tickWidth);
	}

	void TuningKnobLookAndFeel::drawRotarySlider(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const sliderPosProportional,
		float rotaryStartAngle,
		float rotaryEndAngle,
		Slider& sl)
	{
		int minDim = std::min(w, h);

		int32_t intMinVal = int32_t(std::ceil(sl.getMinimum()));
		int32_t intMaxVal = int32_t(std::floor(sl.getMaximum()));

		float r1, r2, r3;
		Image knobImg = GetKnobImage_(true, minDim, r1, r2, r3);
		float tickWidth = 2.0f;

		std::vector<float> ticks;
		std::vector<float> miniTicks;
		for (int32_t n = intMinVal; n <= intMaxVal; ++n)
		{
#if 1
			if (n == 0 || n == 7 || n == -7)
				ticks.push_back(float(sl.valueToProportionOfLength(n)));
			else
				miniTicks.push_back(float(sl.valueToProportionOfLength(n)));
#else
			int nMod = n % 12;
			if (nMod == 0 || nMod == 7 || nMod == -5)
				ticks.push_back(float(sl.valueToProportionOfLength(n)));
			else
				miniTicks.push_back(float(sl.valueToProportionOfLength(n)));
#endif
		}

		DrawKnob_(
			g, x, y, w, h,
			sliderPosProportional, rotaryStartAngle, rotaryEndAngle, sl,
			knobImg, ticks, miniTicks,
			r1, r2, r3, tickWidth);
	}

	void FreqKnobLookAndFeel::drawRotarySlider(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const sliderPosProportional,
		float rotaryStartAngle,
		float rotaryEndAngle,
		Slider& sl)
	{
		int minDim = std::min(w, h);

		float r1, r2, r3;
		Image knobImg = GetKnobImage_(true, minDim, r1, r2, r3);
		float tickWidth = 3.0f;

		std::vector<float> ticks;
		std::vector<float> miniTicks;
		
		// This is more hard-coded than I want in the end
		// Especially since this assumes specific knob range & mapping
		// Also, I'm not even sure if I like the log ticks in the first place
		// But it'll do for now
		
		// Sub Phatty/37 doesn't actually use a true log knob - it's more sensitive in the middle

		std::vector<uint32_t> tickFreqs = { 20,   30,   40,   50,   60,   70,   80,   90,
		                             100,   200,  300,  400,  500,  600,  700,  800,  900,
		                             1000,  2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,
		                             10000, 20000 };

		float startLog = logf(float(tickFreqs.front()));
		float endLog = logf(float(tickFreqs.back()));

		for (auto it = tickFreqs.begin(); it != tickFreqs.end(); ++it)
		{

			float logVal = Utils::ReverseInterp<float>(startLog, endLog, logf(float(*it)));
			
			if (*it == tickFreqs.front() || *it == tickFreqs.back() || *it == 100 || *it == 1000 || *it == 10000)
				ticks.push_back(logVal);
			else
				miniTicks.push_back(logVal);
		}

		DrawKnob_(
			g, x, y, w, h,
			sliderPosProportional, rotaryStartAngle, rotaryEndAngle, sl,
			knobImg, ticks, miniTicks,
			r1, r2, r3, tickWidth);
	}
	
	// ***** Switch functions *****

	// returns true if successful
	static bool DrawToggle_(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		int val,
		int const nSteps, // 2 or 3
		bool bIsVert)
	{
		char const* pImgData = 0;
		int imgSize = 0;

		// If range 0-2, 1 is center
		// Otherwise, 1 is end
		if (val == 1 && nSteps == 2)
			val = 2;

		switch (val) {
		case 0:
			pImgData = bIsVert ? BinaryData::switchvdown_32_png : BinaryData::switchhleft_32_png;
			imgSize = bIsVert ? BinaryData::switchvdown_32_pngSize : BinaryData::switchhleft_32_pngSize;
			break;
		case 1:
			pImgData = bIsVert ? BinaryData::switchvcenter_32_png : BinaryData::switchhcenter_32_png;
			imgSize = bIsVert ? BinaryData::switchvcenter_32_pngSize : BinaryData::switchhcenter_32_pngSize;
			break;
		case 2:
			pImgData = bIsVert ? BinaryData::switchvup_32_png : BinaryData::switchhright_32_png;
			imgSize = bIsVert ? BinaryData::switchvup_32_pngSize : BinaryData::switchhright_32_pngSize;
			break;
		default:
			return false;
		}

		if (!pImgData) return false;

		Image img = ImageCache::getFromMemory(pImgData, imgSize);

		if (bIsVert)
			DrawImageCentered_(g, img, x + w/2.0f, y + h/2.0f, w, 0);
		else
			DrawImageCentered_(g, img, x + w/2.0f, y + h/2.0f, 0, h);

		return true;
	}

	void DefaultLookAndFeel::drawLinearSlider(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const /*sliderPos*/,
		float const /*minSliderPos*/,
		float const /*maxSliderPos*/,
		Slider::SliderStyle const style,
		Slider& sl)
	{
		// Center coords
		float cx = x + (float(w) / 2.0f);
		float cy = y + (float(h) / 2.0f);

		// Mouseover
		bool const bIsMouseOver = sl.isEnabled() && sl.isMouseOverOrDragging();

		bool bIsVert = false;

		switch (style) {
		case Slider::SliderStyle::LinearHorizontal:
		case Slider::SliderStyle::LinearBar:
			bIsVert = false;
			break;
		case Slider::SliderStyle::LinearVertical:
		case Slider::SliderStyle::LinearBarVertical:
			bIsVert = true;
			break;
		default:
			// TODO: throw?
			return;
		}

		if (sl.getInterval() > 0.05f) {
			int nSteps = ToInt((sl.getMaximum() - sl.getMinimum()) / sl.getInterval()) + 1;

			if (nSteps == 2 || nSteps == 3) {
				// Use toggle graphic

				int val = ToInt(
					Utils::ReverseInterp(sl.getMinimum(), sl.getMaximum(), sl.getValue()) * (nSteps-1)
					);

				if (DrawToggle_(g, x, y, w, h, val, nSteps, bIsVert)) return;
			}

			// Otherwise fall back on standard behavior
		}

		// Draw slider track

		int minx, miny, maxx, maxy;
		if (bIsVert) {
			minx = ToInt(cx);
			maxx = ToInt(cx);
			miny = y;
			maxy = y + h;
		}
		else {
			minx = x;
			maxx = x + w;
			miny = ToInt(cy);
			maxy = ToInt(cy);
		}

		g.setColour(Colours::black);
		g.drawLine(float(minx), float(miny), float(maxx), float(maxy), 2.0f);

		// Draw cap

		// TODO: figure out why this one doesn't work when the other does
		// (what values are sliderPos anyway?)
		//float pos = Utils::ReverseInterp(minSliderPos, maxSliderPos, sliderPos);
		double pos = Utils::ReverseInterp(sl.getMinimum(), sl.getMaximum(), sl.getValue());

		int imgx, imgy;
		if (bIsVert) {
			imgx = ToInt(cx);
			imgy = ToInt(Utils::Interp(double(y + h), double(y), pos));
		}
		else {
			imgx = ToInt(Utils::Interp(double(x), double(x + w), pos));
			imgy = ToInt(cy);
		}

		Image img = ImageCache::getFromMemory(BinaryData::slidercap_32_png, BinaryData::slidercap_32_pngSize);
		
		DrawImageCentered_(g, img, float(imgx), float(imgy), w, h);
	}

	// ***** Other LookAndFeel overrides *****

	Typeface::Ptr DefaultLookAndFeel::getTypefaceForFont(const Font &f) {

		/*
		// Default definition:
		if (defaultSans.isNotEmpty() && f.getTypefaceName() == Font::getDefaultSansSerifFontName())
		{
			Font f(font);
			f.setTypefaceName(defaultSans);
			return Typeface::createSystemTypefaceFor(f);
		}

		return Font::getDefaultTypefaceForFont(font);
		*/

		if (f.getTypefaceName() == Font::getDefaultSansSerifFontName())
		{
			return Typeface::createSystemTypefaceFor(BinaryData::MuliRegular_ttf, BinaryData::MuliRegular_ttfSize);
		}

		return Font::getDefaultTypefaceForFont(f);
	}

	// Copied and modified from juce::LookAndFeel_V2
	void DefaultLookAndFeel::drawGroupComponentOutline(
		Graphics& g,
		int width, int height,
		const String& text,
		const Justification& position,
		GroupComponent& group)
	{
		const float lineWidth = 4.0f;
		const float textH = 15.0f;
		const float indent = 3.0f;
		const float textEdgeGap = 4.0f;
		float cs = 5.0f;
		
		Font f(textH);

		//Path p;
		float x = indent;
		float y = f.getAscent() - 3.0f;
		float w = jmax(0.0f, width - x * 2.0f);
		float h = jmax(0.0f, height - y - indent);
		cs = jmin(cs, w * 0.5f, h * 0.5f);
		const float cs2 = 2.0f * cs;

		float textW = text.isEmpty() ? 0 : jlimit(0.0f, jmax(0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth(text) + textEdgeGap * 2.0f);
		float textX = cs + textEdgeGap;

		if (position.testFlags(Justification::horizontallyCentred))
			textX = cs + (w - cs2 - textW) * 0.5f;
		else if (position.testFlags(Justification::right))
			textX = w - cs - textW - textEdgeGap;

		const float alpha = group.isEnabled() ? 1.0f : 0.5f;

		g.setColour(group.findColour(GroupComponent::outlineColourId)
			.withMultipliedAlpha(alpha));
		
		const float lineY = y-1;

		g.drawLine(
			x + textX + textW, lineY,
			x + w, lineY,
			lineWidth);

		g.drawLine(
			x + textX, lineY,
			x, lineY,
			lineWidth);

		g.setColour(group.findColour(GroupComponent::textColourId)
			.withMultipliedAlpha(alpha));
		g.setFont(f);
		g.drawText(text,
			roundToInt(x + textX), 0,
			roundToInt(textW),
			roundToInt(textH),
			Justification::centred, true);
	}

} // namespace Gui