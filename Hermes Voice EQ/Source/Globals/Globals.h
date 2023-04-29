#pragma once
#include <JuceHeader.h>

extern juce::Colour _mainBackgroundColor;
extern juce::Colour _mainTextColor;
extern juce::Colour _auxTextColor;
extern juce::Colour _widgetFillColor;
extern juce::Colour _auxBackgroundColor;
extern juce::Colour _blackBackgroundColor;

namespace ViatorParameters
{
    extern const juce::String band1ID;
    extern const juce::String band1Name;

    extern const juce::String band2ID;
    extern const juce::String band2Name;

    extern const juce::String band3ID;
    extern const juce::String band3Name;

    extern const juce::String band4ID;
    extern const juce::String band4Name;

    extern const juce::String band5ID;
    extern const juce::String band5Name;

    extern const juce::String band6ID;
    extern const juce::String band6Name;

    class Params
    {
    public:
        Params()
        {
            _ids.push_back(ViatorParameters::band1ID);
            _ids.push_back(ViatorParameters::band2ID);
            _ids.push_back(ViatorParameters::band3ID);
            _ids.push_back(ViatorParameters::band4ID);
            _ids.push_back(ViatorParameters::band5ID);
            _ids.push_back(ViatorParameters::band6ID);
        }
        std::vector<juce::String> getIDs() { return _ids;};
    private:
        std::vector<juce::String> _ids;
    };
}
