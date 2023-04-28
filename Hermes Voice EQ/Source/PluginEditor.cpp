/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HermesVoiceEQAudioProcessorEditor::HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

HermesVoiceEQAudioProcessorEditor::~HermesVoiceEQAudioProcessorEditor()
{
}

//==============================================================================
void HermesVoiceEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(_mainBackgroundColor);
    g.fillAll ();

    g.setColour (_mainTextColor);
    g.setFont (juce::Font("Helvetica", 15.0f, juce::Justification::centred));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void HermesVoiceEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
