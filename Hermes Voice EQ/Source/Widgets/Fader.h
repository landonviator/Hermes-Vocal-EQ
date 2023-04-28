#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"
#include "../LAF/FaderLAF.h"

class Fader  : public juce::Slider
{
public:
    Fader();
    ~Fader() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    // Shadow
    juce::DropShadow shadowProperties;
    juce::DropShadowEffect dialShadow;
    
    // LAF
    juce::CustomFader _customFaderLAF;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fader)
};
