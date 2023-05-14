#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
// Param data
struct SliderParameterData
{
    public:
        juce::String _id;
        juce::String _name;
        float _min;
        float _max;
        float _initial;
        float _q;
};

struct ButtonParameterData
{
    public:
        juce::String _id;
        juce::String _name;
        bool _initial;
};

    class Params
    {
    public:
        Params();
        
        // Get a ref to the param data
        std::vector<ViatorParameters::SliderParameterData>& getSliderParams();
        std::vector<ViatorParameters::ButtonParameterData>& getButtonParams();
        
    private:
        // Adds params to the vector
        void initSliderParams();
        void initButtonParams();
        
        
    private:
        // Vector holding param data
        std::vector<ViatorParameters::SliderParameterData> _sliderParams;
        std::vector<ViatorParameters::ButtonParameterData> _buttonParams;
    };
}
