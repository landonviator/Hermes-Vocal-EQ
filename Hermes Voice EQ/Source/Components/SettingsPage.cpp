#include <JuceHeader.h>
#include "SettingsPage.h"

SettingsPage::SettingsPage()
{
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.setColour(_blackBackgroundColor);
    g.fillAll();
}

void SettingsPage::resized()
{
}
