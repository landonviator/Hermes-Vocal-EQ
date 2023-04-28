#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Globals/Globals.h"
#include "Components/Header.h"

class HermesVoiceEQAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor&);
    ~HermesVoiceEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HermesVoiceEQAudioProcessor& audioProcessor;
    
    void setWindowSizeLogic();
    
    juce::Slider _band1Dial;
    juce::Slider _band2Dial;
    juce::Slider _band3Dial;
    juce::Slider _band4Dial;
    juce::Slider _band5Dial;
    juce::Slider _band6Dial;
    std::vector<juce::Slider*> _dials =
    {
        &_band1Dial, &_band2Dial, &_band3Dial,
        &_band4Dial, &_band5Dial, &_band6Dial
    };
    
    void initDialProps(juce::Slider& dial);
    
    Header _headerComp;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesVoiceEQAudioProcessorEditor)
};
