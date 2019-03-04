/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthuljaAudioProcessorEditor::SynthuljaAudioProcessorEditor (SynthuljaAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (400, 400);

	//===========================================OSCILLATOR MENUS==================================================

	addAndMakeVisible(&osc1TypeMenu);
	oscTypeMenus_PTR.add(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.parameterTree, "osc1Type", osc1TypeMenu));
	osc1TypeMenu.addItem("Sine", 1);
	osc1TypeMenu.addItem("Square", 2);
	osc1TypeMenu.addItem("Saw", 3);
	osc1TypeMenu.setText("Sine");
	osc1TypeMenu.setLookAndFeel(&myLookAndFeel);

	addAndMakeVisible(&osc2TypeMenu);
	oscTypeMenus_PTR.add(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.parameterTree, "osc2Type", osc2TypeMenu));
	osc2TypeMenu.addItem("Sine", 1);
	osc2TypeMenu.addItem("Square", 2);
	osc2TypeMenu.addItem("Saw", 3);
	osc2TypeMenu.setText("Sine");
	osc2TypeMenu.setLookAndFeel(&myLookAndFeel);

	//============================================ENVELOPE SLIDERS================================================

	addAndMakeVisible(&attackSlider);
	envSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "attack", attackSlider));
	attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	attackSlider.setRange(0.01f, 5.0f, 0.01f);
	attackSlider.setLookAndFeel(&myLookAndFeel);

	addAndMakeVisible(&decaySlider);
	envSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "decay", decaySlider));
	decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	decaySlider.setRange(0.01f, 5.0f, 0.01f);
	decaySlider.setLookAndFeel(&myLookAndFeel);

	addAndMakeVisible(&sustainSlider);
	envSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "sustain", sustainSlider));
	sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	sustainSlider.setRange(0.0f, 1.0f, 0.01f);
	sustainSlider.setLookAndFeel(&myLookAndFeel);

	sustainSlider.setSkewFactorFromMidPoint(0.15);

	addAndMakeVisible(&releaseSlider);
	envSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "release", releaseSlider));
	releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	releaseSlider.setRange(0.01f, 2.0f, 0.01f);
	releaseSlider.setLookAndFeel(&myLookAndFeel);


	//=============================================FILTER SLIDERS==================================================

	addAndMakeVisible(&filterTypeMenu);
	filterTypeMenu_PTR.reset(new AudioProcessorValueTreeState::ComboBoxAttachment(processor.parameterTree, "filterTypeMenu", filterTypeMenu));
	filterTypeMenu.addItem("Low Pass", 1);
	filterTypeMenu.addItem("Band Pass", 2);
	filterTypeMenu.addItem("High Pass", 3);
	filterTypeMenu.setText("Low Pass");
	filterTypeMenu.setLookAndFeel(&myLookAndFeel);

	addAndMakeVisible(&filterCutoffSlider);
	filterSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "filterFrequency", filterCutoffSlider));
	filterCutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	filterCutoffSlider.setRange(20, 20000, 1);
	filterCutoffSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	filterCutoffSlider.setLookAndFeel(&myLookAndFeel);
	filterCutoffSlider.setSkewFactorFromMidPoint(10000);


	addAndMakeVisible(&filterResonanceSlider);
	filterSliders_PTR.add(new AudioProcessorValueTreeState::SliderAttachment(processor.parameterTree, "filterResonance", filterResonanceSlider));
	filterResonanceSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	filterResonanceSlider.setRange(0.1f, 5.0f, 0.1f);
	filterResonanceSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
	filterResonanceSlider.setLookAndFeel(&myLookAndFeel);

	
}

SynthuljaAudioProcessorEditor::~SynthuljaAudioProcessorEditor()
{
}

//==============================================================================
void SynthuljaAudioProcessorEditor::paint (Graphics& g)
{

	g.fillAll(Colours::teal);

	juce::Rectangle<int> area = getLocalBounds();

	juce::Rectangle<int> oscillatorArea = area.removeFromLeft(getWidth() / 2);
	juce::Rectangle<int> oscillator1Area = oscillatorArea.removeFromTop(getHeight() / 2);
	juce::Rectangle<int> adsrArea = area.removeFromTop(getHeight() / 2);

	g.setColour(Colours::black);
	g.drawRoundedRectangle(oscillatorArea.reduced(10).toFloat(), 10.0f, 1.0f);
	g.drawRoundedRectangle(oscillator1Area.reduced(10).toFloat(), 10.0f, 1.0f);
	g.drawRoundedRectangle(adsrArea.reduced(10).toFloat(), 10.0f, 1.0f);
	g.drawRoundedRectangle(area.reduced(10).toFloat(), 10.0f, 1.0f);

	g.drawText("Oscillator 1", oscillator1Area.reduced(10), Justification::centredBottom);
	g.drawText("Oscillator 2", oscillatorArea.reduced(10), Justification::centredBottom);
  
}

void SynthuljaAudioProcessorEditor::resized()
{
	juce::Rectangle<int> area = getLocalBounds();

	int sliderWidth = 20;
	int sliderHeight = 100;

	juce::Rectangle<int> oscillatorArea = area.removeFromLeft(getWidth()/2);
	juce::Rectangle<int> oscillator1Area = oscillatorArea.removeFromTop(getHeight() / 2);

	osc1TypeMenu.setBounds(50, 50, oscillator1Area.getWidth() - 100, 20);
	osc2TypeMenu.setBounds(50, 250, oscillatorArea.getWidth() - 100, 20);

	attackSlider.setBounds(area.getWidth() + 50, 40, sliderWidth, sliderHeight );
	decaySlider.setBounds(area.getWidth() + 70, 40, sliderWidth, sliderHeight );
	sustainSlider.setBounds(area.getWidth() + 90, 40, sliderWidth, sliderHeight);
	releaseSlider.setBounds(area.getWidth() + 110, 40, sliderWidth, sliderHeight);

	filterTypeMenu.setBounds(area.getWidth() + 30, 250, area.getWidth() - 100, 20);
	filterCutoffSlider.setBounds(area.getWidth() + 20, 300, 80, 80);
	filterResonanceSlider.setBounds(area.getWidth() + 100, 300, 80, 80);



}
