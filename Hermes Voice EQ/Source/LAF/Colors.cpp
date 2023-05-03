#include "Colors.h"
namespace ViatorThemes
{
    ViatorThemes::ViatorThemeData::ViatorThemeData()
    {
    }

    void ViatorThemes::ViatorThemeData::setCurrentTheme(Theme newTheme)
    {
        switch (newTheme)
        {
            case Theme::kPrimeDark:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(33, 37, 43);
                _mainTextColor = juce::Colour::fromRGB(87, 154, 208);
                _widgetFillColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
                _auxBackgroundColor = _mainBackgroundColor.darker(0.25f);
                _auxTextColor = juce::Colour::fromRGB(74, 81, 98);
                _blackBackgroundColor = juce::Colour::fromRGB(33, 35, 37);
                break;
            }
                
            case Theme::kPrimeLight:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(140, 142, 154);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
                _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
                _auxBackgroundColor = juce::Colour::fromRGB(124, 125, 126);
                _auxTextColor = juce::Colour::fromRGB(184, 196, 146);
                _blackBackgroundColor = juce::Colour::fromRGB(118, 119, 120);
                break;
            }
                
            case Theme::kRetro:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(40, 42, 54);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
                _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
                _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
                _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
                break;
            }
                
            case Theme::kLofi:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(40, 42, 54);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
                _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
                _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
                _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
                break;
            }
                
            case Theme::kVaporWave:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(40, 42, 54);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
                _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
                _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
                _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
            }
        }
    }

    juce::Colour ViatorThemes::ViatorThemeData::getMainBackgroundColor()
    {
        return _mainBackgroundColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getMainTextColor()
    {
        return _mainTextColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getWidgetFillColor()
    {
        return _widgetFillColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getAuxBackgroundColor()
    {
        return _auxBackgroundColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getAuxTextColor()
    {
        return _auxTextColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getBlackBackgroundColor()
    {
        return _blackBackgroundColor;
    }
}
