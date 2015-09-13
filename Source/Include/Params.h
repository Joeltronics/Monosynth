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

#include "Utils/Types.h"
#include "Utils/DspUtils.h"
#include "Utils/Debug.h"

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
addParameter(new IntParam("Osc 2 Coarse Tune", 0, {-7,19})); \
addParameter(new FloatParam("Osc 2 Fine Tune", 0.0f, {-1.0f,1.0f})); \
addParameter(new EnumParam("Sub Osc Octave", {"-2","-1"}, 1)); \
addParameter(new EnumParam("Sub Osc Wave", {"Tri","Square","Pulse"}, 0)); \
addParameter(new FloatParam("Osc 1 Mix", 1.0f)); \
addParameter(new FloatParam("Osc 2 Mix")); \
addParameter(new FloatParam("Sub Mix")); \
addParameter(new FloatParam("Ring Mod Mix")); \
addParameter(new FloatParam("Noise Mix")); \
addParameter(new FloatParam("Filter Frequency")); /*TODO: range*/ \
addParameter(new FloatParam("Filter Resonance")); \
addParameter(new EnumParam("Filter Model", {"IC","Transistor","Diode"}, 0)); \
addParameter(new BoolParam("Filter KB Track")); \
addParameter(new EnumParam("Filter Poles", {"2","4"}, 0)); \
addParameter(new FloatParam("Filter Env Amount", 0.0f, {-1.0f,1.0f})); \
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

// "Host value" = in range 0 to 1
// "Actual value" = in whatever range is set (though the default is also 0 to 1)

class FloatParam : public Param
{
public:
	// All constructor args are in terms of actual values
	// (Though if no range given, actual will have same range as host)
	FloatParam(const juce::String& paramName,
			float defaultParamValue = 0.0f,
			Utils::Range_t<float> paramRange = {0.0f, 1.0f},
			juce::String const& unitName = juce::String(""),
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		m_val(defaultParamValue),
		m_range(paramRange),
		Param(paramName, unitName, defaultParamValue, bIsInverted, bIsAutomatable, bIsMeta)
	{}

	// AudioProcessorParameter functions

	float getValue() const override
		{ return ActualToHost_(GetActualValue()); }

	void setValue(float newValue) override
		{ SetActualValue(HostToActual_(newValue)); }

	float getValueForText(const juce::String& text) const override
		{ return ActualToHost_(text.getFloatValue()); }

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return juce::String(HostToActual_(value)); }

	// New functions
	
	void SetActualValue(float newValue) {
		newValue = m_range.Clip(newValue);
		m_val.set(newValue);
	}

	float GetActualValue() const { return m_val.get(); }
	float GetMin() const { return m_range.min; }
	float GetMax() const { return m_range.max; }
	Utils::Range_t<float> GetRange() const { return m_range; }

private:

	float HostToActual_(float hostVal) const {
		hostVal = Utils::Clip(hostVal, 0.0f, 1.0f);
		return Utils::Interp(m_range.min, m_range.max, hostVal);
	}

	float ActualToHost_(float actualVal) const
		{ return Utils::ReverseInterp(m_range.min, m_range.max, actualVal); }

	juce::Atomic<float> m_val;
	Utils::Range_t<float> m_range;
};

// ***** IntParam *****

// "Host value" = in range 0 to 1
// "Actual value" = in whatever range is set (though the default is also 0 to 1)

class IntParam : public Param
{
public:
	// All constructor args are in terms of actual values
	// (Though if no range given, actual will have same range as host)
	IntParam(const juce::String& paramName,
		int defaultParamValue = 0,
		Utils::Range_t<int> paramRange = { 0, 1 },
		juce::String const& unitName = juce::String(""),
		bool bIsInverted = false,
		bool bIsAutomatable = true,
		bool bIsMeta = false) :
		m_val(defaultParamValue),
		m_range(paramRange),
		Param(paramName, unitName, defaultParamValue, bIsInverted, bIsAutomatable, bIsMeta)
	{}

	// AudioProcessorParameter functions

	float getValue() const override
		{ return ActualToHost_(GetActualValue()); }

	void setValue(float newValue) override
		{ SetActualValue(HostToActual_(newValue)); }

	float getValueForText(const juce::String& text) const override
		{ return ActualToHost_(text.getFloatValue()); }

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return juce::String(HostToActual_(value)); }

	int getNumSteps() const override
		{ return (m_range.max - m_range.min + 1); }

	// New functions

	void SetActualValue(int newValue) {
		newValue = m_range.Clip(newValue);
		m_val.set(newValue);
	}

	int GetActualValue() const { return m_val.get(); }
	int GetMin() const { return m_range.min; }
	int GetMax() const { return m_range.max; }
	Utils::Range_t<int> GetRange() const { return m_range; }

private:

	int HostToActual_(float hostVal) const {
		hostVal = Utils::Clip(hostVal, 0.0f, 1.0f);
		return Utils::RoundTo<int>(Utils::Interp<float>(m_range.min, m_range.max, hostVal));
	}

	float ActualToHost_(int actualVal) const
		{ return Utils::ReverseInterp<float>(m_range.min, m_range.max, actualVal); }

	juce::Atomic<int> m_val;
	Utils::Range_t<int> m_range;
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

	// AudioProcessorParameter functions

	float getValue() const override
		{ return (m_val.get() ? 1.0f : 0.0f); }

	void setValue(float newValue) override
		{ m_val.set(newValue >= 0.5f); }

	float getValueForText(const juce::String& text) const override {
		if (text.equalsIgnoreCase(mk_names[0])) return 0.0f;
		if (text.equalsIgnoreCase(mk_names[1])) return 1.0f;
		return text.getFloatValue() >= 0.5f;
	}

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return mk_names[value >= 0.5f]; }

	int getNumSteps() const override { return 2; }

	// New functions

	bool GetBool() const { return !!m_val.get(); }

private:
	juce::Atomic<size_t> m_val;
	std::array<juce::String, 2> const mk_names;
};

// ***** EnumParam *****

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

	// AudioProcessorParameter functions

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

	// New functions

	size_t GetActualValue() const { return m_val.get(); }
	size_t GetNumVals() const { return mk_nVals; }

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
