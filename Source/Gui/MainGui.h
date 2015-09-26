/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_ADBA7C90E028EAEC__
#define __JUCE_HEADER_ADBA7C90E028EAEC__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "Gui/LookAndFeel.h"

#include "Plugin/PluginProcessor.h"

#include "Params.h"

#include <typeinfo>

namespace Gui {

// Introjucer generated code assumes "using namespace juce"
// Instead of including this line in a header file (bad!), just import specific types into GUI namespace.
// Still try to only include MainGui.h when necessary, though.

using Component = juce::Component;
using SliderListener = juce::SliderListener;
using ComboBoxListener = juce::ComboBoxListener;
using String = juce::String;
using Graphics = juce::Graphics;

using Slider = juce::Slider;
using Label = juce::Label;
using GroupComponent = juce::GroupComponent;
using ComboBox = juce::ComboBox;

template<class T>
using ScopedPointer = juce::ScopedPointer<T>;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainGui  : public Component,
                 public SliderListener,
                 public ComboBoxListener
{
public:
    //==============================================================================
    MainGui (MonosynthAudioProcessor& p);
    ~MainGui();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	// ...and private methods!
	void SetSliderIDs_();
	void BindParamsToSliders_();
	void SetSpecialKnobs_();

	DefaultLookAndFeel defaultLookAndFeel;
	TuningKnobLookAndFeel tuningLookAndFeel;
	FreqKnobLookAndFeel freqLookAndFeel;

	MonosynthAudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> groupComponent11;
    ScopedPointer<Label> label70;
    ScopedPointer<Label> label80;
    ScopedPointer<Slider> swi_pitchmod_dest;
    ScopedPointer<GroupComponent> groupComponent2;
    ScopedPointer<GroupComponent> groupComponent6;
    ScopedPointer<GroupComponent> groupComponent13;
    ScopedPointer<GroupComponent> groupComponent3;
    ScopedPointer<Slider> swi_filt_poles;
    ScopedPointer<GroupComponent> groupComponent4;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<Slider> sli_o1_sh;
    ScopedPointer<GroupComponent> groupComponent8;
    ScopedPointer<GroupComponent> groupComponent5;
    ScopedPointer<Slider> sli_o2_sh;
    ScopedPointer<Slider> sli_mix_o1;
    ScopedPointer<Slider> sli_mix_o2;
    ScopedPointer<Slider> sli_mix_sub;
    ScopedPointer<Slider> sli_mix_ring;
    ScopedPointer<Slider> sli_mix_noise;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<Slider> sli_o2_tune;
    ScopedPointer<Label> label8;
    ScopedPointer<Slider> sli_filt_freq;
    ScopedPointer<Label> label13;
    ScopedPointer<Slider> sli_filt_res;
    ScopedPointer<Slider> sli_filt_env;
    ScopedPointer<Slider> sli_filt_lfo;
    ScopedPointer<Slider> sli_drive;
    ScopedPointer<Slider> sli_o2_mod;
    ScopedPointer<Slider> sli_o1_mod;
    ScopedPointer<Slider> sli_o2_finetune;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> label11;
    ScopedPointer<GroupComponent> groupComponent7;
    ScopedPointer<Slider> sli_env_att;
    ScopedPointer<Label> label17;
    ScopedPointer<Label> label18;
    ScopedPointer<Label> label19;
    ScopedPointer<Label> label20;
    ScopedPointer<Slider> sli_filt_gain;
    ScopedPointer<Label> label21;
    ScopedPointer<Slider> sli_pitchmod_amt;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label25;
    ScopedPointer<GroupComponent> groupComponent9;
    ScopedPointer<GroupComponent> groupComponent10;
    ScopedPointer<Slider> sli_glide_amt;
    ScopedPointer<Slider> sli_bend_range;
    ScopedPointer<Label> label26;
    ScopedPointer<Label> label28;
    ScopedPointer<Slider> sli_lfo2_freq;
    ScopedPointer<Label> label29;
    ScopedPointer<Slider> sli_lfo2_att;
    ScopedPointer<Label> label31;
    ScopedPointer<Label> label30;
    ScopedPointer<Slider> sli_filt_vel;
    ScopedPointer<Slider> sli_filt_resbass;
    ScopedPointer<Slider> sli_env_dec;
    ScopedPointer<Slider> sli_env_sus;
    ScopedPointer<Slider> sli_env_rel;
    ScopedPointer<Slider> sli_pitchmod_scale;
    ScopedPointer<Label> label32;
    ScopedPointer<Label> label24;
    ScopedPointer<Slider> sli_env_vel;
    ScopedPointer<Slider> sli_aenv_vel;
    ScopedPointer<Slider> swi_lfo1_sh;
    ScopedPointer<Slider> swi_lfo2_sh;
    ScopedPointer<Label> label48;
    ScopedPointer<Label> label49;
    ScopedPointer<Slider> sli_lfo1_freq;
    ScopedPointer<Label> label51;
    ScopedPointer<Label> label53;
    ScopedPointer<Label> label54;
    ScopedPointer<Label> label55;
    ScopedPointer<Label> label56;
    ScopedPointer<Label> label57;
    ScopedPointer<Label> label58;
    ScopedPointer<Label> label59;
    ScopedPointer<Label> label60;
    ScopedPointer<Label> label61;
    ScopedPointer<Slider> swi_o1_lfosrc;
    ScopedPointer<Slider> swi_o1_sh;
    ScopedPointer<Slider> swi_sub_sh;
    ScopedPointer<Slider> swi_sub_oct;
    ScopedPointer<Label> label62;
    ScopedPointer<Label> label63;
    ScopedPointer<Label> label64;
    ScopedPointer<Label> label65;
    ScopedPointer<Slider> swi_glide;
    ScopedPointer<Label> label69;
    ScopedPointer<Label> label23;
    ScopedPointer<Label> label72;
    ScopedPointer<Label> label73;
    ScopedPointer<Label> label74;
    ScopedPointer<Label> label75;
    ScopedPointer<Slider> swi_filt_lfosrc;
    ScopedPointer<Slider> swi_filt_kb;
    ScopedPointer<Label> label78;
    ScopedPointer<Slider> slider41;
    ScopedPointer<Label> label79;
    ScopedPointer<Label> label82;
    ScopedPointer<Label> label83;
    ScopedPointer<Slider> swi_o2_lfosrc;
    ScopedPointer<Label> label84;
    ScopedPointer<Label> label85;
    ScopedPointer<Label> label86;
    ScopedPointer<Slider> swi_o2_sh;
    ScopedPointer<Label> label87;
    ScopedPointer<Label> label88;
    ScopedPointer<Label> label90;
    ScopedPointer<Slider> swi_pitchmod_scale;
    ScopedPointer<Label> label91;
    ScopedPointer<Label> label92;
    ScopedPointer<Label> label93;
    ScopedPointer<Slider> swi_pitchmod_src;
    ScopedPointer<Label> label96;
    ScopedPointer<Slider> swi_lfo1_kb;
    ScopedPointer<Label> label50;
    ScopedPointer<Label> label52;
    ScopedPointer<Label> label47;
    ScopedPointer<Label> label97;
    ScopedPointer<Label> label98;
    ScopedPointer<Slider> swi_noise_color;
    ScopedPointer<Label> label99;
    ScopedPointer<Label> label100;
    ScopedPointer<Label> label101;
    ScopedPointer<Label> label105;
    ScopedPointer<Label> label106;
    ScopedPointer<Label> label107;
    ScopedPointer<Label> label108;
    ScopedPointer<Label> label109;
    ScopedPointer<Label> label111;
    ScopedPointer<Label> label112;
    ScopedPointer<Slider> swi_tune_type;
    ScopedPointer<Label> label113;
    ScopedPointer<Label> label114;
    ScopedPointer<Label> label115;
    ScopedPointer<Label> label116;
    ScopedPointer<Slider> swi_glide_type;
    ScopedPointer<Label> label117;
    ScopedPointer<Label> label118;
    ScopedPointer<Slider> sli_tune_instab;
    ScopedPointer<Slider> sli_shape_instab;
    ScopedPointer<Label> label119;
    ScopedPointer<Label> label120;
    ScopedPointer<Label> label22;
    ScopedPointer<Label> label121;
    ScopedPointer<Label> label122;
    ScopedPointer<Slider> swi_filt_lfosrc2;
    ScopedPointer<Label> label76;
    ScopedPointer<Label> label77;
    ScopedPointer<Label> label123;
    ScopedPointer<Label> label110;
    ScopedPointer<Label> label124;
    ScopedPointer<Label> label125;
    ScopedPointer<Label> label126;
    ScopedPointer<Label> label127;
    ScopedPointer<Label> label36;
    ScopedPointer<ComboBox> comboBox;
    ScopedPointer<Label> label12;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label15;
    ScopedPointer<Label> label16;
    ScopedPointer<Slider> swi_pitchmod_src2;
    ScopedPointer<Label> label104;
    ScopedPointer<Slider> swi_lfo1_kb2;
    ScopedPointer<Label> label37;
    ScopedPointer<Label> label43;
    ScopedPointer<Label> label46;
    ScopedPointer<Slider> swi_pitchmod_src3;
    ScopedPointer<Label> label66;
    ScopedPointer<Label> label40;
    ScopedPointer<Label> label41;
    ScopedPointer<Label> label44;
    ScopedPointer<Label> label68;
    ScopedPointer<Label> label81;
    ScopedPointer<Slider> sli_lfo2_sh;
    ScopedPointer<Label> label89;
    ScopedPointer<Label> label27;
    ScopedPointer<Label> label33;
    ScopedPointer<Slider> sli_lfo1_sh;
    ScopedPointer<Label> label34;
    ScopedPointer<Label> label35;
    ScopedPointer<Slider> swi_lfo2_att;
    ScopedPointer<Label> label38;
    ScopedPointer<Label> label39;
    ScopedPointer<Slider> swi_pitchmod_scale2;
    ScopedPointer<Label> label42;
    ScopedPointer<Label> label45;
    ScopedPointer<Label> label67;
    ScopedPointer<Label> label94;
    ScopedPointer<Slider> swi_pitchmod_dest2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainGui)
};

//[EndFile] You can add extra defines here...

} // namespace Gui

//[/EndFile]

#endif   // __JUCE_HEADER_ADBA7C90E028EAEC__
