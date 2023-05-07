#include <JuceHeader.h>
#include "Header.h"
#include "../PluginEditor.h"

Header::Header()
{
    // Settings
    setSettingsButtonProps();
    
    _dropShadow = std::make_unique<juce::DropShadower>(juce::DropShadow(juce::Colours::black.withAlpha(0.5f), 5, {}));
    _dropShadow->setOwner(this);
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
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
        
        auto black = juce::Colour::fromRGB(0, 0, 0);
        bool isHighContrast = currentBGColor == black;
        
        g.setColour(black.withAlpha(isHighContrast ? 1.0f : 0.2f));
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOnId, isHighContrast ? contrastColor : nonContrastColor);
        _settingsButton.setColour(juce::TextButton::ColourIds::textColourOffId, isHighContrast ? contrastColor : nonContrastColor);
    }

    
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
    auto buttonWidth = getHeight() * 0.75;
    auto padding = getHeight() * 0.125;
    
    _settingsButton.setBounds(getWidth() - buttonWidth - padding, padding, buttonWidth, buttonWidth);
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
