/*
  ==============================================================================

    LookAndFeel.cpp
    Created: 25 Aug 2015 8:13:38am
    Author:  Joel

  ==============================================================================
*/

#include "LookAndFeel.h"

#include "JuceHeader.h"

#include "Utils/DspUtils.h"

#include <cmath>
#include <vector>

namespace Gui {

	static inline int ToInt(float f) { return static_cast<int>(std::round(f)); }
	static inline int ToInt(double d) { return static_cast<int>(std::round(d)); }

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

	void DefaultLookAndFeel::drawRotarySlider(
		Graphics& g,
		int const x, int const y,
		int const w, int const h,
		float const sliderPosProportional,
		float rotaryStartAngle,
		float rotaryEndAngle,
		Slider& sl)
	{
		// Center coords
		float cx = x + (float(w) / 2.0f);
		float cy = y + (float(h) / 2.0f);

		// Angles coming in seem to be clockwise starting at the top
		// We want these in Cartesian coordinates (counterclockwise starting to the right)
		rotaryStartAngle = float(M_PI_2) - rotaryStartAngle;
		rotaryEndAngle = float(M_PI_2) - rotaryEndAngle;
		float angle = Utils::Interp(rotaryStartAngle, rotaryEndAngle, sliderPosProportional);
		
		// Mouseover
		bool const bIsMouseOver = sl.isEnabled() && sl.isMouseOverOrDragging();

		// TODO: use mouseover value

		// Max Radius
		int minDim = std::min(w, h);
		float maxRadius = minDim / 2.0f;

		// Values to set depending on knob size
		std::vector<float> ticks;
		Image img;
		float r1, r2, tickWidth;

		float minVal = float(sl.getMinimum());
		float maxVal = float(sl.getMaximum());
		//float range = maxVal - minVal;

		int32_t intMinVal = int32_t(std::ceil(minVal));
		int32_t intMaxVal = int32_t(std::floor(maxVal));
		//int32_t intRange = intMaxVal - intMinVal;

		if (minDim >= 88) {
			img = ImageCache::getFromMemory(BinaryData::bigknob88_png, BinaryData::bigknob88_pngSize);
			r2 = (cx - x) * 0.38f;
			r1 = r2 * 0.25f;
			tickWidth = 3.0f;

			ticks.push_back(rotaryStartAngle);
			ticks.push_back(rotaryEndAngle);

			// Draw all ticks
			for (int32_t n = intMinVal; n <= intMaxVal; ++n)
				ticks.push_back(Utils::Interp(rotaryStartAngle, rotaryEndAngle, Utils::ReverseInterp(minVal, maxVal, float(n))));
		}
		else if (minDim >= 48) {
			img = ImageCache::getFromMemory(BinaryData::bigknob88_png, BinaryData::bigknob88_pngSize);
			r2 = (cx - x) * 0.38f;
			r1 = r2 * 0.25f;
			tickWidth = 2.0f;

			// HACK FIXME: this is a way of detecting osc2 tuning knob - but a bad one
			if (intMaxVal - intMinVal < 20) {
				// Draw all ticks
				for (int32_t n = intMinVal; n <= intMaxVal; ++n)
					ticks.push_back(Utils::Interp(rotaryStartAngle, rotaryEndAngle, Utils::ReverseInterp(minVal, maxVal, float(n))));
			}
			else {
				ticks.push_back(Utils::Interp(rotaryStartAngle, rotaryEndAngle, Utils::ReverseInterp(minVal, maxVal, 0.0f)));
				ticks.push_back(Utils::Interp(rotaryStartAngle, rotaryEndAngle, Utils::ReverseInterp(minVal, maxVal, 12.0f)));
			}
		}
		else if (minDim >= 32) {
			img = ImageCache::getFromMemory(BinaryData::knob32_png, BinaryData::knob32_pngSize);
			r2 = (cx - x) * 0.5f;
			r1 = r2 * 0.25f;
			tickWidth = 2.0f;

			// Draw start & end, and center point if bipolar
			ticks.push_back(rotaryStartAngle);
			if (minVal < 0) ticks.push_back(Utils::Interp(rotaryStartAngle, rotaryEndAngle, Utils::ReverseInterp(minVal, maxVal, 0.0f)));
			ticks.push_back(rotaryEndAngle);
		}
		else {
			img = ImageCache::getFromMemory(BinaryData::knob24_png, BinaryData::knob24_pngSize);
			r2 = (cx - x) * 0.5f;
			r1 = r2 * 0.25f;
			tickWidth = 1.0f;
		}

		// Draw ticks
		g.setColour(Colours::whitesmoke);
		for (std::vector<float>::const_iterator it = ticks.begin(); it != ticks.end(); ++it) {
			DrawTick_(g, cx, cy, r2, maxRadius, *it);
		}

		// Draw knob image
		DrawImageCentered_(g, img, cx, cy, w, h);

		// Draw knob indicator
		g.setColour(Colours::whitesmoke);
		DrawTick_(g, cx, cy, r1, r2, angle, tickWidth);
	}
	
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

} // namespace Gui