/*
  ==============================================================================

    Params.h
    Created: 7 Sep 2015 6:26:12pm
    Author:  Joel

  ==============================================================================
*/

#ifndef PARAMS_H_INCLUDED
#define PARAMS_H_INCLUDED

#include "JuceHeader.h"

#include "Utils/DspUtils.h"

#include <vector>
#include <array>

#if _DEBUG
#define SETUP_DEBUG_PARAMS()

#else
#define SETUP_DEBUG_PARAMS()
#endif

// Note: these params must have the same name as the corresponding knob in the GUI!
// Also, name must be less than 30 characters
// See MainGui.cpp constructor for details

#define SETUP_PARAMS() \
addParameter(new EnumParam("Osc 1 Wave", {"Tri","Rect","Saw"}, 2)); \
addParameter(new FloatParam("Osc 1 Shape")); \
addParameter(new EnumParam("Osc 2 Wave", {"Tri","Rect","Saw"}, 2)); \
addParameter(new FloatParam("Osc 2 Shape")); \
addParameter(new FloatParam("Osc 2 Fine Tune", 0.5f)); \
addParameter(new EnumParam("Sub Osc Octave", {"-2","-1"}, 1)); \
addParameter(new EnumParam("Sub Osc Wave", {"Tri","Square","Pulse"}, 0)); \
addParameter(new FloatParam("Osc 1 Mix", 1.0f)); \
addParameter(new FloatParam("Osc 2 Mix")); \
addParameter(new FloatParam("Sub Mix")); \
addParameter(new FloatParam("Ring Mod Mix")); \
addParameter(new FloatParam("Noise Mix")); \
addParameter(new FloatParam("Filter Frequency")); \
addParameter(new FloatParam("Filter Resonance")); \
addParameter(new EnumParam("Filter Model", {"IC","Transistor","Diode"}, 0)); \
addParameter(new BoolParam("Filter KB Track")); \
addParameter(new EnumParam("Filter Poles", {"2","4"}, 0)); \
addParameter(new FloatParam("Filter Env Amount")); \
addParameter(new EnumParam("Filter Env Polarity", {"-","+"}, 1)); \
addParameter(new FloatParam("Filter Vel Amount")); \
addParameter(new FloatParam("Filter LFO Amount")); \
addParameter(new EnumParam("Filter LFO Select", {"LFO 1","LFO 2"}, 0)); \
addParameter(new FloatParam("Filt Env Attack")); \
addParameter(new FloatParam("Filt Env Decay")); \
addParameter(new FloatParam("Filt Env Sustain", 1.0f)); \
addParameter(new FloatParam("Filt Env Release")); \
addParameter(new FloatParam("Filt Env Velocity")); \
addParameter(new FloatParam("Amp Env Attack")); \
addParameter(new FloatParam("Amp Env Decay")); \
addParameter(new FloatParam("Amp Env Sustain", 1.0f)); \
addParameter(new FloatParam("Amp Env Release")); \
addParameter(new FloatParam("Amp Env Velocity")); \
addParameter(new FloatParam("LFO 1 Freq", 0.5f)); \
addParameter(new EnumParam("LFO 1 Shape", {"Squ","Tri","+Saw","-Saw","S&H"})); \
addParameter(new FloatParam("LFO 2 Freq", 0.5f)); \
addParameter(new EnumParam("LFO 2 Shape", {"Squ","Tri","+Saw","-Saw","S&H","+Env","-Env"})); \
addParameter(new FloatParam("LFO 2 Attack")); \
SETUP_DEBUG_PARAMS()




// ***** Param *****

