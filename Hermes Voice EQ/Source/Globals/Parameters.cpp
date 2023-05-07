#include "Parameters.h"

ViatorParameters::Params::Params()
{
    initParams();
}

std::vector<ViatorParameters::Parameter>& ViatorParameters::Params::getParams()
{
    return _params;
}

void ViatorParameters::Params::initParams()
{
    _params.push_back({ViatorParameters::band1ID, ViatorParameters::band1Name, 0, 100, 100, 0.3f});
    _params.push_back({ViatorParameters::band2ID, ViatorParameters::band2Name, -15.0, 15.0f, 0.0f, 0.6f});
    _params.push_back({ViatorParameters::band3ID, ViatorParameters::band3Name, -15.0, 15.0f, 0.0f, 0.6f});
    _params.push_back({ViatorParameters::band4ID, ViatorParameters::band4Name, -15.0, 15.0f, 0.0f, 0.6f});
    _params.push_back({ViatorParameters::band5ID, ViatorParameters::band5Name, -15.0f, 15.0f, 0.0f, 0.1f});
    _params.push_back({ViatorParameters::band6ID, ViatorParameters::band6Name, 0, 100, 100, 0.6f});
}
