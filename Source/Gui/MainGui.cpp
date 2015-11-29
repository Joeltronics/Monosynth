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

//[Headers] You can add your own extra header files here...

#include <math.h>
#include "Utils/Logger.h"

using namespace juce;

//[/Headers]

#include "MainGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

namespace Gui {

//[/MiscUserDefs]

//==============================================================================
MainGui::MainGui (MonosynthAudioProcessor& p)
    : processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
	LOG("Constructing MainGui");
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent12 = new GroupComponent ("new group",
                                                              TRANS("Effects")));
    groupComponent12->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent12->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent11 = new GroupComponent ("new group",
                                                              TRANS("Pitch Mod")));
    groupComponent11->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent11->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (label70 = new Label ("new label",
                                            TRANS("Osc 1")));
    label70->setFont (Font (12.00f, Font::plain));
    label70->setJustificationType (Justification::centredRight);
    label70->setEditable (false, false, false);
    label70->setColour (Label::textColourId, Colours::white);
    label70->setColour (TextEditor::textColourId, Colours::black);
    label70->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label80 = new Label ("new label",
                                            TRANS("1+2")));
    label80->setFont (Font (12.00f, Font::plain));
    label80->setJustificationType (Justification::centred);
    label80->setEditable (false, false, false);
    label80->setColour (Label::textColourId, Colours::white);
    label80->setColour (TextEditor::textColourId, Colours::black);
    label80->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_pitchmod_dest = new Slider ("new slider"));
    swi_pitchmod_dest->setRange (1, 2, 0.5);
    swi_pitchmod_dest->setSliderStyle (Slider::LinearHorizontal);
    swi_pitchmod_dest->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_pitchmod_dest->addListener (this);

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Mixer")));
    groupComponent2->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent2->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent6 = new GroupComponent ("new group",
                                                             TRANS("Overdrive & VCA")));
    groupComponent6->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent6->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent13 = new GroupComponent ("new group",
                                                              TRANS("Effects")));
    groupComponent13->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent13->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Filter")));
    groupComponent3->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent3->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (swi_filt_poles = new Slider ("Filter Poles"));
    swi_filt_poles->setRange (2, 4, 2);
    swi_filt_poles->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_poles->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_poles->addListener (this);

    addAndMakeVisible (groupComponent4 = new GroupComponent ("new group",
                                                             TRANS("Osc2")));
    groupComponent4->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent4->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Osc1")));
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_o1_sh = new Slider ("Osc 1 Shape"));
    sli_o1_sh->setRange (0, 10, 0);
    sli_o1_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o1_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o1_sh->addListener (this);

    addAndMakeVisible (groupComponent8 = new GroupComponent ("new group",
                                                             TRANS("Input")));
    groupComponent8->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent8->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent5 = new GroupComponent ("new group",
                                                             TRANS("Sub")));
    groupComponent5->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent5->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_o2_sh = new Slider ("Osc 2 Shape"));
    sli_o2_sh->setRange (0, 10, 0);
    sli_o2_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o2_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o2_sh->addListener (this);

    addAndMakeVisible (sli_mix_o1 = new Slider ("Osc 1 Mix"));
    sli_mix_o1->setRange (0, 10, 0);
    sli_mix_o1->setSliderStyle (Slider::LinearVertical);
    sli_mix_o1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mix_o1->addListener (this);

    addAndMakeVisible (sli_mix_o2 = new Slider ("Osc 2 Mix"));
    sli_mix_o2->setRange (0, 10, 0);
    sli_mix_o2->setSliderStyle (Slider::LinearVertical);
    sli_mix_o2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mix_o2->addListener (this);

    addAndMakeVisible (sli_mix_sub = new Slider ("Sub Mix"));
    sli_mix_sub->setRange (0, 10, 0);
    sli_mix_sub->setSliderStyle (Slider::LinearVertical);
    sli_mix_sub->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mix_sub->addListener (this);

    addAndMakeVisible (sli_mix_ring = new Slider ("Ring Mod Mix"));
    sli_mix_ring->setRange (0, 10, 0);
    sli_mix_ring->setSliderStyle (Slider::LinearVertical);
    sli_mix_ring->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mix_ring->addListener (this);

    addAndMakeVisible (sli_mix_noise = new Slider ("Noise Mix"));
    sli_mix_noise->setRange (0, 10, 0);
    sli_mix_noise->setSliderStyle (Slider::LinearVertical);
    sli_mix_noise->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mix_noise->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("1")));
    label->setFont (Font (12.00f, Font::plain));
    label->setJustificationType (Justification::centredTop);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("2\n")));
    label2->setFont (Font (12.00f, Font::plain));
    label2->setJustificationType (Justification::centredTop);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Sub")));
    label3->setFont (Font (12.00f, Font::plain));
    label3->setJustificationType (Justification::centredTop);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Ring")));
    label4->setFont (Font (12.00f, Font::plain));
    label4->setJustificationType (Justification::centredTop);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::white);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Noise")));
    label5->setFont (Font (12.00f, Font::plain));
    label5->setJustificationType (Justification::centredTop);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::white);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_o2_tune = new Slider ("Osc 2 Coarse Tune"));
    sli_o2_tune->setRange (-7, 19, 1);
    sli_o2_tune->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o2_tune->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o2_tune->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Tuning")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centred);
    label8->setEditable (false, false, false);
    label8->setColour (Label::textColourId, Colours::white);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_freq = new Slider ("Filter Frequency"));
    sli_filt_freq->setRange (0, 10, 0);
    sli_filt_freq->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_freq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_freq->addListener (this);

    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("Frequency")));
    label13->setFont (Font (15.00f, Font::plain));
    label13->setJustificationType (Justification::centred);
    label13->setEditable (false, false, false);
    label13->setColour (Label::textColourId, Colours::white);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_res = new Slider ("Filter Resonance"));
    sli_filt_res->setRange (0, 10, 0);
    sli_filt_res->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_res->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_res->addListener (this);

    addAndMakeVisible (sli_filt_env = new Slider ("Filter Env Amount"));
    sli_filt_env->setRange (-1, 1, 0);
    sli_filt_env->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_env->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_env->addListener (this);

    addAndMakeVisible (sli_filt_lfo = new Slider ("Filter LFO Amount"));
    sli_filt_lfo->setRange (0, 1, 0);
    sli_filt_lfo->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_lfo->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_lfo->addListener (this);

    addAndMakeVisible (sli_drive = new Slider ("Overdrive"));
    sli_drive->setRange (0, 10, 0);
    sli_drive->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_drive->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_drive->addListener (this);

    addAndMakeVisible (sli_o2_mod = new Slider ("new slider"));
    sli_o2_mod->setRange (0, 10, 0);
    sli_o2_mod->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o2_mod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o2_mod->addListener (this);

    addAndMakeVisible (sli_o1_mod = new Slider ("new slider"));
    sli_o1_mod->setRange (0, 10, 0);
    sli_o1_mod->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o1_mod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o1_mod->addListener (this);

    addAndMakeVisible (sli_o2_finetune = new Slider ("Osc 2 Fine Tune"));
    sli_o2_finetune->setRange (-1, 1, 0);
    sli_o2_finetune->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o2_finetune->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o2_finetune->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Fine")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colours::white);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Env")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centred);
    label9->setEditable (false, false, false);
    label9->setColour (Label::textColourId, Colours::white);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Resonance")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centred);
    label10->setEditable (false, false, false);
    label10->setColour (Label::textColourId, Colours::white);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Overdrive")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centred);
    label11->setEditable (false, false, false);
    label11->setColour (Label::textColourId, Colours::white);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent7 = new GroupComponent ("new group",
                                                             TRANS("Envelope")));
    groupComponent7->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent7->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_env_att = new Slider ("Env Attack"));
    sli_env_att->setRange (0, 10, 0);
    sli_env_att->setSliderStyle (Slider::LinearVertical);
    sli_env_att->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_att->addListener (this);

    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("A")));
    label17->setFont (Font (12.00f, Font::plain));
    label17->setJustificationType (Justification::centred);
    label17->setEditable (false, false, false);
    label17->setColour (Label::textColourId, Colours::white);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("D")));
    label18->setFont (Font (12.00f, Font::plain));
    label18->setJustificationType (Justification::centred);
    label18->setEditable (false, false, false);
    label18->setColour (Label::textColourId, Colours::white);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label19 = new Label ("new label",
                                            TRANS("S")));
    label19->setFont (Font (12.00f, Font::plain));
    label19->setJustificationType (Justification::centred);
    label19->setEditable (false, false, false);
    label19->setColour (Label::textColourId, Colours::white);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("R")));
    label20->setFont (Font (12.00f, Font::plain));
    label20->setJustificationType (Justification::centred);
    label20->setEditable (false, false, false);
    label20->setColour (Label::textColourId, Colours::white);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_gain = new Slider ("Filter Gain"));
    sli_filt_gain->setRange (0, 10, 0);
    sli_filt_gain->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_gain->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_gain->addListener (this);

    addAndMakeVisible (label21 = new Label ("new label",
                                            TRANS("Gain")));
    label21->setFont (Font (15.00f, Font::plain));
    label21->setJustificationType (Justification::centred);
    label21->setEditable (false, false, false);
    label21->setColour (Label::textColourId, Colours::white);
    label21->setColour (TextEditor::textColourId, Colours::black);
    label21->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_pitchmod_amt = new Slider ("new slider"));
    sli_pitchmod_amt->setRange (0, 10, 0);
    sli_pitchmod_amt->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_pitchmod_amt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_pitchmod_amt->addListener (this);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("LFO")));
    label7->setFont (Font (12.00f, Font::plain));
    label7->setJustificationType (Justification::centred);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colours::white);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label25 = new Label ("new label",
                                            TRANS("LFO")));
    label25->setFont (Font (12.00f, Font::plain));
    label25->setJustificationType (Justification::centred);
    label25->setEditable (false, false, false);
    label25->setColour (Label::textColourId, Colours::white);
    label25->setColour (TextEditor::textColourId, Colours::black);
    label25->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent9 = new GroupComponent ("new group",
                                                             TRANS("LFO1")));
    groupComponent9->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent9->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent10 = new GroupComponent ("new group",
                                                              TRANS("LFO2")));
    groupComponent10->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent10->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_glide_amt = new Slider ("new slider"));
    sli_glide_amt->setRange (0, 10, 0);
    sli_glide_amt->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_glide_amt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_glide_amt->addListener (this);

    addAndMakeVisible (sli_bend_range = new Slider ("new slider"));
    sli_bend_range->setRange (1, 13, 1);
    sli_bend_range->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_bend_range->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_bend_range->addListener (this);

    addAndMakeVisible (label26 = new Label ("new label",
                                            TRANS("Bend Range")));
    label26->setFont (Font (15.00f, Font::plain));
    label26->setJustificationType (Justification::centred);
    label26->setEditable (false, false, false);
    label26->setColour (Label::textColourId, Colours::white);
    label26->setColour (TextEditor::textColourId, Colours::black);
    label26->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label28 = new Label ("new label",
                                            TRANS("Freq")));
    label28->setFont (Font (12.00f, Font::plain));
    label28->setJustificationType (Justification::centred);
    label28->setEditable (false, false, false);
    label28->setColour (Label::textColourId, Colours::white);
    label28->setColour (TextEditor::textColourId, Colours::black);
    label28->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_lfo2_freq = new Slider ("LFO 2 Freq"));
    sli_lfo2_freq->setRange (0, 10, 0);
    sli_lfo2_freq->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_lfo2_freq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_lfo2_freq->addListener (this);

    addAndMakeVisible (label29 = new Label ("new label",
                                            TRANS("Freq")));
    label29->setFont (Font (12.00f, Font::plain));
    label29->setJustificationType (Justification::centred);
    label29->setEditable (false, false, false);
    label29->setColour (Label::textColourId, Colours::white);
    label29->setColour (TextEditor::textColourId, Colours::black);
    label29->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_lfo2_att = new Slider ("LFO 1 Attack"));
    sli_lfo2_att->setRange (0, 10, 0);
    sli_lfo2_att->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_lfo2_att->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_lfo2_att->addListener (this);

    addAndMakeVisible (label31 = new Label ("new label",
                                            TRANS("Attack")));
    label31->setFont (Font (12.00f, Font::plain));
    label31->setJustificationType (Justification::centred);
    label31->setEditable (false, false, false);
    label31->setColour (Label::textColourId, Colours::white);
    label31->setColour (TextEditor::textColourId, Colours::black);
    label31->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label30 = new Label ("new label",
                                            TRANS("Vel")));
    label30->setFont (Font (15.00f, Font::plain));
    label30->setJustificationType (Justification::centred);
    label30->setEditable (false, false, false);
    label30->setColour (Label::textColourId, Colours::white);
    label30->setColour (TextEditor::textColourId, Colours::black);
    label30->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_vel = new Slider ("Filter Vel Amount"));
    sli_filt_vel->setRange (0, 1, 0);
    sli_filt_vel->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_vel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_vel->addListener (this);

    addAndMakeVisible (sli_env_dec = new Slider ("Env Decay"));
    sli_env_dec->setRange (0, 10, 0);
    sli_env_dec->setSliderStyle (Slider::LinearVertical);
    sli_env_dec->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_dec->addListener (this);

    addAndMakeVisible (sli_env_sus = new Slider ("Env Sustain"));
    sli_env_sus->setRange (0, 10, 0);
    sli_env_sus->setSliderStyle (Slider::LinearVertical);
    sli_env_sus->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_sus->addListener (this);

    addAndMakeVisible (sli_env_rel = new Slider ("Env Release"));
    sli_env_rel->setRange (0, 10, 0);
    sli_env_rel->setSliderStyle (Slider::LinearVertical);
    sli_env_rel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_rel->addListener (this);

    addAndMakeVisible (sli_pitchmod_scale = new Slider ("new slider"));
    sli_pitchmod_scale->setRange (0, 10, 0);
    sli_pitchmod_scale->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_pitchmod_scale->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_pitchmod_scale->addListener (this);

    addAndMakeVisible (label32 = new Label ("new label",
                                            TRANS("LFO")));
    label32->setFont (Font (15.00f, Font::plain));
    label32->setJustificationType (Justification::centred);
    label32->setEditable (false, false, false);
    label32->setColour (Label::textColourId, Colours::white);
    label32->setColour (TextEditor::textColourId, Colours::black);
    label32->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label24 = new Label ("new label",
                                            TRANS("Vel to\n"
                                            "Time")));
    label24->setFont (Font (15.00f, Font::plain));
    label24->setJustificationType (Justification::centred);
    label24->setEditable (false, false, false);
    label24->setColour (Label::textColourId, Colours::white);
    label24->setColour (TextEditor::textColourId, Colours::black);
    label24->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_env_vel = new Slider ("Filt Env Velocity"));
    sli_env_vel->setRange (0, 10, 0);
    sli_env_vel->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_env_vel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel->addListener (this);

    addAndMakeVisible (sli_aenv_vel = new Slider ("Amp Env Velocity"));
    sli_aenv_vel->setRange (0, 10, 0);
    sli_aenv_vel->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_aenv_vel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_aenv_vel->addListener (this);

    addAndMakeVisible (swi_lfo1_sh = new Slider ("LFO 1 Shape"));
    swi_lfo1_sh->setRange (1, 5, 1);
    swi_lfo1_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    swi_lfo1_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo1_sh->addListener (this);

    addAndMakeVisible (swi_lfo2_sh = new Slider ("LFO 2 Shape"));
    swi_lfo2_sh->setRange (1, 6, 1);
    swi_lfo2_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    swi_lfo2_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo2_sh->addListener (this);

    addAndMakeVisible (label48 = new Label ("new label",
                                            TRANS("0")));
    label48->setFont (Font (12.00f, Font::plain));
    label48->setJustificationType (Justification::centred);
    label48->setEditable (false, false, false);
    label48->setColour (Label::textColourId, Colours::white);
    label48->setColour (TextEditor::textColourId, Colours::black);
    label48->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label49 = new Label ("new label",
                                            TRANS("+12")));
    label49->setFont (Font (12.00f, Font::plain));
    label49->setJustificationType (Justification::centredLeft);
    label49->setEditable (false, false, false);
    label49->setColour (Label::textColourId, Colours::white);
    label49->setColour (TextEditor::textColourId, Colours::black);
    label49->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_lfo1_freq = new Slider ("LFO 1 Freq"));
    sli_lfo1_freq->setRange (0, 10, 0);
    sli_lfo1_freq->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_lfo1_freq->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_lfo1_freq->addListener (this);

    addAndMakeVisible (label51 = new Label ("new label",
                                            TRANS("Saw")));
    label51->setFont (Font (12.00f, Font::plain));
    label51->setJustificationType (Justification::centredLeft);
    label51->setEditable (false, false, false);
    label51->setColour (Label::textColourId, Colours::white);
    label51->setColour (TextEditor::textColourId, Colours::black);
    label51->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label53 = new Label ("new label",
                                            TRANS("Rect")));
    label53->setFont (Font (12.00f, Font::plain));
    label53->setJustificationType (Justification::centredLeft);
    label53->setEditable (false, false, false);
    label53->setColour (Label::textColourId, Colours::white);
    label53->setColour (TextEditor::textColourId, Colours::black);
    label53->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label54 = new Label ("new label",
                                            TRANS("Tri")));
    label54->setFont (Font (12.00f, Font::plain));
    label54->setJustificationType (Justification::centredLeft);
    label54->setEditable (false, false, false);
    label54->setColour (Label::textColourId, Colours::white);
    label54->setColour (TextEditor::textColourId, Colours::black);
    label54->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label55 = new Label ("new label",
                                            TRANS("Pulse")));
    label55->setFont (Font (12.00f, Font::plain));
    label55->setJustificationType (Justification::centredLeft);
    label55->setEditable (false, false, false);
    label55->setColour (Label::textColourId, Colours::white);
    label55->setColour (TextEditor::textColourId, Colours::black);
    label55->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label56 = new Label ("new label",
                                            TRANS("Squ")));
    label56->setFont (Font (12.00f, Font::plain));
    label56->setJustificationType (Justification::centredLeft);
    label56->setEditable (false, false, false);
    label56->setColour (Label::textColourId, Colours::white);
    label56->setColour (TextEditor::textColourId, Colours::black);
    label56->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label57 = new Label ("new label",
                                            TRANS("Tri")));
    label57->setFont (Font (12.00f, Font::plain));
    label57->setJustificationType (Justification::centredLeft);
    label57->setEditable (false, false, false);
    label57->setColour (Label::textColourId, Colours::white);
    label57->setColour (TextEditor::textColourId, Colours::black);
    label57->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label58 = new Label ("new label",
                                            TRANS("-1")));
    label58->setFont (Font (10.00f, Font::plain));
    label58->setJustificationType (Justification::centredRight);
    label58->setEditable (false, false, false);
    label58->setColour (Label::textColourId, Colours::white);
    label58->setColour (TextEditor::textColourId, Colours::black);
    label58->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label59 = new Label ("new label",
                                            TRANS("-2")));
    label59->setFont (Font (10.00f, Font::plain));
    label59->setJustificationType (Justification::centredRight);
    label59->setEditable (false, false, false);
    label59->setColour (Label::textColourId, Colours::white);
    label59->setColour (TextEditor::textColourId, Colours::black);
    label59->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label60 = new Label ("new label",
                                            TRANS("2")));
    label60->setFont (Font (12.00f, Font::plain));
    label60->setJustificationType (Justification::centredLeft);
    label60->setEditable (false, false, false);
    label60->setColour (Label::textColourId, Colours::white);
    label60->setColour (TextEditor::textColourId, Colours::black);
    label60->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label61 = new Label ("new label",
                                            TRANS("1")));
    label61->setFont (Font (12.00f, Font::plain));
    label61->setJustificationType (Justification::centredRight);
    label61->setEditable (false, false, false);
    label61->setColour (Label::textColourId, Colours::white);
    label61->setColour (TextEditor::textColourId, Colours::black);
    label61->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_o1_lfosrc = new Slider ("new slider"));
    swi_o1_lfosrc->setRange (1, 2, 1);
    swi_o1_lfosrc->setSliderStyle (Slider::LinearHorizontal);
    swi_o1_lfosrc->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o1_lfosrc->addListener (this);

    addAndMakeVisible (swi_o1_sh = new Slider ("Osc 1 Wave"));
    swi_o1_sh->setRange (0, 2, 1);
    swi_o1_sh->setSliderStyle (Slider::LinearVertical);
    swi_o1_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o1_sh->addListener (this);

    addAndMakeVisible (swi_sub_sh = new Slider ("Sub Osc Wave"));
    swi_sub_sh->setRange (0, 2, 1);
    swi_sub_sh->setSliderStyle (Slider::LinearVertical);
    swi_sub_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_sub_sh->addListener (this);

    addAndMakeVisible (swi_sub_oct = new Slider ("Sub Osc Octave"));
    swi_sub_oct->setRange (-2, -1, 1);
    swi_sub_oct->setSliderStyle (Slider::LinearVertical);
    swi_sub_oct->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_sub_oct->addListener (this);

    addAndMakeVisible (label62 = new Label ("new label",
                                            TRANS("Glide")));
    label62->setFont (Font (15.00f, Font::plain));
    label62->setJustificationType (Justification::centred);
    label62->setEditable (false, false, false);
    label62->setColour (Label::textColourId, Colours::white);
    label62->setColour (TextEditor::textColourId, Colours::black);
    label62->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label63 = new Label ("new label",
                                            TRANS("On")));
    label63->setFont (Font (12.00f, Font::plain));
    label63->setJustificationType (Justification::centredLeft);
    label63->setEditable (false, false, false);
    label63->setColour (Label::textColourId, Colours::white);
    label63->setColour (TextEditor::textColourId, Colours::black);
    label63->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label64 = new Label ("new label",
                                            TRANS("Legato")));
    label64->setFont (Font (12.00f, Font::plain));
    label64->setJustificationType (Justification::centredLeft);
    label64->setEditable (false, false, false);
    label64->setColour (Label::textColourId, Colours::white);
    label64->setColour (TextEditor::textColourId, Colours::black);
    label64->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label65 = new Label ("new label",
                                            TRANS("Off")));
    label65->setFont (Font (12.00f, Font::plain));
    label65->setJustificationType (Justification::centredLeft);
    label65->setEditable (false, false, false);
    label65->setColour (Label::textColourId, Colours::white);
    label65->setColour (TextEditor::textColourId, Colours::black);
    label65->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_glide = new Slider ("new slider"));
    swi_glide->setRange (0, 2, 1);
    swi_glide->setSliderStyle (Slider::LinearVertical);
    swi_glide->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_glide->addListener (this);

    addAndMakeVisible (label69 = new Label ("new label",
                                            TRANS("Osc 2")));
    label69->setFont (Font (12.00f, Font::plain));
    label69->setJustificationType (Justification::centredLeft);
    label69->setEditable (false, false, false);
    label69->setColour (Label::textColourId, Colours::white);
    label69->setColour (TextEditor::textColourId, Colours::black);
    label69->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label23 = new Label ("new label",
                                            TRANS("4")));
    label23->setFont (Font (12.00f, Font::plain));
    label23->setJustificationType (Justification::centredLeft);
    label23->setEditable (false, false, false);
    label23->setColour (Label::textColourId, Colours::white);
    label23->setColour (TextEditor::textColourId, Colours::black);
    label23->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label72 = new Label ("new label",
                                            TRANS("2")));
    label72->setFont (Font (12.00f, Font::plain));
    label72->setJustificationType (Justification::centredRight);
    label72->setEditable (false, false, false);
    label72->setColour (Label::textColourId, Colours::white);
    label72->setColour (TextEditor::textColourId, Colours::black);
    label72->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label73 = new Label ("new label",
                                            TRANS("Poles")));
    label73->setFont (Font (12.00f, Font::plain));
    label73->setJustificationType (Justification::centred);
    label73->setEditable (false, false, false);
    label73->setColour (Label::textColourId, Colours::white);
    label73->setColour (TextEditor::textColourId, Colours::black);
    label73->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label74 = new Label ("new label",
                                            TRANS("2")));
    label74->setFont (Font (12.00f, Font::plain));
    label74->setJustificationType (Justification::centredLeft);
    label74->setEditable (false, false, false);
    label74->setColour (Label::textColourId, Colours::white);
    label74->setColour (TextEditor::textColourId, Colours::black);
    label74->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label75 = new Label ("new label",
                                            TRANS("1")));
    label75->setFont (Font (12.00f, Font::plain));
    label75->setJustificationType (Justification::centredRight);
    label75->setEditable (false, false, false);
    label75->setColour (Label::textColourId, Colours::white);
    label75->setColour (TextEditor::textColourId, Colours::black);
    label75->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_lfosrc = new Slider ("Filter LFO Select"));
    swi_filt_lfosrc->setRange (0, 1, 1);
    swi_filt_lfosrc->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_lfosrc->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_lfosrc->addListener (this);

    addAndMakeVisible (swi_filt_kb = new Slider ("Filter KB Track"));
    swi_filt_kb->setRange (0, 1, 1);
    swi_filt_kb->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_kb->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_kb->addListener (this);

    addAndMakeVisible (label78 = new Label ("new label",
                                            TRANS("KB Track")));
    label78->setFont (Font (12.00f, Font::plain));
    label78->setJustificationType (Justification::centred);
    label78->setEditable (false, false, false);
    label78->setColour (Label::textColourId, Colours::white);
    label78->setColour (TextEditor::textColourId, Colours::black);
    label78->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (slider41 = new Slider ("new slider"));
    slider41->setRange (0, 1, 1);
    slider41->setSliderStyle (Slider::LinearHorizontal);
    slider41->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider41->addListener (this);

    addAndMakeVisible (label79 = new Label ("new label",
                                            TRANS("Sync")));
    label79->setFont (Font (12.00f, Font::plain));
    label79->setJustificationType (Justification::centredLeft);
    label79->setEditable (false, false, false);
    label79->setColour (Label::textColourId, Colours::white);
    label79->setColour (TextEditor::textColourId, Colours::black);
    label79->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label82 = new Label ("new label",
                                            TRANS("2")));
    label82->setFont (Font (12.00f, Font::plain));
    label82->setJustificationType (Justification::centredLeft);
    label82->setEditable (false, false, false);
    label82->setColour (Label::textColourId, Colours::white);
    label82->setColour (TextEditor::textColourId, Colours::black);
    label82->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label83 = new Label ("new label",
                                            TRANS("1")));
    label83->setFont (Font (12.00f, Font::plain));
    label83->setJustificationType (Justification::centredRight);
    label83->setEditable (false, false, false);
    label83->setColour (Label::textColourId, Colours::white);
    label83->setColour (TextEditor::textColourId, Colours::black);
    label83->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_o2_lfosrc = new Slider ("new slider"));
    swi_o2_lfosrc->setRange (1, 2, 1);
    swi_o2_lfosrc->setSliderStyle (Slider::LinearHorizontal);
    swi_o2_lfosrc->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o2_lfosrc->addListener (this);

    addAndMakeVisible (label84 = new Label ("new label",
                                            TRANS("Saw")));
    label84->setFont (Font (12.00f, Font::plain));
    label84->setJustificationType (Justification::centredLeft);
    label84->setEditable (false, false, false);
    label84->setColour (Label::textColourId, Colours::white);
    label84->setColour (TextEditor::textColourId, Colours::black);
    label84->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label85 = new Label ("new label",
                                            TRANS("Rect")));
    label85->setFont (Font (12.00f, Font::plain));
    label85->setJustificationType (Justification::centredLeft);
    label85->setEditable (false, false, false);
    label85->setColour (Label::textColourId, Colours::white);
    label85->setColour (TextEditor::textColourId, Colours::black);
    label85->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label86 = new Label ("new label",
                                            TRANS("Tri")));
    label86->setFont (Font (12.00f, Font::plain));
    label86->setJustificationType (Justification::centredLeft);
    label86->setEditable (false, false, false);
    label86->setColour (Label::textColourId, Colours::white);
    label86->setColour (TextEditor::textColourId, Colours::black);
    label86->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_o2_sh = new Slider ("Osc 2 Wave"));
    swi_o2_sh->setRange (0, 2, 1);
    swi_o2_sh->setSliderStyle (Slider::LinearVertical);
    swi_o2_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o2_sh->addListener (this);

    addAndMakeVisible (label87 = new Label ("new label",
                                            TRANS("Scale By")));
    label87->setFont (Font (15.00f, Font::plain));
    label87->setJustificationType (Justification::centred);
    label87->setEditable (false, false, false);
    label87->setColour (Label::textColourId, Colours::white);
    label87->setColour (TextEditor::textColourId, Colours::black);
    label87->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label88 = new Label ("new label",
                                            TRANS("Vel")));
    label88->setFont (Font (12.00f, Font::plain));
    label88->setJustificationType (Justification::centredLeft);
    label88->setEditable (false, false, false);
    label88->setColour (Label::textColourId, Colours::white);
    label88->setColour (TextEditor::textColourId, Colours::black);
    label88->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label90 = new Label ("new label",
                                            TRANS("Mod Wh")));
    label90->setFont (Font (12.00f, Font::plain));
    label90->setJustificationType (Justification::centredLeft);
    label90->setEditable (false, false, false);
    label90->setColour (Label::textColourId, Colours::white);
    label90->setColour (TextEditor::textColourId, Colours::black);
    label90->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_pitchmod_scale = new Slider ("new slider"));
    swi_pitchmod_scale->setRange (0, 1, 1);
    swi_pitchmod_scale->setSliderStyle (Slider::LinearVertical);
    swi_pitchmod_scale->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_pitchmod_scale->addListener (this);

    addAndMakeVisible (label91 = new Label ("new label",
                                            TRANS("LFO1")));
    label91->setFont (Font (12.00f, Font::plain));
    label91->setJustificationType (Justification::centredLeft);
    label91->setEditable (false, false, false);
    label91->setColour (Label::textColourId, Colours::white);
    label91->setColour (TextEditor::textColourId, Colours::black);
    label91->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label92 = new Label ("new label",
                                            TRANS("LFO2")));
    label92->setFont (Font (12.00f, Font::plain));
    label92->setJustificationType (Justification::centredLeft);
    label92->setEditable (false, false, false);
    label92->setColour (Label::textColourId, Colours::white);
    label92->setColour (TextEditor::textColourId, Colours::black);
    label92->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label93 = new Label ("new label",
                                            TRANS("Env")));
    label93->setFont (Font (12.00f, Font::plain));
    label93->setJustificationType (Justification::centredLeft);
    label93->setEditable (false, false, false);
    label93->setColour (Label::textColourId, Colours::white);
    label93->setColour (TextEditor::textColourId, Colours::black);
    label93->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_pitchmod_src = new Slider ("new slider"));
    swi_pitchmod_src->setRange (0, 2, 1);
    swi_pitchmod_src->setSliderStyle (Slider::LinearVertical);
    swi_pitchmod_src->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_pitchmod_src->addListener (this);

    addAndMakeVisible (label96 = new Label ("new label",
                                            TRANS("KB")));
    label96->setFont (Font (12.00f, Font::plain));
    label96->setJustificationType (Justification::centredLeft);
    label96->setEditable (false, false, false);
    label96->setColour (Label::textColourId, Colours::white);
    label96->setColour (TextEditor::textColourId, Colours::black);
    label96->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_lfo1_kb = new Slider ("new slider"));
    swi_lfo1_kb->setRange (0, 1, 1);
    swi_lfo1_kb->setSliderStyle (Slider::LinearHorizontal);
    swi_lfo1_kb->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo1_kb->addListener (this);

    addAndMakeVisible (label50 = new Label ("new label",
                                            TRANS("-1")));
    label50->setFont (Font (12.00f, Font::plain));
    label50->setJustificationType (Justification::centred);
    label50->setEditable (false, false, false);
    label50->setColour (Label::textColourId, Colours::white);
    label50->setColour (TextEditor::textColourId, Colours::black);
    label50->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label52 = new Label ("new label",
                                            TRANS("+1")));
    label52->setFont (Font (12.00f, Font::plain));
    label52->setJustificationType (Justification::centred);
    label52->setEditable (false, false, false);
    label52->setColour (Label::textColourId, Colours::white);
    label52->setColour (TextEditor::textColourId, Colours::black);
    label52->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label47 = new Label ("new label",
                                            TRANS("0")));
    label47->setFont (Font (12.00f, Font::plain));
    label47->setJustificationType (Justification::centredRight);
    label47->setEditable (false, false, false);
    label47->setColour (Label::textColourId, Colours::white);
    label47->setColour (TextEditor::textColourId, Colours::black);
    label47->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label100 = new Label ("new label",
                                             TRANS("Shape")));
    label100->setFont (Font (12.00f, Font::plain));
    label100->setJustificationType (Justification::centred);
    label100->setEditable (false, false, false);
    label100->setColour (Label::textColourId, Colours::white);
    label100->setColour (TextEditor::textColourId, Colours::black);
    label100->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label101 = new Label ("new label",
                                             TRANS("Shape")));
    label101->setFont (Font (12.00f, Font::plain));
    label101->setJustificationType (Justification::centred);
    label101->setEditable (false, false, false);
    label101->setColour (Label::textColourId, Colours::white);
    label101->setColour (TextEditor::textColourId, Colours::black);
    label101->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label105 = new Label ("new label",
                                             TRANS("Amt")));
    label105->setFont (Font (15.00f, Font::plain));
    label105->setJustificationType (Justification::centred);
    label105->setEditable (false, false, false);
    label105->setColour (Label::textColourId, Colours::white);
    label105->setColour (TextEditor::textColourId, Colours::black);
    label105->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label106 = new Label ("new label",
                                             TRANS("Source")));
    label106->setFont (Font (15.00f, Font::plain));
    label106->setJustificationType (Justification::centred);
    label106->setEditable (false, false, false);
    label106->setColour (Label::textColourId, Colours::white);
    label106->setColour (TextEditor::textColourId, Colours::black);
    label106->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label107 = new Label ("new label",
                                             TRANS("1")));
    label107->setFont (Font (12.00f, Font::plain));
    label107->setJustificationType (Justification::centred);
    label107->setEditable (false, false, false);
    label107->setColour (Label::textColourId, Colours::white);
    label107->setColour (TextEditor::textColourId, Colours::black);
    label107->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label108 = new Label ("new label",
                                             TRANS("24")));
    label108->setFont (Font (12.00f, Font::plain));
    label108->setJustificationType (Justification::centred);
    label108->setEditable (false, false, false);
    label108->setColour (Label::textColourId, Colours::white);
    label108->setColour (TextEditor::textColourId, Colours::black);
    label108->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label109 = new Label ("new label",
                                             TRANS("12")));
    label109->setFont (Font (12.00f, Font::plain));
    label109->setJustificationType (Justification::centred);
    label109->setEditable (false, false, false);
    label109->setColour (Label::textColourId, Colours::white);
    label109->setColour (TextEditor::textColourId, Colours::black);
    label109->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label76 = new Label ("new label",
                                            TRANS("+")));
    label76->setFont (Font (12.00f, Font::plain));
    label76->setJustificationType (Justification::centredLeft);
    label76->setEditable (false, false, false);
    label76->setColour (Label::textColourId, Colours::white);
    label76->setColour (TextEditor::textColourId, Colours::black);
    label76->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label77 = new Label ("new label",
                                            TRANS("-")));
    label77->setFont (Font (12.00f, Font::plain));
    label77->setJustificationType (Justification::centredRight);
    label77->setEditable (false, false, false);
    label77->setColour (Label::textColourId, Colours::white);
    label77->setColour (TextEditor::textColourId, Colours::black);
    label77->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label123 = new Label ("new label",
                                             TRANS("+7")));
    label123->setFont (Font (12.00f, Font::plain));
    label123->setJustificationType (Justification::centred);
    label123->setEditable (false, false, false);
    label123->setColour (Label::textColourId, Colours::white);
    label123->setColour (TextEditor::textColourId, Colours::black);
    label123->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label110 = new Label ("new label",
                                             TRANS("20")));
    label110->setFont (Font (12.00f, Font::plain));
    label110->setJustificationType (Justification::centredRight);
    label110->setEditable (false, false, false);
    label110->setColour (Label::textColourId, Colours::white);
    label110->setColour (TextEditor::textColourId, Colours::black);
    label110->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label124 = new Label ("new label",
                                             TRANS("20k")));
    label124->setFont (Font (12.00f, Font::plain));
    label124->setJustificationType (Justification::centredLeft);
    label124->setEditable (false, false, false);
    label124->setColour (Label::textColourId, Colours::white);
    label124->setColour (TextEditor::textColourId, Colours::black);
    label124->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label125 = new Label ("new label",
                                             TRANS("100")));
    label125->setFont (Font (12.00f, Font::plain));
    label125->setJustificationType (Justification::centredRight);
    label125->setEditable (false, false, false);
    label125->setColour (Label::textColourId, Colours::white);
    label125->setColour (TextEditor::textColourId, Colours::black);
    label125->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label126 = new Label ("new label",
                                             TRANS("1k")));
    label126->setFont (Font (12.00f, Font::plain));
    label126->setJustificationType (Justification::centredLeft);
    label126->setEditable (false, false, false);
    label126->setColour (Label::textColourId, Colours::white);
    label126->setColour (TextEditor::textColourId, Colours::black);
    label126->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label127 = new Label ("new label",
                                             TRANS("10k")));
    label127->setFont (Font (12.00f, Font::plain));
    label127->setJustificationType (Justification::centredLeft);
    label127->setEditable (false, false, false);
    label127->setColour (Label::textColourId, Colours::white);
    label127->setColour (TextEditor::textColourId, Colours::black);
    label127->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label36 = new Label ("new label",
                                            TRANS("Velocity")));
    label36->setFont (Font (15.00f, Font::plain));
    label36->setJustificationType (Justification::centred);
    label36->setEditable (false, false, false);
    label36->setColour (Label::textColourId, Colours::white);
    label36->setColour (TextEditor::textColourId, Colours::black);
    label36->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Pre-Filt")));
    label14->setFont (Font (12.00f, Font::plain));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (Label::textColourId, Colours::white);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("Pre-Drive")));
    label15->setFont (Font (12.00f, Font::plain));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (Label::textColourId, Colours::white);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label16 = new Label ("new label",
                                            TRANS("Post-Drive")));
    label16->setFont (Font (12.00f, Font::plain));
    label16->setJustificationType (Justification::centredLeft);
    label16->setEditable (false, false, false);
    label16->setColour (Label::textColourId, Colours::white);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_pitchmod_src2 = new Slider ("new slider"));
    swi_pitchmod_src2->setRange (0, 2, 1);
    swi_pitchmod_src2->setSliderStyle (Slider::LinearVertical);
    swi_pitchmod_src2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_pitchmod_src2->addListener (this);

    addAndMakeVisible (label66 = new Label ("new label",
                                            TRANS("S&H")));
    label66->setFont (Font (12.00f, Font::plain));
    label66->setJustificationType (Justification::centredLeft);
    label66->setEditable (false, false, false);
    label66->setColour (Label::textColourId, Colours::white);
    label66->setColour (TextEditor::textColourId, Colours::black);
    label66->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label40 = new Label ("new label",
                                            TRANS("Tri/Squ")));
    label40->setFont (Font (12.00f, Font::plain));
    label40->setJustificationType (Justification::centredRight);
    label40->setEditable (false, false, false);
    label40->setColour (Label::textColourId, Colours::white);
    label40->setColour (TextEditor::textColourId, Colours::black);
    label40->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label41 = new Label ("new label",
                                            TRANS("Saw")));
    label41->setFont (Font (12.00f, Font::plain));
    label41->setJustificationType (Justification::centred);
    label41->setEditable (false, false, false);
    label41->setColour (Label::textColourId, Colours::white);
    label41->setColour (TextEditor::textColourId, Colours::black);
    label41->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label44 = new Label ("new label",
                                            TRANS("Env")));
    label44->setFont (Font (12.00f, Font::plain));
    label44->setJustificationType (Justification::centredLeft);
    label44->setEditable (false, false, false);
    label44->setColour (Label::textColourId, Colours::white);
    label44->setColour (TextEditor::textColourId, Colours::black);
    label44->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label68 = new Label ("new label",
                                            TRANS("S&H")));
    label68->setFont (Font (12.00f, Font::plain));
    label68->setJustificationType (Justification::centredLeft);
    label68->setEditable (false, false, false);
    label68->setColour (Label::textColourId, Colours::white);
    label68->setColour (TextEditor::textColourId, Colours::black);
    label68->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label81 = new Label ("new label",
                                            TRANS("Shape")));
    label81->setFont (Font (12.00f, Font::plain));
    label81->setJustificationType (Justification::centred);
    label81->setEditable (false, false, false);
    label81->setColour (Label::textColourId, Colours::white);
    label81->setColour (TextEditor::textColourId, Colours::black);
    label81->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_lfo2_sh = new Slider ("LFO 2 Shape Tweak"));
    sli_lfo2_sh->setRange (0, 10, 0);
    sli_lfo2_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_lfo2_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_lfo2_sh->addListener (this);

    addAndMakeVisible (label89 = new Label ("new label",
                                            TRANS("Shape")));
    label89->setFont (Font (12.00f, Font::plain));
    label89->setJustificationType (Justification::centred);
    label89->setEditable (false, false, false);
    label89->setColour (Label::textColourId, Colours::white);
    label89->setColour (TextEditor::textColourId, Colours::black);
    label89->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label27 = new Label ("new label",
                                            TRANS("Tri/Squ")));
    label27->setFont (Font (12.00f, Font::plain));
    label27->setJustificationType (Justification::centredRight);
    label27->setEditable (false, false, false);
    label27->setColour (Label::textColourId, Colours::white);
    label27->setColour (TextEditor::textColourId, Colours::black);
    label27->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label33 = new Label ("new label",
                                            TRANS("Saw")));
    label33->setFont (Font (12.00f, Font::plain));
    label33->setJustificationType (Justification::centred);
    label33->setEditable (false, false, false);
    label33->setColour (Label::textColourId, Colours::white);
    label33->setColour (TextEditor::textColourId, Colours::black);
    label33->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_lfo1_sh = new Slider ("LFO 1 Shape Tweak"));
    sli_lfo1_sh->setRange (0, 10, 0);
    sli_lfo1_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_lfo1_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_lfo1_sh->addListener (this);

    addAndMakeVisible (label38 = new Label ("new label",
                                            TRANS("Envelope")));
    label38->setFont (Font (12.00f, Font::plain));
    label38->setJustificationType (Justification::centredLeft);
    label38->setEditable (false, false, false);
    label38->setColour (Label::textColourId, Colours::white);
    label38->setColour (TextEditor::textColourId, Colours::black);
    label38->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label39 = new Label ("new label",
                                            TRANS("Gate")));
    label39->setFont (Font (12.00f, Font::plain));
    label39->setJustificationType (Justification::centredLeft);
    label39->setEditable (false, false, false);
    label39->setColour (Label::textColourId, Colours::white);
    label39->setColour (TextEditor::textColourId, Colours::black);
    label39->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_vcasource = new Slider ("VCA Source"));
    swi_vcasource->setRange (0, 1, 1);
    swi_vcasource->setSliderStyle (Slider::LinearVertical);
    swi_vcasource->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_vcasource->addListener (this);

    addAndMakeVisible (sli_drive2 = new Slider ("Reverb Amount"));
    sli_drive2->setRange (0, 10, 0);
    sli_drive2->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_drive2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_drive2->addListener (this);

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("Reverb")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centred);
    label12->setEditable (false, false, false);
    label12->setColour (Label::textColourId, Colours::white);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label22 = new Label ("new label",
                                            TRANS("Chorus")));
    label22->setFont (Font (15.00f, Font::plain));
    label22->setJustificationType (Justification::centred);
    label22->setEditable (false, false, false);
    label22->setColour (Label::textColourId, Colours::white);
    label22->setColour (TextEditor::textColourId, Colours::black);
    label22->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label42 = new Label ("new label",
                                            TRANS("2")));
    label42->setFont (Font (12.00f, Font::plain));
    label42->setJustificationType (Justification::centredLeft);
    label42->setEditable (false, false, false);
    label42->setColour (Label::textColourId, Colours::white);
    label42->setColour (TextEditor::textColourId, Colours::black);
    label42->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label45 = new Label ("new label",
                                            TRANS("1")));
    label45->setFont (Font (12.00f, Font::plain));
    label45->setJustificationType (Justification::centredLeft);
    label45->setEditable (false, false, false);
    label45->setColour (Label::textColourId, Colours::white);
    label45->setColour (TextEditor::textColourId, Colours::black);
    label45->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label67 = new Label ("new label",
                                            TRANS("Off")));
    label67->setFont (Font (12.00f, Font::plain));
    label67->setJustificationType (Justification::centredLeft);
    label67->setEditable (false, false, false);
    label67->setColour (Label::textColourId, Colours::white);
    label67->setColour (TextEditor::textColourId, Colours::black);
    label67->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_glide2 = new Slider ("Chorus"));
    swi_glide2->setRange (0, 2, 1);
    swi_glide2->setSliderStyle (Slider::LinearVertical);
    swi_glide2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_glide2->addListener (this);

    addAndMakeVisible (label37 = new Label ("new label",
                                            TRANS("Legato")));
    label37->setFont (Font (12.00f, Font::plain));
    label37->setJustificationType (Justification::centredRight);
    label37->setEditable (false, false, false);
    label37->setColour (Label::textColourId, Colours::white);
    label37->setColour (TextEditor::textColourId, Colours::black);
    label37->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label43 = new Label ("new label",
                                            TRANS("Legato on Sus Pedal")));
    label43->setFont (Font (12.00f, Font::plain));
    label43->setJustificationType (Justification::centred);
    label43->setEditable (false, false, false);
    label43->setColour (Label::textColourId, Colours::white);
    label43->setColour (TextEditor::textColourId, Colours::black);
    label43->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_pitchmod_dest2 = new Slider ("new slider"));
    swi_pitchmod_dest2->setRange (1, 2, 0.5);
    swi_pitchmod_dest2->setSliderStyle (Slider::LinearHorizontal);
    swi_pitchmod_dest2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_pitchmod_dest2->addListener (this);

    addAndMakeVisible (label46 = new Label ("new label",
                                            TRANS("Retrig")));
    label46->setFont (Font (12.00f, Font::plain));
    label46->setJustificationType (Justification::centredLeft);
    label46->setEditable (false, false, false);
    label46->setColour (Label::textColourId, Colours::white);
    label46->setColour (TextEditor::textColourId, Colours::black);
    label46->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

    swi_lfo1_sh->setRotaryParameters(float(-1.5*M_PI/6.0), float(1.5*M_PI/6.0), true);
    swi_lfo2_sh->setRotaryParameters(float(-2.0*M_PI/6.0), float(2.0*M_PI/6.0), true);

    LookAndFeel::setDefaultLookAndFeel(&defaultLookAndFeel);

    //[/UserPreSize]

    setSize (795, 400);


    //[Constructor] You can add your own custom stuff here..

	SetSliderIDs_();
	BindParamsToSliders_();
	SetSpecialKnobs_();

    //[/Constructor]
}

