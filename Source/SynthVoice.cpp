/*
  ==============================================================================

    SynthVoice.cpp
    Created: 13 Feb 2019 1:14:49am
    Author:  Borna


	SynthVoice Class which plays back sounds on the synthesiser. 

	1. ENVELOPE FUNCTIONS
	2. OSCILLATOR FUNCTIONS
	3. GENERAL SYNTHVOICE FUNCTIONS

	**Filter has to be implemented in the processor class, because it is derived from the DSP module.

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(SynthesiserSound* sound){

	return dynamic_cast <SynthSound*> (sound) != nullptr;

}

//===================================ENVELOPE FUNCTIONS==========================================
/*Functions for manipulating the ADSR envelope. 

	1. setEnvSampleRate() - sets the sample rate for the envelope
	2. setEnvParams() - sets the parameters of the ADSR envelope; uses the parameter tree to read the values from the GUI
*/

void SynthVoice::setEnvSampleRate() {

	env1.setSampleRate(getSampleRate());

}

void SynthVoice::setEnvParams(float *attack, float *decay, float *sustain, float *release) {

	setEnvSampleRate();

	juce::ADSR::Parameters params;

	params.attack = *attack;
	params.decay = *decay;
	params.sustain = *sustain;
	params.release = *release;

	env1.setParameters(params);

}

//======================================================================================================

//=======================================OSCILLATOR FUNCTIONS===========================================
/*Functions used for setting up the oscillators and the waveforms that they produce.

	1. setWaveformSelection - sets the type of oscillator used; uses the parameter tree to read the selection from the GUI
	2. getWaveform - depending on the selection of wave, returns the float value that the oscillators produce
*/


void SynthVoice::setWaveformSelection(float *selection1, float *selection2) {

	waveformSelection1 = *selection1;
	waveformSelection2 = *selection2;

}

float SynthVoice::getWaveform(int waveformChoice, int oscillator) {

	if (oscillator == 1) {

		switch (waveformChoice) {
		case 0:

			return osc1.sinewave(frequency);

		case 1:

			return osc1.saw(frequency);

		case 2:

			return osc1.square(frequency);
		}
	}

	else if (oscillator == 2) {

		switch (waveformChoice) {
		case 0:

			return osc2.sinewave(frequency/2);

		case 1:

			return osc2.saw(frequency/2);

		case 2:

			return osc2.square(frequency/2);
		}

	}


}

//========================================GENERAL SYNTHVOICE FUNCTIONS===================================================

/*
	General functions to implement Synth Voice class, which synthesises the sound when a key is pressed.

	1. startNote() - when a MIDI input is received, it reads the frequency of the note and velocity. Also, triggers the ADSR envelope
	2. stopNote() - clears current note, also stops the ADSR envelope
	3. pitchWheelMoved() - not implemented
	4. controllerMoved() - not implemented
	5. renderNextBlock() - calculates the output buffer which containts the information about the exiting sound.

*/


void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {

	env1.noteOn();

	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	level = velocity;

}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {

	env1.noteOff();

	allowTailOff = true;
	if (velocity == 0)
		clearCurrentNote();

}


void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
	

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {


}

void SynthVoice::renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {

	for (int sample = startSample; sample < numSamples; ++sample) {

		for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {

			wave =( getWaveform(waveformSelection1, 1)*level + getWaveform(waveformSelection2, 2)*level ) * env1.getNextSample();

			outputBuffer.addSample(channel, startSample, wave);
		}
		++startSample;
	}

	
}
