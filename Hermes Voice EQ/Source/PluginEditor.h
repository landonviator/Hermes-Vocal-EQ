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
    
#pragma mark Objects
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    HermesVoiceEQAudioProcessor& audioProcessor;
    
    // theme
    ViatorThemes::ViatorThemeData _theme;
    
    // dials
    viator_gui::Fader _band1Dial;
    viator_gui::Fader _band2Dial;
    viator_gui::Fader _band3Dial;
    viator_gui::Fader _band4Dial;
    viator_gui::Fader _band5Dial;
    viator_gui::Fader _band6Dial;
    std::vector<viator_gui::Fader*> _dials =
    {
        &_band1Dial, &_band2Dial, &_band3Dial,
        &_band4Dial, &_band5Dial, &_band6Dial
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
    std::vector<juce::Label*> _dialLabels =
    {
        &_band1DialLabel, &_band2DialLabel, &_band3DialLabel,
        &_band4DialLabel, &_band5DialLabel, &_band6DialLabel
    };
    
    juce::Label _tooltipLabel;
    
    // label texts
    juce::String _band1DialLabelText = "Rumble";
    juce::String _band2DialLabelText = "Mud";
    juce::String _band3DialLabelText = "Muffle";
    juce::String _band4DialLabelText = "Clarity";
    juce::String _band5DialLabelText = "Air";
    juce::String _band6DialLabelText = "Noise";
    std::vector<juce::String*> _labelNames =
    {
        &_band1DialLabelText, &_band2DialLabelText, &_band3DialLabelText,
        &_band4DialLabelText, &_band5DialLabelText, &_band6DialLabelText
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
    
#pragma mark Methods
private:
    // window
    void setWindowSizeLogic();
    
    // dials
    void initDialProps(viator_gui::Fader& dial, int index);
    void updateSliderColors();
    
    // labels
    void initLabelProps(juce::Label& label, int index);
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

    
#pragma mark Vars
private:
    juce::String driveToolTip =
    {
        "This knob drives the input harder into the exciter circuit, which makes mid and upper range harmonic distortion. \nIncreasing the drive also boosts a hard-coded low-shelf EQ to compensate for perceived low-end loss."
    };
    
    juce::String rangeToolTip =
    {
        "This knob sets the cutoff of frequencies affected by the harmonic distortion. Any frequencies above this cutoff are affected by harmonic distortion."
    };
    
    juce::String lowpassToolTip =
    {
        "This dial sets the cutoff for a lowpass (high cut) filter."
    };
    
    juce::String trimToolTip =
    {
        "A volume control for the wet signal only."
    };
    
    juce::String outToolTip =
    {
        "A master output volume control for the entire plugin's output."
    };
    
    juce::String mixToolTip =
    {
        "The Mix fader mixes the uneffected input from the DAW with the effected processing from the plugin."
    };
    
    std::vector<juce::String> _sliderTooltips =
    {
        driveToolTip, rangeToolTip, lowpassToolTip, trimToolTip, outToolTip, mixToolTip
    };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HermesVoiceEQAudioProcessorEditor)
};
