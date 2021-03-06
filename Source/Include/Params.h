/*
  ==============================================================================

    Params.h
    Created: 7 Sep 2015 6:26:12pm
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

#ifndef PARAMS_H_INCLUDED
#define PARAMS_H_INCLUDED

#include "JuceHeader.h"

#include "Utils/Types.h"
#include "Utils/DspUtils.h"
#include "Utils/Debug.h"
#include "Utils/Logger.h"

#include <vector>
#include <array>

// ***** Param *****

// Class Param is in range 0-1, as are all overridden virtual methods
// However, some param types optionally have their own ranges, with values
// in these ranges exposed in functions not from AudioProcessorParameter
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

	virtual ~Param() {}

	// from juce::AudioProcessorParameter
	float getDefaultValue() const override { return defaultValue; }
	juce::String getName(int /*maximumStringLength*/) const override { return name; } // TODO: use maximumStringLength
	juce::String getLabel() const override { return units; }
	bool isOrientationInverted() const override { return bInverted; }
	bool isAutomatable() const override { return bAutomatable; }
	bool isMetaParameter() const override { return bMeta; }	
	
	// from juce::SliderListener
	void sliderValueChanged(juce::Slider* slider) override {
		DEBUG_ASSERT(slider);
		
		//LOG(getName() + juce::String::formatted(" slider changed: %f", slider->getValue()));

		// FIXME: this doesn't work
		//setValueNotifyingHost(float(slider->valueToProportionOfLength(slider->getValue())));

		// This won't notify host, but is otherwise better (doesn't need to convert to host range & back)
		SetActualValue(float(slider->getValue()));
	}

	// New methods
	virtual float GetActualValue() const = 0;
	virtual void SetActualValue(float val) = 0;
	virtual float GetMin() const = 0;
	virtual float GetMax() const = 0;
	juce::String getName() const { return name; } // same as juce::AudioProcessorParameter function but with no args
	
	virtual float GetInterval() const {
		return (getNumSteps() == 0) ?
			0.0f :
			1.0f / (getNumSteps() - 1.0f);
	};

	virtual void BindToSlider(juce::Slider* pSlider) {
		DEBUG_ASSERT(pSlider);
		pSlider->setRange(GetMin(), GetMax(), GetInterval());
		pSlider->setValue(GetActualValue());
		pSlider->addListener(this);

		//LOG(getName() + String::formatted(" = %.2f [%.1f,%.1f,%.1f]", GetActualValue(), GetMin(), GetInterval(), GetMax()));
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
        Param(paramName, unitName, defaultParamValue, bIsInverted, bIsAutomatable, bIsMeta),
		m_val(defaultParamValue),
		m_range(paramRange)
	{}

	~FloatParam() {}

	// AudioProcessorParameter functions

	float getValue() const override
		{ return ActualToHost_(GetActualValue()); }

	void setValue(float newValue) override
		{ SetActualValue(HostToActual_(newValue)); }

	float getValueForText(const juce::String& text) const override
		{ return ActualToHost_(text.getFloatValue()); }

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return juce::String(HostToActual_(value)); }

	// Param functions

	float GetMin() const override { return m_range.min; }
	float GetMax() const override { return m_range.max; }
	float GetInterval() const override { return 0.0f; }

	void SetActualValue(float newValue) override {
		newValue = m_range.Clip(newValue);
		m_val.set(newValue);
	}

	float GetActualValue() const override { return m_val.get(); }

private:

	float HostToActual_(float hostVal) const {
		hostVal = Utils::Clip(hostVal, 0.0f, 1.0f);
		return Utils::Interp(m_range.min, m_range.max, hostVal);
	}

	float ActualToHost_(float actualVal) const
		{ return Utils::ReverseInterp(m_range.min, m_range.max, actualVal); }

	juce::Atomic<float> m_val;
	Utils::Range_t<float> const m_range;
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
		Param(paramName, unitName, ActualToHost_(defaultParamValue), bIsInverted, bIsAutomatable, bIsMeta),
		m_val(defaultParamValue),
		m_range(paramRange)
	{}

	~IntParam() {}

	// AudioProcessorParameter functions

	float getValue() const override
		{ return ActualToHost_(GetInt()); }

	void setValue(float newValue) override
		{ SetActualValue(float(HostToActual_(newValue))); }

	float getValueForText(const juce::String& text) const override
		{ return ActualToHost_(Utils::RoundTo<int>(text.getFloatValue())); }

	juce::String getText(float value, int /*maximumStringLength*/) const override
		{ return juce::String(HostToActual_(value)); }

	int getNumSteps() const override
		{ return (m_range.max - m_range.min + 1); }

	// Param functions

	void SetActualValue(float newValue) {
		m_val.set(m_range.Clip(Utils::RoundTo<int>(newValue)));
	}

	float GetActualValue() const { return float(m_val.get()); }
	float GetMin() const override { return float(m_range.min); }
	float GetMax() const override { return float(m_range.max); }
	float GetInterval() const override { return 1.0f; }

	// Other functions

	void SetInt(int newValue) { m_val.set(m_range.Clip(newValue)); }
	int GetInt() const { return m_val.get();  }

