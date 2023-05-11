#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"
#include "../PluginProcessor.h"

class HermesVoiceEQAudioProcessorEditor;
class Header  : public juce::Component
{
public:
    Header(HermesVoiceEQAudioProcessor&);
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // settings stuff
    bool isSettingsActive();
    
    // tooltip stuff
    void enableToolTips(const bool shouldEnable);
    
// objects
private:
    HermesVoiceEQAudioProcessor& _audioProcessor;
    
    // settings
    viator_gui::TextButton _settingsButton;
    viator_gui::SettingsButton _wrenchButton;
    
    // shadow
    std::unique_ptr<juce::DropShadower> _dropShadow;
    
    // buttons
    viator_gui::TextButton _maleButton;
    viator_gui::TextButton _femaleButton;
    viator_gui::CustomTextButton _customButton;
    
    // dial attachments
    using buttonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    juce::OwnedArray<buttonAttachment> _buttonAttachments;
    std::unique_ptr<buttonAttachment> _maleAttach;
    std::unique_ptr<buttonAttachment> _femaleAttach;
    
    // tooltip
    juce::TooltipWindow _tooltipWindow;
    
// methods
private:
    void setSettingsButtonProps();
    void initButtons(viator_gui::TextButton& button);
    void updateButtonColors(juce::Graphics& g);
    void initTooltips();
    
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
