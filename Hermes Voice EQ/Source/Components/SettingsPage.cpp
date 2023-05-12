#include <JuceHeader.h>
#include "SettingsPage.h"
#include "../PluginEditor.h"

SettingsPage::SettingsPage()
{
    // labels
    int index = 0;
    initThemeLabelProps();
    for (auto& label : _buttonLabels)
    {
        initButtonLabels(*label, index);
        index++;
    }
    
    // menus
    initThemeMenuProps();
    
    index = 0;
    
    // buttons
    for (auto& button : _buttons)
    {
        initButtonProps(*button, index);
        index++;
    }
    
    // shadow
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
    auto lineColor = juce::Colours::whitesmoke.withAlpha(0.1f);
    auto lineMargin = 6;
    
    g.setColour(_innerBgColor);
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::black.withAlpha(0.4f));
    g.fillRect(getLocalBounds());
    
//    g.setColour(lineColor);
//    g.drawLine(_buttons[0]->getX(), _buttons[0]->getY() - lineMargin, _buttons[3]->getRight(), _buttons[0]->getY() - lineMargin, 1.0f);
//    g.drawLine(_buttons[0]->getX(), _contrastButton.getY() - lineMargin, _buttons[3]->getRight(), _contrastButton.getY() - lineMargin, 1.0f);
}

void SettingsPage::resized()
{
    // theme label
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.1;
    auto labelWidth = getWidth() * 0.3;
    auto labelHeight = labelWidth * 0.3;
    _themeLabel.setBounds(leftMargin, topMargin, labelWidth, labelHeight);
    
    auto labelY = _themeLabel.getBottom() + labelHeight;
    for (int i = 0; i < _buttonLabels.size(); ++i)
    {
        _buttonLabels[i]->setBounds(leftMargin, labelY, labelWidth, labelHeight);
        labelY += labelHeight;
        
        if (i == 1)
        {
            labelY += labelHeight;
        }
    }
    
    // theme menu
    auto menuWidth = labelWidth * 1.5;
    auto padding = labelHeight * 0.5;
    _themeMenu.setBounds(_themeLabel.getRight() + padding, topMargin, menuWidth, labelHeight);
    
    // buttons
    auto buttonY = _buttonLabels[0]->getY();
    for (int i = 0; i <_buttons.size(); i++)
    {
        _buttons[i]->setBounds(_themeMenu.getX(), buttonY, labelWidth * 0.5, labelHeight);
        buttonY += labelHeight;
        
        if (i == 1)
        {
            buttonY += labelHeight;
        }
    }
}

void SettingsPage::initThemeLabelProps()
{
    _themeLabel.setText("Color Theme", juce::dontSendNotification);
    _themeLabel.setJustificationType(juce::Justification::centredLeft);
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

void SettingsPage::initButtonProps(viator_gui::TextButton& button, int index)
{
    if (&button == &_emailButton)
    {
        _emailButton.onClick = [this]()
        {
            sendEmail("viatordsp@gmail.com", "bruh", "BRUH");
        };
    }
    
    if (&button == &_patreonButton)
    {
        _patreonButton.onClick = [this]()
        {
            auto patreon = juce::URL("https://www.patreon.com/ViatorDSP");
            patreon.launchInDefaultBrowser();
        };
    }
    
    if (&button == &_youtubeButton)
    {
        _youtubeButton.onClick = [this]()
        {
            auto youtube = juce::URL("https://www.youtube.com/@drbruisin");
            youtube.launchInDefaultBrowser();
        };
    }
    
    if (&button == &_instaButton)
    {
        _instaButton.onClick = [this]()
        {
            auto insta = juce::URL("https://www.instagram.com/viatordsp/");
            insta.launchInDefaultBrowser();
        };
    }
    
    if (&button == &_contrastButton)
    {
        button.onClick = [this]()
        {
            // to the editor
            sendChangeMessage();
        };
    }
    
    if (&button == &_tooltipButton)
    {
        button.setClickingTogglesState(true);
        button.setToggleState(true, juce::dontSendNotification);
        button.onClick = [this]()
        {
            // to the editor
            sendChangeMessage();
        };
    }
    
    button.setButtonText(*_buttonTexts[index]);
    button.setColour(juce::TextButton::ColourIds::buttonColourId, _innerBgColor);
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, _innerBgColor.brighter(0.25));
    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, _textColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, _textColor);
    button.setLookAndFeel(&_customButton);
    addAndMakeVisible(button);
}

void SettingsPage::initButtonLabels(juce::Label &label, int index)
{
    label.setText(*_labelTexts[index], juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centredLeft);
    label.setFont(juce::Font("Helvetica", 12.0f, juce::Font::FontStyleFlags::bold));
    label.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(155, 165, 175));
    addAndMakeVisible(label);
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