class Param :
	public juce::AudioProcessorParameter,
	public juce::SliderListener
{
public:
	Param(juce::String const& paramName,
			juce::String const& unitName,
			float defaultParamValue,
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		name(paramName),
		units(unitName),
		defaultValue(defaultParamValue),
		bInverted(bIsInverted),
		bAutomatable(bIsAutomatable),
		bMeta(bIsMeta)
	{}

	float getDefaultValue() const override { return defaultValue; }
	juce::String getName(int /*maximumStringLength*/) const override { return name; } // TODO: use maximumStringLength
	juce::String getLabel() const override { return units; }
	bool isOrientationInverted() const override { return bInverted; }
	bool isAutomatable() const override { return bAutomatable; }
	bool isMetaParameter() const override { return bMeta; }	
	
	// from juce::SliderListener
	void sliderValueChanged(juce::Slider* slider) override { 
		DEBUG_ASSERT(slider);
		setValue(float(Utils::ReverseInterp(slider->getMinimum(), slider->getMaximum(), slider->getValue())));
	}

protected:
	juce::String const name;
	juce::String const units;
	float const defaultValue;
	bool const bInverted;
	bool const bAutomatable;
	bool const bMeta;
};

// ***** FloatParam *****

class FloatParam : public Param
{
public:
	FloatParam(const juce::String& paramName,
			float defaultParamValue = 0.0f,
			juce::String const& unitName = juce::String(""),
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		m_val(defaultParamValue),
		Param(paramName, unitName, defaultParamValue, bIsInverted, bIsAutomatable, bIsMeta)
	{}

	float getValue() const override
		{ return m_val.get(); }

	void setValue(float newValue) override
		{ m_val.set(newValue); }

	float getValueForText(const juce::String& text) const override
		{ return text.getFloatValue(); }

private:
	juce::Atomic<float> m_val;
};

// ***** BoolParam *****

class BoolParam : public Param
{
public:
	BoolParam(juce::String const& paramName,
			std::array<juce::String, 2> const& valueNames = {"false","true"},
			bool bDefaultParamValue = false,
			juce::String const& unitName = juce::String(""),
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		m_val(size_t(bDefaultParamValue)),
		mk_names(valueNames),
		Param(paramName, unitName, float(bDefaultParamValue), bIsInverted, bIsAutomatable, bIsMeta)
	{}

	float getValue() const override
		{ return float(m_val.get()); }

	void setValue(float newValue) override
		{ m_val.set(newValue >= 0.5f); }

	float getValueForText(const juce::String& text) const override {
		if (text.equalsIgnoreCase(mk_names[0])) return 0.0f;
		if (text.equalsIgnoreCase(mk_names[1])) return 1.0f;
		return text.getFloatValue() >= 0.5f;
	}

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return mk_names[value >= 0.5f]; }

	int getNumSteps() const override
		{ return 2; }

private:
	juce::Atomic<size_t> m_val;
	std::array<juce::String, 2> const mk_names;
};

// ***** EnumParam *****

// Max 256 values
class EnumParam : public Param
{
public:
	EnumParam(juce::String const& paramName,
			std::vector<juce::String> const& paramEnumValueNames,
			size_t defaultParamValue = 0,
			juce::String const& unitName = juce::String(""),
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		mk_enums(paramEnumValueNames),
		mk_nVals(paramEnumValueNames.size()),
		m_val(defaultParamValue),
		Param(paramName, unitName, IntToFloatVal_(defaultParamValue), bIsInverted, bIsAutomatable, bIsMeta)
	{}

	float getValue() const override
		{ return IntToFloatVal_(m_val.get()); }

	void setValue(float newValue) override
		{ m_val.set(FloatToIntVal_(newValue)); }

	float getValueForText(const juce::String& text) const override {
		// If text matches one of enums
		for (size_t n = 0; n < mk_nVals; ++n)
			if (text.equalsIgnoreCase(mk_enums[n])) return float(n);
		
		// Or, if float
		return text.getFloatValue();
	}

	int getNumSteps() const override
		{ return mk_nVals; }

	juce::String getText(float value, int /*maximumStringLength*/) const override {
		size_t intVal = FloatToIntVal_(value);
		return (intVal < mk_nVals) ? mk_enums[intVal] : juce::String(value);
	}

private:

	size_t FloatToIntVal_(float floatVal) const {
		floatVal = Utils::Clip(floatVal, 0.0f, 1.0f);
		return Utils::RoundTo<size_t>(
			Utils::Interp(0.0f, float(mk_nVals-1), floatVal));
	}
	
	float IntToFloatVal_(size_t intVal) const {
		return Utils::ReverseInterp(0.0f, float(mk_nVals-1), float(intVal));
	}

	std::vector<juce::String> const mk_enums;
	size_t const mk_nVals;
	Atomic<size_t> m_val;
};




#endif  // PARAMS_H_INCLUDED
