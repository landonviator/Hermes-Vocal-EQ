#include "Parameters.h"

ViatorParameters::Params::Params()
{
    initSliderParams();
    initButtonParams();
}

std::vector<ViatorParameters::SliderParameterData>& ViatorParameters::Params::getSliderParams()
{
    return _sliderParams;
}

void ViatorParameters::Params::initSliderParams()
{
    _sliderParams.push_back({ViatorParameters::band1ID, ViatorParameters::band1Name, 0, 100, 0, 0.75f});
    _sliderParams.push_back({ViatorParameters::band2ID, ViatorParameters::band2Name, 0, 100, 0, 0.6f});
    _sliderParams.push_back({ViatorParameters::band3ID, ViatorParameters::band3Name, 0, 100, 0, 0.6f});
    _sliderParams.push_back({ViatorParameters::band4ID, ViatorParameters::band4Name, 0, 100, 0, 0.6f});
    _sliderParams.push_back({ViatorParameters::band5ID, ViatorParameters::band5Name, -10.0f, 10.0f, 0.0f, 0.4f});
    _sliderParams.push_back({ViatorParameters::band6ID, ViatorParameters::band6Name, 0, 100, 0, 0.7f});
    _sliderParams.push_back({ViatorParameters::inputID, ViatorParameters::inputName, -30.0f, 30.0f, 0.0f, 0.0f});
    _sliderParams.push_back({ViatorParameters::outputID, ViatorParameters::outputName, -30.0f, 30.0f, 0.0f, 0.0f});
}

std::vector<ViatorParameters::ButtonParameterData>& ViatorParameters::Params::getButtonParams()
{
    return _buttonParams;
}

void ViatorParameters::Params::initButtonParams()
{
    _buttonParams.push_back({ViatorParameters::voiceID, ViatorParameters::voiceName, true});
}
