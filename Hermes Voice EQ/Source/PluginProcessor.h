#pragma once
#include <JuceHeader.h>
#include "DSP/FilterBank.h"
#include "Globals/Globals.h"
#include "Globals/Parameters.h"


class HermesVoiceEQAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    HermesVoiceEQAudioProcessor();
    ~HermesVoiceEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    ViatorParameters::Params _parameterMap;
    juce::AudioProcessorValueTreeState _treeState;

// objects
private:
    juce::dsp::ProcessSpec _spec;
    FilterBank<float> _filterBankModule;
    juce::dsp::Gain<float> _inputGainModule;
    juce::dsp::Gain<float> _outputGainModule;
 
// methods
private:
    void prepareModules(juce::dsp::ProcessSpec& spec);
    void updateFilters();
    void updateParameters();
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    static juce::String valueToTextFunction(float x) { return juce::String(static_cast<int>(x)); }
    static float textToValueFunction(const juce::String& str) { return str.getFloatValue(); }
    
// variables
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesVoiceEQAudioProcessor)
};
