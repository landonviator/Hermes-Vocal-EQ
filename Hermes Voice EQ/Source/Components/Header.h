#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"

class HermesVoiceEQAudioProcessorEditor;
class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Settings
    bool isSettingsActive();
    
private:
    
    // Shadow
    std::unique_ptr<juce::DropShadower> _dropShadow;
    float _shadowAlpha = 0.5f;
    
    // Settings
    juce::TextButton _settingsButton;
    void setSettingsButtonProps();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
