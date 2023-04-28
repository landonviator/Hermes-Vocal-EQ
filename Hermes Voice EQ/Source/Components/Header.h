#pragma once
#include <JuceHeader.h>
#include "../Globals/Globals.h"

class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    std::unique_ptr<juce::DropShadower> _dropShadow;
    float _shadowAlpha = 0.5f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
