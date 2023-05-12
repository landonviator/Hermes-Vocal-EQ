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
    
    // constrast stuff
    bool getIsHighContrast();
    void resetToNonContrast();
    
    // tooltip stuff
    bool getShouldUseTooltips();

// objects
private:
    viator_gui::Menu _themeMenu;
    juce::Label _themeLabel;
    
    viator_gui::TextButton _emailButton;
    juce::Label _emailButtonLabel;
    viator_gui::TextButton _patreonButton;
    juce::Label _patreonButtonLabel;
    viator_gui::TextButton _youtubeButton;
    juce::Label _youtubeButtonLabel;
    viator_gui::TextButton _instaButton;
    juce::Label _instaButtonLabel;
    viator_gui::TextButton _contrastButton;
    juce::Label _contrastButtonLabel;
    viator_gui::TextButton _tooltipButton;
    juce::Label _tooltipButtonLabel;
    
    viator_gui::CustomTextButton _customButton;
    
// methods
private:
    void initThemeLabelProps();
    void initThemeMenuProps();
    void initButtonLabels(juce::Label& label, int index);
    void initButtonProps(viator_gui::TextButton& button, int index);
    void sendEmail(const juce::String& recipient, const juce::String& subject, const juce::String& body);
    
// vars
private:
    std::vector<viator_gui::TextButton*> _buttons =
    {
        &_contrastButton, &_tooltipButton, &_emailButton,
        &_patreonButton, &_youtubeButton, &_instaButton
    };
    
    std::vector<juce::Label*> _buttonLabels =
    {
        &_contrastButtonLabel, &_tooltipButtonLabel, &_emailButtonLabel,
        &_patreonButtonLabel, &_youtubeButtonLabel, &_instaButtonLabel
    };
    
    std::vector<juce::String*> _labelTexts =
    {
        &_contrastButtonLabelText, &_tooltipButtonLabelText, &_emailButtonLabelText, &_patreonButtonLabelText, &_youtubeButtonLabelText, &_instaButtonLabelText
    };
    
    std::vector<juce::String*> _buttonTexts =
    {
        &_contrastButtonText, &_tooltipButtonText, &_emailButtonText,
        &_patreonButtonText, &_youtubeButtonText, &_instaButtonText
    };
    
    // colors
    const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
    const juce::Colour _innerBgColor = juce::Colour::fromRGB(40, 44, 52);
    
    // shadow
    std::unique_ptr<juce::DropShadower> _dropShadow;
    
    // label texts
    juce::String _emailButtonLabelText = "Email";
    juce::String _patreonButtonLabelText = "Patreon";
    juce::String _youtubeButtonLabelText = "YouTube";
    juce::String _instaButtonLabelText = "Instagram";
    juce::String _contrastButtonLabelText = "High-Contrast";
    juce::String _tooltipButtonLabelText = "Tooltips";
    
    juce::String _emailButtonText = "Go!";
    juce::String _patreonButtonText = "Go!";
    juce::String _youtubeButtonText = "Go!";
    juce::String _instaButtonText = "Go!";
    juce::String _contrastButtonText = "On";
    juce::String _tooltipButtonText = "On";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
