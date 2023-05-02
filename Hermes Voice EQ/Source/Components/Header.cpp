#include <JuceHeader.h>
#include "Header.h"
#include "../PluginEditor.h"

Header::Header()
{
    // Shadow
    _dropShadow = std::make_unique<juce::DropShadower>(juce::DropShadow(juce::Colours::black.withAlpha(_shadowAlpha), 5, {}));
    _dropShadow->setOwner(this);
    
    // Settings
    setSettingsButtonProps();
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    auto* parent = dynamic_cast<HermesVoiceEQAudioProcessorEditor*>(getParentComponent());
    
    if (parent == nullptr)
        return;
    
    g.setColour(parent->getThemeData().getAuxBackgroundColor());
    g.fillAll();
}

void Header::resized()
{
    auto buttonWidth = getHeight();
    auto buttonHeight = buttonWidth * 0.5;
    auto padding = getHeight() * 0.25;
    
    _settingsButton.setBounds(getWidth() - buttonWidth - padding, padding, buttonWidth, buttonHeight);
}

#pragma mark Buttons
void Header::setSettingsButtonProps()
{
    _settingsButton.setClickingTogglesState(true);
    _settingsButton.setButtonText("Sets");
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
