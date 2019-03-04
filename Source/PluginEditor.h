/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "MyLookAndFeel.h"

//==============================================================================
/**
*/
class SynthuljaAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SynthuljaAudioProcessorEditor (SynthuljaAudioProcessor&);
    ~SynthuljaAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthuljaAudioProcessor& processor;

	MyLookAndFeel myLookAndFeel;

	Slider attackSlider;
	Slider decaySlider;
	Slider sustainSlider;
	Slider releaseSlider;

	Slider filterCutoffSlider;
	Slider filterResonanceSlider;
	ComboBox filterTypeMenu;

	ComboBox osc1TypeMenu;
	ComboBox osc2TypeMenu;


	OwnedArray<AudioProcessorValueTreeState::ComboBoxAttachment> oscTypeMenus_PTR;
	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeMenu_PTR;

	OwnedArray<AudioProcessorValueTreeState::SliderAttachment> envSliders_PTR;
	OwnedArray<AudioProcessorValueTreeState::SliderAttachment> filterSliders_PTR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthuljaAudioProcessorEditor)
};
