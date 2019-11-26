/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class OverdriveAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    OverdriveAudioProcessorEditor (OverdriveAudioProcessor&);
    ~OverdriveAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OverdriveAudioProcessor& processor;
	
	Slider overdriveSlider;
	Slider wetDrySlider;
	//Label sampleValueLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveAudioProcessorEditor)
};
