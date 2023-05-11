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
    for (auto& button : _buttons)
    {
        button->setLookAndFeel(nullptr);
    }
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
    // theme label
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.1;
    auto labelWidth = getWidth() * 0.25;
    auto labelHeight = labelWidth * 0.5;
    _themeLabel.setBounds(leftMargin, topMargin, labelWidth, labelHeight);
    
    // theme menu
    auto menuWidth = labelWidth * 2.0;
    auto padding = labelHeight * 0.5;
    _themeMenu.setBounds(_themeLabel.getRight() + padding, topMargin, menuWidth, labelHeight);
    
    // social buttons
    auto buttonWidth = getWidth() * 0.185;
    auto buttonHeight = buttonWidth * 0.5;
    auto spaceBetween = buttonWidth * 0.1;
    for (int i = 0; i <_buttons.size(); i++)
    {
        if (i == 0)
        {
            _buttons[i]->setBounds(leftMargin, _themeLabel.getBottom() + labelHeight, buttonWidth, buttonHeight);
        }
        
        else if (i < _buttons.size() - 1)
        {
            _buttons[i]->setBounds(_buttons[i - 1]->getRight() + spaceBetween, _themeLabel.getBottom() + labelHeight, buttonWidth, buttonHeight);
        }
    }
    
    // constrast btn
    auto button1 = _buttons[0];
    auto button4 = _buttons[3];
    auto width = button4->getRight() - button1->getX();
    _contrastButton.setBounds(button1->getX(), button1->getBottom() + spaceBetween, width, buttonHeight);
    
    // tooltip btn
    _tooltipButton.setBounds(_buttons[0]->getX(), _contrastButton.getBottom() + spaceBetween, buttonWidth, buttonHeight);
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
    _themeMenu.setSelectedId(1);
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
        
        if (_contrastButton.getToggleState())
        {
            _contrastButton.triggerClick();
        }
        
        getParentComponent()->repaint();
    };
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
    
    if (&button == &_contrastButton)
    {
        button.setButtonText("High Contrast");
        button.onClick = [this]()
        {
            // to the editor
            sendChangeMessage();
        };
    }
    
    if (&button == &_tooltipButton)
    {
        button.setButtonText("Tooltips");
        button.setClickingTogglesState(true);
        button.setToggleState(true, juce::dontSendNotification);
        button.onClick = [this]()
        {
            // to the editor
            sendChangeMessage();
        };
    }
    
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colour::fromRGB(74, 81, 98).darker(0.5).withAlpha(0.3f));
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colour::fromRGB(74, 81, 98).darker(0.5).withAlpha(0.6f));
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

bool SettingsPage::getIsHighContrast()
{
    return _contrastButton.getToggleState();
}

void SettingsPage::resetToNonContrast()
{
    _themeMenu.onChange();
}

bool SettingsPage::getShouldUseTooltips()
{
    return _tooltipButton.getToggleState();
}