private:

	int HostToActual_(float hostVal) const {
		hostVal = Utils::Clip(hostVal, 0.0f, 1.0f);
		return Utils::RoundTo<int>(Utils::Interp(float(m_range.min), float(m_range.max), hostVal));
	}

	float ActualToHost_(int actualVal) const
		{ return Utils::ReverseInterp(float(m_range.min), float(m_range.max), float(actualVal)); }

	juce::Atomic<int> m_val;
	Utils::Range_t<int> const m_range;
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
		Param(paramName, unitName, float(bDefaultParamValue), bIsInverted, bIsAutomatable, bIsMeta),
		m_val(size_t(bDefaultParamValue)),
		mk_names(valueNames)
	{}

	~BoolParam() {}

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

	// Param functions

	void SetActualValue(float newValue) override { setValue(newValue); }
	float GetActualValue() const override { return getValue(); }
	float GetMin() const override { return 0.0f; }
	float GetMax() const override { return 1.0f; }
	float GetInterval() const override { return 1.0f; }

	// New functions

	bool GetBool() const { return !!m_val.get(); }

private:
	juce::Atomic<size_t> m_val;
	std::array<juce::String, 2> const mk_names;
};

// ***** EnumParam *****

class EnumParam : public Param,
	public juce::ComboBoxListener
{
public:
	EnumParam(juce::String const& paramName,
			std::vector<juce::String> const& paramEnumValueNames,
			size_t defaultParamValue = 0,
			juce::String const& unitName = juce::String(""),
			bool bIsInverted = false,
			bool bIsAutomatable = true,
			bool bIsMeta = false) :
		Param(paramName, unitName, IntToFloatVal_(defaultParamValue), bIsInverted, bIsAutomatable, bIsMeta),
		mk_enums(paramEnumValueNames),
		mk_nVals(paramEnumValueNames.size()),
		m_val(defaultParamValue)
	{}

	~EnumParam() {}

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

	// Param functions

	float GetMin() const override { return 0.0f; }
	float GetMax() const override { return float(mk_nVals - 1); }

	void SetActualValue(float newValue) override {
		m_val.set(Utils::Clip<int>(Utils::RoundTo<int>(newValue), 0, mk_nVals));
	}

	float GetActualValue() const override { return float(m_val.get()); }
	
	// ComboBoxListener functions

	void comboBoxChanged(juce::ComboBox* comboBox) override {
		// TODO: currently this won't notify host (same issues as sliderValueChanged)

		int val = comboBox->getSelectedItemIndex();
		
		if (val >= 0)
			SetInt(size_t(val));
		else
			LOG(juce::String("Tried to set enum parameter ") + getName() + juce::String::formatted(" to value %i", val));
	}

	// New functions
	
	virtual void BindToComboBox(juce::ComboBox* pComboBox) {
		DEBUG_ASSERT(pComboBox);
		// TODO: log error if not same number of options
		pComboBox->setSelectedItemIndex(GetInt());
		pComboBox->addListener(this);

		LOG(getName() + juce::String::formatted(" = %.2f [%.1f,%.1f,%.1f]", GetActualValue(), GetMin(), GetInterval(), GetMax()));
	}

	size_t GetNumVals() const { return mk_nVals; }
	float GetInterval() const override { return 1.0f; }

	void SetInt(size_t newValue) { m_val.set(std::min(newValue, mk_nVals-1)); }
	size_t GetInt() const { return m_val.get(); }

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
	juce::Atomic<size_t> m_val;
};

struct ParamStruct {
private:
	std::vector<Param*> paramList;

public:

	EnumParam* osc1wave;
	FloatParam* osc1shape;
	FloatParam* osc1shapeMod;
	EnumParam* osc1shapeModSrc;
	EnumParam* osc2wave;
	IntParam* osc2oct;
	FloatParam* osc2coarse;
	FloatParam* osc2fine;
	BoolParam* osc2sync;
	IntParam* subOscOct;
	EnumParam* subOscWave;
	FloatParam* mixOsc1;
	FloatParam* mixOsc2;
	FloatParam* mixSub;
	FloatParam* mixRing;
	FloatParam* mixNoise;
	FloatParam* filtFreq;
	FloatParam* filtRes;
	FloatParam* filtGain;
	EnumParam* filtModel;
	EnumParam* filtKb;
	EnumParam* filtPoles;
	FloatParam* filtEnv;
	FloatParam* filtMod1Amt;
	FloatParam* filtMod2Amt;
	FloatParam* envAtt;
	FloatParam* envDec;
	FloatParam* envSus;
	FloatParam* envRel;
	FloatParam* envVel;
	EnumParam* vcaSource;
	FloatParam* vcaVel;
	FloatParam* mod1freq;
	FloatParam* mod1shape;
	EnumParam* mod1range;
	FloatParam* mod1mod2amt;
	EnumParam* mod1mod2type;
	EnumParam* mod2type;
	FloatParam* mod2attack;
	FloatParam* mod2decay;

