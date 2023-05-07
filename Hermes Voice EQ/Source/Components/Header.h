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
    
    // settings stuff
    bool isSettingsActive();
    
// objects
private:
    // settings
    viator_gui::TextButton _settingsButton;
    viator_gui::SettingsButton _wrenchButton;
    
    // shadow
    std::unique_ptr<juce::DropShadower> _dropShado
    
// methods
private:
    void setSettingsButtonProps();
    
// vars
private:
    const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
