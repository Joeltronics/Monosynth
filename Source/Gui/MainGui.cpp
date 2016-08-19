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

    addAndMakeVisible (groupComponent16 = new GroupComponent ("new group",
                                                              TRANS("Velocity")));
    groupComponent16->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent16->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent11 = new GroupComponent ("new group",
                                                              TRANS("Glide")));
    groupComponent11->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent11->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent4 = new GroupComponent ("new group",
                                                             TRANS("Osc 2")));
    groupComponent4->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent4->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent14 = new GroupComponent ("new group",
                                                              TRANS("Osc 1")));
    groupComponent14->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent14->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent10 = new GroupComponent ("new group",
                                                              TRANS("Mod 2 (LFO/Envelope)")));
    groupComponent10->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent10->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent12 = new GroupComponent ("new group",
                                                              TRANS("Effects")));
    groupComponent12->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent12->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Oscillators")));
    groupComponent2->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent2->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent6 = new GroupComponent ("new group",
                                                             TRANS("VCA")));
    groupComponent6->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent6->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent13 = new GroupComponent ("new group",
                                                              TRANS("Effects")));
    groupComponent13->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent13->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent3 = new GroupComponent ("new group",
                                                             TRANS("Filter")));
    groupComponent3->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent3->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (swi_filt_poles = new Slider ("Filter Poles"));
    swi_filt_poles->setRange (2, 4, 2);
    swi_filt_poles->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_poles->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_poles->addListener (this);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Osc1")));
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_o1_sh = new Slider ("Osc 1 Shape"));
    sli_o1_sh->setRange (0, 10, 0);
    sli_o1_sh->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o1_sh->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o1_sh->addListener (this);

    addAndMakeVisible (groupComponent8 = new GroupComponent ("new group",
                                                             TRANS("Mono Mode")));
    groupComponent8->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent8->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent5 = new GroupComponent ("new group",
                                                             TRANS("Sub")));
    groupComponent5->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent5->setColour (GroupComponent::textColourId, Colours::white);

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
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredTop);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colours::white);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("2")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredTop);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Sub")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredTop);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Ring")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredTop);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::white);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Noise")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredTop);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::white);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_o2_tune = new Slider ("Osc 2 Coarse Tune"));
    sli_o2_tune->setRange (-7, 7, 0);
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
    sli_filt_env->setRange (0, 1, 0);
    sli_filt_env->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_env->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_env->addListener (this);

    addAndMakeVisible (sli_drive = new Slider ("Overdrive"));
    sli_drive->setRange (0, 10, 0);
    sli_drive->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_drive->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_drive->addListener (this);

    addAndMakeVisible (sli_o2_finetune = new Slider ("Osc 2 Fine Tune"));
    sli_o2_finetune->setRange (-1, 1, 0);
    sli_o2_finetune->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o2_finetune->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o2_finetune->addListener (this);

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Fine")));
    label6->setFont (Font (12.00f, Font::plain));
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
    groupComponent7->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent7->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_env_att = new Slider ("Env Attack"));
    sli_env_att->setRange (0, 10, 0);
    sli_env_att->setSliderStyle (Slider::LinearVertical);
    sli_env_att->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_att->addListener (this);

    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("A")));
    label17->setFont (Font (15.00f, Font::plain));
    label17->setJustificationType (Justification::centred);
    label17->setEditable (false, false, false);
    label17->setColour (Label::textColourId, Colours::white);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("D")));
    label18->setFont (Font (15.00f, Font::plain));
    label18->setJustificationType (Justification::centred);
    label18->setEditable (false, false, false);
    label18->setColour (Label::textColourId, Colours::white);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label19 = new Label ("new label",
                                            TRANS("S")));
    label19->setFont (Font (15.00f, Font::plain));
    label19->setJustificationType (Justification::centred);
    label19->setEditable (false, false, false);
    label19->setColour (Label::textColourId, Colours::white);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("R")));
    label20->setFont (Font (15.00f, Font::plain));
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

    addAndMakeVisible (groupComponent9 = new GroupComponent ("new group",
                                                             TRANS("Mod 1 (LFO)")));
    groupComponent9->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent9->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (sli_glide_amt = new Slider ("new slider"));
    sli_glide_amt->setRange (0, 10, 0);
    sli_glide_amt->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_glide_amt->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_glide_amt->addListener (this);

    addAndMakeVisible (label28 = new Label ("new label",
                                            TRANS("Rate")));
    label28->setFont (Font (15.00f, Font::plain));
    label28->setJustificationType (Justification::centred);
    label28->setEditable (false, false, false);
    label28->setColour (Label::textColourId, Colours::white);
    label28->setColour (TextEditor::textColourId, Colours::black);
    label28->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_mod2_a = new Slider ("Mod 2 Attack"));
    sli_mod2_a->setRange (0, 10, 0);
    sli_mod2_a->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod2_a->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod2_a->addListener (this);

    addAndMakeVisible (label29 = new Label ("new label",
                                            TRANS("Attack")));
    label29->setFont (Font (15.00f, Font::plain));
    label29->setJustificationType (Justification::centred);
    label29->setEditable (false, false, false);
    label29->setColour (Label::textColourId, Colours::white);
    label29->setColour (TextEditor::textColourId, Colours::black);
    label29->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (sli_env_vel = new Slider ("Env Vel Rate"));
    sli_env_vel->setRange (0, 1, 0.5);
    sli_env_vel->setSliderStyle (Slider::LinearVertical);
    sli_env_vel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel->addListener (this);

    addAndMakeVisible (sli_aenv_vel = new Slider ("Amp Env Velocity"));
    sli_aenv_vel->setRange (0, 10, 0);
    sli_aenv_vel->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_aenv_vel->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_aenv_vel->addListener (this);

    addAndMakeVisible (sli_mod1_rate = new Slider ("Mod 1 Rate"));
    sli_mod1_rate->setRange (0, 10, 0);
    sli_mod1_rate->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod1_rate->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod1_rate->addListener (this);

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
    label58->setFont (Font (12.00f, Font::plain));
    label58->setJustificationType (Justification::centredLeft);
    label58->setEditable (false, false, false);
    label58->setColour (Label::textColourId, Colours::white);
    label58->setColour (TextEditor::textColourId, Colours::black);
    label58->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label59 = new Label ("new label",
                                            TRANS("-2")));
    label59->setFont (Font (12.00f, Font::plain));
    label59->setJustificationType (Justification::centredLeft);
    label59->setEditable (false, false, false);
    label59->setColour (Label::textColourId, Colours::white);
    label59->setColour (TextEditor::textColourId, Colours::black);
    label59->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (label23 = new Label ("new label",
                                            TRANS("4")));
    label23->setFont (Font (15.00f, Font::plain));
    label23->setJustificationType (Justification::centredLeft);
    label23->setEditable (false, false, false);
    label23->setColour (Label::textColourId, Colours::white);
    label23->setColour (TextEditor::textColourId, Colours::black);
    label23->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label72 = new Label ("new label",
                                            TRANS("2")));
    label72->setFont (Font (15.00f, Font::plain));
    label72->setJustificationType (Justification::centredRight);
    label72->setEditable (false, false, false);
    label72->setColour (Label::textColourId, Colours::white);
    label72->setColour (TextEditor::textColourId, Colours::black);
    label72->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label73 = new Label ("new label",
                                            TRANS("Poles")));
    label73->setFont (Font (15.00f, Font::plain));
    label73->setJustificationType (Justification::centred);
    label73->setEditable (false, false, false);
    label73->setColour (Label::textColourId, Colours::white);
    label73->setColour (TextEditor::textColourId, Colours::black);
    label73->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_kb = new Slider ("Filter KB Track"));
    swi_filt_kb->setRange (0, 1, 0.5);
    swi_filt_kb->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_kb->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_kb->addListener (this);

    addAndMakeVisible (label78 = new Label ("new label",
                                            TRANS("KB Track")));
    label78->setFont (Font (15.00f, Font::plain));
    label78->setJustificationType (Justification::centred);
    label78->setEditable (false, false, false);
    label78->setColour (Label::textColourId, Colours::white);
    label78->setColour (TextEditor::textColourId, Colours::black);
    label78->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_o2_sync = new Slider ("Osc 2 Sync"));
    swi_o2_sync->setRange (0, 1, 1);
    swi_o2_sync->setSliderStyle (Slider::LinearVertical);
    swi_o2_sync->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o2_sync->addListener (this);

    addAndMakeVisible (label79 = new Label ("new label",
                                            TRANS("Sync")));
    label79->setFont (Font (15.00f, Font::plain));
    label79->setJustificationType (Justification::centred);
    label79->setEditable (false, false, false);
    label79->setColour (Label::textColourId, Colours::white);
    label79->setColour (TextEditor::textColourId, Colours::black);
    label79->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (label100 = new Label ("new label",
                                             TRANS("Shape")));
    label100->setFont (Font (15.00f, Font::plain));
    label100->setJustificationType (Justification::centred);
    label100->setEditable (false, false, false);
    label100->setColour (Label::textColourId, Colours::white);
    label100->setColour (TextEditor::textColourId, Colours::black);
    label100->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label101 = new Label ("new label",
                                             TRANS("Shape")));
    label101->setFont (Font (15.00f, Font::plain));
    label101->setJustificationType (Justification::centred);
    label101->setEditable (false, false, false);
    label101->setColour (Label::textColourId, Colours::white);
    label101->setColour (TextEditor::textColourId, Colours::black);
    label101->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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
                                            TRANS("Amplitude")));
    label36->setFont (Font (15.00f, Font::plain));
    label36->setJustificationType (Justification::centred);
    label36->setEditable (false, false, false);
    label36->setColour (Label::textColourId, Colours::white);
    label36->setColour (TextEditor::textColourId, Colours::black);
    label36->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Pre-Filter")));
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

    addAndMakeVisible (label38 = new Label ("new label",
                                            TRANS("Envelope")));
    label38->setFont (Font (12.00f, Font::plain));
    label38->setJustificationType (Justification::centredLeft);
    label38->setEditable (false, false, false);
    label38->setColour (Label::textColourId, Colours::white);
    label38->setColour (TextEditor::textColourId, Colours::black);
    label38->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label39 = new Label ("new label",
                                            TRANS("Gate + Click")));
    label39->setFont (Font (12.00f, Font::plain));
    label39->setJustificationType (Justification::centredLeft);
    label39->setEditable (false, false, false);
    label39->setColour (Label::textColourId, Colours::white);
    label39->setColour (TextEditor::textColourId, Colours::black);
    label39->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_vcasource = new Slider ("VCA Source"));
    swi_vcasource->setRange (0, 2, 1);
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
                                            TRANS("Pedal Legato")));
    label43->setFont (Font (12.00f, Font::plain));
    label43->setJustificationType (Justification::centredLeft);
    label43->setEditable (false, false, false);
    label43->setColour (Label::textColourId, Colours::white);
    label43->setColour (TextEditor::textColourId, Colours::black);
    label43->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_retrig_mode = new Slider ("Retrigger Mode"));
    swi_retrig_mode->setRange (1, 2, 0.5);
    swi_retrig_mode->setSliderStyle (Slider::LinearVertical);
    swi_retrig_mode->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_retrig_mode->addListener (this);

    addAndMakeVisible (label46 = new Label ("new label",
                                            TRANS("Retrig")));
    label46->setFont (Font (12.00f, Font::plain));
    label46->setJustificationType (Justification::centredLeft);
    label46->setEditable (false, false, false);
    label46->setColour (Label::textColourId, Colours::white);
    label46->setColour (TextEditor::textColourId, Colours::black);
    label46->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label35 = new Label ("new label",
                                            TRANS("+1")));
    label35->setFont (Font (12.00f, Font::plain));
    label35->setJustificationType (Justification::centredLeft);
    label35->setEditable (false, false, false);
    label35->setColour (Label::textColourId, Colours::white);
    label35->setColour (TextEditor::textColourId, Colours::black);
    label35->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label47 = new Label ("new label",
                                            TRANS("0")));
    label47->setFont (Font (12.00f, Font::plain));
    label47->setJustificationType (Justification::centredLeft);
    label47->setEditable (false, false, false);
    label47->setColour (Label::textColourId, Colours::white);
    label47->setColour (TextEditor::textColourId, Colours::black);
    label47->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_vco2_oct = new Slider ("Osc 2 Octave"));
    swi_vco2_oct->setRange (-2, -1, 1);
    swi_vco2_oct->setSliderStyle (Slider::LinearVertical);
    swi_vco2_oct->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_vco2_oct->addListener (this);

    addAndMakeVisible (label48 = new Label ("new label",
                                            TRANS("Oct")));
    label48->setFont (Font (12.00f, Font::plain));
    label48->setJustificationType (Justification::centred);
    label48->setEditable (false, false, false);
    label48->setColour (Label::textColourId, Colours::white);
    label48->setColour (TextEditor::textColourId, Colours::black);
    label48->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_mod2_b = new Slider ("Mod 2 Decay"));
    sli_mod2_b->setRange (0, 10, 0);
    sli_mod2_b->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod2_b->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod2_b->addListener (this);

    addAndMakeVisible (label31 = new Label ("new label",
                                            TRANS("Decay")));
    label31->setFont (Font (15.00f, Font::plain));
    label31->setJustificationType (Justification::centred);
    label31->setEditable (false, false, false);
    label31->setColour (Label::textColourId, Colours::white);
    label31->setColour (TextEditor::textColourId, Colours::black);
    label31->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label94 = new Label ("new label",
                                            TRANS("Type")));
    label94->setFont (Font (15.00f, Font::plain));
    label94->setJustificationType (Justification::centred);
    label94->setEditable (false, false, false);
    label94->setColour (Label::textColourId, Colours::white);
    label94->setColour (TextEditor::textColourId, Colours::black);
    label94->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label24 = new Label ("new label",
                                            TRANS("Filter")));
    label24->setFont (Font (15.00f, Font::plain));
    label24->setJustificationType (Justification::centred);
    label24->setEditable (false, false, false);
    label24->setColour (Label::textColourId, Colours::white);
    label24->setColour (TextEditor::textColourId, Colours::black);
    label24->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_env_vel_ampl = new Slider ("Env Vel Amp"));
    sli_env_vel_ampl->setRange (0, 1, 0.5);
    sli_env_vel_ampl->setSliderStyle (Slider::LinearVertical);
    sli_env_vel_ampl->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel_ampl->addListener (this);

    addAndMakeVisible (label96 = new Label ("new label",
                                            TRANS("Res")));
    label96->setFont (Font (12.00f, Font::plain));
    label96->setJustificationType (Justification::centred);
    label96->setEditable (false, false, false);
    label96->setColour (Label::textColourId, Colours::white);
    label96->setColour (TextEditor::textColourId, Colours::black);
    label96->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label97 = new Label ("new label",
                                            TRANS("Freq")));
    label97->setFont (Font (12.00f, Font::plain));
    label97->setJustificationType (Justification::centred);
    label97->setEditable (false, false, false);
    label97->setColour (Label::textColourId, Colours::white);
    label97->setColour (TextEditor::textColourId, Colours::black);
    label97->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label30 = new Label ("new label",
                                            TRANS("1")));
    label30->setFont (Font (12.00f, Font::plain));
    label30->setJustificationType (Justification::centredRight);
    label30->setEditable (false, false, false);
    label30->setColour (Label::textColourId, Colours::white);
    label30->setColour (TextEditor::textColourId, Colours::black);
    label30->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label98 = new Label ("new label",
                                            TRANS("0.5")));
    label98->setFont (Font (12.00f, Font::plain));
    label98->setJustificationType (Justification::centredRight);
    label98->setEditable (false, false, false);
    label98->setColour (Label::textColourId, Colours::white);
    label98->setColour (TextEditor::textColourId, Colours::black);
    label98->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label99 = new Label ("new label",
                                            TRANS("0")));
    label99->setFont (Font (12.00f, Font::plain));
    label99->setJustificationType (Justification::centredRight);
    label99->setEditable (false, false, false);
    label99->setColour (Label::textColourId, Colours::white);
    label99->setColour (TextEditor::textColourId, Colours::black);
    label99->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label109 = new Label ("new label",
                                             TRANS("1")));
    label109->setFont (Font (12.00f, Font::plain));
    label109->setJustificationType (Justification::centredRight);
    label109->setEditable (false, false, false);
    label109->setColour (Label::textColourId, Colours::white);
    label109->setColour (TextEditor::textColourId, Colours::black);
    label109->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label32 = new Label ("new label",
                                            TRANS("2")));
    label32->setFont (Font (12.00f, Font::plain));
    label32->setJustificationType (Justification::centredLeft);
    label32->setEditable (false, false, false);
    label32->setColour (Label::textColourId, Colours::white);
    label32->setColour (TextEditor::textColourId, Colours::black);
    label32->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label74 = new Label ("new label",
                                            TRANS("Mod")));
    label74->setFont (Font (12.00f, Font::plain));
    label74->setJustificationType (Justification::centred);
    label74->setEditable (false, false, false);
    label74->setColour (Label::textColourId, Colours::white);
    label74->setColour (TextEditor::textColourId, Colours::black);
    label74->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_o1_shapeMod = new Slider ("Osc 1 Shape Mod"));
    sli_o1_shapeMod->setRange (0, 1, 0);
    sli_o1_shapeMod->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_o1_shapeMod->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_o1_shapeMod->addListener (this);

    addAndMakeVisible (swi_o1_shapeMod_src = new Slider ("Osc 1 Shape Mod Source"));
    swi_o1_shapeMod_src->setRange (0, 1, 1);
    swi_o1_shapeMod_src->setSliderStyle (Slider::LinearHorizontal);
    swi_o1_shapeMod_src->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o1_shapeMod_src->addListener (this);

    addAndMakeVisible (groupComponent15 = new GroupComponent ("new group",
                                                              TRANS("Pitch Mod")));
    groupComponent15->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent15->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (swi_o2_sh4 = new Slider ("Pitch Mod Dest"));
    swi_o2_sh4->setRange (1, 2, 0.5);
    swi_o2_sh4->setSliderStyle (Slider::LinearVertical);
    swi_o2_sh4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o2_sh4->addListener (this);

    addAndMakeVisible (sli_mod2_a2 = new Slider ("Mod 2 Param A"));
    sli_mod2_a2->setRange (0, 10, 0);
    sli_mod2_a2->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod2_a2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod2_a2->addListener (this);

    addAndMakeVisible (label114 = new Label ("new label",
                                             TRANS("Mod 2")));
    label114->setFont (Font (15.00f, Font::plain));
    label114->setJustificationType (Justification::centred);
    label114->setEditable (false, false, false);
    label114->setColour (Label::textColourId, Colours::white);
    label114->setColour (TextEditor::textColourId, Colours::black);
    label114->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_mod1 = new Slider ("Filter Mod 1 Amount"));
    sli_filt_mod1->setRange (0, 1, 0);
    sli_filt_mod1->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_mod1->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_mod1->addListener (this);

    addAndMakeVisible (label60 = new Label ("new label",
                                            TRANS("Mod 1")));
    label60->setFont (Font (15.00f, Font::plain));
    label60->setJustificationType (Justification::centred);
    label60->setEditable (false, false, false);
    label60->setColour (Label::textColourId, Colours::white);
    label60->setColour (TextEditor::textColourId, Colours::black);
    label60->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_filt_mod2 = new Slider ("Filter Mod 2 Amount"));
    sli_filt_mod2->setRange (0, 1, 0);
    sli_filt_mod2->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_mod2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_mod2->addListener (this);

    addAndMakeVisible (label115 = new Label ("new label",
                                             TRANS("Mod 2")));
    label115->setFont (Font (15.00f, Font::plain));
    label115->setJustificationType (Justification::centred);
    label115->setEditable (false, false, false);
    label115->setColour (Label::textColourId, Colours::white);
    label115->setColour (TextEditor::textColourId, Colours::black);
    label115->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label108 = new Label ("new label",
                                             TRANS("Osc 1")));
    label108->setFont (Font (12.00f, Font::plain));
    label108->setJustificationType (Justification::centredLeft);
    label108->setEditable (false, false, false);
    label108->setColour (Label::textColourId, Colours::white);
    label108->setColour (TextEditor::textColourId, Colours::black);
    label108->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label111 = new Label ("new label",
                                             TRANS("1+2")));
    label111->setFont (Font (12.00f, Font::plain));
    label111->setJustificationType (Justification::centredLeft);
    label111->setEditable (false, false, false);
    label111->setColour (Label::textColourId, Colours::white);
    label111->setColour (TextEditor::textColourId, Colours::black);
    label111->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label112 = new Label ("new label",
                                             TRANS("Osc 2")));
    label112->setFont (Font (12.00f, Font::plain));
    label112->setJustificationType (Justification::centredLeft);
    label112->setEditable (false, false, false);
    label112->setColour (Label::textColourId, Colours::white);
    label112->setColour (TextEditor::textColourId, Colours::black);
    label112->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label116 = new Label ("new label",
                                             TRANS("On")));
    label116->setFont (Font (12.00f, Font::plain));
    label116->setJustificationType (Justification::centredLeft);
    label116->setEditable (false, false, false);
    label116->setColour (Label::textColourId, Colours::white);
    label116->setColour (TextEditor::textColourId, Colours::black);
    label116->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label117 = new Label ("new label",
                                             TRANS("Off")));
    label117->setFont (Font (12.00f, Font::plain));
    label117->setJustificationType (Justification::centredLeft);
    label117->setEditable (false, false, false);
    label117->setColour (Label::textColourId, Colours::white);
    label117->setColour (TextEditor::textColourId, Colours::black);
    label117->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_env_vel2 = new Slider ("new label"));
    sli_env_vel2->setRange (0, 1, 0.5);
    sli_env_vel2->setSliderStyle (Slider::LinearVertical);
    sli_env_vel2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel2->addListener (this);

    addAndMakeVisible (label89 = new Label ("new label",
                                            TRANS("Env")));
    label89->setFont (Font (15.00f, Font::plain));
    label89->setJustificationType (Justification::centred);
    label89->setEditable (false, false, false);
    label89->setColour (Label::textColourId, Colours::white);
    label89->setColour (TextEditor::textColourId, Colours::black);
    label89->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_vel2 = new Slider ("Filter Velocity"));
    swi_filt_vel2->setRange (0, 1, 0.5);
    swi_filt_vel2->setSliderStyle (Slider::LinearVertical);
    swi_filt_vel2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_vel2->addListener (this);

    addAndMakeVisible (label118 = new Label ("Res",
                                             TRANS("Rate")));
    label118->setFont (Font (12.00f, Font::plain));
    label118->setJustificationType (Justification::centred);
    label118->setEditable (false, false, false);
    label118->setColour (Label::textColourId, Colours::white);
    label118->setColour (TextEditor::textColourId, Colours::black);
    label118->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label119 = new Label ("Freq",
                                             TRANS("Env")));
    label119->setFont (Font (12.00f, Font::plain));
    label119->setJustificationType (Justification::centred);
    label119->setEditable (false, false, false);
    label119->setColour (Label::textColourId, Colours::white);
    label119->setColour (TextEditor::textColourId, Colours::black);
    label119->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_env_vel3 = new Slider ("new label"));
    sli_env_vel3->setRange (0, 1, 0.5);
    sli_env_vel3->setSliderStyle (Slider::LinearVertical);
    sli_env_vel3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel3->addListener (this);

    addAndMakeVisible (label25 = new Label ("new label",
                                            TRANS("Mod 1")));
    label25->setFont (Font (15.00f, Font::plain));
    label25->setJustificationType (Justification::centred);
    label25->setEditable (false, false, false);
    label25->setColour (Label::textColourId, Colours::white);
    label25->setColour (TextEditor::textColourId, Colours::black);
    label25->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_vel3 = new Slider ("Filter Velocity"));
    swi_filt_vel3->setRange (0, 1, 0.5);
    swi_filt_vel3->setSliderStyle (Slider::LinearVertical);
    swi_filt_vel3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_vel3->addListener (this);

    addAndMakeVisible (label120 = new Label ("Res",
                                             TRANS("Rate")));
    label120->setFont (Font (12.00f, Font::plain));
    label120->setJustificationType (Justification::centred);
    label120->setEditable (false, false, false);
    label120->setColour (Label::textColourId, Colours::white);
    label120->setColour (TextEditor::textColourId, Colours::black);
    label120->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label121 = new Label ("Freq",
                                             TRANS("Amt")));
    label121->setFont (Font (12.00f, Font::plain));
    label121->setJustificationType (Justification::centred);
    label121->setEditable (false, false, false);
    label121->setColour (Label::textColourId, Colours::white);
    label121->setColour (TextEditor::textColourId, Colours::black);
    label121->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label61 = new Label ("new label",
                                            TRANS("Mod 2")));
    label61->setFont (Font (15.00f, Font::plain));
    label61->setJustificationType (Justification::centred);
    label61->setEditable (false, false, false);
    label61->setColour (Label::textColourId, Colours::white);
    label61->setColour (TextEditor::textColourId, Colours::black);
    label61->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_vel4 = new Slider ("Filter Velocity"));
    swi_filt_vel4->setRange (0, 1, 0.5);
    swi_filt_vel4->setSliderStyle (Slider::LinearVertical);
    swi_filt_vel4->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_vel4->addListener (this);

    addAndMakeVisible (label70 = new Label ("Freq",
                                            TRANS("Amt")));
    label70->setFont (Font (12.00f, Font::plain));
    label70->setJustificationType (Justification::centred);
    label70->setEditable (false, false, false);
    label70->setColour (Label::textColourId, Colours::white);
    label70->setColour (TextEditor::textColourId, Colours::black);
    label70->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent18 = new GroupComponent ("new group",
                                                              TRANS("Mod Wheel")));
    groupComponent18->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent18->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("KB Track")));
    label7->setFont (Font (12.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colours::white);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label50 = new Label ("new label",
                                            TRANS("High")));
    label50->setFont (Font (12.00f, Font::plain));
    label50->setJustificationType (Justification::centredLeft);
    label50->setEditable (false, false, false);
    label50->setColour (Label::textColourId, Colours::white);
    label50->setColour (TextEditor::textColourId, Colours::black);
    label50->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_lfo1_range = new Slider ("Mod 1 Range"));
    swi_lfo1_range->setRange (1, 2, 0.5);
    swi_lfo1_range->setSliderStyle (Slider::LinearVertical);
    swi_lfo1_range->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo1_range->addListener (this);

    addAndMakeVisible (label52 = new Label ("new label",
                                            TRANS("Low")));
    label52->setFont (Font (12.00f, Font::plain));
    label52->setJustificationType (Justification::centredLeft);
    label52->setEditable (false, false, false);
    label52->setColour (Label::textColourId, Colours::white);
    label52->setColour (TextEditor::textColourId, Colours::black);
    label52->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label40 = new Label ("new label",
                                            TRANS("Amt")));
    label40->setFont (Font (12.00f, Font::plain));
    label40->setJustificationType (Justification::centredLeft);
    label40->setEditable (false, false, false);
    label40->setColour (Label::textColourId, Colours::white);
    label40->setColour (TextEditor::textColourId, Colours::black);
    label40->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label41 = new Label ("new label",
                                            TRANS("Rate")));
    label41->setFont (Font (12.00f, Font::plain));
    label41->setJustificationType (Justification::centredLeft);
    label41->setEditable (false, false, false);
    label41->setColour (Label::textColourId, Colours::white);
    label41->setColour (TextEditor::textColourId, Colours::black);
    label41->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_mod1_from_mod2 = new Slider ("Mod 1 From Mod 2 Type"));
    swi_mod1_from_mod2->setRange (1, 2, 0.5);
    swi_mod1_from_mod2->setSliderStyle (Slider::LinearVertical);
    swi_mod1_from_mod2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_mod1_from_mod2->addListener (this);

    addAndMakeVisible (label44 = new Label ("new label",
                                            TRANS("Shape")));
    label44->setFont (Font (12.00f, Font::plain));
    label44->setJustificationType (Justification::centredLeft);
    label44->setEditable (false, false, false);
    label44->setColour (Label::textColourId, Colours::white);
    label44->setColour (TextEditor::textColourId, Colours::black);
    label44->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label82 = new Label ("new label",
                                            TRANS("From Mod 2")));
    label82->setFont (Font (15.00f, Font::plain));
    label82->setJustificationType (Justification::centred);
    label82->setEditable (false, false, false);
    label82->setColour (Label::textColourId, Colours::white);
    label82->setColour (TextEditor::textColourId, Colours::black);
    label82->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label26 = new Label ("new label",
                                            TRANS("Shape")));
    label26->setFont (Font (15.00f, Font::plain));
    label26->setJustificationType (Justification::centred);
    label26->setEditable (false, false, false);
    label26->setColour (Label::textColourId, Colours::white);
    label26->setColour (TextEditor::textColourId, Colours::black);
    label26->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_mod1_shape = new Slider ("Mod 1 Shape"));
    sli_mod1_shape->setRange (0, 10, 0);
    sli_mod1_shape->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod1_shape->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod1_shape->addListener (this);

    addAndMakeVisible (label27 = new Label ("new label",
                                            TRANS("LFO")));
    label27->setFont (Font (12.00f, Font::plain));
    label27->setJustificationType (Justification::centredLeft);
    label27->setEditable (false, false, false);
    label27->setColour (Label::textColourId, Colours::white);
    label27->setColour (TextEditor::textColourId, Colours::black);
    label27->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label33 = new Label ("new label",
                                            TRANS("Env+")));
    label33->setFont (Font (12.00f, Font::plain));
    label33->setJustificationType (Justification::centredLeft);
    label33->setEditable (false, false, false);
    label33->setColour (Label::textColourId, Colours::white);
    label33->setColour (TextEditor::textColourId, Colours::black);
    label33->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_mod2_type = new Slider ("Mod 2 Type"));
    swi_mod2_type->setRange (1, 2, 0.5);
    swi_mod2_type->setSliderStyle (Slider::LinearVertical);
    swi_mod2_type->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_mod2_type->addListener (this);

    addAndMakeVisible (label34 = new Label ("new label",
                                            TRANS("Env-")));
    label34->setFont (Font (12.00f, Font::plain));
    label34->setJustificationType (Justification::centredLeft);
    label34->setEditable (false, false, false);
    label34->setColour (Label::textColourId, Colours::white);
    label34->setColour (TextEditor::textColourId, Colours::black);
    label34->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_env_vel5 = new Slider ("new label"));
    sli_env_vel5->setRange (0, 1, 0.5);
    sli_env_vel5->setSliderStyle (Slider::LinearVertical);
    sli_env_vel5->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_env_vel5->addListener (this);

    addAndMakeVisible (label66 = new Label ("new label",
                                            TRANS("Glide")));
    label66->setFont (Font (15.00f, Font::plain));
    label66->setJustificationType (Justification::centred);
    label66->setEditable (false, false, false);
    label66->setColour (Label::textColourId, Colours::white);
    label66->setColour (TextEditor::textColourId, Colours::black);
    label66->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label68 = new Label ("Res",
                                            TRANS("Time")));
    label68->setFont (Font (12.00f, Font::plain));
    label68->setJustificationType (Justification::centred);
    label68->setEditable (false, false, false);
    label68->setColour (Label::textColourId, Colours::white);
    label68->setColour (TextEditor::textColourId, Colours::black);
    label68->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_mod2_a3 = new Slider ("Mod 2 Param A"));
    sli_mod2_a3->setRange (0, 10, 0);
    sli_mod2_a3->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod2_a3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod2_a3->addListener (this);

    addAndMakeVisible (label49 = new Label ("new label",
                                            TRANS("Mod 1")));
    label49->setFont (Font (15.00f, Font::plain));
    label49->setJustificationType (Justification::centred);
    label49->setEditable (false, false, false);
    label49->setColour (Label::textColourId, Colours::white);
    label49->setColour (TextEditor::textColourId, Colours::black);
    label49->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label69 = new Label ("new label",
                                            TRANS("Squ")));
    label69->setFont (Font (12.00f, Font::plain));
    label69->setJustificationType (Justification::centred);
    label69->setEditable (false, false, false);
    label69->setColour (Label::textColourId, Colours::white);
    label69->setColour (TextEditor::textColourId, Colours::black);
    label69->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label71 = new Label ("new label",
                                            TRANS("Tri")));
    label71->setFont (Font (12.00f, Font::plain));
    label71->setJustificationType (Justification::centred);
    label71->setEditable (false, false, false);
    label71->setColour (Label::textColourId, Colours::white);
    label71->setColour (TextEditor::textColourId, Colours::black);
    label71->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label75 = new Label ("new label",
                                            TRANS("Sin")));
    label75->setFont (Font (12.00f, Font::plain));
    label75->setJustificationType (Justification::centred);
    label75->setEditable (false, false, false);
    label75->setColour (Label::textColourId, Colours::white);
    label75->setColour (TextEditor::textColourId, Colours::black);
    label75->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (groupComponent17 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent17->setTextLabelPosition (Justification::centred);
    groupComponent17->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent17->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent19 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent19->setTextLabelPosition (Justification::centred);
    groupComponent19->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent19->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent20 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent20->setTextLabelPosition (Justification::centred);
    groupComponent20->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent20->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent21 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent21->setTextLabelPosition (Justification::centred);
    groupComponent21->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent21->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent22 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent22->setTextLabelPosition (Justification::centred);
    groupComponent22->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent22->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (groupComponent23 = new GroupComponent ("new group",
                                                              String::empty));
    groupComponent23->setTextLabelPosition (Justification::centred);
    groupComponent23->setColour (GroupComponent::outlineColourId, Colour (0x99ffffff));
    groupComponent23->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (swi_o2_sh2 = new Slider ("Pitch Mod Dest"));
    swi_o2_sh2->setRange (1, 2, 0.5);
    swi_o2_sh2->setSliderStyle (Slider::LinearVertical);
    swi_o2_sh2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_o2_sh2->addListener (this);

    addAndMakeVisible (label62 = new Label ("new label",
                                            TRANS("Osc 1")));
    label62->setFont (Font (12.00f, Font::plain));
    label62->setJustificationType (Justification::centredLeft);
    label62->setEditable (false, false, false);
    label62->setColour (Label::textColourId, Colours::white);
    label62->setColour (TextEditor::textColourId, Colours::black);
    label62->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label76 = new Label ("new label",
                                            TRANS("1+2")));
    label76->setFont (Font (12.00f, Font::plain));
    label76->setJustificationType (Justification::centredLeft);
    label76->setEditable (false, false, false);
    label76->setColour (Label::textColourId, Colours::white);
    label76->setColour (TextEditor::textColourId, Colours::black);
    label76->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label77 = new Label ("new label",
                                            TRANS("Osc 2")));
    label77->setFont (Font (12.00f, Font::plain));
    label77->setJustificationType (Justification::centredLeft);
    label77->setEditable (false, false, false);
    label77->setColour (Label::textColourId, Colours::white);
    label77->setColour (TextEditor::textColourId, Colours::black);
    label77->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_mod1_from_mod2 = new Slider ("Mod 1 From Mod 2 Amt"));
    sli_mod1_from_mod2->setRange (0, 1, 0);
    sli_mod1_from_mod2->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_mod1_from_mod2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_mod1_from_mod2->addListener (this);

    addAndMakeVisible (label80 = new Label ("new label",
                                            TRANS("Gate")));
    label80->setFont (Font (12.00f, Font::plain));
    label80->setJustificationType (Justification::centredLeft);
    label80->setEditable (false, false, false);
    label80->setColour (Label::textColourId, Colours::white);
    label80->setColour (TextEditor::textColourId, Colours::black);
    label80->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]

	LookAndFeel::setDefaultLookAndFeel(&defaultLookAndFeel);

    //[/UserPreSize]

    setSize (820, 408);


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

    groupComponent16 = nullptr;
    groupComponent11 = nullptr;
    groupComponent4 = nullptr;
    groupComponent14 = nullptr;
    groupComponent10 = nullptr;
    groupComponent12 = nullptr;
    groupComponent2 = nullptr;
    groupComponent6 = nullptr;
    groupComponent13 = nullptr;
    groupComponent3 = nullptr;
    swi_filt_poles = nullptr;
    groupComponent = nullptr;
    sli_o1_sh = nullptr;
    groupComponent8 = nullptr;
    groupComponent5 = nullptr;
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
    sli_drive = nullptr;
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
    groupComponent9 = nullptr;
    sli_glide_amt = nullptr;
    label28 = nullptr;
    sli_mod2_a = nullptr;
    label29 = nullptr;
    sli_env_dec = nullptr;
    sli_env_sus = nullptr;
    sli_env_rel = nullptr;
    sli_env_vel = nullptr;
    sli_aenv_vel = nullptr;
    sli_mod1_rate = nullptr;
    label51 = nullptr;
    label53 = nullptr;
    label54 = nullptr;
    label55 = nullptr;
    label56 = nullptr;
    label57 = nullptr;
    label58 = nullptr;
    label59 = nullptr;
    swi_o1_sh = nullptr;
    swi_sub_sh = nullptr;
    swi_sub_oct = nullptr;
    label63 = nullptr;
    label64 = nullptr;
    label65 = nullptr;
    swi_glide = nullptr;
    label23 = nullptr;
    label72 = nullptr;
    label73 = nullptr;
    swi_filt_kb = nullptr;
    label78 = nullptr;
    swi_o2_sync = nullptr;
    label79 = nullptr;
    label84 = nullptr;
    label85 = nullptr;
    label86 = nullptr;
    swi_o2_sh = nullptr;
    label100 = nullptr;
    label101 = nullptr;
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
    swi_retrig_mode = nullptr;
    label46 = nullptr;
    label35 = nullptr;
    label47 = nullptr;
    swi_vco2_oct = nullptr;
    label48 = nullptr;
    sli_mod2_b = nullptr;
    label31 = nullptr;
    label94 = nullptr;
    label24 = nullptr;
    sli_env_vel_ampl = nullptr;
    label96 = nullptr;
    label97 = nullptr;
    label30 = nullptr;
    label98 = nullptr;
    label99 = nullptr;
    label109 = nullptr;
    label32 = nullptr;
    label74 = nullptr;
    sli_o1_shapeMod = nullptr;
    swi_o1_shapeMod_src = nullptr;
    groupComponent15 = nullptr;
    swi_o2_sh4 = nullptr;
    sli_mod2_a2 = nullptr;
    label114 = nullptr;
    sli_filt_mod1 = nullptr;
    label60 = nullptr;
    sli_filt_mod2 = nullptr;
    label115 = nullptr;
    label108 = nullptr;
    label111 = nullptr;
    label112 = nullptr;
    label116 = nullptr;
    label117 = nullptr;
    sli_env_vel2 = nullptr;
    label89 = nullptr;
    swi_filt_vel2 = nullptr;
    label118 = nullptr;
    label119 = nullptr;
    sli_env_vel3 = nullptr;
    label25 = nullptr;
    swi_filt_vel3 = nullptr;
    label120 = nullptr;
    label121 = nullptr;
    label61 = nullptr;
    swi_filt_vel4 = nullptr;
    label70 = nullptr;
    groupComponent18 = nullptr;
    label7 = nullptr;
    label50 = nullptr;
    swi_lfo1_range = nullptr;
    label52 = nullptr;
    label40 = nullptr;
    label41 = nullptr;
    swi_mod1_from_mod2 = nullptr;
    label44 = nullptr;
    label82 = nullptr;
    label26 = nullptr;
    sli_mod1_shape = nullptr;
    label27 = nullptr;
    label33 = nullptr;
    swi_mod2_type = nullptr;
    label34 = nullptr;
    sli_env_vel5 = nullptr;
    label66 = nullptr;
    label68 = nullptr;
    sli_mod2_a3 = nullptr;
    label49 = nullptr;
    label69 = nullptr;
    label71 = nullptr;
    label75 = nullptr;
    groupComponent17 = nullptr;
    groupComponent19 = nullptr;
    groupComponent20 = nullptr;
    groupComponent21 = nullptr;
    groupComponent22 = nullptr;
    groupComponent23 = nullptr;
    swi_o2_sh2 = nullptr;
    label62 = nullptr;
    label76 = nullptr;
    label77 = nullptr;
    sli_mod1_from_mod2 = nullptr;
    label80 = nullptr;


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

    groupComponent16->setBounds (368, 309, 452, 96);
    groupComponent11->setBounds (118, 309, 122, 96);
    groupComponent4->setBounds (245, 216, 266, 96);
    groupComponent14->setBounds (245, 124, 164, 96);
    groupComponent10->setBounds (2, 124, 238, 96);
    groupComponent12->setBounds (657, 216, 162, 96);
    groupComponent2->setBounds (245, 0, 266, 128);
    groupComponent6->setBounds (657, 124, 162, 96);
    groupComponent13->setBounds (1400, -128, 240, 80);
    groupComponent3->setBounds (516, 0, 136, 312);
    swi_filt_poles->setBounds (529, 141, 56, 20);
    groupComponent->setBounds (-280, -72, 144, 100);
    sli_o1_sh->setBounds (294, 161, 48, 48);
    groupComponent8->setBounds (2, 309, 113, 96);
    groupComponent5->setBounds (414, 124, 97, 96);
    sli_mix_o1->setBounds (300, 32, 24, 88);
    sli_mix_o2->setBounds (332, 32, 24, 88);
    sli_mix_sub->setBounds (364, 32, 24, 88);
    sli_mix_ring->setBounds (396, 32, 24, 88);
    sli_mix_noise->setBounds (428, 32, 24, 88);
    label->setBounds (292, 16, 40, 16);
    label2->setBounds (324, 16, 39, 16);
    label3->setBounds (356, 16, 40, 16);
    label4->setBounds (388, 16, 39, 16);
    label5->setBounds (420, 16, 40, 16);
    sli_o2_tune->setBounds (407, 252, 56, 56);
    label8->setBounds (407, 232, 56, 16);
    sli_filt_freq->setBounds (532, 40, 104, 88);
    label13->setBounds (524, 20, 120, 16);
    sli_filt_res->setBounds (588, 205, 56, 48);
    sli_filt_env->setBounds (524, 268, 32, 32);
    sli_drive->setBounds (747, 161, 56, 48);
    sli_o2_finetune->setBounds (466, 252, 32, 32);
    label6->setBounds (467, 235, 29, 12);
    label9->setBounds (520, 253, 40, 16);
    label10->setBounds (580, 189, 72, 16);
    label11->setBounds (743, 143, 64, 15);
    groupComponent7->setBounds (657, 0, 162, 128);
    sli_env_att->setBounds (678, 32, 24, 88);
    label17->setBounds (678, 16, 24, 16);
    label18->setBounds (709, 16, 24, 16);
    label19->setBounds (740, 16, 24, 16);
    label20->setBounds (771, 16, 24, 16);
    sli_filt_gain->setBounds (523, 205, 56, 48);
    label21->setBounds (522, 189, 56, 16);
    groupComponent9->setBounds (1, 0, 238, 128);
    sli_glide_amt->setBounds (125, 338, 56, 48);
    label28->setBounds (93, 16, 48, 16);
    sli_mod2_a->setBounds (102, 161, 48, 48);
    label29->setBounds (102, 143, 48, 16);
    sli_env_dec->setBounds (709, 32, 24, 88);
    sli_env_sus->setBounds (740, 32, 24, 88);
    sli_env_rel->setBounds (771, 32, 24, 88);
    sli_env_vel->setBounds (592, 348, 20, 56);
    sli_aenv_vel->setBounds (383, 356, 48, 48);
    sli_mod1_rate->setBounds (93, 31, 48, 48);
    label51->setBounds (263, 163, 32, 12);
    label53->setBounds (263, 178, 32, 12);
    label54->setBounds (263, 193, 32, 12);
    label55->setBounds (476, 163, 42, 12);
    label56->setBounds (476, 178, 32, 12);
    label57->setBounds (476, 193, 32, 12);
    label58->setBounds (439, 163, 22, 10);
    label59->setBounds (439, 195, 22, 10);
    swi_o1_sh->setBounds (248, 155, 20, 56);
    swi_sub_sh->setBounds (462, 155, 20, 56);
    swi_sub_oct->setBounds (425, 155, 20, 56);
    label63->setBounds (197, 341, 32, 10);
    label64->setBounds (197, 356, 39, 12);
    label65->setBounds (197, 373, 32, 10);
    swi_glide->setBounds (181, 333, 20, 56);
    label23->setBounds (575, 143, 24, 16);
    label72->setBounds (516, 143, 24, 16);
    label73->setBounds (591, 143, 56, 16);
    swi_filt_kb->setBounds (529, 165, 56, 20);
    label78->setBounds (591, 169, 56, 16);
    swi_o2_sync->setBounds (310, 247, 20, 56);
    label79->setBounds (312, 232, 44, 16);
    label84->setBounds (263, 255, 32, 12);
    label85->setBounds (263, 270, 32, 12);
    label86->setBounds (263, 285, 32, 12);
    swi_o2_sh->setBounds (248, 247, 20, 56);
    label100->setBounds (246, 232, 48, 16);
    label101->setBounds (252, 143, 87, 16);
    label110->setBounds (537, 117, 25, 16);
    label124->setBounds (606, 117, 36, 16);
    label125->setBounds (515, 60, 31, 16);
    label126->setBounds (595, 35, 27, 16);
    label127->setBounds (621, 95, 36, 16);
    label36->setBounds (396, 331, 88, 12);
    label14->setBounds (445, 356, 54, 10);
    label15->setBounds (445, 371, 54, 10);
    label16->setBounds (445, 386, 54, 10);
    swi_pitchmod_src2->setBounds (429, 348, 20, 56);
    label38->setBounds (685, 163, 60, 12);
    label39->setBounds (685, 193, 72, 12);
    swi_vcasource->setBounds (669, 155, 20, 56);
    sli_drive2->setBounds (747, 253, 56, 48);
    label12->setBounds (747, 232, 56, 16);
    label22->setBounds (665, 232, 56, 16);
    label42->setBounds (685, 256, 32, 10);
    label45->setBounds (685, 271, 32, 10);
    label67->setBounds (685, 286, 32, 10);
    swi_glide2->setBounds (669, 247, 20, 56);
    label37->setBounds (30, 341, 42, 12);
    label43->setBounds (30, 357, 76, 12);
    swi_retrig_mode->setBounds (12, 333, 20, 56);
    label46->setBounds (30, 373, 48, 12);
    label35->setBounds (380, 255, 24, 12);
    label47->setBounds (380, 285, 24, 12);
    swi_vco2_oct->setBounds (366, 247, 20, 56);
    label48->setBounds (376, 235, 29, 12);
    sli_mod2_b->setBounds (164, 161, 48, 48);
    label31->setBounds (164, 143, 48, 16);
    label94->setBounds (31, 143, 56, 16);
    label24->setBounds (558, 321, 89, 16);
    sli_env_vel_ampl->setBounds (560, 348, 20, 56);
    label96->setBounds (585, 340, 32, 10);
    label97->setBounds (555, 340, 32, 10);
    label30->setBounds (499, 355, 30, 12);
    label98->setBounds (499, 371, 30, 12);
    label99->setBounds (499, 387, 30, 12);
    label109->setBounds (345, 198, 16, 12);
    label32->setBounds (384, 198, 16, 12);
    label74->setBounds (353, 148, 40, 12);
    sli_o1_shapeMod->setBounds (357, 162, 32, 32);
    swi_o1_shapeMod_src->setBounds (353, 196, 40, 16);
    groupComponent15->setBounds (2, 216, 238, 96);
    swi_o2_sh4->setBounds (178, 247, 20, 56);
    sli_mod2_a2->setBounds (127, 253, 48, 48);
    label114->setBounds (123, 232, 96, 16);
    sli_filt_mod1->setBounds (567, 268, 32, 32);
    label60->setBounds (558, 253, 50, 16);
    sli_filt_mod2->setBounds (609, 268, 32, 32);
    label115->setBounds (603, 253, 50, 16);
    label108->setBounds (195, 255, 40, 12);
    label111->setBounds (195, 270, 40, 12);
    label112->setBounds (195, 285, 40, 12);
    label116->setBounds (327, 255, 32, 12);
    label117->setBounds (327, 285, 32, 12);
    sli_env_vel2->setBounds (656, 348, 20, 56);
    label89->setBounds (646, 321, 39, 16);
    swi_filt_vel2->setBounds (624, 348, 20, 56);
    label118->setBounds (649, 340, 32, 10);
    label119->setBounds (619, 340, 32, 10);
    sli_env_vel3->setBounds (720, 348, 20, 56);
    label25->setBounds (683, 321, 64, 16);
    swi_filt_vel3->setBounds (688, 348, 20, 56);
    label120->setBounds (713, 340, 32, 10);
    label121->setBounds (683, 340, 32, 10);
    label61->setBounds (736, 321, 53, 16);
    swi_filt_vel4->setBounds (752, 348, 20, 56);
    label70->setBounds (747, 340, 32, 10);
    groupComponent18->setBounds (245, 309, 118, 96);
    label7->setBounds (101, 78, 56, 12);
    label50->setBounds (101, 94, 46, 12);
    swi_lfo1_range->setBounds (87, 70, 20, 56);
    label52->setBounds (101, 110, 46, 12);
    label40->setBounds (186, 76, 40, 12);
    label41->setBounds (186, 92, 40, 12);
    swi_mod1_from_mod2->setBounds (168, 70, 20, 56);
    label44->setBounds (186, 108, 40, 12);
    label82->setBounds (161, 16, 76, 16);
    label26->setBounds (15, 16, 48, 16);
    sli_mod1_shape->setBounds (15, 43, 48, 48);
    label27->setBounds (42, 163, 40, 12);
    label33->setBounds (42, 179, 40, 12);
    swi_mod2_type->setBounds (28, 155, 20, 56);
    label34->setBounds (42, 195, 40, 12);
    sli_env_vel5->setBounds (528, 348, 20, 56);
    label66->setBounds (518, 321, 39, 16);
    label68->setBounds (521, 340, 32, 10);
    sli_mod2_a3->setBounds (10, 253, 48, 48);
    label49->setBounds (6, 232, 96, 16);
    label69->setBounds (47, 87, 29, 10);
    label71->setBounds (7, 87, 27, 10);
    label75->setBounds (23, 34, 30, 10);
    groupComponent17->setBounds (239, 0, 7, 408);
    groupComponent19->setBounds (510, 0, 7, 312);
    groupComponent20->setBounds (651, 0, 7, 312);
    groupComponent21->setBounds (408, 124, 7, 96);
    groupComponent22->setBounds (362, 309, 7, 96);
    groupComponent23->setBounds (113, 309, 7, 96);
    swi_o2_sh2->setBounds (62, 247, 20, 56);
    label62->setBounds (79, 255, 40, 12);
    label76->setBounds (79, 270, 40, 12);
    label77->setBounds (79, 285, 40, 12);
    sli_mod1_from_mod2->setBounds (184, 37, 32, 32);
    label80->setBounds (685, 178, 59, 12);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainGui::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == swi_filt_poles)
    {
        //[UserSliderCode_swi_filt_poles] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_poles]
    }
    else if (sliderThatWasMoved == sli_o1_sh)
    {
        //[UserSliderCode_sli_o1_sh] -- add your slider handling code here..
        //[/UserSliderCode_sli_o1_sh]
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
    else if (sliderThatWasMoved == sli_drive)
    {
        //[UserSliderCode_sli_drive] -- add your slider handling code here..
        //[/UserSliderCode_sli_drive]
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
    else if (sliderThatWasMoved == sli_glide_amt)
    {
        //[UserSliderCode_sli_glide_amt] -- add your slider handling code here..
        //[/UserSliderCode_sli_glide_amt]
    }
    else if (sliderThatWasMoved == sli_mod2_a)
    {
        //[UserSliderCode_sli_mod2_a] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod2_a]
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
    else if (sliderThatWasMoved == sli_mod1_rate)
    {
        //[UserSliderCode_sli_mod1_rate] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod1_rate]
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
    else if (sliderThatWasMoved == swi_filt_kb)
    {
        //[UserSliderCode_swi_filt_kb] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_kb]
    }
    else if (sliderThatWasMoved == swi_o2_sync)
    {
        //[UserSliderCode_swi_o2_sync] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_sync]
    }
    else if (sliderThatWasMoved == swi_o2_sh)
    {
        //[UserSliderCode_swi_o2_sh] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_sh]
    }
    else if (sliderThatWasMoved == swi_pitchmod_src2)
    {
        //[UserSliderCode_swi_pitchmod_src2] -- add your slider handling code here..
        //[/UserSliderCode_swi_pitchmod_src2]
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
    else if (sliderThatWasMoved == swi_retrig_mode)
    {
        //[UserSliderCode_swi_retrig_mode] -- add your slider handling code here..
        //[/UserSliderCode_swi_retrig_mode]
    }
    else if (sliderThatWasMoved == swi_vco2_oct)
    {
        //[UserSliderCode_swi_vco2_oct] -- add your slider handling code here..
        //[/UserSliderCode_swi_vco2_oct]
    }
    else if (sliderThatWasMoved == sli_mod2_b)
    {
        //[UserSliderCode_sli_mod2_b] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod2_b]
    }
    else if (sliderThatWasMoved == sli_env_vel_ampl)
    {
        //[UserSliderCode_sli_env_vel_ampl] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_vel_ampl]
    }
    else if (sliderThatWasMoved == sli_o1_shapeMod)
    {
        //[UserSliderCode_sli_o1_shapeMod] -- add your slider handling code here..
        //[/UserSliderCode_sli_o1_shapeMod]
    }
    else if (sliderThatWasMoved == swi_o1_shapeMod_src)
    {
        //[UserSliderCode_swi_o1_shapeMod_src] -- add your slider handling code here..
        //[/UserSliderCode_swi_o1_shapeMod_src]
    }
    else if (sliderThatWasMoved == swi_o2_sh4)
    {
        //[UserSliderCode_swi_o2_sh4] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_sh4]
    }
    else if (sliderThatWasMoved == sli_mod2_a2)
    {
        //[UserSliderCode_sli_mod2_a2] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod2_a2]
    }
    else if (sliderThatWasMoved == sli_filt_mod1)
    {
        //[UserSliderCode_sli_filt_mod1] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_mod1]
    }
    else if (sliderThatWasMoved == sli_filt_mod2)
    {
        //[UserSliderCode_sli_filt_mod2] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_mod2]
    }
    else if (sliderThatWasMoved == sli_env_vel2)
    {
        //[UserSliderCode_sli_env_vel2] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_vel2]
    }
    else if (sliderThatWasMoved == swi_filt_vel2)
    {
        //[UserSliderCode_swi_filt_vel2] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_vel2]
    }
    else if (sliderThatWasMoved == sli_env_vel3)
    {
        //[UserSliderCode_sli_env_vel3] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_vel3]
    }
    else if (sliderThatWasMoved == swi_filt_vel3)
    {
        //[UserSliderCode_swi_filt_vel3] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_vel3]
    }
    else if (sliderThatWasMoved == swi_filt_vel4)
    {
        //[UserSliderCode_swi_filt_vel4] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_vel4]
    }
    else if (sliderThatWasMoved == swi_lfo1_range)
    {
        //[UserSliderCode_swi_lfo1_range] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo1_range]
    }
    else if (sliderThatWasMoved == swi_mod1_from_mod2)
    {
        //[UserSliderCode_swi_mod1_from_mod2] -- add your slider handling code here..
        //[/UserSliderCode_swi_mod1_from_mod2]
    }
    else if (sliderThatWasMoved == sli_mod1_shape)
    {
        //[UserSliderCode_sli_mod1_shape] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod1_shape]
    }
    else if (sliderThatWasMoved == swi_mod2_type)
    {
        //[UserSliderCode_swi_mod2_type] -- add your slider handling code here..
        //[/UserSliderCode_swi_mod2_type]
    }
    else if (sliderThatWasMoved == sli_env_vel5)
    {
        //[UserSliderCode_sli_env_vel5] -- add your slider handling code here..
        //[/UserSliderCode_sli_env_vel5]
    }
    else if (sliderThatWasMoved == sli_mod2_a3)
    {
        //[UserSliderCode_sli_mod2_a3] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod2_a3]
    }
    else if (sliderThatWasMoved == swi_o2_sh2)
    {
        //[UserSliderCode_swi_o2_sh2] -- add your slider handling code here..
        //[/UserSliderCode_swi_o2_sh2]
    }
    else if (sliderThatWasMoved == sli_mod1_from_mod2)
    {
        //[UserSliderCode_sli_mod1_from_mod2] -- add your slider handling code here..
        //[/UserSliderCode_sli_mod1_from_mod2]
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
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="820"
                 initialHeight="408">
  <BACKGROUND backgroundColour="ff1c1c1c"/>
  <GROUPCOMPONENT name="new group" id="b2f9541b359ca4e4" memberName="groupComponent16"
                  virtualName="" explicitFocusOrder="0" pos="368 309 452 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Velocity"/>
  <GROUPCOMPONENT name="new group" id="f4df9d35924c55e8" memberName="groupComponent11"
                  virtualName="" explicitFocusOrder="0" pos="118 309 122 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Glide"/>
  <GROUPCOMPONENT name="new group" id="3c0dca09a310f370" memberName="groupComponent4"
                  virtualName="" explicitFocusOrder="0" pos="245 216 266 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Osc 2"/>
  <GROUPCOMPONENT name="new group" id="7a201a096780ea78" memberName="groupComponent14"
                  virtualName="" explicitFocusOrder="0" pos="245 124 164 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Osc 1"/>
  <GROUPCOMPONENT name="new group" id="2f9f6ffa0d9e55e2" memberName="groupComponent10"
                  virtualName="" explicitFocusOrder="0" pos="2 124 238 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Mod 2 (LFO/Envelope)"/>
  <GROUPCOMPONENT name="new group" id="9da2be2e767c916e" memberName="groupComponent12"
                  virtualName="" explicitFocusOrder="0" pos="657 216 162 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Effects"/>
  <GROUPCOMPONENT name="new group" id="2bd57dadf55e124b" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="245 0 266 128" outlinecol="99ffffff"
                  textcol="ffffffff" title="Oscillators"/>
  <GROUPCOMPONENT name="new group" id="d354cd4b1913022f" memberName="groupComponent6"
                  virtualName="" explicitFocusOrder="0" pos="657 124 162 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="VCA"/>
  <GROUPCOMPONENT name="new group" id="4290aa3f94cba83c" memberName="groupComponent13"
                  virtualName="" explicitFocusOrder="0" pos="1400 -128 240 80"
                  outlinecol="66ffffff" textcol="ffffffff" title="Effects"/>
  <GROUPCOMPONENT name="new group" id="b5f4751ee1ed8057" memberName="groupComponent3"
                  virtualName="" explicitFocusOrder="0" pos="516 0 136 312" outlinecol="99ffffff"
                  textcol="ffffffff" title="Filter"/>
  <SLIDER name="Filter Poles" id="9366d7598a118d48" memberName="swi_filt_poles"
          virtualName="" explicitFocusOrder="0" pos="529 141 56 20" min="2"
          max="4" int="2" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="9fb59b5f6494cccc" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="-280 -72 144 100"
                  outlinecol="99ffffff" textcol="ffffffff" title="Osc1"/>
  <SLIDER name="Osc 1 Shape" id="13d0d9d98ecd6c62" memberName="sli_o1_sh"
          virtualName="" explicitFocusOrder="0" pos="294 161 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="d9483dc1d74a73c9" memberName="groupComponent8"
                  virtualName="" explicitFocusOrder="0" pos="2 309 113 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Mono Mode"/>
  <GROUPCOMPONENT name="new group" id="f6c32fd096d279ac" memberName="groupComponent5"
                  virtualName="" explicitFocusOrder="0" pos="414 124 97 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Sub"/>
  <SLIDER name="Osc 1 Mix" id="746c27abdb30c3f3" memberName="sli_mix_o1"
          virtualName="" explicitFocusOrder="0" pos="300 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 2 Mix" id="ce7d24772767eab2" memberName="sli_mix_o2"
          virtualName="" explicitFocusOrder="0" pos="332 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Mix" id="c473607e8321130a" memberName="sli_mix_sub"
          virtualName="" explicitFocusOrder="0" pos="364 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Ring Mod Mix" id="3da0d3c7747b8bc" memberName="sli_mix_ring"
          virtualName="" explicitFocusOrder="0" pos="396 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Noise Mix" id="a0d38f18199b6967" memberName="sli_mix_noise"
          virtualName="" explicitFocusOrder="0" pos="428 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3037bbda4f7de879" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="292 16 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="8c2ee959913bd57b" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="324 16 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="92542b3e1c3bed26" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="356 16 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sub" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="6278c010791905e2" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="388 16 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Ring" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <LABEL name="new label" id="f8c149110071038a" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="420 16 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Noise" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="12"/>
  <SLIDER name="Osc 2 Coarse Tune" id="3d1bb66ede0105e3" memberName="sli_o2_tune"
          virtualName="" explicitFocusOrder="0" pos="407 252 56 56" min="-7"
          max="7" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="119ab5d1772f94fd" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="407 232 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tuning" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Frequency" id="922a8512e459ea78" memberName="sli_filt_freq"
          virtualName="" explicitFocusOrder="0" pos="532 40 104 88" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="688179c92518c30a" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="524 20 120 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Frequency" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Resonance" id="4e819dd141ad6884" memberName="sli_filt_res"
          virtualName="" explicitFocusOrder="0" pos="588 205 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Filter Env Amount" id="bf7ee7b16a44fd46" memberName="sli_filt_env"
          virtualName="" explicitFocusOrder="0" pos="524 268 32 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Overdrive" id="3be38c3ceff9b1f2" memberName="sli_drive"
          virtualName="" explicitFocusOrder="0" pos="747 161 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 2 Fine Tune" id="d9194a49db24b17e" memberName="sli_o2_finetune"
          virtualName="" explicitFocusOrder="0" pos="466 252 32 32" min="-1"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fd2d7af415f27f29" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="467 235 29 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Fine" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="419f2d32f5cd22a5" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="520 253 40 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="eebe59db1e731703" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="580 189 72 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b942b70f43767d13" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="743 143 64 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Overdrive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="8e4a429367bb6ed1" memberName="groupComponent7"
                  virtualName="" explicitFocusOrder="0" pos="657 0 162 128" outlinecol="99ffffff"
                  textcol="ffffffff" title="Envelope"/>
  <SLIDER name="Env Attack" id="9256184baa5e0e12" memberName="sli_env_att"
          virtualName="" explicitFocusOrder="0" pos="678 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="63d1beb2781877c5" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="678 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="A" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="bc2e22f7640f2440" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="709 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="D" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a76ec9d2625ae5a3" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="740 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="S" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="42f9bf81569b1e57" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="771 16 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="R" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Gain" id="d11eaf494d445128" memberName="sli_filt_gain"
          virtualName="" explicitFocusOrder="0" pos="523 205 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="abf1632f3009ec70" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="522 189 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="d530435b1472d6bd" memberName="groupComponent9"
                  virtualName="" explicitFocusOrder="0" pos="1 0 238 128" outlinecol="99ffffff"
                  textcol="ffffffff" title="Mod 1 (LFO)"/>
  <SLIDER name="new slider" id="ca4ffa3f27169af8" memberName="sli_glide_amt"
          virtualName="" explicitFocusOrder="0" pos="125 338 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="1ecd7ab8e03bb46a" memberName="label28" virtualName=""
         explicitFocusOrder="0" pos="93 16 48 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Rate" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="Mod 2 Attack" id="320ebe3eb3fc4ddf" memberName="sli_mod2_a"
          virtualName="" explicitFocusOrder="0" pos="102 161 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="ef22716764130697" memberName="label29" virtualName=""
         explicitFocusOrder="0" pos="102 143 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Env Decay" id="22d76f58418fb20b" memberName="sli_env_dec"
          virtualName="" explicitFocusOrder="0" pos="709 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Sustain" id="19781c82024cb700" memberName="sli_env_sus"
          virtualName="" explicitFocusOrder="0" pos="740 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Release" id="e6a3be71b101f31f" memberName="sli_env_rel"
          virtualName="" explicitFocusOrder="0" pos="771 32 24 88" min="0"
          max="10" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Env Vel Rate" id="ccc08de89b923d42" memberName="sli_env_vel"
          virtualName="" explicitFocusOrder="0" pos="592 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Amp Env Velocity" id="52f95a0d1dc63936" memberName="sli_aenv_vel"
          virtualName="" explicitFocusOrder="0" pos="383 356 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Mod 1 Rate" id="b473ed648319c3c5" memberName="sli_mod1_rate"
          virtualName="" explicitFocusOrder="0" pos="93 31 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a64876f8e639f198" memberName="label51" virtualName=""
         explicitFocusOrder="0" pos="263 163 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="db9a93b2d2513aac" memberName="label53" virtualName=""
         explicitFocusOrder="0" pos="263 178 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rect" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="59ee6ba7e3eb521f" memberName="label54" virtualName=""
         explicitFocusOrder="0" pos="263 193 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a1b7c767ce93174" memberName="label55" virtualName=""
         explicitFocusOrder="0" pos="476 163 42 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pulse" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e6118cecc0940531" memberName="label56" virtualName=""
         explicitFocusOrder="0" pos="476 178 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Squ" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d4f6a5cfc0a64135" memberName="label57" virtualName=""
         explicitFocusOrder="0" pos="476 193 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b9ef87d8f2eb14bf" memberName="label58" virtualName=""
         explicitFocusOrder="0" pos="439 163 22 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="-1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e930acfdc20baad5" memberName="label59" virtualName=""
         explicitFocusOrder="0" pos="439 195 22 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="-2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 1 Wave" id="e145a51361506cda" memberName="swi_o1_sh"
          virtualName="" explicitFocusOrder="0" pos="248 155 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Osc Wave" id="38673bb6b3afd895" memberName="swi_sub_sh"
          virtualName="" explicitFocusOrder="0" pos="462 155 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Sub Osc Octave" id="9ad005c2310e0623" memberName="swi_sub_oct"
          virtualName="" explicitFocusOrder="0" pos="425 155 20 56" min="-2"
          max="-1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="acbac73778a2cdcf" memberName="label63" virtualName=""
         explicitFocusOrder="0" pos="197 341 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="On" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6394f8f8d3f8e81f" memberName="label64" virtualName=""
         explicitFocusOrder="0" pos="197 356 39 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Legato" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c5fcdbfac6f2e29" memberName="label65" virtualName=""
         explicitFocusOrder="0" pos="197 373 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Off" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="692296ee6459bc79" memberName="swi_glide"
          virtualName="" explicitFocusOrder="0" pos="181 333 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="678fadab46d9a69e" memberName="label23" virtualName=""
         explicitFocusOrder="0" pos="575 143 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="4" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f1ef89eff647ee05" memberName="label72" virtualName=""
         explicitFocusOrder="0" pos="516 143 24 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="51b1c7c05b9444c0" memberName="label73" virtualName=""
         explicitFocusOrder="0" pos="591 143 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Poles" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter KB Track" id="3aff6026701ab6fc" memberName="swi_filt_kb"
          virtualName="" explicitFocusOrder="0" pos="529 165 56 20" min="0"
          max="1" int="0.5" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c953c9b10bd66654" memberName="label78" virtualName=""
         explicitFocusOrder="0" pos="591 169 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="KB Track" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Osc 2 Sync" id="1dfe389adfa42abd" memberName="swi_o2_sync"
          virtualName="" explicitFocusOrder="0" pos="310 247 20 56" min="0"
          max="1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a7e9361804280688" memberName="label79" virtualName=""
         explicitFocusOrder="0" pos="312 232 44 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Sync" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8ab6e14003e4ade2" memberName="label84" virtualName=""
         explicitFocusOrder="0" pos="263 255 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Saw" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9c21a2ecab495cad" memberName="label85" virtualName=""
         explicitFocusOrder="0" pos="263 270 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rect" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2ddc4676c3df97a3" memberName="label86" virtualName=""
         explicitFocusOrder="0" pos="263 285 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tri" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 2 Wave" id="3b884ec8bb678763" memberName="swi_o2_sh"
          virtualName="" explicitFocusOrder="0" pos="248 247 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="37928afa14c5ad1d" memberName="label100"
         virtualName="" explicitFocusOrder="0" pos="246 232 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="c2258f9a17615d4c" memberName="label101"
         virtualName="" explicitFocusOrder="0" pos="252 143 87 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="b19745e0adb6724e" memberName="label110"
         virtualName="" explicitFocusOrder="0" pos="537 117 25 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="20" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="944c47c83029687f" memberName="label124"
         virtualName="" explicitFocusOrder="0" pos="606 117 36 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="20k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="62201f3d19ea01a7" memberName="label125"
         virtualName="" explicitFocusOrder="0" pos="515 60 31 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="100" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="2aad2e8c6ad2f227" memberName="label126"
         virtualName="" explicitFocusOrder="0" pos="595 35 27 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a896398c2324146" memberName="label127" virtualName=""
         explicitFocusOrder="0" pos="621 95 36 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="10k" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="94d0f1fdc830d927" memberName="label36" virtualName=""
         explicitFocusOrder="0" pos="396 331 88 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amplitude" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="244dc8a10230e796" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="445 356 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pre-Filter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7f97df13b20ff493" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="445 371 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pre-Drive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8deaa9617e51ea95" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="445 386 54 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Post-Drive" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="8718f1916d2e3d17" memberName="swi_pitchmod_src2"
          virtualName="" explicitFocusOrder="0" pos="429 348 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="93a34653caa27da8" memberName="label38" virtualName=""
         explicitFocusOrder="0" pos="685 163 60 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Envelope" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="729da4349ae748c5" memberName="label39" virtualName=""
         explicitFocusOrder="0" pos="685 193 72 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gate + Click" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="VCA Source" id="7e89d72d33aa2bf1" memberName="swi_vcasource"
          virtualName="" explicitFocusOrder="0" pos="669 155 20 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Reverb Amount" id="2fea1fd25759315c" memberName="sli_drive2"
          virtualName="" explicitFocusOrder="0" pos="747 253 56 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="bebd7aba5523fced" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="747 232 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Reverb" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="12bca2c7f5f38bbb" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="665 232 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Chorus" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ab1e31df4ab51c63" memberName="label42" virtualName=""
         explicitFocusOrder="0" pos="685 256 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f92210fee39471d6" memberName="label45" virtualName=""
         explicitFocusOrder="0" pos="685 271 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c423afd097d508bb" memberName="label67" virtualName=""
         explicitFocusOrder="0" pos="685 286 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Off" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Chorus" id="b4a58afcd4823304" memberName="swi_glide2" virtualName=""
          explicitFocusOrder="0" pos="669 247 20 56" min="0" max="2" int="1"
          style="LinearVertical" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="b85c9abef7437058" memberName="label37" virtualName=""
         explicitFocusOrder="0" pos="30 341 42 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Legato" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="a56c1c55f79cdd1d" memberName="label43" virtualName=""
         explicitFocusOrder="0" pos="30 357 76 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pedal Legato" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Retrigger Mode" id="97cedc0ad434b4b" memberName="swi_retrig_mode"
          virtualName="" explicitFocusOrder="0" pos="12 333 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="ccea09327fffd238" memberName="label46" virtualName=""
         explicitFocusOrder="0" pos="30 373 48 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Retrig" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5517c63f3d6d88b9" memberName="label35" virtualName=""
         explicitFocusOrder="0" pos="380 255 24 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="+1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d9aeaf9addceab1e" memberName="label47" virtualName=""
         explicitFocusOrder="0" pos="380 285 24 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Osc 2 Octave" id="73f117a62518004f" memberName="swi_vco2_oct"
          virtualName="" explicitFocusOrder="0" pos="366 247 20 56" min="-2"
          max="-1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="158c0a0124d74c60" memberName="label48" virtualName=""
         explicitFocusOrder="0" pos="376 235 29 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Oct" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="Mod 2 Decay" id="fcbb3ebf60decb49" memberName="sli_mod2_b"
          virtualName="" explicitFocusOrder="0" pos="164 161 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8854676ee05c0d17" memberName="label31" virtualName=""
         explicitFocusOrder="0" pos="164 143 48 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Decay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a970c357fc51d319" memberName="label94" virtualName=""
         explicitFocusOrder="0" pos="31 143 56 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Type" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="8bf1c7a80584439e" memberName="label24" virtualName=""
         explicitFocusOrder="0" pos="558 321 89 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Filter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Env Vel Amp" id="3903de77e7991b2" memberName="sli_env_vel_ampl"
          virtualName="" explicitFocusOrder="0" pos="560 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="45106067e65ceab6" memberName="label96" virtualName=""
         explicitFocusOrder="0" pos="585 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Res" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="9e24352991170c81" memberName="label97" virtualName=""
         explicitFocusOrder="0" pos="555 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Freq" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="ec6c6eafdaa0f296" memberName="label30" virtualName=""
         explicitFocusOrder="0" pos="499 355 30 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="eaf06c61dec091b6" memberName="label98" virtualName=""
         explicitFocusOrder="0" pos="499 371 30 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0.5" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="4ff8290fdbb3ec1c" memberName="label99" virtualName=""
         explicitFocusOrder="0" pos="499 387 30 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="b13dc5a657b3f527" memberName="label109"
         virtualName="" explicitFocusOrder="0" pos="345 198 16 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <LABEL name="new label" id="440923ae122bcd95" memberName="label32" virtualName=""
         explicitFocusOrder="0" pos="384 198 16 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5fad1191a5333e86" memberName="label74" virtualName=""
         explicitFocusOrder="0" pos="353 148 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="Osc 1 Shape Mod" id="37a455399be282f2" memberName="sli_o1_shapeMod"
          virtualName="" explicitFocusOrder="0" pos="357 162 32 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Osc 1 Shape Mod Source" id="889406e7d01ee0d7" memberName="swi_o1_shapeMod_src"
          virtualName="" explicitFocusOrder="0" pos="353 196 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="new group" id="124df9d8dc5a23a2" memberName="groupComponent15"
                  virtualName="" explicitFocusOrder="0" pos="2 216 238 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Pitch Mod"/>
  <SLIDER name="Pitch Mod Dest" id="4bea1227bdd0435d" memberName="swi_o2_sh4"
          virtualName="" explicitFocusOrder="0" pos="178 247 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="Mod 2 Param A" id="4311def691d02af5" memberName="sli_mod2_a2"
          virtualName="" explicitFocusOrder="0" pos="127 253 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fafeb06c5e6ee44" memberName="label114" virtualName=""
         explicitFocusOrder="0" pos="123 232 96 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Mod 1 Amount" id="ebe4841d9f9a325b" memberName="sli_filt_mod1"
          virtualName="" explicitFocusOrder="0" pos="567 268 32 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="ea99f1ee0bffe27b" memberName="label60" virtualName=""
         explicitFocusOrder="0" pos="558 253 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Mod 2 Amount" id="76786c96966c36a1" memberName="sli_filt_mod2"
          virtualName="" explicitFocusOrder="0" pos="609 268 32 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="b2cffd0f1b65df15" memberName="label115"
         virtualName="" explicitFocusOrder="0" pos="603 253 50 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="35c083dd96eeae1c" memberName="label108"
         virtualName="" explicitFocusOrder="0" pos="195 255 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b4073041ed98b361" memberName="label111"
         virtualName="" explicitFocusOrder="0" pos="195 270 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1+2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1fc25b30d5e665b" memberName="label112" virtualName=""
         explicitFocusOrder="0" pos="195 285 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bc8496b02259602e" memberName="label116"
         virtualName="" explicitFocusOrder="0" pos="327 255 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="On" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="38ddb52606d712ba" memberName="label117"
         virtualName="" explicitFocusOrder="0" pos="327 285 32 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Off" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new label" id="47120d01e1bac2cc" memberName="sli_env_vel2"
          virtualName="" explicitFocusOrder="0" pos="656 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="78178cdbd1ab10bb" memberName="label89" virtualName=""
         explicitFocusOrder="0" pos="646 321 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Velocity" id="275cc0f2822f4f6f" memberName="swi_filt_vel2"
          virtualName="" explicitFocusOrder="0" pos="624 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Res" id="824305feeed24d1a" memberName="label118" virtualName=""
         explicitFocusOrder="0" pos="649 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="Freq" id="6ced03ba10643dd2" memberName="label119" virtualName=""
         explicitFocusOrder="0" pos="619 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="new label" id="97ea6760092759ce" memberName="sli_env_vel3"
          virtualName="" explicitFocusOrder="0" pos="720 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="dabd04f7eef94378" memberName="label25" virtualName=""
         explicitFocusOrder="0" pos="683 321 64 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Velocity" id="e08683319132272c" memberName="swi_filt_vel3"
          virtualName="" explicitFocusOrder="0" pos="688 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Res" id="f15c3208e18485da" memberName="label120" virtualName=""
         explicitFocusOrder="0" pos="713 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="Freq" id="f1b9a0780a0fba35" memberName="label121" virtualName=""
         explicitFocusOrder="0" pos="683 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amt" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="abb9ad12a9f27cdc" memberName="label61" virtualName=""
         explicitFocusOrder="0" pos="736 321 53 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Mod 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="Filter Velocity" id="e9906d6a347995b7" memberName="swi_filt_vel4"
          virtualName="" explicitFocusOrder="0" pos="752 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="Freq" id="c47a087af7167700" memberName="label70" virtualName=""
         explicitFocusOrder="0" pos="747 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amt" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="c20e5ad22176b5db" memberName="groupComponent18"
                  virtualName="" explicitFocusOrder="0" pos="245 309 118 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="Mod Wheel"/>
  <LABEL name="new label" id="66e888260079f227" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="101 78 56 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="KB Track" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2dd42349d843e77c" memberName="label50" virtualName=""
         explicitFocusOrder="0" pos="101 94 46 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="High" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Mod 1 Range" id="a71a217a5cdfce5a" memberName="swi_lfo1_range"
          virtualName="" explicitFocusOrder="0" pos="87 70 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="abad29a194653e2e" memberName="label52" virtualName=""
         explicitFocusOrder="0" pos="101 110 46 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Low" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b0913b071652730d" memberName="label40" virtualName=""
         explicitFocusOrder="0" pos="186 76 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Amt" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="af65f27e2e1203dd" memberName="label41" virtualName=""
         explicitFocusOrder="0" pos="186 92 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Mod 1 From Mod 2 Type" id="df99bc8b2dadda52" memberName="swi_mod1_from_mod2"
          virtualName="" explicitFocusOrder="0" pos="168 70 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="5b84dfab4e1fcb09" memberName="label44" virtualName=""
         explicitFocusOrder="0" pos="186 108 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="bb17562d5859fcb4" memberName="label82" virtualName=""
         explicitFocusOrder="0" pos="161 16 76 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="From Mod 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a79935d2a06dfb40" memberName="label26" virtualName=""
         explicitFocusOrder="0" pos="15 16 48 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Shape" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="Mod 1 Shape" id="44c2acf6a263b720" memberName="sli_mod1_shape"
          virtualName="" explicitFocusOrder="0" pos="15 43 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="2788d9c460133bcf" memberName="label27" virtualName=""
         explicitFocusOrder="0" pos="42 163 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f2d020e29afb4981" memberName="label33" virtualName=""
         explicitFocusOrder="0" pos="42 179 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env+" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Mod 2 Type" id="163f460c7c72f914" memberName="swi_mod2_type"
          virtualName="" explicitFocusOrder="0" pos="28 155 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a8a100504a52c30" memberName="label34" virtualName=""
         explicitFocusOrder="0" pos="42 195 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Env-" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new label" id="b6fb137cd4249c20" memberName="sli_env_vel5"
          virtualName="" explicitFocusOrder="0" pos="528 348 20 56" min="0"
          max="1" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="a0355a6961c99596" memberName="label66" virtualName=""
         explicitFocusOrder="0" pos="518 321 39 16" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="Res" id="37dc6878256fcd51" memberName="label68" virtualName=""
         explicitFocusOrder="0" pos="521 340 32 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="36"/>
  <SLIDER name="Mod 2 Param A" id="4753d1fce7208f90" memberName="sli_mod2_a3"
          virtualName="" explicitFocusOrder="0" pos="10 253 48 48" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8c984a846870e717" memberName="label49" virtualName=""
         explicitFocusOrder="0" pos="6 232 96 16" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Mod 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="82b1a3ea8e01aa13" memberName="label69" virtualName=""
         explicitFocusOrder="0" pos="47 87 29 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Squ" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="d248620906abf2f9" memberName="label71" virtualName=""
         explicitFocusOrder="0" pos="7 87 27 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Tri" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="edda5fca34597443" memberName="label75" virtualName=""
         explicitFocusOrder="0" pos="23 34 30 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Sin" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="36"/>
  <GROUPCOMPONENT name="new group" id="5d2c7b1cddd739fa" memberName="groupComponent17"
                  virtualName="" explicitFocusOrder="0" pos="239 0 7 408" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="new group" id="cce9193e23759f4e" memberName="groupComponent19"
                  virtualName="" explicitFocusOrder="0" pos="510 0 7 312" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="new group" id="c6a8b01ac1b239f6" memberName="groupComponent20"
                  virtualName="" explicitFocusOrder="0" pos="651 0 7 312" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="new group" id="26f118603c7544cd" memberName="groupComponent21"
                  virtualName="" explicitFocusOrder="0" pos="408 124 7 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="new group" id="3a3603320aa9a6c8" memberName="groupComponent22"
                  virtualName="" explicitFocusOrder="0" pos="362 309 7 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <GROUPCOMPONENT name="new group" id="11f6657ca19ff463" memberName="groupComponent23"
                  virtualName="" explicitFocusOrder="0" pos="113 309 7 96" outlinecol="99ffffff"
                  textcol="ffffffff" title="" textpos="36"/>
  <SLIDER name="Pitch Mod Dest" id="7cb04d9ab5b9ac36" memberName="swi_o2_sh2"
          virtualName="" explicitFocusOrder="0" pos="62 247 20 56" min="1"
          max="2" int="0.5" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8476f4277b4d0904" memberName="label62" virtualName=""
         explicitFocusOrder="0" pos="79 255 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="479f7fd1fb7ee7a9" memberName="label76" virtualName=""
         explicitFocusOrder="0" pos="79 270 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="1+2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f23a4666dc729988" memberName="label77" virtualName=""
         explicitFocusOrder="0" pos="79 285 40 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="Mod 1 From Mod 2 Amt" id="4f0e61f1a372a89d" memberName="sli_mod1_from_mod2"
          virtualName="" explicitFocusOrder="0" pos="184 37 32 32" min="0"
          max="1" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="1d0c985d98531fd4" memberName="label80" virtualName=""
         explicitFocusOrder="0" pos="685 178 59 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Gate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
