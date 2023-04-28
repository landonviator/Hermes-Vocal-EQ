#include <JuceHeader.h>
#include "Fader.h"

//==============================================================================
Fader::Fader()
{
    // Slider props
    setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::ColourIds::backgroundColourId, _auxBackgroundColor);
    setColour(juce::Slider::ColourIds::textBoxTextColourId, _auxTextColor);
    setColour(juce::Slider::ColourIds::trackColourId, _widgetFillColor);
    setColour(juce::Slider::ColourIds::thumbColourId, _mainTextColor);
    setRange(-15.0, 15.0, 0.1);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 64, 32);
    setTextValueSuffix(" dB");
    setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    setDoubleClickReturnValue(true, 0.0);
    setLookAndFeel(&_customFaderLAF);
    
    // Shadow
    shadowProperties.radius = 10;
    shadowProperties.offset = juce::Point<int> (-1, 1);
    shadowProperties.colour = juce::Colours::black.withAlpha(0.25f);
    dialShadow.setShadowProperties (shadowProperties);
    setComponentEffect(&dialShadow);
}

Fader::~Fader()
{
}

void Fader::paint (juce::Graphics& g)
{
    juce::Slider::paint(g);
}

void Fader::resized()
{
    juce::Slider::resized();
}
