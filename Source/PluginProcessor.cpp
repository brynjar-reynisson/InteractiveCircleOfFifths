/*
  ==============================================================================

   This file is part of the InteractiveCircleOfFifths plugin code.
   Copyright (c) Brynjar Reynisson

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   to use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
   REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
   AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
   INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
   PERFORMANCE OF THIS SOFTWARE.

  ==============================================================================
*/
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InteractiveCircleOfFifthsAudioProcessor::InteractiveCircleOfFifthsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

InteractiveCircleOfFifthsAudioProcessor::~InteractiveCircleOfFifthsAudioProcessor()
{
}

//==============================================================================
const juce::String InteractiveCircleOfFifthsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool InteractiveCircleOfFifthsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool InteractiveCircleOfFifthsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool InteractiveCircleOfFifthsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double InteractiveCircleOfFifthsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int InteractiveCircleOfFifthsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int InteractiveCircleOfFifthsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void InteractiveCircleOfFifthsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String InteractiveCircleOfFifthsAudioProcessor::getProgramName (int index)
{
    return {};
}

void InteractiveCircleOfFifthsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void InteractiveCircleOfFifthsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void InteractiveCircleOfFifthsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool InteractiveCircleOfFifthsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void InteractiveCircleOfFifthsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Let's do absolutely nothing here
}

//==============================================================================
bool InteractiveCircleOfFifthsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* InteractiveCircleOfFifthsAudioProcessor::createEditor()
{
    if (wrapperType == wrapperType_Standalone)
    {
        if (TopLevelWindow::getNumTopLevelWindows() == 1)
        {
            TopLevelWindow* w = TopLevelWindow::getTopLevelWindow(0);
            w->setUsingNativeTitleBar(true);
        }
    }
    return new InteractiveCircleOfFifthsAudioProcessorEditor (*this);
}

//==============================================================================
void InteractiveCircleOfFifthsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void InteractiveCircleOfFifthsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InteractiveCircleOfFifthsAudioProcessor();
}
