#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
    // Param data
    struct Parameter
    {
        public:
            juce::String _id;
            juce::String _name;
            float _min;
            float _max;
            float _initial;
            float _q;
    };

    class Params
    {
    public:
        Params();
        
        // Get a ref to the param data
        std::vector<ViatorParameters::Parameter>& getParams();
        
    private:
        // Vector holding param data
        std::vector<ViatorParameters::Parameter> _params;
        
        // Adds params to the vector
        void initParams();
    };
}