	// Note: these params must have the same name as the corresponding knob in the GUI!
	// Also, name must be less than 30 characters
	// See MainGui.cpp constructor for details

	/*
	Something else has to manually delete these!
	i.e. these will be added to PluginProcessor, which calls addParameter, which adds them
	to juce::OwnedArray, which deletes them on destruction
	
	However, this process doesn't happen in unit test, so the memory leaks!
	Really this whole thing needs to be overhauled - change to a PluginState object of something
	*/

#define AP(X) paramList.push_back(X)
	ParamStruct()
	{
		AP(osc1wave = new EnumParam("Osc 1 Wave", { "Tri","Rect","Saw" }, 2));
		AP(osc1shape = new FloatParam("Osc 1 Shape"));
		AP(osc1shapeMod = new FloatParam("Osc 1 Shape Mod"));
		AP(osc1shapeModSrc = new EnumParam("Osc 1 Shape Mod Source", {"Mod 1", "Mod 2"}, 0));
		AP(osc2wave = new EnumParam("Osc 2 Wave", { "Tri","Rect","Saw" }, 2));
		AP(osc2oct = new IntParam("Osc 2 Octave", 0, { 0, 1 }));
		AP(osc2coarse = new FloatParam("Osc 2 Coarse Tune", 0, { -7.09f, 7.07f }));
		// Initialize osc 2 fine tune to slightly off center
		AP(osc2fine = new FloatParam("Osc 2 Fine Tune", 0.021f, { -1.0f, 1.0f }));
		AP(osc2sync = new BoolParam("Osc 2 Sync", {"Off", "On"}, false));
		AP(subOscOct = new IntParam("Sub Osc Octave", -1, { -2, -1 }));
		AP(subOscWave = new EnumParam("Sub Osc Wave", { "Tri", "Square", "Pulse" }, 0));
		AP(mixOsc1 = new FloatParam("Osc 1 Mix", 1.0f));
		AP(mixOsc2 = new FloatParam("Osc 2 Mix"));
		AP(mixSub = new FloatParam("Sub Mix"));
		AP(mixRing = new FloatParam("Ring Mod Mix"));
		AP(mixNoise = new FloatParam("Noise Mix"));
		AP(filtFreq = new FloatParam("Filter Frequency", 1.0f));
		AP(filtRes = new FloatParam("Filter Resonance"));
		AP(filtGain = new FloatParam("Filter Gain", 0.5f));
		AP(filtModel = new EnumParam("Filter Model", { "Off", "Transistor", "Diode" }, 1));
		AP(filtKb = new EnumParam("Filter KB Track", { "0", "0.5", "1" }, 2));
		AP(filtPoles = new EnumParam("Filter Poles", { "2", "4" }, 1));
		AP(filtEnv = new FloatParam("Filter Env Amount"));
		AP(filtMod1Amt = new FloatParam("Filter Mod 1 Amount"));
		AP(filtMod2Amt = new FloatParam("Filter Mod 2 Amount"));
		AP(envAtt = new FloatParam("Env Attack"));
		AP(envDec = new FloatParam("Env Decay"));
		AP(envSus = new FloatParam("Env Sustain", 1.0f));
		AP(envRel = new FloatParam("Env Release"));
		AP(envVel = new FloatParam("Env Velocity"));
		AP(vcaSource = new EnumParam("VCA Source", {"Gate + Click", "Gate", "Envelope"}, 1));
		AP(vcaVel = new FloatParam("VCA Velocity"));
		AP(mod1freq = new FloatParam("Mod 1 Rate", 0.5f));
		AP(mod1shape = new FloatParam("Mod 1 Shape", 0.0f, { -1.0f, 1.0f }));
		AP(mod1range = new EnumParam("Mod 1 Range", {"Low", "High", "KB Track"}));
		AP(mod1mod2amt = new FloatParam("Mod 1 From Mod 2 Amt"));
		AP(mod1mod2type = new EnumParam("Mod 1 From Mod 2 Type", { "Shape", "Rate", "Amount" }, 2));
		AP(mod2type = new EnumParam("Mod 2 Type", { "Env-", "Env+", "LFO" }, 1));
		AP(mod2attack = new FloatParam("Mod 2 Attack", 0.5f));
		AP(mod2decay = new FloatParam("Mod 2 Decay", 0.5f));
	}
#undef AP

	std::vector<Param*> const& GetParamList() const { return paramList; }
};








#endif  // PARAMS_H_INCLUDED
