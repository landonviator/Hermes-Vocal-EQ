#include <JuceHeader.h>
#include "Header.h"
#include "../PluginEditor.h"

Header::Header()
{
    // Settings
    setSettingsButtonProps();
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    auto headerLogo = juce::ImageCache::getFromMemory(BinaryData::landon_png, BinaryData::landon_pngSize);
    g.drawImageWithin(headerLogo,
                      getWidth() * 0.02,
                      0,
                      getWidth() * 0.17,
                      getHeight(),
                      juce::RectanglePlacement::centred);
    
    auto* parent = dynamic_cast<HermesVoiceEQAudioProcessorEditor*>(getParentComponent());
    
    if (parent == nullptr)
        return;
    
    g.setColour(juce::Colours::transparentBlack);
    g.fillAll();
    
    g.setColour(parent->getThemeData().getAuxTextColor());
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 2.0f);
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
