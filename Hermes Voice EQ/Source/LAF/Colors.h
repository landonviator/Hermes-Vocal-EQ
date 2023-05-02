#pragma once
#include <JuceHeader.h>

namespace ViatorThemes
{
    class ViatorThemeData
    {
    public:
        ViatorThemeData();
        
        juce::Colour getMainBackgroundColor();
        juce::Colour getMainTextColor();
        juce::Colour getWidgetFillColor();
        juce::Colour getAuxBackgroundColor();
        juce::Colour getAuxTextColor();
        juce::Colour getBlackBackgroundColor();
        
        enum class Theme
        {
            kPrimeDark,
            kPrimeLight,
            kRetro,
            kLofi,
            kVaporWave
        };
        void setCurrentTheme(Theme newTheme);
        
    private:
        
        
        // Theme
        Theme _currentTheme = Theme::kPrimeDark;
        
        // Colors
        juce::Colour _mainBackgroundColor = juce::Colour::fromRGB(40, 42, 54);
        juce::Colour _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
        juce::Colour _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
        juce::Colour _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
        juce::Colour _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
        juce::Colour _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
    };
}
