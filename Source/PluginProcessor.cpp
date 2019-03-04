/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


StringArray getOscillatorTypes() {

	StringArray oscTypes = { "Sine", "Square", "Saw" };

	return oscTypes;

}

StringArray getFilterTypes() {
	
	StringArray filterTypes = { "Low Pass", "Band Pass", "High Pass" };

	return filterTypes;

}


AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {

	std::vector<std::unique_ptr<AudioProcessorParameterGroup>> params;

	{
		auto oscType1 = std::make_unique<AudioParameterChoice>("osc1Type", "Oscillator 1 Type", getOscillatorTypes(), 0);
		auto oscType2 = std::make_unique<AudioParameterChoice>("osc2Type", "Oscillator 2 Type", getOscillatorTypes(), 0);

		auto group = std::make_unique<AudioProcessorParameterGroup>("oscTypes", "Oscillator Types", "|",
			std::move(oscType1),
			std::move(oscType2));
		params.push_back(std::move(group));
	}

	{
		auto attackParam = std::make_unique<AudioParameterFloat>("attack", "EG Attack", NormalisableRange<float>(0.01f, 5.0f, 0.01f), 0.1f);
		auto decayParam = std::make_unique<AudioParameterFloat>("decay", "EG decay", NormalisableRange<float>(0.01f, 5.0f, 0.01f), 0.1f);
		auto sustainParam = std::make_unique<AudioParameterFloat>("sustain", "EG sustain", NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.2f);
		auto releaseParam = std::make_unique<AudioParameterFloat>("release", "EG release", NormalisableRange<float>(0.01f, 2.0f, 0.01f), 1.0f);

		auto group = std::make_unique<AudioProcessorParameterGroup>("envParams", "Envelope Parameters", "|", 
																	std::move(attackParam), 
																	std::move(decayParam),
																	std::move(sustainParam), 
																	std::move(releaseParam));

		params.push_back(std::move(group));
	
	}

	{
		
			auto filterFreqParam = std::make_unique<AudioParameterFloat>("filterFrequency", "Filter Frequency", NormalisableRange<float>(20, 20000, 1), 1000);
			auto filterResParam = std::make_unique<AudioParameterFloat>("filterResonance", "Filter Resonance", NormalisableRange<float>(0.1f, 5.0f, 0.1f), 1.0f);
			auto filterTypeParam = std::make_unique<AudioParameterChoice>("filterType", "Filter Type", getFilterTypes(), 0);

			auto group = std::make_unique<AudioProcessorParameterGroup>("filterParams", "Filter Parameters", "|",
				std::move(filterFreqParam),
				std::move(filterResParam),
				std::move(filterTypeParam));

			params.push_back(std::move(group));

	}

	return { params.begin(), params.end() };
}

//==============================================================================
SynthuljaAudioProcessor::SynthuljaAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	),
	parameterTree(*this, nullptr, "PARAMTERS", createParameterLayout())
#endif
{
	mySynth.clearVoices();
	for (int i = 0; i < 5; i++) {

		mySynth.addVoice(new SynthVoice());

	}
	mySynth.clearSounds();
	mySynth.addSound(new SynthSound());
}

SynthuljaAudioProcessor::~SynthuljaAudioProcessor()
{
}

//==============================================================================
const String SynthuljaAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthuljaAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthuljaAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthuljaAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthuljaAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthuljaAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthuljaAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthuljaAudioProcessor::setCurrentProgram (int index)
{
}

const String SynthuljaAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthuljaAudioProcessor::changeProgramName (int index, const String& newName)
{
}


void SynthuljaAudioProcessor::updateFilter() {

		float filterSelection = *parameterTree.getRawParameterValue("filterType");
		float filterCutoff = *parameterTree.getRawParameterValue("filterFrequency");
		float filterResonance = *parameterTree.getRawParameterValue("filterResonance");

		if (filterSelection == 0) {
			svFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
			svFilter.state->setCutOffFrequency(getSampleRate(), filterCutoff, filterResonance);
		}

		else if (filterSelection == 1) {
			svFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
			svFilter.state->setCutOffFrequency(getSampleRate(), filterCutoff, filterResonance);
		}

		else if (filterSelection == 2) {
			svFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
			svFilter.state->setCutOffFrequency(getSampleRate(), filterCutoff, filterResonance);
		}

}

//==============================================================================
void SynthuljaAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mySynth.setCurrentPlaybackSampleRate(lastSampleRate);


	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();

	svFilter.reset();
	svFilter.prepare(spec);
	updateFilter();
}

void SynthuljaAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthuljaAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthuljaAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (int i = 0; i < mySynth.getNumVoices(); i++) {
		if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
		{

			myVoice->setEnvParams(parameterTree.getRawParameterValue("attack"),
				parameterTree.getRawParameterValue("decay"),
				parameterTree.getRawParameterValue("sustain"),
				parameterTree.getRawParameterValue("release"));

			myVoice->setWaveformSelection(parameterTree.getRawParameterValue("osc1Type"), parameterTree.getRawParameterValue("osc2Type"));
		}
	}

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

	updateFilter();
	dsp::AudioBlock<float> block(buffer);
	svFilter.process(dsp::ProcessContextReplacing<float>(block));


}

//==============================================================================
bool SynthuljaAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SynthuljaAudioProcessor::createEditor()
{
    return new SynthuljaAudioProcessorEditor (*this);
}

//==============================================================================
void SynthuljaAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthuljaAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthuljaAudioProcessor();
}
