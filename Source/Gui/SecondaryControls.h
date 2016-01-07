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

#ifndef __JUCE_HEADER_7123DAFC9A307C70__
#define __JUCE_HEADER_7123DAFC9A307C70__

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
class SecondaryControls  : public Component,
                           public SliderListener,
                           public ComboBoxListener
{
public:
    //==============================================================================
    SecondaryControls ();
    ~SecondaryControls();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> sli_filt_resbass;
    ScopedPointer<Label> label97;
    ScopedPointer<Label> label98;
    ScopedPointer<Slider> swi_noise_color;
    ScopedPointer<Label> label111;
    ScopedPointer<Label> label112;
    ScopedPointer<Slider> swi_tune_type;
    ScopedPointer<Label> label113;
    ScopedPointer<Label> label114;
    ScopedPointer<Label> label115;
    ScopedPointer<Label> label116;
    ScopedPointer<Slider> swi_glide_type;
    ScopedPointer<Label> label117;
    ScopedPointer<Slider> sli_tune_instab;
    ScopedPointer<Label> label119;
    ScopedPointer<Label> label22;
    ScopedPointer<Label> label121;
    ScopedPointer<Slider> swi_filt_lfosrc2;
    ScopedPointer<Label> label104;
    ScopedPointer<Slider> swi_lfo1_kb2;
    ScopedPointer<Label> label2;
    ScopedPointer<Slider> swi_filt_lfosrc3;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Slider> swi_glide_type2;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> label11;
    ScopedPointer<Slider> swi_glide_type3;
    ScopedPointer<Label> label12;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label34;
    ScopedPointer<Label> label35;
    ScopedPointer<Slider> swi_lfo2_att;
    ScopedPointer<Label> label3;
    ScopedPointer<ComboBox> comboBox;
    ScopedPointer<Slider> sli_bend_range;
    ScopedPointer<Label> label26;
    ScopedPointer<Label> label107;
    ScopedPointer<Label> label108;
    ScopedPointer<Label> label109;
    ScopedPointer<Label> label4;
    ScopedPointer<Slider> sli_tune_instab2;
    ScopedPointer<Slider> sli_shape_instab2;
    ScopedPointer<Label> label13;
    ScopedPointer<Label> label15;
    ScopedPointer<Slider> sli_shape_instab3;
    ScopedPointer<Label> label16;
    ScopedPointer<Label> label17;
    ScopedPointer<Label> label18;
    ScopedPointer<Slider> swi_tune_type2;
    ScopedPointer<Label> label19;
    ScopedPointer<Label> label20;
    ScopedPointer<Slider> swi_filt_lfosrc4;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SecondaryControls)
};

//[EndFile] You can add extra defines here...

} // namespace Gui

//[/EndFile]

#endif   // __JUCE_HEADER_7123DAFC9A307C70__
