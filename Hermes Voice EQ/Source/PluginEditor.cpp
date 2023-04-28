#include "PluginProcessor.h"
#include "PluginEditor.h"

HermesVoiceEQAudioProcessorEditor::HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Window sizing
    setWindowSizeLogic();
    
    // Init Dials
    for (auto& dial : _dials)
    {
        initDialProps(*dial);
    }
    
    // Init Labels
    for (auto i = 0; i < _dialLabels.size(); i++)
    {
        initLabelProps(*_dialLabels[i], i);
    }
    
    addAndMakeVisible(_headerComp);
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
    
    _headerComp.setBounds(0, 0, getWidth(), getHeight() * 0.12);
    
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

void HermesVoiceEQAudioProcessorEditor::initDialProps(Fader &dial)
{
    addAndMakeVisible(dial);
}

void HermesVoiceEQAudioProcessorEditor::initLabelProps(juce::Label &label, int index)
{
    label.setColour(juce::Label::ColourIds::textColourId, _auxTextColor);
    label.setText(*_labelNames[index], juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(_dials[index], false);
    addAndMakeVisible(label);
}
