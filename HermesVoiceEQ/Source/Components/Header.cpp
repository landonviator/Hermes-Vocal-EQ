#include <JuceHeader.h>
#include "Header.h"
#include "../PluginEditor.h"

Header::Header(HermesVoiceEQAudioProcessor& p) : _audioProcessor(p)
{
    // Settings
    setSettingsButtonProps();
    
    // shadow
    _dropShadow = std::make_unique<juce::DropShadower>(juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 5, {}));
    _dropShadow->setOwner(this);
    
    // buttons
    for (auto& button : _buttons)
    {
        initButtons(*button);
    }
    
    // button attachments
    _buttonAttachments.add(std::make_unique<buttonAttachment>(_audioProcessor._treeState, ViatorParameters::voiceID, _maleButton));
    
    // tooltip
    initTooltips();
    
    _maleButton.setButtonText(_maleButton.getToggleState() ? "Voice: Male" : "Voice: Female");

    _maleButton.onClick = [this]()
    {
        _maleButton.setButtonText(_maleButton.getToggleState() ? "Voice: Male" : "Voice: Female");
    };
}

Header::~Header()
{
    for (auto& button : _buttons)
    {
        button->setLookAndFeel(nullptr);
    }
    
    _settingsButton.setLookAndFeel(nullptr);
}

void Header::paint (juce::Graphics& g)
{
    // update colors on theme change
    updateButtonColors(g);
    
    // set background color
    g.fillRect(getLocalBounds());
    
    // update wrench color
    setSettingsButtonProps();
    
    // force image to color correctly
    g.setColour(juce::Colours::white);
    
    // add logo image
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon_png, BinaryData::landon_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight(),
                      juce::RectanglePlacement::centred);
}

void Header::resized()
{
    // settings
    auto squareButtonWidth = getHeight() * 0.75;
    auto padding = getHeight() * 0.125;
    auto spaceBetween = squareButtonWidth * 0.25;
    _settingsButton.setBounds(getWidth() - squareButtonWidth - padding, padding, squareButtonWidth, squareButtonWidth);
    
    // buttons
    auto maleButtonWidth = squareButtonWidth * 2.0;
    _maleButton.setBounds(_settingsButton.getX() - maleButtonWidth - spaceBetween, _settingsButton.getY(), maleButtonWidth, squareButtonWidth);
}

#pragma mark Buttons
void Header::setSettingsButtonProps()
{
    addAndMakeVisible(_settingsButton);
    
    _settingsButton.onClick = [this]()
    {
        getParentComponent()->resized();
    };
}

bool Header::isSettingsActive()
{
    return _settingsButton.getToggleState();
}

void Header::initButtons(viator_gui::TextButton &button)
{
    _maleButton.setButtonText("Voice: Male");
    _maleButton.setButtonStyle(viator_gui::TextButton::ButtonStyle::kNormal);
    _settingsButton.setTooltip("Settings");
    _settingsButton.setButtonStyle(viator_gui::TextButton::ButtonStyle::kSettings);
    _maleButton.setTooltip("Voice preset");
    button.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::transparentBlack);
    button.setColour(juce::ComboBox::outlineColourId, juce::Colours::transparentBlack);
    button.setColour(juce::TextButton::ColourIds::textColourOnId, _textColor);
    button.setColour(juce::TextButton::ColourIds::textColourOffId, _textColor);
    button.setLookAndFeel(&_customButton);
    addAndMakeVisible(button);
}

void Header::updateButtonColors(juce::Graphics& g)
{
    // init color info from parent
    auto* parent = dynamic_cast<HermesVoiceEQAudioProcessorEditor*>(getParentComponent());
    if (parent != nullptr)
    {
        auto currentBGColor = parent->getThemeData().getAuxBackgroundColor();
        auto nonContrastColor = parent->getThemeData().getWidgetFillColor();
        auto contrastColor = parent->getThemeData().getMainBackgroundColor();
        
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOnId, nonContrastColor);
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOffId, nonContrastColor);
        _maleButton.setColour(juce::TextButton::ColourIds::textColourOnId, nonContrastColor);
        _maleButton.setColour(juce::TextButton::ColourIds::textColourOffId, nonContrastColor);
        
        auto black = juce::Colour::fromRGB(0, 0, 0);
        bool isHighContrast = currentBGColor == black;
        
        g.setColour(black.withAlpha(isHighContrast ? 1.0f : 0.2f));
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOnId, isHighContrast ? contrastColor : nonContrastColor);
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOffId, isHighContrast ? contrastColor : nonContrastColor);
        _maleButton.setColour(juce::TextButton::ColourIds::textColourOnId, isHighContrast ? contrastColor : nonContrastColor);
        _maleButton.setColour(juce::TextButton::ColourIds::textColourOffId, isHighContrast ? contrastColor : nonContrastColor);
    }
}

void Header::initTooltips()
{
    _tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::backgroundColourId, juce::Colour::fromRGB(33, 37, 43));
    _tooltipWindow.getLookAndFeel().setColour(juce::TooltipWindow::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    addAndMakeVisible(_tooltipWindow);
}

void Header::enableToolTips(const bool shouldEnable)
{
    _tooltipWindow.enableTooltips(shouldEnable);
}

void Header::changeListenerCallback(juce::ChangeBroadcaster *source)
{
}
