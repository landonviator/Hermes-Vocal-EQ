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
    g.setColour(_innerBgColor);
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::black.withAlpha(0.4f));
    g.fillRect(getLocalBounds());
    
    g.setColour(juce::Colours::white);
    
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
    _settingsButton.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::dimgrey.brighter(0.5));
    _settingsButton.setColour(juce::TextButton::ColourIds::textColourOffId, juce::Colours::dimgrey.brighter(0.5));
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
