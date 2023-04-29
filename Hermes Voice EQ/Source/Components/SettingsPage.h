#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"

class SettingsPage  : public juce::Component
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
