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

#include "SecondaryControls.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

namespace Gui {

//[/MiscUserDefs]

//==============================================================================
SecondaryControls::SecondaryControls ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (sli_filt_resbass = new Slider ("new slider"));
    sli_filt_resbass->setRange (0, 10, 0);
    sli_filt_resbass->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_filt_resbass->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_filt_resbass->addListener (this);

    addAndMakeVisible (label97 = new Label ("new label",
                                            TRANS("White")));
    label97->setFont (Font (12.00f, Font::plain));
    label97->setJustificationType (Justification::centredLeft);
    label97->setEditable (false, false, false);
    label97->setColour (Label::textColourId, Colours::white);
    label97->setColour (TextEditor::textColourId, Colours::black);
    label97->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label98 = new Label ("new label",
                                            TRANS("Pink")));
    label98->setFont (Font (12.00f, Font::plain));
    label98->setJustificationType (Justification::centredRight);
    label98->setEditable (false, false, false);
    label98->setColour (Label::textColourId, Colours::white);
    label98->setColour (TextEditor::textColourId, Colours::black);
    label98->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_noise_color = new Slider ("new slider"));
    swi_noise_color->setRange (0, 1, 1);
    swi_noise_color->setSliderStyle (Slider::LinearHorizontal);
    swi_noise_color->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_noise_color->addListener (this);

    addAndMakeVisible (label111 = new Label ("new label",
                                             TRANS("Hz")));
    label111->setFont (Font (12.00f, Font::plain));
    label111->setJustificationType (Justification::centredLeft);
    label111->setEditable (false, false, false);
    label111->setColour (Label::textColourId, Colours::white);
    label111->setColour (TextEditor::textColourId, Colours::black);
    label111->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label112 = new Label ("new label",
                                             TRANS("Cents")));
    label112->setFont (Font (12.00f, Font::plain));
    label112->setJustificationType (Justification::centredRight);
    label112->setEditable (false, false, false);
    label112->setColour (Label::textColourId, Colours::white);
    label112->setColour (TextEditor::textColourId, Colours::black);
    label112->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_tune_type = new Slider ("new slider"));
    swi_tune_type->setRange (0, 1, 1);
    swi_tune_type->setSliderStyle (Slider::LinearHorizontal);
    swi_tune_type->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_tune_type->addListener (this);

    addAndMakeVisible (label113 = new Label ("new label",
                                             TRANS("Osc 2 Fine Tune")));
    label113->setFont (Font (12.00f, Font::plain));
    label113->setJustificationType (Justification::centred);
    label113->setEditable (false, false, false);
    label113->setColour (Label::textColourId, Colours::white);
    label113->setColour (TextEditor::textColourId, Colours::black);
    label113->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label114 = new Label ("new label",
                                             TRANS("Exp")));
    label114->setFont (Font (12.00f, Font::plain));
    label114->setJustificationType (Justification::centredLeft);
    label114->setEditable (false, false, false);
    label114->setColour (Label::textColourId, Colours::white);
    label114->setColour (TextEditor::textColourId, Colours::black);
    label114->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label115 = new Label ("new label",
                                             TRANS("Time")));
    label115->setFont (Font (12.00f, Font::plain));
    label115->setJustificationType (Justification::centredLeft);
    label115->setEditable (false, false, false);
    label115->setColour (Label::textColourId, Colours::white);
    label115->setColour (TextEditor::textColourId, Colours::black);
    label115->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label116 = new Label ("new label",
                                             TRANS("Rate")));
    label116->setFont (Font (12.00f, Font::plain));
    label116->setJustificationType (Justification::centredLeft);
    label116->setEditable (false, false, false);
    label116->setColour (Label::textColourId, Colours::white);
    label116->setColour (TextEditor::textColourId, Colours::black);
    label116->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_glide_type = new Slider ("new slider"));
    swi_glide_type->setRange (0, 2, 1);
    swi_glide_type->setSliderStyle (Slider::LinearVertical);
    swi_glide_type->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_glide_type->addListener (this);

    addAndMakeVisible (label117 = new Label ("new label",
                                             TRANS("Glide")));
    label117->setFont (Font (15.00f, Font::plain));
    label117->setJustificationType (Justification::centred);
    label117->setEditable (false, false, false);
    label117->setColour (Label::textColourId, Colours::white);
    label117->setColour (TextEditor::textColourId, Colours::black);
    label117->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label118 = new Label ("new label",
                                             TRANS("Instability")));
    label118->setFont (Font (15.00f, Font::plain));
    label118->setJustificationType (Justification::centred);
    label118->setEditable (false, false, false);
    label118->setColour (Label::textColourId, Colours::white);
    label118->setColour (TextEditor::textColourId, Colours::black);
    label118->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sli_tune_instab = new Slider ("new slider"));
    sli_tune_instab->setRange (0, 10, 0);
    sli_tune_instab->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_tune_instab->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_tune_instab->addListener (this);

    addAndMakeVisible (sli_shape_instab = new Slider ("new slider"));
    sli_shape_instab->setRange (0, 10, 0);
    sli_shape_instab->setSliderStyle (Slider::RotaryVerticalDrag);
    sli_shape_instab->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    sli_shape_instab->addListener (this);

    addAndMakeVisible (label119 = new Label ("new label",
                                             TRANS("Tuning")));
    label119->setFont (Font (12.00f, Font::plain));
    label119->setJustificationType (Justification::centredLeft);
    label119->setEditable (false, false, false);
    label119->setColour (Label::textColourId, Colours::white);
    label119->setColour (TextEditor::textColourId, Colours::black);
    label119->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label120 = new Label ("new label",
                                             TRANS("Shape")));
    label120->setFont (Font (12.00f, Font::plain));
    label120->setJustificationType (Justification::centredLeft);
    label120->setEditable (false, false, false);
    label120->setColour (Label::textColourId, Colours::white);
    label120->setColour (TextEditor::textColourId, Colours::black);
    label120->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label22 = new Label ("new label",
                                            TRANS("Resonance\n"
                                            "Bass")));
    label22->setFont (Font (15.00f, Font::plain));
    label22->setJustificationType (Justification::centred);
    label22->setEditable (false, false, false);
    label22->setColour (Label::textColourId, Colours::white);
    label22->setColour (TextEditor::textColourId, Colours::black);
    label22->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label121 = new Label ("new label",
                                             TRANS("Enable Overdrive")));
    label121->setFont (Font (12.00f, Font::plain));
    label121->setJustificationType (Justification::centredLeft);
    label121->setEditable (false, false, false);
    label121->setColour (Label::textColourId, Colours::white);
    label121->setColour (TextEditor::textColourId, Colours::black);
    label121->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_lfosrc2 = new Slider ("new slider"));
    swi_filt_lfosrc2->setRange (0, 1, 1);
    swi_filt_lfosrc2->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_lfosrc2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_lfosrc2->addListener (this);

    addAndMakeVisible (label104 = new Label ("new label",
                                             TRANS("Reset LFOs on retrig")));
    label104->setFont (Font (12.00f, Font::plain));
    label104->setJustificationType (Justification::centredLeft);
    label104->setEditable (false, false, false);
    label104->setColour (Label::textColourId, Colours::white);
    label104->setColour (TextEditor::textColourId, Colours::black);
    label104->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_lfo1_kb2 = new Slider ("new slider"));
    swi_lfo1_kb2->setRange (0, 1, 1);
    swi_lfo1_kb2->setSliderStyle (Slider::LinearHorizontal);
    swi_lfo1_kb2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo1_kb2->addListener (this);

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Clicky VCA Gate")));
    label2->setFont (Font (12.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (Label::textColourId, Colours::white);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_filt_lfosrc3 = new Slider ("new slider"));
    swi_filt_lfosrc3->setRange (0, 1, 1);
    swi_filt_lfosrc3->setSliderStyle (Slider::LinearHorizontal);
    swi_filt_lfosrc3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_filt_lfosrc3->addListener (this);

    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Raw")));
    label5->setFont (Font (12.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::white);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("Glide")));
    label6->setFont (Font (12.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colours::white);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Glide + Bend")));
    label7->setFont (Font (12.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (Label::textColourId, Colours::white);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_glide_type2 = new Slider ("new slider"));
    swi_glide_type2->setRange (0, 2, 1);
    swi_glide_type2->setSliderStyle (Slider::LinearVertical);
    swi_glide_type2->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_glide_type2->addListener (this);

    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Osc 1 Pitch")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centred);
    label8->setEditable (false, false, false);
    label8->setColour (Label::textColourId, Colours::white);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Raw")));
    label9->setFont (Font (12.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (Label::textColourId, Colours::white);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Glide")));
    label10->setFont (Font (12.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (Label::textColourId, Colours::white);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Glide + Bend")));
    label11->setFont (Font (12.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (Label::textColourId, Colours::white);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_glide_type3 = new Slider ("new slider"));
    swi_glide_type3->setRange (0, 2, 1);
    swi_glide_type3->setSliderStyle (Slider::LinearVertical);
    swi_glide_type3->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_glide_type3->addListener (this);

    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("Osc 2 Pitch")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centred);
    label12->setEditable (false, false, false);
    label12->setColour (Label::textColourId, Colours::white);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Noise")));
    label14->setFont (Font (15.00f, Font::plain));
    label14->setJustificationType (Justification::centred);
    label14->setEditable (false, false, false);
    label14->setColour (Label::textColourId, Colours::white);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label34 = new Label ("new label",
                                            TRANS("Attack")));
    label34->setFont (Font (12.00f, Font::plain));
    label34->setJustificationType (Justification::centredLeft);
    label34->setEditable (false, false, false);
    label34->setColour (Label::textColourId, Colours::white);
    label34->setColour (TextEditor::textColourId, Colours::black);
    label34->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label35 = new Label ("new label",
                                            TRANS("Decay")));
    label35->setFont (Font (12.00f, Font::plain));
    label35->setJustificationType (Justification::centredLeft);
    label35->setEditable (false, false, false);
    label35->setColour (Label::textColourId, Colours::white);
    label35->setColour (TextEditor::textColourId, Colours::black);
    label35->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (swi_lfo2_att = new Slider ("LFO2 Attack/Decay"));
    swi_lfo2_att->setRange (0, 1, 1);
    swi_lfo2_att->setSliderStyle (Slider::LinearVertical);
    swi_lfo2_att->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    swi_lfo2_att->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("LFO 2 Attack")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (comboBox = new ComboBox ("Filter Model"));
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (TRANS("Filter Model"));
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addItem (TRANS("Off"), 1);
    comboBox->addItem (TRANS("Transistor Ladder"), 2);
    comboBox->addItem (TRANS("Diode Ladder"), 3);
    comboBox->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (500, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SecondaryControls::~SecondaryControls()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    sli_filt_resbass = nullptr;
    label97 = nullptr;
    label98 = nullptr;
    swi_noise_color = nullptr;
    label111 = nullptr;
    label112 = nullptr;
    swi_tune_type = nullptr;
    label113 = nullptr;
    label114 = nullptr;
    label115 = nullptr;
    label116 = nullptr;
    swi_glide_type = nullptr;
    label117 = nullptr;
    label118 = nullptr;
    sli_tune_instab = nullptr;
    sli_shape_instab = nullptr;
    label119 = nullptr;
    label120 = nullptr;
    label22 = nullptr;
    label121 = nullptr;
    swi_filt_lfosrc2 = nullptr;
    label104 = nullptr;
    swi_lfo1_kb2 = nullptr;
    label2 = nullptr;
    swi_filt_lfosrc3 = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    swi_glide_type2 = nullptr;
    label8 = nullptr;
    label9 = nullptr;
    label10 = nullptr;
    label11 = nullptr;
    swi_glide_type3 = nullptr;
    label12 = nullptr;
    label14 = nullptr;
    label34 = nullptr;
    label35 = nullptr;
    swi_lfo2_att = nullptr;
    label3 = nullptr;
    comboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SecondaryControls::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c1c1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SecondaryControls::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sli_filt_resbass->setBounds (359, 57, 48, 32);
    label97->setBounds (173, 46, 43, 10);
    label98->setBounds (104, 46, 45, 10);
    swi_noise_color->setBounds (141, 43, 40, 16);
    label111->setBounds (180, 113, 30, 10);
    label112->setBounds (123, 113, 34, 10);
    swi_tune_type->setBounds (149, 110, 40, 16);
    label113->setBounds (123, 96, 88, 15);
    label114->setBounds (29, 179, 35, 10);
    label115->setBounds (29, 195, 40, 10);
    label116->setBounds (29, 211, 40, 10);
    swi_glide_type->setBounds (15, 172, 19, 56);
    label117->setBounds (13, 162, 48, 15);
    label118->setBounds (232, 16, 75, 20);
    sli_tune_instab->setBounds (236, 35, 24, 24);
    sli_shape_instab->setBounds (236, 57, 24, 24);
    label119->setBounds (257, 34, 48, 24);
    label120->setBounds (257, 57, 48, 24);
    label22->setBounds (344, 23, 80, 34);
    label121->setBounds (288, 233, 104, 12);
    swi_filt_lfosrc2->setBounds (257, 231, 40, 16);
    label104->setBounds (44, 264, 61, 32);
    swi_lfo1_kb2->setBounds (12, 272, 40, 16);
    label2->setBounds (289, 206, 95, 12);
    swi_filt_lfosrc3->setBounds (258, 204, 40, 16);
    label5->setBounds (32, 28, 35, 10);
    label6->setBounds (32, 44, 40, 10);
    label7->setBounds (32, 60, 80, 10);
    swi_glide_type2->setBounds (18, 21, 19, 56);
    label8->setBounds (16, 12, 72, 15);
    label9->setBounds (32, 96, 35, 10);
    label10->setBounds (32, 112, 40, 10);
    label11->setBounds (32, 128, 80, 10);
    swi_glide_type3->setBounds (18, 89, 19, 56);
    label12->setBounds (16, 80, 72, 15);
    label14->setBounds (122, 24, 75, 15);
    label34->setBounds (148, 229, 49, 10);
    label35->setBounds (148, 244, 49, 10);
    swi_lfo2_att->setBounds (133, 220, 16, 40);
    label3->setBounds (112, 208, 96, 15);
    comboBox->setBounds (272, 120, 120, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SecondaryControls::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sli_filt_resbass)
    {
        //[UserSliderCode_sli_filt_resbass] -- add your slider handling code here..
        //[/UserSliderCode_sli_filt_resbass]
    }
    else if (sliderThatWasMoved == swi_noise_color)
    {
        //[UserSliderCode_swi_noise_color] -- add your slider handling code here..
        //[/UserSliderCode_swi_noise_color]
    }
    else if (sliderThatWasMoved == swi_tune_type)
    {
        //[UserSliderCode_swi_tune_type] -- add your slider handling code here..
        //[/UserSliderCode_swi_tune_type]
    }
    else if (sliderThatWasMoved == swi_glide_type)
    {
        //[UserSliderCode_swi_glide_type] -- add your slider handling code here..
        //[/UserSliderCode_swi_glide_type]
    }
    else if (sliderThatWasMoved == sli_tune_instab)
    {
        //[UserSliderCode_sli_tune_instab] -- add your slider handling code here..
        //[/UserSliderCode_sli_tune_instab]
    }
    else if (sliderThatWasMoved == sli_shape_instab)
    {
        //[UserSliderCode_sli_shape_instab] -- add your slider handling code here..
        //[/UserSliderCode_sli_shape_instab]
    }
    else if (sliderThatWasMoved == swi_filt_lfosrc2)
    {
        //[UserSliderCode_swi_filt_lfosrc2] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_lfosrc2]
    }
    else if (sliderThatWasMoved == swi_lfo1_kb2)
    {
        //[UserSliderCode_swi_lfo1_kb2] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo1_kb2]
    }
    else if (sliderThatWasMoved == swi_filt_lfosrc3)
    {
        //[UserSliderCode_swi_filt_lfosrc3] -- add your slider handling code here..
        //[/UserSliderCode_swi_filt_lfosrc3]
    }
    else if (sliderThatWasMoved == swi_glide_type2)
    {
        //[UserSliderCode_swi_glide_type2] -- add your slider handling code here..
        //[/UserSliderCode_swi_glide_type2]
    }
    else if (sliderThatWasMoved == swi_glide_type3)
    {
        //[UserSliderCode_swi_glide_type3] -- add your slider handling code here..
        //[/UserSliderCode_swi_glide_type3]
    }
    else if (sliderThatWasMoved == swi_lfo2_att)
    {
        //[UserSliderCode_swi_lfo2_att] -- add your slider handling code here..
        //[/UserSliderCode_swi_lfo2_att]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void SecondaryControls::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox)
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

} // namespace Gui

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SecondaryControls" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="500" initialHeight="300">
  <BACKGROUND backgroundColour="ff1c1c1c"/>
  <SLIDER name="new slider" id="785b4bba36ddbb84" memberName="sli_filt_resbass"
          virtualName="" explicitFocusOrder="0" pos="359 57 48 32" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="7d04b59c36e446b2" memberName="label97" virtualName=""
         explicitFocusOrder="0" pos="173 46 43 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="White" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5fe6882c9a7e7367" memberName="label98" virtualName=""
         explicitFocusOrder="0" pos="104 46 45 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Pink" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="b3bfb5605ac16f1d" memberName="swi_noise_color"
          virtualName="" explicitFocusOrder="0" pos="141 43 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="f7d41627cbc579bd" memberName="label111"
         virtualName="" explicitFocusOrder="0" pos="180 113 30 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Hz" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ea554e618021a2b2" memberName="label112"
         virtualName="" explicitFocusOrder="0" pos="123 113 34 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Cents" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="34"/>
  <SLIDER name="new slider" id="a6b0788b80c26159" memberName="swi_tune_type"
          virtualName="" explicitFocusOrder="0" pos="149 110 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="69e8630ce6b29c9c" memberName="label113"
         virtualName="" explicitFocusOrder="0" pos="123 96 88 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Osc 2 Fine Tune"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="f31a739f49e54751" memberName="label114"
         virtualName="" explicitFocusOrder="0" pos="29 179 35 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Exp" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="85de66ed3dc33db1" memberName="label115"
         virtualName="" explicitFocusOrder="0" pos="29 195 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="382734bd47b507ef" memberName="label116"
         virtualName="" explicitFocusOrder="0" pos="29 211 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Rate" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="f4c8dfa89b2d9239" memberName="swi_glide_type"
          virtualName="" explicitFocusOrder="0" pos="15 172 19 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="bef16673747564c4" memberName="label117"
         virtualName="" explicitFocusOrder="0" pos="13 162 48 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="61723174b32dc750" memberName="label118"
         virtualName="" explicitFocusOrder="0" pos="232 16 75 20" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Instability" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <SLIDER name="new slider" id="37aafb176850241e" memberName="sli_tune_instab"
          virtualName="" explicitFocusOrder="0" pos="236 35 24 24" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="new slider" id="93127b2857ac305e" memberName="sli_shape_instab"
          virtualName="" explicitFocusOrder="0" pos="236 57 24 24" min="0"
          max="10" int="0" style="RotaryVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fb39f80023ca0a29" memberName="label119"
         virtualName="" explicitFocusOrder="0" pos="257 34 48 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Tuning" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="7700c713c66972b4" memberName="label120"
         virtualName="" explicitFocusOrder="0" pos="257 57 48 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Shape" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="be2f453c2cf64201" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="344 23 80 34" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Resonance&#10;Bass"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="637cab065add0171" memberName="label121"
         virtualName="" explicitFocusOrder="0" pos="288 233 104 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Enable Overdrive"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="3a62912dcdeb23ff" memberName="swi_filt_lfosrc2"
          virtualName="" explicitFocusOrder="0" pos="257 231 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="bc675c8fe449178f" memberName="label104"
         virtualName="" explicitFocusOrder="0" pos="44 264 61 32" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Reset LFOs on retrig"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="3ec464d79b406e02" memberName="swi_lfo1_kb2"
          virtualName="" explicitFocusOrder="0" pos="12 272 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c391779b3ff5cdaf" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="289 206 95 12" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Clicky VCA Gate"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="d1a52db9041bf75b" memberName="swi_filt_lfosrc3"
          virtualName="" explicitFocusOrder="0" pos="258 204 40 16" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="3cf08adc6166eeaa" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="32 28 35 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Raw" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b09c1b517bb0897b" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="32 44 40 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Glide" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ae37a63363f05ffa" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="32 60 80 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Glide + Bend" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="dc4bb29d2d6deff0" memberName="swi_glide_type2"
          virtualName="" explicitFocusOrder="0" pos="18 21 19 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="9ab477c9934196ac" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="16 12 72 15" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Osc 1 Pitch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="285809f2541278d7" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="32 96 35 10" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Raw" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b922f7a1e8d71aff" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="32 112 40 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="fefeaa3e905a2edd" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="32 128 80 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Glide + Bend" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="d8998e31d2b915d" memberName="swi_glide_type3"
          virtualName="" explicitFocusOrder="0" pos="18 89 19 56" min="0"
          max="2" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="591054563f0717ab" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="16 80 72 15" textCol="ffffffff" edTextCol="ff000000"
         edBkgCol="0" labelText="Osc 2 Pitch" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="f72560acb21d0d6a" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="122 24 75 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Noise" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="2a9ab2f0ac301cfa" memberName="label34" virtualName=""
         explicitFocusOrder="0" pos="148 229 49 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Attack" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="66430b8dfb9a92cd" memberName="label35" virtualName=""
         explicitFocusOrder="0" pos="148 244 49 10" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Decay" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12" bold="0" italic="0" justification="33"/>
  <SLIDER name="LFO2 Attack/Decay" id="ca40100f8534db76" memberName="swi_lfo2_att"
          virtualName="" explicitFocusOrder="0" pos="133 220 16 40" min="0"
          max="1" int="1" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="addbe50fe3c13f62" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="112 208 96 15" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="LFO 2 Attack" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <COMBOBOX name="Filter Model" id="66a4871135953e41" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="272 120 120 16" editable="0"
            layout="33" items="Off&#10;Transistor Ladder&#10;Diode Ladder"
            textWhenNonSelected="Filter Model" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
