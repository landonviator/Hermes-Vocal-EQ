#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Globals/Globals.h"
#include "Components/Header.h"
#include "Components/SettingsPage.h"
#include "Widgets/Fader.h"

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
    
    Fader _band1Dial;
    Fader _band2Dial;
    Fader _band3Dial;
    Fader _band4Dial;
    Fader _band5Dial;
    Fader _band6Dial;
    std::vector<Fader*> _dials =
    {
        &_band1Dial, &_band2Dial, &_band3Dial,
        &_band4Dial, &_band5Dial, &_band6Dial
    };
    void initDialProps(Fader& dial, int index);
    
    Header _headerComp;
    
    juce::Label _band1DialLabel;
    juce::Label _band2DialLabel;
    juce::Label _band3DialLabel;
    juce::Label _band4DialLabel;
    juce::Label _band5DialLabel;
    juce::Label _band6DialLabel;
    std::vector<juce::Label*> _dialLabels =
    {
        &_band1DialLabel, &_band2DialLabel, &_band3DialLabel,
        &_band4DialLabel, &_band5DialLabel, &_band6DialLabel
    };
    void initLabelProps(juce::Label& label, int index);
    
    juce::String _band1DialLabelText = "Rumble";
    juce::String _band2DialLabelText = "Mud";
    juce::String _band3DialLabelText = "Muffle";
    juce::String _band4DialLabelText = "Clarity";
    juce::String _band5DialLabelText = "Air";
    juce::String _band6DialLabelText = "Noise";
    std::vector<juce::String*> _labelNames =
    {
        &_band1DialLabelText, &_band2DialLabelText, &_band3DialLabelText,
        &_band4DialLabelText, &_band5DialLabelText, &_band6DialLabelText
    };
    
    // Settings
    SettingsPage _settingsPage;
    void setSettingsState(bool isActive);
    juce::Label _settingsOverlay;
    void initOverlayProps();
    
    using sliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::OwnedArray<sliderAttachment> _sliderAttachments;
    std::unique_ptr<sliderAttachment> _band1Attach;
    std::unique_ptr<sliderAttachment> _band2Attach;
    std::unique_ptr<sliderAttachment> _band3Attach;
    std::unique_ptr<sliderAttachment> _band4Attach;
    std::unique_ptr<sliderAttachment> _band5Attach;
    std::unique_ptr<sliderAttachment> _band6Attach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesVoiceEQAudioProcessorEditor)
};
