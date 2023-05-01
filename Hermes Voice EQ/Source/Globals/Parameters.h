#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
    struct Parameter
    {
        public:
            juce::String _id;
            juce::String _name;
            float _min;
            float _max;
            float _initial;
    };

    class Params
    {
    public:
        Params()
        {
            _params.push_back({ViatorParameters::band1ID, ViatorParameters::band1Name, -15.0, 15.0, 0.0f});
            _params.push_back({ViatorParameters::band2ID, ViatorParameters::band2Name, -15.0, 15.0f, 0.0f});
            _params.push_back({ViatorParameters::band3ID, ViatorParameters::band3Name, -15.0, 15.0f, 0.0f});
            _params.push_back({ViatorParameters::band4ID, ViatorParameters::band4Name, -15.0, 15.0f, 0.0f});
            _params.push_back({ViatorParameters::band5ID, ViatorParameters::band5Name, -15.0, 15.0f, 0.0f});
            _params.push_back({ViatorParameters::band6ID, ViatorParameters::band6Name, -15.0, 15.0, 0.0f});
        }
        
        std::vector<ViatorParameters::Parameter> getParams() { return _params;};
    private:
        std::vector<ViatorParameters::Parameter> _params;
    };
}
