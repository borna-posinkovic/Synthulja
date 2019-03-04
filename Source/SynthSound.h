/*
  ==============================================================================

    SynthSound.h
    Created: 13 Feb 2019 1:14:41am
    Author:  Borna

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthVoice.h"


class SynthSound : public SynthesiserSound {

public:

	bool appliesToNote(int midiNoteNumber) override {
		return true;
	}

	bool appliesToChannel(int midiChannel) override {
		return true;
	}

};