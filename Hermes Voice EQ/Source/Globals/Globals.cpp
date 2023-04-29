#include "Globals.h"

juce::Colour _mainBackgroundColor = juce::Colour::fromRGB(40, 42, 54);
juce::Colour _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
juce::Colour _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
juce::Colour _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
juce::Colour _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
juce::Colour _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);

namespace ViatorParameters
{
    const juce::String band1ID = "band1";
    const juce::String band1Name = "Rumble";

    const juce::String band2ID = "band2";
    const juce::String band2Name = "Mud";

    const juce::String band3ID = "band3";
    const juce::String band3Name = "Muffle";

    const juce::String band4ID = "band4";
    const juce::String band4Name = "Clarity";

    const juce::String band5ID = "band5";
    const juce::String band5Name = "Air";

    const juce::String band6ID = "band6";
    const juce::String band6Name = "Noise";
}
