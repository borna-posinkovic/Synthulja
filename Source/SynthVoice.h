/*
  ==============================================================================

    SynthVoice.h
    Created: 13 Feb 2019 1:14:49am
    Author:  Borna

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice {

public:

	bool canPlaySound(SynthesiserSound* sound) override;

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;

	void stopNote(float velocity, bool allowTailOff) override;

	void pitchWheelMoved(int newPitchWheelValue) override;

	void controllerMoved(int controllerNumber, int newControllerValue) override;

	void renderNextBlock(AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;

	void setEnvParams(float *attack, float *decay, float *sustain, float *release);

	float getWaveform(int waveformChoice, int oscillator);

	void setWaveformSelection(float *selection1, float *selection2);

	void setEnvSampleRate();

private:

	int waveformSelection1;
	int waveformSelection2;

	ADSR env1;

	//ADSR env2;

	float frequency;
	float level;

	float wave;
	float sound;
	
	maxiOsc osc1;
	maxiOsc osc2;
	int numOscs = 2;

	int numEnvs = 2;

	std::vector<maxiOsc> osc = { osc1, osc2 };
	//std::vector<ADSR> env = { env1, env2 };
};





