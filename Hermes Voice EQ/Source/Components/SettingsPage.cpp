#include <JuceHeader.h>
#include "SettingsPage.h"
#include "../PluginEditor.h"

SettingsPage::SettingsPage()
{
    // Labels
    initThemeLabelProps();
    
    // Menus
    initThemeMenuProps();
}

SettingsPage::~SettingsPage()
{
}

void SettingsPage::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black.brighter(0.1));
    g.fillAll();
}

void SettingsPage::resized()
{
    auto leftMargin = getWidth() * 0.1;
    auto topMargin = getHeight() * 0.1;
    auto labelWidth = getWidth() * 0.25;
    auto labelHeight = labelWidth * 0.5;
    _themeLabel.setBounds(leftMargin, topMargin, labelWidth, labelHeight);
    
    auto menuWidth = labelWidth * 2.0;
    auto padding = labelHeight * 0.5;
    _themeMenu.setBounds(_themeLabel.getRight() + padding, topMargin, menuWidth, labelHeight);
}

void SettingsPage::initThemeLabelProps()
{
    _themeLabel.setText("Color Theme", juce::dontSendNotification);
    _themeLabel.setJustificationType(juce::Justification::centred);
    _themeLabel.setFont(juce::Font("Helvetica", 12.0f, juce::Font::FontStyleFlags::bold));
    _themeLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::transparentBlack);
    _themeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colour::fromRGB(155, 165, 175));
    addAndMakeVisible(_themeLabel);
}

void SettingsPage::initThemeMenuProps()
{
    _themeMenu.addItem("Prime Dark", 1);
    _themeMenu.addItem("Prime Light", 2);
    _themeMenu.addItem("Lofi", 3);
    _themeMenu.addItem("Retro", 4);
    _themeMenu.addItem("Vapor Wave", 5);
    addAndMakeVisible(_themeMenu);
    
    _themeMenu.onChange = [this]()
    {
        auto* parent = dynamic_cast<HermesVoiceEQAudioProcessorEditor*>(getParentComponent());
        
        if (parent == nullptr)
            return;
        
        switch (_themeMenu.getSelectedId())
        {
            case 1:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kPrimeDark);
                break;
            }
                
            case 2:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kPrimeLight);
                break;
            }
                
            case 3:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kLofi);
                break;
            }
                
            case 4:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kRetro);
                break;
            }
                
            case 5:
            {
                parent->getThemeData().setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kVaporWave);
                break;
            }
        }
        
        getParentComponent()->repaint();
    };
    
    _themeMenu.setSelectedId(1);
}
