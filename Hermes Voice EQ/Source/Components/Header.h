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
    
    // settings
    bool isSettingsActive();
    
private:
    void setSettingsButtonProps();
    
private:
    // settings
    viator_gui::TextButton _settingsButton;
    viator_gui::SettingsButton _wrenchButton;
    
    // shadow
    std::unique_ptr<juce::DropShadower> _dropShadow;
    
private:
    const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    const juce::Colour _innerBgColor = juce::Colour::fromRGB(40, 44, 52);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
