#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"
#include "../Widgets/TextButton.h"

class HermesVoiceEQAudioProcessorEditor;
class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // Settings
    bool isSettingsActive();
    
private:
    
    // Settings
    viator_gui::TextButton _settingsButton;
    void setSettingsButtonProps();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
