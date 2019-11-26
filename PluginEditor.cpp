/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OverdriveAudioProcessorEditor::OverdriveAudioProcessorEditor (OverdriveAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);

	overdriveSlider.setSliderStyle(Slider::Rotary);
	overdriveSlider.setRange(1.0, 20.0, 0.1);
	overdriveSlider.setTextBoxStyle(Slider::NoTextBox, false, 20, 0);
	overdriveSlider.setPopupDisplayEnabled(true, false, this);
	overdriveSlider.setTextValueSuffix("overdrive step");
	overdriveSlider.setValue(1.0);
	addAndMakeVisible(&overdriveSlider);
	overdriveSlider.addListener(this);

	wetDrySlider.setSliderStyle(Slider::Rotary);
	wetDrySlider.setRange(0.0, 100.0, 0.1);
	wetDrySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 0);
	wetDrySlider.setPopupDisplayEnabled(true, false, this);
	wetDrySlider.setTextValueSuffix(" ");
	wetDrySlider.setValue(0.0);
	addAndMakeVisible(&wetDrySlider);
	wetDrySlider.addListener(this);


}

OverdriveAudioProcessorEditor::~OverdriveAudioProcessorEditor()
{
}

//==============================================================================
void OverdriveAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	Rectangle<int>asd(50, 140,100,100);
	Rectangle<int>asd2(250, 140, 100, 100);
	g.drawFittedText("Overdrive level", asd, Justification::centred, 1);
	g.drawFittedText("Wet/Dry", asd2, Justification::centred, 1);
}

void OverdriveAudioProcessorEditor::resized()
{
	overdriveSlider.setBounds(0, 0, 200, 200);
	wetDrySlider.setBounds(200, 0, 200, 200);
}

void OverdriveAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.overdriveSliderValue = overdriveSlider.getValue();
	processor.wetDry = wetDrySlider.getValue();
}