MainGui::~MainGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent12 = nullptr;
    groupComponent11 = nullptr;
    label70 = nullptr;
    label80 = nullptr;
    swi_pitchmod_dest = nullptr;
    groupComponent2 = nullptr;
    groupComponent6 = nullptr;
    groupComponent13 = nullptr;
    groupComponent3 = nullptr;
    swi_filt_poles = nullptr;
    groupComponent4 = nullptr;
    groupComponent = nullptr;
    sli_o1_sh = nullptr;
    groupComponent8 = nullptr;
    groupComponent5 = nullptr;
    sli_o2_sh = nullptr;
    sli_mix_o1 = nullptr;
    sli_mix_o2 = nullptr;
    sli_mix_sub = nullptr;
    sli_mix_ring = nullptr;
    sli_mix_noise = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    sli_o2_tune = nullptr;
    label8 = nullptr;
    sli_filt_freq = nullptr;
    label13 = nullptr;
    sli_filt_res = nullptr;
    sli_filt_env = nullptr;
    sli_filt_lfo = nullptr;
    sli_drive = nullptr;
    sli_o2_mod = nullptr;
    sli_o1_mod = nullptr;
    sli_o2_finetune = nullptr;
    label6 = nullptr;
    label9 = nullptr;
    label10 = nullptr;
    label11 = nullptr;
    groupComponent7 = nullptr;
    sli_env_att = nullptr;
    label17 = nullptr;
    label18 = nullptr;
    label19 = nullptr;
    label20 = nullptr;
    sli_filt_gain = nullptr;
    label21 = nullptr;
    sli_pitchmod_amt = nullptr;
    label7 = nullptr;
    label25 = nullptr;
    groupComponent9 = nullptr;
    groupComponent10 = nullptr;
    sli_glide_amt = nullptr;
    sli_bend_range = nullptr;
    label26 = nullptr;
    label28 = nullptr;
    sli_lfo2_freq = nullptr;
    label29 = nullptr;
    sli_lfo2_att = nullptr;
    label31 = nullptr;
    label30 = nullptr;
    sli_filt_vel = nullptr;
    sli_env_dec = nullptr;
    sli_env_sus = nullptr;
    sli_env_rel = nullptr;
    sli_pitchmod_scale = nullptr;
    label32 = nullptr;
    label24 = nullptr;
    sli_env_vel = nullptr;
    sli_aenv_vel = nullptr;
    swi_lfo1_sh = nullptr;
    swi_lfo2_sh = nullptr;
    label48 = nullptr;
    label49 = nullptr;
    sli_lfo1_freq = nullptr;
    label51 = nullptr;
    label53 = nullptr;
    label54 = nullptr;
    label55 = nullptr;
    label56 = nullptr;
    label57 = nullptr;
    label58 = nullptr;
    label59 = nullptr;
    label60 = nullptr;
    label61 = nullptr;
    swi_o1_lfosrc = nullptr;
    swi_o1_sh = nullptr;
    swi_sub_sh = nullptr;
    swi_sub_oct = nullptr;
    label62 = nullptr;
    label63 = nullptr;
    label64 = nullptr;
    label65 = nullptr;
    swi_glide = nullptr;
    label69 = nullptr;
    label23 = nullptr;
    label72 = nullptr;
    label73 = nullptr;
    label74 = nullptr;
    label75 = nullptr;
    swi_filt_lfosrc = nullptr;
    swi_filt_kb = nullptr;
    label78 = nullptr;
    slider41 = nullptr;
    label79 = nullptr;
    label82 = nullptr;
    label83 = nullptr;
    swi_o2_lfosrc = nullptr;
    label84 = nullptr;
    label85 = nullptr;
    label86 = nullptr;
    swi_o2_sh = nullptr;
    label87 = nullptr;
    label88 = nullptr;
    label90 = nullptr;
    swi_pitchmod_scale = nullptr;
    label91 = nullptr;
    label92 = nullptr;
    label93 = nullptr;
    swi_pitchmod_src = nullptr;
    label96 = nullptr;
    swi_lfo1_kb = nullptr;
    label50 = nullptr;
    label52 = nullptr;
    label47 = nullptr;
    label100 = nullptr;
    label101 = nullptr;
    label105 = nullptr;
    label106 = nullptr;
    label107 = nullptr;
    label108 = nullptr;
    label109 = nullptr;
    label76 = nullptr;
    label77 = nullptr;
    label123 = nullptr;
    label110 = nullptr;
    label124 = nullptr;
    label125 = nullptr;
    label126 = nullptr;
    label127 = nullptr;
    label36 = nullptr;
    label14 = nullptr;
    label15 = nullptr;
    label16 = nullptr;
    swi_pitchmod_src2 = nullptr;
    label66 = nullptr;
    label40 = nullptr;
    label41 = nullptr;
    label44 = nullptr;
    label68 = nullptr;
    label81 = nullptr;
    sli_lfo2_sh = nullptr;
    label89 = nullptr;
    label27 = nullptr;
    label33 = nullptr;
    sli_lfo1_sh = nullptr;
    label38 = nullptr;
    label39 = nullptr;
    swi_vcasource = nullptr;
    sli_drive2 = nullptr;
    label12 = nullptr;
    label22 = nullptr;
    label42 = nullptr;
    label45 = nullptr;
    label67 = nullptr;
    swi_glide2 = nullptr;
    label37 = nullptr;
    label43 = nullptr;
    swi_pitchmod_dest2 = nullptr;
    label46 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainGui::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c1c1c));

    //[UserPaint] Add your own custom painting code here..

	Image bg = ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize);

	g.drawImage(bg, 0, 0, getWidth(), getHeight(), 0, 0, bg.getWidth(), bg.getHeight(), false);

    //[/UserPaint]
}

void MainGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent12->setBounds (606, 253, 178, 91);
    groupComponent11->setBounds (160, 200, 112, 192);
    label70->setBounds (158, 222, 42, 8);
    label80->setBounds (189, 234, 56, 10);
    swi_pitchmod_dest->setBounds (188, 216, 56, 20);
    groupComponent2->setBounds (278, 0, 176, 128);
    groupComponent6->setBounds (606, 129, 178, 122);
    groupComponent13->setBounds (1400, -128, 240, 80);
    groupComponent3->setBounds (462, 0, 136, 304);
    swi_filt_poles->setBounds (538, 216, 40, 16);
    groupComponent4->setBounds (8, 98, 264, 102);
    groupComponent->setBounds (8, 0, 144, 96);
    sli_o1_sh->setBounds (48, 28, 56, 48);
    groupComponent8->setBounds (8, 200, 144, 192);
    groupComponent5->setBounds (172, 0, 96, 96);
    sli_o2_sh->setBounds (47, 126, 56, 48);
    sli_mix_o1->setBounds (286, 16, 24, 88);
    sli_mix_o2->setBounds (318, 16, 24, 88);
    sli_mix_sub->setBounds (350, 16, 24, 88);
    sli_mix_ring->setBounds (382, 16, 24, 88);
    sli_mix_noise->setBounds (414, 16, 24, 88);
    label->setBounds (278, 104, 40, 16);
    label2->setBounds (310, 104, 39, 16);
    label3->setBounds (342, 104, 40, 16);
    label4->setBounds (374, 104, 39, 16);
    label5->setBounds (406, 104, 40, 16);
    sli_o2_tune->setBounds (154, 135, 48, 48);
    label8->setBounds (151, 112, 56, 16);
    sli_filt_freq->setBounds (478, 36, 104, 88);
    label13->setBounds (470, 15, 120, 16);
    sli_filt_res->setBounds (532, 153, 56, 48);
    sli_filt_env->setBounds (469, 253, 40, 32);
    sli_filt_lfo->setBounds (549, 253, 40, 32);
    sli_drive->setBounds (624, 200, 56, 48);
    sli_o2_mod->setBounds (21, 137, 24, 24);
    sli_o1_mod->setBounds (23, 39, 24, 24);
    sli_o2_finetune->setBounds (211, 136, 56, 48);
    label6->setBounds (219, 112, 40, 16);
    label9->setBounds (469, 237, 40, 16);
    label10->setBounds (525, 137, 72, 16);
    label11->setBounds (619, 185, 64, 15);
    groupComponent7->setBounds (606, 0, 178, 128);
    sli_env_att->setBounds (614, 32, 24, 88);
    label17->setBounds (614, 16, 24, 16);
    label18->setBounds (646, 16, 24, 16);
    label19->setBounds (678, 16, 24, 16);
    label20->setBounds (710, 16, 24, 16);
    sli_filt_gain->setBounds (470, 153, 56, 48);
    label21->setBounds (472, 137, 56, 16);
    sli_pitchmod_amt->setBounds (223, 268, 40, 40);
    label7->setBounds (13, 160, 40, 10);
    label25->setBounds (15, 62, 40, 10);
    groupComponent9->setBounds (275, 128, 184, 112);
    groupComponent10->setBounds (275, 240, 184, 136);
    sli_glide_amt->setBounds (29, 337, 56, 48);
    sli_bend_range->setBounds (51, 264, 56, 48);
    label26->setBounds (33, 250, 96, 16);
    label28->setBounds (289, 144, 56, 14);
    sli_lfo2_freq->setBounds (283, 271, 56, 48);
    label29->setBounds (283, 258, 56, 14);
    sli_lfo2_att->setBounds (321, 324, 56, 48);
    label31->setBounds (321, 309, 56, 14);
    label30->setBounds (509, 237, 40, 16);
    sli_filt_vel->setBounds (509, 253, 40, 32);
    sli_env_dec->setBounds (646, 32, 24, 88);
    sli_env_sus->setBounds (678, 32, 24, 88);
    sli_env_rel->setBounds (710, 32, 24, 88);
    sli_pitchmod_scale->setBounds (223, 344, 40, 40);
    label32->setBounds (549, 237, 40, 16);
    label24->setBounds (732, 40, 50, 32);
    sli_env_vel->setBounds (736, 72, 40, 32);
    sli_aenv_vel->setBounds (723, 164, 40, 32);
    swi_lfo1_sh->setBounds (363, 156, 64, 64);
    swi_lfo2_sh->setBounds (363, 269, 64, 64);
    label48->setBounds (219, 128, 40, 8);
    label49->setBounds (192, 137, 33, 16);
    sli_lfo1_freq->setBounds (289, 159, 56, 48);
    label51->setBounds (114, 30, 32, 10);
    label53->setBounds (114, 46, 32, 10);
    label54->setBounds (114, 62, 32, 10);
    label55->setBounds (234, 32, 30, 10);
    label56->setBounds (234, 48, 32, 10);
    label57->setBounds (234, 64, 32, 10);
    label58->setBounds (177, 38, 24, 8);
    label59->setBounds (177, 62, 24, 8);
    label60->setBounds (48, 76, 16, 10);
    label61->setBounds (8, 76, 16, 10);
    swi_o1_lfosrc->setBounds (16, 73, 40, 16);
    swi_o1_sh->setBounds (99, 22, 20, 56);
    swi_sub_sh->setBounds (219, 24, 20, 56);
    swi_sub_oct->setBounds (196, 34, 16, 40);
    label62->setBounds (29, 320, 96, 16);
    label63->setBounds (94, 339, 32, 10);
    label64->setBounds (94, 354, 39, 12);
    label65->setBounds (94, 371, 32, 10);
    swi_glide->setBounds (80, 331, 20, 56);
    label69->setBounds (231, 222, 48, 8);
    label23->setBounds (571, 219, 16, 10);
    label72->setBounds (527, 219, 16, 10);
    label73->setBounds (537, 206, 40, 10);
    label74->setBounds (581, 288, 16, 10);
    label75->setBounds (541, 288, 16, 10);
    swi_filt_lfosrc->setBounds (549, 284, 40, 16);
    swi_filt_kb->setBounds (482, 216, 40, 16);
    label78->setBounds (471, 206, 56, 10);
    slider41->setBounds (111, 179, 40, 16);
    label79->setBounds (143, 182, 32, 10);
    label82->setBounds (48, 176, 16, 10);
    label83->setBounds (8, 176, 16, 10);
    swi_o2_lfosrc->setBounds (16, 173, 40, 16);
    label84->setBounds (114, 127, 32, 10);
    label85->setBounds (114, 143, 32, 10);
    label86->setBounds (114, 159, 32, 10);
    swi_o2_sh->setBounds (99, 119, 20, 56);
    label87->setBounds (170, 329, 88, 16);
    label88->setBounds (186, 349, 35, 10);
    label90->setBounds (186, 364, 40, 10);
    swi_pitchmod_scale->setBounds (171, 340, 16, 40);
    label91->setBounds (186, 270, 40, 10);
    label92->setBounds (186, 286, 40, 10);
    label93->setBounds (186, 302, 40, 10);
    swi_pitchmod_src->setBounds (171, 263, 20, 56);
    label96->setBounds (323, 214, 24, 10);
    swi_lfo1_kb->setBounds (291, 211, 40, 16);
    label50->setBounds (209, 174, 20, 16);
    label52->setBounds (248, 174, 24, 16);
    label47->setBounds (144, 137, 16, 16);
    label100->setBounds (48, 112, 56, 14);
    label101->setBounds (48, 14, 56, 14);
    label105->setBounds (223, 252, 40, 16);
    label106->setBounds (163, 252, 64, 16);
    label107->setBounds (51, 304, 20, 16);
    label108->setBounds (87, 304, 24, 16);
    label109->setBounds (94, 294, 24, 16);
    label76->setBounds (495, 280, 18, 10);
    label77->setBounds (468, 280, 15, 10);
    label123->setBounds (172, 123, 26, 16);
    label110->setBounds (483, 113, 25, 16);
    label124->setBounds (552, 113, 36, 16);
    label125->setBounds (461, 56, 31, 16);
    label126->setBounds (541, 31, 27, 16);
    label127->setBounds (567, 91, 36, 16);
    label36->setBounds (712, 152, 64, 12);
    label14->setBounds (724, 197, 54, 10);
    label15->setBounds (724, 213, 54, 10);
    label16->setBounds (724, 229, 54, 10);
    swi_pitchmod_src2->setBounds (708, 190, 20, 56);
    label66->setBounds (415, 153, 32, 16);
    label40->setBounds (331, 271, 48, 16);
    label41->setBounds (364, 255, 32, 16);
    label44->setBounds (420, 276, 36, 16);
    label68->setBounds (400, 256, 32, 16);
    label81->setBounds (414, 224, 40, 10);
    sli_lfo2_sh->setBounds (418, 307, 32, 32);
    label89->setBounds (414, 338, 40, 10);
    label27->setBounds (339, 151, 48, 16);
    label33->setBounds (378, 142, 32, 16);
    sli_lfo1_sh->setBounds (418, 194, 32, 32);
    label38->setBounds (642, 149, 67, 10);
    label39->setBounds (642, 164, 59, 10);
    swi_vcasource->setBounds (627, 140, 16, 40);
    sli_drive2->setBounds (704, 282, 56, 48);
    label12->setBounds (704, 267, 56, 16);
    label22->setBounds (630, 267, 56, 16);
    label42->setBounds (648, 286, 32, 10);
    label45->setBounds (648, 302, 39, 10);
    label67->setBounds (648, 318, 32, 10);
    swi_glide2->setBounds (634, 278, 20, 56);
    label37->setBounds (22, 219, 42, 12);
    label43->setBounds (37, 233, 88, 12);
    swi_pitchmod_dest2->setBounds (52, 215, 56, 20);
    label46->setBounds (95, 219, 48, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == swi_pitchmod_dest)
    {
        //[UserSliderCode_swi_pitchmod_dest] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_dest]
    }
    else if (sliderThatWasMoved == swi_filt_poles)
    {
        //[UserSliderCode_swi_filt_poles] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_poles]
    }
    else if (sliderThatWasMoved == sli_o1_sh)
    {
        //[UserSliderCode_sli_o1_sh] -- add your slider handling code here..
        //[/UserSliderCode_sli_o1_sh]
    }
    else if (sliderThatWasMoved == sli_o2_sh)
    {
        //[UserSliderCode_sli_o2_sh] -- add your slider handling code here..
        //[/UserSliderCode_sli_o2_sh]
    }
    else if (sliderThatWasMoved == sli_mix_o1)
    {
        //[UserSliderCode_sli_mix_o1] -- add your slider handling code here..
        //[/UserSliderCode_sli_mix_o1]
    }
    else if (sliderThatWasMoved == sli_mix_o2)
    {
        //[UserSliderCode_sli_mix_o2] -- add your slider handling code here..
        //[/UserSliderCode_sli_mix_o2]
    }
    else if (sliderThatWasMoved == sli_mix_sub)
    {
        //[UserSliderCode_sli_mix_sub] -- add your slider handling code here..
        //[/UserSliderCode_sli_mix_sub]
    }
    else if (sliderThatWasMoved == sli_mix_ring)
    {
        //[UserSliderCode_sli_mix_ring] -- add your slider handling code here..
        //[/UserSliderCode_sli_mix_ring]
    }
    else if (sliderThatWasMoved == sli_mix_noise)
    {
        //[UserSliderCode_sli_mix_noise] -- add your slider handling code here..
        //[/UserSliderCode_sli_mix_noise]
    }
    else if (sliderThatWasMoved == sli_o2_tune)
    {
        //[UserSliderCode_sli_o2_tune] -- add your slider handling code here..
        //[/UserSliderCode_sli_o2_tune]
    }
    else if (sliderThatWasMoved == sli_filt_freq)
    {
        //[UserSliderCode_sli_filt_freq] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_freq]
    }
    else if (sliderThatWasMoved == sli_filt_res)
    {
        //[UserSliderCode_sli_filt_res] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_res]
    }
    else if (sliderThatWasMoved == sli_filt_env)
    {
        //[UserSliderCode_sli_filt_env] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_env]
    }
    else if (sliderThatWasMoved == sli_filt_lfo)
    {
        //[UserSliderCode_sli_filt_lfo] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_lfo]
    }
    else if (sliderThatWasMoved == sli_drive)
    {
        //[UserSliderCode_sli_drive] -- add your slider handling code here..
        //[/UserSliderCode_sli_drive]
    }
    else if (sliderThatWasMoved == sli_o2_mod)
    {
        //[UserSliderCode_sli_o2_mod] -- add your slider handling code here..
        //[/UserSliderCode_sli_o2_mod]
    }
    else if (sliderThatWasMoved == sli_o1_mod)
    {
        //[UserSliderCode_sli_o1_mod] -- add your slider handling code here..
        //[/UserSliderCode_sli_o1_mod]
    }
    else if (sliderThatWasMoved == sli_o2_finetune)
    {
        //[UserSliderCode_sli_o2_finetune] -- add your slider handling code here..
        //[/UserSliderCode_sli_o2_finetune]
    }
    else if (sliderThatWasMoved == sli_env_att)
    {
        //[UserSliderCode_sli_env_att] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_att]
    }
    else if (sliderThatWasMoved == sli_filt_gain)
    {
        //[UserSliderCode_sli_filt_gain] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_gain]
    }
    else if (sliderThatWasMoved == sli_pitchmod_amt)
    {
        //[UserSliderCode_sli_pitchmod_amt] -- add your slider handling code here..
        //[/UserSliderCode_sli_pitchmod_amt]
    }
    else if (sliderThatWasMoved == sli_glide_amt)
    {
        //[UserSliderCode_sli_glide_amt] -- add your slider handling code here..
        //[/UserSliderCode_sli_glide_amt]
    }
    else if (sliderThatWasMoved == sli_bend_range)
    {
        //[UserSliderCode_sli_bend_range] -- add your slider handling code here..
        //[/UserSliderCode_sli_bend_range]
    }
    else if (sliderThatWasMoved == sli_lfo2_freq)
    {
        //[UserSliderCode_sli_lfo2_freq] -- add your slider handling code here..
        //[/UserSliderCode_sli_lfo2_freq]
    }
    else if (sliderThatWasMoved == sli_lfo2_att)
    {
        //[UserSliderCode_sli_lfo2_att] -- add your slider handling code here..
        //[/UserSliderCode_sli_lfo2_att]
    }
    else if (sliderThatWasMoved == sli_filt_vel)
    {
        //[UserSliderCode_sli_filt_vel] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_vel]
    }
    else if (sliderThatWasMoved == sli_env_dec)
    {
        //[UserSliderCode_sli_env_dec] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_dec]
    }
    else if (sliderThatWasMoved == sli_env_sus)
    {
        //[UserSliderCode_sli_env_sus] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_sus]
    }
    else if (sliderThatWasMoved == sli_env_rel)
    {
        //[UserSliderCode_sli_env_rel] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_rel]
    }
    else if (sliderThatWasMoved == sli_pitchmod_scale)
    {
        //[UserSliderCode_sli_pitchmod_scale] -- add your slider handling code here..
        //[/UserSliderCode_sli_pitchmod_scale]
    }
    else if (sliderThatWasMoved == sli_env_vel)
    {
        //[UserSliderCode_sli_env_vel] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_vel]
    }
    else if (sliderThatWasMoved == sli_aenv_vel)
    {
        //[UserSliderCode_sli_aenv_vel] -- add your slider handling code here..
        //[/UserSliderCode_sli_aenv_vel]
    }
    else if (sliderThatWasMoved == swi_lfo1_sh)
    {
        //[UserSliderCode_swi_lfo1_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo1_sh]
    }
    else if (sliderThatWasMoved == swi_lfo2_sh)
    {
        //[UserSliderCode_swi_lfo2_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo2_sh]
    }
    else if (sliderThatWasMoved == sli_lfo1_freq)
    {
        //[UserSliderCode_sli_lfo1_freq] -- add your slider handling code here..
        //[/UserSliderCode_sli_lfo1_freq]
    }
    else if (sliderThatWasMoved == swi_o1_lfosrc)
    {
        //[UserSliderCode_swi_o1_lfosrc] -- add your slider handling code here..
        //[/UserSliderCode_swi_o1_lfosrc]
    }
    else if (sliderThatWasMoved == swi_o1_sh)
    {
        //[UserSliderCode_swi_o1_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_o1_sh]
    }
    else if (sliderThatWasMoved == swi_sub_sh)
    {
        //[UserSliderCode_swi_sub_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_sub_sh]
    }
    else if (sliderThatWasMoved == swi_sub_oct)
    {
        //[UserSliderCode_swi_sub_oct] -- add your slider handling code here..
        //[/UserSliderCode_swi_sub_oct]
    }
    else if (sliderThatWasMoved == swi_glide)
    {
        //[UserSliderCode_swi_glide] -- add your slider handling code here..
        //[/UserSliderCode_swi_glide]
    }
    else if (sliderThatWasMoved == swi_filt_lfosrc)
    {
        //[UserSliderCode_swi_filt_lfosrc] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_lfosrc]
    }
    else if (sliderThatWasMoved == swi_filt_kb)
    {
        //[UserSliderCode_swi_filt_kb] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_kb]
    }
    else if (sliderThatWasMoved == slider41)
    {
        //[UserSliderCode_slider41] -- add your slider handling code here..
        //[/UserSliderCode_slider41]
    }
    else if (sliderThatWasMoved == swi_o2_lfosrc)
    {
        //[UserSliderCode_swi_o2_lfosrc] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_lfosrc]
    }
    else if (sliderThatWasMoved == swi_o2_sh)
    {
        //[UserSliderCode_swi_o2_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_sh]
    }
    else if (sliderThatWasMoved == swi_pitchmod_scale)
    {
        //[UserSliderCode_swi_pitchmod_scale] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_scale]
    }
    else if (sliderThatWasMoved == swi_pitchmod_src)
    {
        //[UserSliderCode_swi_pitchmod_src] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_src]
    }
    else if (sliderThatWasMoved == swi_lfo1_kb)
    {
        //[UserSliderCode_swi_lfo1_kb] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo1_kb]
    }
    else if (sliderThatWasMoved == swi_pitchmod_src2)
    {
        //[UserSliderCode_swi_pitchmod_src2] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_src2]
    }
    else if (sliderThatWasMoved == sli_lfo2_sh)
    {
        //[UserSliderCode_sli_lfo2_sh] -- add your slider handling code here..
        //[/UserSliderCode_sli_lfo2_sh]
    }
    else if (sliderThatWasMoved == sli_lfo1_sh)
    {
        //[UserSliderCode_sli_lfo1_sh] -- add your slider handling code here..
        //[/UserSliderCode_sli_lfo1_sh]
    }
    else if (sliderThatWasMoved == swi_vcasource)
    {
        //[UserSliderCode_swi_vcasource] -- add your slider handling code here..
        //[/UserSliderCode_swi_vcasource]
    }
    else if (sliderThatWasMoved == sli_drive2)
    {
        //[UserSliderCode_sli_drive2] -- add your slider handling code here..
        //[/UserSliderCode_sli_drive2]
    }
    else if (sliderThatWasMoved == swi_glide2)
    {
        //[UserSliderCode_swi_glide2] -- add your slider handling code here..
        //[/UserSliderCode_swi_glide2]
    }
    else if (sliderThatWasMoved == swi_pitchmod_dest2)
    {
        //[UserSliderCode_swi_pitchmod_dest2] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_dest2]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


/* TODO: Find a non-hacky way to match up params with sliders
*
* This doesn't need to happen at runtime!
* This algorithm should have a complexity of O(n), plus whatever the complexity of findChildWithID is
* So the overall complexity will be either O(n*log(n)) or O(n^2)
*
* Besides complexity issues, it's dependent on knobs & params having exactly the same name - which
* would be okay if it happened at compile-time, but not at runtime. (Though at least we log if there
* are mismatched names.) Also, it will break if two sliders or two params have the same name.
*
* The problem is, there isn't really any way to do this without either a ton of manual repetitive code
* writing (that could break if ever making Introjucer changes), or using some sort of code generation
* script (which is a pain because you would have to re-run it any time you make absolutely any Introjucer
* change)
*
* I also tried a method that overloaded addAndMakeVisible to do this, but Introjucer code calls setRange()
* after calling addAndMakeVisible, so the part that sets the range (inside Param::BindToSlider) was
* useless, and the only ways around that were even hackier.
*
* This will have to do, at least for now - without a code generation script, it's the least hacky solution.
*/

void MainGui::SetSliderIDs_() {

	size_t nChildren = this->getNumChildComponents();
	size_t numNewSlider = 0;

	for (size_t n = 0; n < nChildren; ++n) {
		Component* pComp = this->getChildComponent(n);
		DEBUG_ASSERT(pComp);

		Slider* pSlider = dynamic_cast<Slider*>(pComp);
		ComboBox* pComboBox = dynamic_cast<ComboBox*>(pComp);
		if (!pSlider && !pComboBox) continue;

		if (pSlider && pSlider->getName().startsWith("new"))
		{
			numNewSlider++;
			continue;
		}

		pComp->setComponentID(pComp->getName());
	}

	if (numNewSlider) LOG(String::formatted("%u unnamed sliders", numNewSlider));
}

// Note:: SetSliderIds_(); must be called before this!
void MainGui::BindParamsToSliders_() {

	OwnedArray<AudioProcessorParameter> const& paramList = processor.getParameters();

	for (size_t n = 0; n < size_t(paramList.size()); ++n) {
		AudioProcessorParameter* pJuceParam = paramList[n];
		DEBUG_ASSERT(pJuceParam);

		Param* pParam = dynamic_cast<Param*>(pJuceParam);

		String const& paramName = pParam->getName();

		if (!pParam) {
			// The only way this should happen is if a plain juce::AudioProcessorParameter
			// got into the list somehow

			LOG(String("dynamic_cast of AudioProcessorParameter* to Param* failed for param ") + paramName);
			continue;
		}

		Component* pComp = this->findChildWithID(paramName);
		if (!pComp) {
			LOG(String("Could not find component matching ") + paramName);
			continue;
		}

		Slider* pSlider = dynamic_cast<Slider*>(pComp);
		ComboBox* pComboBox = dynamic_cast<ComboBox*>(pComp);
		if (pSlider) {
			pParam->BindToSlider(pSlider);
		}
		else if (pComboBox) {
			EnumParam* pEnumParam = dynamic_cast<EnumParam*>(pParam);

			if (pEnumParam) {
				pEnumParam->BindToComboBox(pComboBox);
			}
			else {
				LOG(String("Found param matching ") + paramName + " that isn't an EnumParam");
				continue;
			}
		}
		else {
			LOG(String("Found component matching ") + paramName + " that isn't an implemented component type");
			continue;
		}
	}
}

void MainGui::SetSpecialKnobs_() {
	Component* pComp;

	pComp = this->findChildWithID("Osc 2 Coarse Tune");
	if (pComp)
		pComp->setLookAndFeel(&tuningLookAndFeel);
	else
		LOG("Could not find component \"Osc 2 Coarse Tune\"");

	pComp = this->findChildWithID("Filter Frequency");
	if (pComp)
		pComp->setLookAndFeel(&freqLookAndFeel);
	else
		LOG("Could not find component \"Filter Frequency\"");
}

} // namespace Gui

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainGui" componentName=""
                 parentClasses="public Component" constructorParams="MonosynthAudioProcessor&amp; p"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="795"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff1c1c1c"/>
  <GROUPCOMPONENT name="new group" id="9da2be2e767c916e" memberName="groupComponent12"
                  virtualName="" explicitFocusOrder="0" pos="606 253 178 91" outlinecol="66ffffff"
                  textcol="ffffffff" title="Effects"/>
  <GROUPCOMPONENT name="new group" id="303c96ba3a6d7786" memberName="groupComponent11"
                  virtualName="" explicitFocusOrder="0" pos="160 200 112 192" outlinecol="66ffffff"
                  textcol="ffffffff" title="Pitch Mod"/>
  <LABEL name="new label" id="331f3423dbdd9216" memberName="label70" virtualName=""
         explicitFocusOrder="0" pos="158 222 42 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="37e280526a434fe5" memberName="label80" virtualName=""
         explicitFocusOrder="0" pos="189 234 56 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1+2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="6fa656f8bb87a7db" memberName="swi_pitchmod_dest"
          virtualName="" explicitFocusOrder="0" pos="188 216 56 20" min="1"
          max="2" int="0.5" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="2bd57dadf55e124b" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="278 0 176 128" outlinecol="66ffffff"
                  textcol="ffffffff" title="Mixer"/>
  <GROUPCOMPONENT name="new group" id="d354cd4b1913022f" memberName="groupComponent6"
                  virtualName="" explicitFocusOrder="0" pos="606 129 178 122" outlinecol="66ffffff"
                  textcol="ffffffff" title="Overdrive &amp; VCA"/>
  <GROUPCOMPONENT name="new group" id="4290aa3f94cba83c" memberName="groupComponent13"
                  virtualName="" explicitFocusOrder="0" pos="1400 -128 240 80"
                  outlinecol="66ffffff" textcol="ffffffff" title="Effects"/>
  <GROUPCOMPONENT name="new group" id="b5f4751ee1ed8057" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="462 0 136 304" outlinecol="66ffffff"
                  textcol="ffffffff" title="Filter"/>
  <SLIDER name="Filter Poles" id="9366d7598a118d48" memberName="swi_filt_poles"
          virtualName="" explicitFocusOrder="0" pos="538 216 40 16" min="2"
          max="4" int="2" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="3c0dca09a310f370" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="8 98 264 102" outlinecol="66ffffff"
                  textcol="ffffffff" title="Osc2"/>
  <GROUPCOMPONENT name="new group" id="9fb59b5f6494cccc" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="8 0 144 96" outlinecol="66ffffff"
                  textcol="ffffffff" title="Osc1"/>
  <SLIDER name="Osc 1 Shape" id="13d0d9d98ecd6c62" memberName="sli_o1_sh"
          virtualName="" explicitFocusOrder="0" pos="48 28 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="d9483dc1d74a73c9" memberName="groupComponent8"
                  virtualName="" explicitFocusOrder="0" pos="8 200 144 192" outlinecol="66ffffff"
                  textcol="ffffffff" title="Input"/>
  <GROUPCOMPONENT name="new group" id="f6c32fd096d279ac" memberName="groupComponent5"
                  virtualName="" explicitFocusOrder="0" pos="172 0 96 96" outlinecol="66ffffff"
                  textcol="ffffffff" title="Sub"/>
  <SLIDER name="Osc 2 Shape" id="cc7559654e6a39df" memberName="sli_o2_sh"
          virtualName="" explicitFocusOrder="0" pos="47 126 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 1 Mix" id="746c27abdb30c3f3" memberName="sli_mix_o1"
          virtualName="" explicitFocusOrder="0" pos="286 16 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 2 Mix" id="ce7d24772767eab2" memberName="sli_mix_o2"
          virtualName="" explicitFocusOrder="0" pos="318 16 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Mix" id="c473607e8321130a" memberName="sli_mix_sub"
          virtualName="" explicitFocusOrder="0" pos="350 16 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Ring Mod Mix" id="3da0d3c7747b8bc" memberName="sli_mix_ring"
          virtualName="" explicitFocusOrder="0" pos="382 16 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Noise Mix" id="a0d38f18199b6967" memberName="sli_mix_noise"
          virtualName="" explicitFocusOrder="0" pos="414 16 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3037bbda4f7de879" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="278 104 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="8c2ee959913bd57b" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="310 104 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="92542b3e1c3bed26" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="342 104 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sub" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="6278c010791905e2" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="374 104 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Ring" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f8c149110071038a" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="406 104 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Noise" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="12"/>
  <SLIDER name="Osc 2 Coarse Tune" id="3d1bb66ede0105e3" memberName="sli_o2_tune"
          virtualName="" explicitFocusOrder="0" pos="154 135 48 48" min="-7"
          max="19" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="119ab5d1772f94fd" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="151 112 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tuning" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Frequency" id="922a8512e459ea78" memberName="sli_filt_freq"
          virtualName="" explicitFocusOrder="0" pos="478 36 104 88" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="688179c92518c30a" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="470 15 120 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Frequency" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Resonance" id="4e819dd141ad6884" memberName="sli_filt_res"
          virtualName="" explicitFocusOrder="0" pos="532 153 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Amount" id="bf7ee7b16a44fd46" memberName="sli_filt_env"
          virtualName="" explicitFocusOrder="0" pos="469 253 40 32" min="-1"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter LFO Amount" id="b500af110555c914" memberName="sli_filt_lfo"
          virtualName="" explicitFocusOrder="0" pos="549 253 40 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Overdrive" id="3be38c3ceff9b1f2" memberName="sli_drive"
          virtualName="" explicitFocusOrder="0" pos="624 200 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="aea714e3499a9c0c" memberName="sli_o2_mod"
          virtualName="" explicitFocusOrder="0" pos="21 137 24 24" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="dd31ebe33841ebd1" memberName="sli_o1_mod"
          virtualName="" explicitFocusOrder="0" pos="23 39 24 24" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 2 Fine Tune" id="d9194a49db24b17e" memberName="sli_o2_finetune"
          virtualName="" explicitFocusOrder="0" pos="211 136 56 48" min="-1"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fd2d7af415f27f29" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="219 112 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Fine" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="419f2d32f5cd22a5" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="469 237 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="eebe59db1e731703" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="525 137 72 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b942b70f43767d13" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="619 185 64 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Overdrive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="8e4a429367bb6ed1" memberName="groupComponent7"
                  virtualName="" explicitFocusOrder="0" pos="606 0 178 128" outlinecol="66ffffff"
                  textcol="ffffffff" title="Envelope"/>
  <SLIDER name="Env Attack" id="9256184baa5e0e12" memberName="sli_env_att"
          virtualName="" explicitFocusOrder="0" pos="614 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="63d1beb2781877c5" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="614 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="bc2e22f7640f2440" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="646 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a76ec9d2625ae5a3" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="678 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="42f9bf81569b1e57" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="710 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Gain" id="d11eaf494d445128" memberName="sli_filt_gain"
          virtualName="" explicitFocusOrder="0" pos="470 153 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="abf1632f3009ec70" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="472 137 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="12fca17f8b6adf7a" memberName="sli_pitchmod_amt"
          virtualName="" explicitFocusOrder="0" pos="223 268 40 40" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="208afd31b5af01cf" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="13 160 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ca823af3ba1cc407" memberName="label25" virtualName=""
         explicitFocusOrder="0" pos="15 62 40 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="d530435b1472d6bd" memberName="groupComponent9"
                  virtualName="" explicitFocusOrder="0" pos="275 128 184 112" outlinecol="66ffffff"
                  textcol="ffffffff" title="LFO1"/>
  <GROUPCOMPONENT name="new group" id="2f9f6ffa0d9e55e2" memberName="groupComponent10"
                  virtualName="" explicitFocusOrder="0" pos="275 240 184 136" outlinecol="66ffffff"
                  textcol="ffffffff" title="LFO2"/>
  <SLIDER name="new slider" id="ca4ffa3f27169af8" memberName="sli_glide_amt"
          virtualName="" explicitFocusOrder="0" pos="29 337 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="6a4efc49fd6eaa55" memberName="sli_bend_range"
          virtualName="" explicitFocusOrder="0" pos="51 264 56 48" min="1"
          max="13" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="31fbb6afc12ace2a" memberName="label26" virtualName=""
         explicitFocusOrder="0" pos="33 250 96 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Bend Range" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1ecd7ab8e03bb46a" memberName="label28" virtualName=""
         explicitFocusOrder="0" pos="289 144 56 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Freq" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO 2 Freq" id="320ebe3eb3fc4ddf" memberName="sli_lfo2_freq"
          virtualName="" explicitFocusOrder="0" pos="283 271 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="ef22716764130697" memberName="label29" virtualName=""
         explicitFocusOrder="0" pos="283 258 56 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Freq" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO 1 Attack" id="adf7d9bbe7bedc02" memberName="sli_lfo2_att"
          virtualName="" explicitFocusOrder="0" pos="321 324 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="677e03b32f7824b6" memberName="label31" virtualName=""
         explicitFocusOrder="0" pos="321 309 56 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c4faced59acd9f5f" memberName="label30" virtualName=""
         explicitFocusOrder="0" pos="509 237 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Vel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Vel Amount" id="2e1b5981e8fb0e0d" memberName="sli_filt_vel"
          virtualName="" explicitFocusOrder="0" pos="509 253 40 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Decay" id="22d76f58418fb20b" memberName="sli_env_dec"
          virtualName="" explicitFocusOrder="0" pos="646 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Sustain" id="19781c82024cb700" memberName="sli_env_sus"
          virtualName="" explicitFocusOrder="0" pos="678 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Release" id="e6a3be71b101f31f" memberName="sli_env_rel"
          virtualName="" explicitFocusOrder="0" pos="710 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="7e1f6915b0e09136" memberName="sli_pitchmod_scale"
          virtualName="" explicitFocusOrder="0" pos="223 344 40 40" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e5cc86881f025c32" memberName="label32" virtualName=""
         explicitFocusOrder="0" pos="549 237 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9209d34f3c9b1813" memberName="label24" virtualName=""
         explicitFocusOrder="0" pos="732 40 50 32" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Vel to&#10;Time"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filt Env Velocity" id="ccc08de89b923d42" memberName="sli_env_vel"
          virtualName="" explicitFocusOrder="0" pos="736 72 40 32" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Velocity" id="52f95a0d1dc63936" memberName="sli_aenv_vel"
          virtualName="" explicitFocusOrder="0" pos="723 164 40 32" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO 1 Shape" id="747eb511b0641157" memberName="swi_lfo1_sh"
          virtualName="" explicitFocusOrder="0" pos="363 156 64 64" min="1"
          max="5" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFO 2 Shape" id="8f80c42fdf365c88" memberName="swi_lfo2_sh"
          virtualName="" explicitFocusOrder="0" pos="363 269 64 64" min="1"
          max="6" int="1" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="e3c6f5ab2adf08ae" memberName="label48" virtualName=""
         explicitFocusOrder="0" pos="219 128 40 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="d1e6db63a46ed8a3" memberName="label49" virtualName=""
         explicitFocusOrder="0" pos="192 137 33 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="+12" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="LFO 1 Freq" id="b473ed648319c3c5" memberName="sli_lfo1_freq"
          virtualName="" explicitFocusOrder="0" pos="289 159 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a64876f8e639f198" memberName="label51" virtualName=""
         explicitFocusOrder="0" pos="114 30 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="db9a93b2d2513aac" memberName="label53" virtualName=""
         explicitFocusOrder="0" pos="114 46 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rect" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="59ee6ba7e3eb521f" memberName="label54" virtualName=""
         explicitFocusOrder="0" pos="114 62 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a1b7c767ce93174" memberName="label55" virtualName=""
         explicitFocusOrder="0" pos="234 32 30 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pulse" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e6118cecc0940531" memberName="label56" virtualName=""
         explicitFocusOrder="0" pos="234 48 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Squ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d4f6a5cfc0a64135" memberName="label57" virtualName=""
         explicitFocusOrder="0" pos="234 64 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b9ef87d8f2eb14bf" memberName="label58" virtualName=""
         explicitFocusOrder="0" pos="177 38 24 8" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="-1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10"
         bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="e930acfdc20baad5" memberName="label59" virtualName=""
         explicitFocusOrder="0" pos="177 62 24 8" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="-2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="10"
         bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="b67319bed377a61f" memberName="label60" virtualName=""
         explicitFocusOrder="0" pos="48 76 16 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ad983231c60134e5" memberName="label61" virtualName=""
         explicitFocusOrder="0" pos="8 76 16 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="994f92468c7f87f3" memberName="swi_o1_lfosrc"
          virtualName="" explicitFocusOrder="0" pos="16 73 40 16" min="1"
          max="2" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 1 Wave" id="e145a51361506cda" memberName="swi_o1_sh"
          virtualName="" explicitFocusOrder="0" pos="99 22 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Osc Wave" id="38673bb6b3afd895" memberName="swi_sub_sh"
          virtualName="" explicitFocusOrder="0" pos="219 24 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Osc Octave" id="9ad005c2310e0623" memberName="swi_sub_oct"
          virtualName="" explicitFocusOrder="0" pos="196 34 16 40" min="-2"
          max="-1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="72064045411c385b" memberName="label62" virtualName=""
         explicitFocusOrder="0" pos="29 320 96 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="acbac73778a2cdcf" memberName="label63" virtualName=""
         explicitFocusOrder="0" pos="94 339 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="On" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6394f8f8d3f8e81f" memberName="label64" virtualName=""
         explicitFocusOrder="0" pos="94 354 39 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Legato" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c5fcdbfac6f2e29" memberName="label65" virtualName=""
         explicitFocusOrder="0" pos="94 371 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Off" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="692296ee6459bc79" memberName="swi_glide"
          virtualName="" explicitFocusOrder="0" pos="80 331 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f621af72285c3ecd" memberName="label69" virtualName=""
         explicitFocusOrder="0" pos="231 222 48 8" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="678fadab46d9a69e" memberName="label23" virtualName=""
         explicitFocusOrder="0" pos="571 219 16 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="4" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f1ef89eff647ee05" memberName="label72" virtualName=""
         explicitFocusOrder="0" pos="527 219 16 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="51b1c7c05b9444c0" memberName="label73" virtualName=""
         explicitFocusOrder="0" pos="537 206 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Poles" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="611f9513d572a3a6" memberName="label74" virtualName=""
         explicitFocusOrder="0" pos="581 288 16 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="228a12205b8fd66b" memberName="label75" virtualName=""
         explicitFocusOrder="0" pos="541 288 16 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <SLIDER name="Filter LFO Select" id="b3c11c5568020657" memberName="swi_filt_lfosrc"
          virtualName="" explicitFocusOrder="0" pos="549 284 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter KB Track" id="3aff6026701ab6fc" memberName="swi_filt_kb"
          virtualName="" explicitFocusOrder="0" pos="482 216 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c953c9b10bd66654" memberName="label78" virtualName=""
         explicitFocusOrder="0" pos="471 206 56 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="KB Track" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="1dfe389adfa42abd" memberName="slider41"
          virtualName="" explicitFocusOrder="0" pos="111 179 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a7e9361804280688" memberName="label79" virtualName=""
         explicitFocusOrder="0" pos="143 182 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sync" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="22a7069d2ac2ef1b" memberName="label82" virtualName=""
         explicitFocusOrder="0" pos="48 176 16 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3a2105c234969ec6" memberName="label83" virtualName=""
         explicitFocusOrder="0" pos="8 176 16 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="7d6b9b0633580160" memberName="swi_o2_lfosrc"
          virtualName="" explicitFocusOrder="0" pos="16 173 40 16" min="1"
          max="2" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8ab6e14003e4ade2" memberName="label84" virtualName=""
         explicitFocusOrder="0" pos="114 127 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9c21a2ecab495cad" memberName="label85" virtualName=""
         explicitFocusOrder="0" pos="114 143 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rect" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2ddc4676c3df97a3" memberName="label86" virtualName=""
         explicitFocusOrder="0" pos="114 159 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 2 Wave" id="3b884ec8bb678763" memberName="swi_o2_sh"
          virtualName="" explicitFocusOrder="0" pos="99 119 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="7af72fab97f77777" memberName="label87" virtualName=""
         explicitFocusOrder="0" pos="170 329 88 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Scale By" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a38816641542b5f5" memberName="label88" virtualName=""
         explicitFocusOrder="0" pos="186 349 35 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Vel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="21c565a3fb99ce55" memberName="label90" virtualName=""
         explicitFocusOrder="0" pos="186 364 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod Wh" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="689dec72771854d7" memberName="swi_pitchmod_scale"
          virtualName="" explicitFocusOrder="0" pos="171 340 16 40" min="0"
          max="1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c9563633985aee29" memberName="label91" virtualName=""
         explicitFocusOrder="0" pos="186 270 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="178f041b11b3989c" memberName="label92" virtualName=""
         explicitFocusOrder="0" pos="186 286 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5993e8b0b82bffbf" memberName="label93" virtualName=""
         explicitFocusOrder="0" pos="186 302 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="2786e978180c30a5" memberName="swi_pitchmod_src"
          virtualName="" explicitFocusOrder="0" pos="171 263 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="5fbafef03a41acb0" memberName="label96" virtualName=""
         explicitFocusOrder="0" pos="323 214 24 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="KB" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="75250b340aecdcc1" memberName="swi_lfo1_kb"
          virtualName="" explicitFocusOrder="0" pos="291 211 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f3faafa75c7a3881" memberName="label50" virtualName=""
         explicitFocusOrder="0" pos="209 174 20 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="-1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1e09c3911c6165f2" memberName="label52" virtualName=""
         explicitFocusOrder="0" pos="248 174 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="+1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="2bb7bacc4f35a31c" memberName="label47" virtualName=""
         explicitFocusOrder="0" pos="144 137 16 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="37928afa14c5ad1d" memberName="label100"
         virtualName="" explicitFocusOrder="0" pos="48 112 56 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c2258f9a17615d4c" memberName="label101"
         virtualName="" explicitFocusOrder="0" pos="48 14 56 14" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="4f9e29710ea85f8b" memberName="label105"
         virtualName="" explicitFocusOrder="0" pos="223 252 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amt" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="3e6b1bc0984a82f6" memberName="label106"
         virtualName="" explicitFocusOrder="0" pos="163 252 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Source" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c2b98f64f381a54e" memberName="label107"
         virtualName="" explicitFocusOrder="0" pos="51 304 20 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a088be42b0aa2bd8" memberName="label108"
         virtualName="" explicitFocusOrder="0" pos="87 304 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="24" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="e800eda52eb4e127" memberName="label109"
         virtualName="" explicitFocusOrder="0" pos="94 294 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="12" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="103c8c075f50b7b0" memberName="label76" virtualName=""
         explicitFocusOrder="0" pos="495 280 18 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="+" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fa96c6c093d2f08" memberName="label77" virtualName=""
         explicitFocusOrder="0" pos="468 280 15 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="-" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="32cdf22a180cf81d" memberName="label123"
         virtualName="" explicitFocusOrder="0" pos="172 123 26 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="+7" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b19745e0adb6724e" memberName="label110"
         virtualName="" explicitFocusOrder="0" pos="483 113 25 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="20" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="944c47c83029687f" memberName="label124"
         virtualName="" explicitFocusOrder="0" pos="552 113 36 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="20k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="62201f3d19ea01a7" memberName="label125"
         virtualName="" explicitFocusOrder="0" pos="461 56 31 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="100" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="2aad2e8c6ad2f227" memberName="label126"
         virtualName="" explicitFocusOrder="0" pos="541 31 27 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a896398c2324146" memberName="label127" virtualName=""
         explicitFocusOrder="0" pos="567 91 36 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="10k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="94d0f1fdc830d927" memberName="label36" virtualName=""
         explicitFocusOrder="0" pos="712 152 64 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Velocity" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="244dc8a10230e796" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="724 197 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pre-Filt" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7f97df13b20ff493" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="724 213 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pre-Drive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8deaa9617e51ea95" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="724 229 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Post-Drive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="8718f1916d2e3d17" memberName="swi_pitchmod_src2"
          virtualName="" explicitFocusOrder="0" pos="708 190 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9c65016fbc168b33" memberName="label66" virtualName=""
         explicitFocusOrder="0" pos="415 153 32 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="S&amp;H" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8ed46fd41cbbaa4d" memberName="label40" virtualName=""
         explicitFocusOrder="0" pos="331 271 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri/Squ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="cde7bdc353dfdd79" memberName="label41" virtualName=""
         explicitFocusOrder="0" pos="364 255 32 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="6e8bbb50c17893de" memberName="label44" virtualName=""
         explicitFocusOrder="0" pos="420 276 36 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9c9a803a16253e9f" memberName="label68" virtualName=""
         explicitFocusOrder="0" pos="400 256 32 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="S&amp;H" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="72b500e40e637972" memberName="label81" virtualName=""
         explicitFocusOrder="0" pos="414 224 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO 2 Shape Tweak" id="6aa0123c515066bf" memberName="sli_lfo2_sh"
          virtualName="" explicitFocusOrder="0" pos="418 307 32 32" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="7c7605ff12980148" memberName="label89" virtualName=""
         explicitFocusOrder="0" pos="414 338 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="1d58ee4a208cf2c2" memberName="label27" virtualName=""
         explicitFocusOrder="0" pos="339 151 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri/Squ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="b44bb20ad98ddf72" memberName="label33" virtualName=""
         explicitFocusOrder="0" pos="378 142 32 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="LFO 1 Shape Tweak" id="156ad723e1b5b6e7" memberName="sli_lfo1_sh"
          virtualName="" explicitFocusOrder="0" pos="418 194 32 32" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="93a34653caa27da8" memberName="label38" virtualName=""
         explicitFocusOrder="0" pos="642 149 67 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Envelope" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="729da4349ae748c5" memberName="label39" virtualName=""
         explicitFocusOrder="0" pos="642 164 59 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="VCA Source" id="7e89d72d33aa2bf1" memberName="swi_vcasource"
          virtualName="" explicitFocusOrder="0" pos="627 140 16 40" min="0"
          max="1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Reverb Amount" id="2fea1fd25759315c" memberName="sli_drive2"
          virtualName="" explicitFocusOrder="0" pos="704 282 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="bebd7aba5523fced" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="704 267 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Reverb" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="12bca2c7f5f38bbb" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="630 267 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Chorus" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ab1e31df4ab51c63" memberName="label42" virtualName=""
         explicitFocusOrder="0" pos="648 286 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f92210fee39471d6" memberName="label45" virtualName=""
         explicitFocusOrder="0" pos="648 302 39 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c423afd097d508bb" memberName="label67" virtualName=""
         explicitFocusOrder="0" pos="648 318 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Off" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Chorus" id="b4a58afcd4823304" memberName="swi_glide2" virtualName=""
          explicitFocusOrder="0" pos="634 278 20 56" min="0" max="2" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="b85c9abef7437058" memberName="label37" virtualName=""
         explicitFocusOrder="0" pos="22 219 42 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Legato" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="a56c1c55f79cdd1d" memberName="label43" virtualName=""
         explicitFocusOrder="0" pos="37 233 88 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Legato on Sus Pedal"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="97cedc0ad434b4b" memberName="swi_pitchmod_dest2"
          virtualName="" explicitFocusOrder="0" pos="52 215 56 20" min="1"
          max="2" int="0.5" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="ccea09327fffd238" memberName="label46" virtualName=""
         explicitFocusOrder="0" pos="95 219 48 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Retrig" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
