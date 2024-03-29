/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
OverdriveAudioProcessor::OverdriveAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

OverdriveAudioProcessor::~OverdriveAudioProcessor()
{
}

//==============================================================================
const String OverdriveAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OverdriveAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OverdriveAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OverdriveAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OverdriveAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OverdriveAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OverdriveAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OverdriveAudioProcessor::setCurrentProgram (int index)
{
}

const String OverdriveAudioProcessor::getProgramName (int index)
{
    return {};
}

void OverdriveAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OverdriveAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void OverdriveAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OverdriveAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

//{
//	addParameter(gain = new AudioParameterFloat(	// L2P2_B
//		"gain",										// L2P2_B
//		"Gain",										// L2P2_B
//		0.0f,										// L2P2_B
//		1.0f,										// L2P2_B
//		0.5f));										// L2P2_B
//}

void OverdriveAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	auto inChNum = getTotalNumInputChannels();
	auto outChNum = getTotalNumOutputChannels();
	auto smpNum = buffer.getNumSamples();

	auto wet = wetDry / 100.0;
	auto dry = 1.0 - wet;

	for (int channel = 0; channel < outChNum; ++channel)
	{
		if (channel>inChNum)
			buffer.clear(channel, 0, smpNum);
		else
		{
			auto* channelData = buffer.getWritePointer(channel, 0);
			for (int smp = 0; smp < smpNum; ++smp)
			{
				channelData[smp] = getOverdriveSignalAmplitude(channelData[smp]);
				channelData[smp] = getWetSignal(channelData[smp]) * wet + channelData[smp] * dry;
			}
		}
	}
}

float OverdriveAudioProcessor::getOverdriveSignalAmplitude(float signal)
{
	float amplitude = overdriveSliderValue;
	signal = signal * amplitude;
	return signal;
}

float OverdriveAudioProcessor::getWetSignal(float signal)
{
	if (signal< -2 / 3)
		signal = -1;
	else if (-1.0 / 3.0 < signal <= -2.0 / 3.0)
		signal = -((3 - (2 + 3 * signal * signal)) / 3);
	else if (1.0 / 3.0 < signal <= -1.0 / 3.0)
		signal = 2 * signal;
	else if (2.0 / 3.0< signal <= 1.0 / 3.0)
		signal = ((3 - (2 + 3 * signal * signal)) / 3);
	else if (2.0 / 3.0< signal)
		signal = 1;
	return signal;
}

//==============================================================================
bool OverdriveAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OverdriveAudioProcessor::createEditor()
{
    return new OverdriveAudioProcessorEditor (*this);
}

//==============================================================================
void OverdriveAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OverdriveAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OverdriveAudioProcessor();
}
