#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Globals/Globals.h"
#include "Components/Header.h"
#include "Components/SettingsPage.h"
#include "LAF/Colors.h"

class HermesVoiceEQAudioProcessorEditor  : public juce::AudioProcessorEditor
, public juce::ChangeListener
{
public:
    HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor&);
    ~HermesVoiceEQAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    ViatorThemes::ViatorThemeData& getThemeData()
    {
            return _theme;
    }
    
// objects
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HermesVoiceEQAudioProcessor& audioProcessor;
    
    // theme
    ViatorThemes::ViatorThemeData _theme;
    
    // faders
    viator_gui::Fader _band1Dial;
    viator_gui::Fader _band2Dial;
    viator_gui::Fader _band3Dial;
    viator_gui::Fader _band4Dial;
    viator_gui::Fader _band5Dial;
    viator_gui::Fader _band6Dial;
    std::vector<viator_gui::Fader*> _faders =
    {
        &_band1Dial, &_band2Dial, &_band3Dial,
        &_band4Dial, &_band5Dial, &_band6Dial
    };
    
    // dials
    viator_gui::Dial _inputDial;
    viator_gui::Dial _outputDial;
    std::vector<viator_gui::Dial*> _dials =
    {
        &_inputDial, &_outputDial
    };
    
    // header
    Header _headerComp;
    
    // labels
    juce::Label _band1DialLabel;
    juce::Label _band2DialLabel;
    juce::Label _band3DialLabel;
    juce::Label _band4DialLabel;
    juce::Label _band5DialLabel;
    juce::Label _band6DialLabel;
    std::vector<juce::Label*> _faderLabels =
    {
        &_band1DialLabel, &_band2DialLabel, &_band3DialLabel,
        &_band4DialLabel, &_band5DialLabel, &_band6DialLabel
    };
    
    juce::Label _tooltipLabel;
    
    // label texts
    juce::String _band1DialLabelText = "Rumble";
    juce::String _band2DialLabelText = "Depth";
    juce::String _band3DialLabelText = "Hollow";
    juce::String _band4DialLabelText = "Nasal";
    juce::String _band5DialLabelText = "Sparkle";
    juce::String _band6DialLabelText = "Noise";
    std::vector<juce::String*> _faderLabelNames =
    {
        &_band1DialLabelText, &_band2DialLabelText, &_band3DialLabelText,
        &_band4DialLabelText, &_band5DialLabelText, &_band6DialLabelText
    };
    
    juce::Label _inputDialLabel;
    juce::Label _outputDialLabel;
    std::vector<juce::Label*> _dialLabels =
    {
        &_inputDialLabel, &_outputDialLabel
    };
    
    juce::String _inputDialLabelText = "Input";
    juce::String _outputDialLabelText = "Output";
    std::vector<juce::String*> _dialLabelNames =
    {
        &_inputDialLabelText, &_outputDialLabelText
    };
    
    // Settings
    SettingsPage _settingsPage;
    juce::Label _settingsOverlay;
    
    // dial attachments
    using sliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    juce::OwnedArray<sliderAttachment> _sliderAttachments;
    std::unique_ptr<sliderAttachment> _band1Attach;
    std::unique_ptr<sliderAttachment> _band2Attach;
    std::unique_ptr<sliderAttachment> _band3Attach;
    std::unique_ptr<sliderAttachment> _band4Attach;
    std::unique_ptr<sliderAttachment> _band5Attach;
    std::unique_ptr<sliderAttachment> _band6Attach;
    std::unique_ptr<sliderAttachment> _inputAttach;
    std::unique_ptr<sliderAttachment> _outputAttach;
    
// methods
private:
    // window
    void setWindowSizeLogic();
    
    // sliders
    void initFaderProps(viator_gui::Fader& fader, int index);
    void initDialProps(viator_gui::Dial& dial, int index);
    void updateSliderColors();
    
    // labels
    void initFaderLabelProps(juce::Label& label, int index);
    void initDialLabelProps(juce::Label& label, int index);
    void updateLabelColors();
    void initTooltipLabel();
    
    // settings
    void setSettingsState(bool isActive);
    void initOverlayProps();
    
    // mouse events
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    
    // change listener
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

// vars
private:
    juce::String _band1ToolTip =
    {
        "Represents the amount of reduction for rumbling frequencies. Increase to eliminate sub noise."
    };
    
    juce::String _band2ToolTip =
    {
        "Represents the amount of added deep bass frequencies. Increase for deep radio vocals."
    };
    
    juce::String _band3ToolTip =
    {
        "Represents the amount of reduction for hollow or boxy frequencies. Increase to fix poor microphone quality."
    };
    
    juce::String _band4ToolTip =
    {
        "Represents the amount of reduction for nasal-like frequencies. Increase to open up the voice."
    };
    
    juce::String _band5ToolTip =
    {
        "Represents the amount of added or reduced treble frequenices. Increase for a nice shine or reduce to eliminate harshness."
    };
    
    juce::String _band6ToolTip =
    {
        "Represents the amount of reduction for noisey, sibilance-causing frequencies. Increase to reduce sibilance or noise."
    };
    
    std::vector<juce::String> _faderTooltips =
    {
        _band1ToolTip, _band2ToolTip, _band3ToolTip, _band4ToolTip, _band5ToolTip, _band6ToolTip
    };
    
    juce::String _inputToolTip =
    {
        "The volume of the signal going into the plugin."
    };
    
    juce::String _outputToolTip =
    {
        "The volume of the signal coming out of the plugin."
    };
    
    std::vector<juce::String> _dialTooltips =
    {
        _inputToolTip, _outputToolTip
    };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesVoiceEQAudioProcessorEditor)
};
