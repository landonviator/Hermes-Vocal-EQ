#include <JuceHeader.h>
#include "SettingsPage.h"
#include "../PluginEditor.h"

SettingsPage::SettingsPage()
{
    // Labels
    initThemeLabelProps();
    
    // Menus
    initThemeMenuProps();
    
    // Buttons
    for (auto& button : _buttons)
    {
        initButtonProps(*button);
    }
    
    _dropShadow = std::make_unique<juce::DropShadower>(juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 5, {}));
    _dropShadow->setOwner(this);
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.setColour(_innerBgColor);
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::black.withAlpha(0.4f));
    g.fillRect(getLocalBounds());
}

void SettingsPage::resized()
{
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.1;
    auto labelWidth = getWidth() * 0.25;
    auto labelHeight = labelWidth * 0.5;
    _themeLabel.setBounds(leftMargin, topMargin, labelWidth, labelHeight);
    
    auto menuWidth = labelWidth * 2.0;
    auto padding = labelHeight * 0.5;
    _themeMenu.setBounds(_themeLabel.getRight() + padding, topMargin, menuWidth, labelHeight);
    
    auto buttonWidth = getWidth() * 0.185;
    auto buttonHeight = buttonWidth * 0.5;
    auto spaceBetween = buttonWidth * 0.1;
    for (int i = 0; i <_buttons.size(); i++)
    {
        if (i == 0)
        {
            _buttons[i]->setBounds(leftMargin, _themeLabel.getBottom() + labelHeight, buttonWidth, buttonHeight);
        }
        
        else
        {
            _buttons[i]->setBounds(_buttons[i - 1]->getRight() + spaceBetween, _themeLabel.getBottom() + labelHeight, buttonWidth, buttonHeight);
        }
    }
}

void SettingsPage::initThemeLabelProps()
{
    _themeLabel.setText("Color Theme", juce::dontSendNotification);
    _themeLabel.setJustificationType(juce::Justification::centred);
    _themeLabel.setFont(juce::Font("Helvetica", 12.0f, juce::Font::FontStyleFlags::bold));
    _themeLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    _themeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(155, 165, 175));
    addAndMakeVisible(_themeLabel);
}

void SettingsPage::initThemeMenuProps()
{
    _themeMenu.addItem("Prime Dark", 1);
    _themeMenu.addItem("Lofi", 2);
    _themeMenu.addItem("Retro", 3);
    _themeMenu.addItem("Vapor Wave", 4);
    addAndMakeVisible(_themeMenu);
    
    _themeMenu.onChange = [this]()
    {
        auto* parent = dynamic_cast<HermesVoiceEQAudioProcessorEditor*>(getParentComponent());
        
        if (parent == nullptr)
            return;
        
        switch (_themeMenu.getSelectedId())
        {
            case 1:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kPrimeDark);
                break;
            }
                
            case 2:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kLofi);
                break;
            }
                
            case 3:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kRetro);
                break;
            }
                
            case 4:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kVaporWave);
                break;
            }
        }
        
        getParentComponent()->repaint();
    };
    
    _themeMenu.setSelectedId(1);
}

void SettingsPage::initButtonProps(viator_gui::TextButton& button)
{
    if (&button == &_emailButton)
    {
        button.setButtonText("Email");
        _emailButton.onClick = [this]()
        {
            sendEmail("viatordsp@gmail.com", "bruh", "BRUH");
        };
    }
    
    if (&button == &_patreonButton)
    {
        button.setButtonText("P");
        _patreonButton.onClick = [this]()
        {
            auto patreon = juce::URL("https://www.patreon.com/ViatorDSP");
            patreon.launchInDefaultBrowser();
        };
    }
    
    if (&button == &_youtubeButton)
    {
        button.setButtonText("YT");
        _youtubeButton.onClick = [this]()
        {
            auto youtube = juce::URL("https://www.youtube.com/@drbruisin");
            youtube.launchInDefaultBrowser();
        };
    }
    
    if (&button == &_instaButton)
    {
        button.setButtonText("Insta");
        _instaButton.onClick = [this]()
        {
            auto insta = juce::URL("https://www.instagram.com/viatordsp/");
            insta.launchInDefaultBrowser();
        };
    }
    
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::dimgrey.withAlpha(0.1f));
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::dimgrey.withAlpha(0.1f));
    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, _textColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, _textColor);
    button.setLookAndFeel(&_customButton);
    addAndMakeVisible(button);
}

void SettingsPage::sendEmail(const juce::String& recipient, const juce::String& subject, const juce::String& body)
{
    // Build the mailto URL
    juce::URL mailtoURL("mailto:" + recipient + "?subject=" + subject + "&body=" + body);

    // Open the mailto URL in the user's default email client
    if (!mailtoURL.launchInDefaultBrowser())
    {
        DBG("Failed to open email client.");
    }
}
