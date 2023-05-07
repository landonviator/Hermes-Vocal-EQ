#pragma once
#include <JuceHeader.h>
#include "../LAF/Colors.h"

class HermesVoiceEQAudioProcessorEditor;
class SettingsPage  : public juce::Component, public juce::ChangeBroadcaster
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool getIsHighContrast();
    void resetToNonContrast();

private:
    juce::Label _themeLabel;
    viator_gui::Menu _themeMenu;
    viator_gui::TextButton _emailButton;
    viator_gui::TextButton _patreonButton;
    viator_gui::TextButton _youtubeButton;
    viator_gui::TextButton _instaButton;
    viator_gui::TextButton _contrastButton;
    viator_gui::CustomTextButton _customButton;
    
private:
    void initThemeLabelProps();
    void initThemeMenuProps();
    void initButtonProps(viator_gui::TextButton& button);
    void sendEmail(const juce::String& recipient, const juce::String& subject, const juce::String& body);
    
private:
    std::vector<viator_gui::TextButton*> _buttons =
    {
        &_emailButton, &_patreonButton, &_youtubeButton,
        &_instaButton, &_contrastButton
    };
    
    const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    
    // shadow
    std::unique_ptr<juce::DropShadower> _dropShadow;
    
    const juce::Colour _innerBgColor = juce::Colour::fromRGB(40, 44, 52);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
