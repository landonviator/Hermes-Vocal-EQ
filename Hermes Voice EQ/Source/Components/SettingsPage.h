#pragma once
#include <JuceHeader.h>
#include "../LAF/Colors.h"

class HermesVoiceEQAudioProcessorEditor;
class SettingsPage  : public juce::Component, public juce::ChangeBroadcaster
{
public:
    SettingsPage();
    ~SettingsPage() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Label _themeLabel;
    juce::ComboBox _themeMenu;
    
private:
    void initThemeLabelProps();
    void initThemeMenuProps();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPage)
};
