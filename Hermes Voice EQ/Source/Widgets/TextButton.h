#pragma once
#include <JuceHeader.h>
#include "../LAF/TextButtonLAF.h"

namespace viator_gui
{
    class TextButton  : public juce::TextButton
    {
    public:
        TextButton();
        ~TextButton() override;

        void paint (juce::Graphics&) override;
        void resized() override;

    private:
        const juce::Colour _textColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
        juce::CustomTextButton _customLAF;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextButton)
    };
}
