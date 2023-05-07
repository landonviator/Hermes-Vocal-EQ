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
    std::unique_ptr<juce::DropShadower> _dropShadow;
    
    // buttons
    viator_gui::TextButton _maleButton;
    viator_gui::TextButton _femaleButton;
    viator_gui::CustomTextButton _customButton;
    
// methods
private:
    void setSettingsButtonProps();
    void initButtons(viator_gui::TextButton& button);
    void updateButtonColors(juce::Graphics& g);
    
// vars
private:
    // colors
    const juce::Colour _innerBgColor = juce::Colour::fromRGB(40, 44, 52);
    const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    std::vector<viator_gui::TextButton*> _buttons =
    {
        &_maleButton, &_femaleButton
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
