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
    _sliderParams.push_back({ViatorParameters::band1ID, ViatorParameters::band1Name, 0, 100, 100, 0.3f});
    _sliderParams.push_back({ViatorParameters::band2ID, ViatorParameters::band2Name, -15.0, 15.0f, 0.0f, 0.6f});
    _sliderParams.push_back({ViatorParameters::band3ID, ViatorParameters::band3Name, -15.0, 15.0f, 0.0f, 0.6f});
    _sliderParams.push_back({ViatorParameters::band4ID, ViatorParameters::band4Name, -15.0, 15.0f, 0.0f, 0.6f});
    _sliderParams.push_back({ViatorParameters::band5ID, ViatorParameters::band5Name, -15.0f, 15.0f, 0.0f, 0.1f});
    _sliderParams.push_back({ViatorParameters::band6ID, ViatorParameters::band6Name, 0, 100, 100, 0.6f});
    _sliderParams.push_back({ViatorParameters::inputID, ViatorParameters::inputName, -30.0f, 30.0f, 0.0f, 0.0f});
    _sliderParams.push_back({ViatorParameters::outputID, ViatorParameters::outputName, -30.0f, 30.0f, 0.0f, 0.0f});
}

std::vector<ViatorParameters::ButtonParameterData>& ViatorParameters::Params::getButtonParams()
{
    return _buttonParams;
}

void ViatorParameters::Params::initButtonParams()
{
    _buttonParams.push_back({ViatorParameters::voiceMaleID, ViatorParameters::voiceMaleName, true});
    _buttonParams.push_back({ViatorParameters::voiceFemaleID, ViatorParameters::voiceFemaleName, false});
}
