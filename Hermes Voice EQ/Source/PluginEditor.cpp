#include "PluginProcessor.h"
#include "PluginEditor.h"

HermesVoiceEQAudioProcessorEditor::HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Window sizing
    setWindowSizeLogic();
    
    auto dialIndex = 0;
    
    // Init Dials
    for (auto& dial : _dials)
    {
        initDialProps(*dial, dialIndex);
        dialIndex++;
    }
    
    // Init Labels
    for (auto i = 0; i < _dialLabels.size(); i++)
    {
        initLabelProps(*_dialLabels[i], i);
    }
    
    // Header
    addAndMakeVisible(_headerComp);
    
    // Settings
    addAndMakeVisible(_settingsPage);
    setSettingsState(_headerComp.isSettingsActive());
}

HermesVoiceEQAudioProcessorEditor::~HermesVoiceEQAudioProcessorEditor()
{
}

void HermesVoiceEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(_mainBackgroundColor);
    g.fillAll ();
}

void HermesVoiceEQAudioProcessorEditor::resized()
{
    auto topMargin = getHeight() * 0.25;
    auto dialWidth = getWidth() * 0.14;
    auto dialHeight = getHeight() * 0.7;
    auto leftMargin = getWidth() * 0.05;
    
    // Header
    _headerComp.setBounds(0, 0, getWidth(), getHeight() * 0.12);
    
    // Settings
    setSettingsState(_headerComp.isSettingsActive());
    _settingsPage.setBounds(getWidth() * 0.66, _headerComp.getBottom(), getWidth() * 0.34, getHeight() - _headerComp.getHeight());
    
    // Sliders
    for (int i = 0; i < _dials.size(); i++)
    {
        if (i == 0)
        {
            _dials[i]->setBounds(leftMargin, topMargin, dialWidth, dialHeight);
        }
        
        else
        {
            _dials[i]->setBounds(_dials[i - 1]->getRight(), topMargin, dialWidth, dialHeight);
        }
    }
    
    // Label font
    for (auto i = 0; i < _dialLabels.size(); i++)
    {
        _dialLabels[i]->setFont(juce::Font("Helvetica", dialWidth * 0.1, juce::Font::FontStyleFlags::bold));
    }
}

#pragma mark Window
void HermesVoiceEQAudioProcessorEditor::setWindowSizeLogic()
{
    // Grab the window instance and create a rectangle
    juce::Rectangle<int> r = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;

    // Using the width is more useful than the height, because we know the height will always be < than width
    float width;
    
    if (r.getWidth() > 2560.0f)
    {
        width = r.getWidth() * 0.3f;
    }
    
    else if (r.getWidth() > 1920.0f)
    {
        width = r.getWidth() * 0.5f;
    }
    
    else if (r.getWidth() > 1440.0f)
    {
        width = r.getWidth() * 0.65f;
    }
    
    else
    {
        width = r.getWidth() * 0.8f;
    }
    
    float height = width * 0.5f;

    // Set the size
    setSize (width, height);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(2.0);
    setResizeLimits(width * 0.5, height * 0.5, width * 1.25, height * 1.25);
}

#pragma mark Dials
void HermesVoiceEQAudioProcessorEditor::initDialProps(Fader &dial, int index)
{
    _sliderAttachments.add(std::make_unique<sliderAttachment>(audioProcessor._treeState, audioProcessor._paramList.getParams()[index]._id, dial));
    addAndMakeVisible(dial);
}

#pragma mark Labels
void HermesVoiceEQAudioProcessorEditor::initLabelProps(juce::Label &label, int index)
{
    label.setColour(juce::Label::ColourIds::textColourId, _auxTextColor);
    label.setText(*_labelNames[index], juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(_dials[index], false);
    addAndMakeVisible(label);
}

void HermesVoiceEQAudioProcessorEditor::initOverlayProps()
{
    _settingsOverlay.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::black.withAlpha(0.25f));
    addAndMakeVisible(_settingsOverlay);
}

#pragma mark Settings
void HermesVoiceEQAudioProcessorEditor::setSettingsState(bool isActive)
{
    _settingsPage.setVisible(isActive);
    _settingsPage.setEnabled(isActive);
}
