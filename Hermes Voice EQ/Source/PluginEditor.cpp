#include "PluginProcessor.h"
#include "PluginEditor.h"

HermesVoiceEQAudioProcessorEditor::HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setName("Editor");
    
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
    initTooltipLabel();
    
    
    // Settings
    addAndMakeVisible(_settingsPage);
    _settingsPage.addChangeListener(this);
    setSettingsState(_headerComp.isSettingsActive());
    updateSliderColors();
    updateLabelColors();
    
    //  Header
    addAndMakeVisible(_headerComp);
}

HermesVoiceEQAudioProcessorEditor::~HermesVoiceEQAudioProcessorEditor()
{
}

void HermesVoiceEQAudioProcessorEditor::paint (juce::Graphics& g)
{
    updateSliderColors();
    updateLabelColors();
    juce::Colour bgColor = _theme.getMainBackgroundColor();
////    g.setGradientFill(juce::ColourGradient::vertical(bgColor.brighter(0.05),
////                                                     getHeight() * 0.1,
////                                                     bgColor.darker(0.25),
////                                                     getHeight() * 0.9));
////    g.fillRect(getLocalBounds());
    juce::Rectangle<int> rect = getLocalBounds();
    juce::Point<float> center = rect.getCentre().toFloat();
    juce::ColourGradient gradient(bgColor.brighter(0.02f), center.x, center.y, bgColor.darker(0.5f), rect.getRight(), rect.getBottom(), true);

    g.setGradientFill(gradient);
    g.fillRect(rect);
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
    _settingsPage.setBounds(getWidth() * 0.66, _headerComp.getBottom() + 10, getWidth() * 0.34 - 10, getHeight() - _headerComp.getHeight() - 20);
    
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
    
    // tooltip label
    auto labelHeight = getHeight() - _band1Dial.getBottom();
    _tooltipLabel.setBounds(0, _band1Dial.getBottom(), getWidth(), labelHeight);
    _tooltipLabel.setFont(juce::Font("Helvetica", labelHeight * 0.6, juce::Font::FontStyleFlags::bold));
    
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
void HermesVoiceEQAudioProcessorEditor::initDialProps(viator_gui::Fader &dial, int index)
{
    _band1Dial.setTextValueSuffix(" %");
    _band6Dial.setTextValueSuffix(" %");
    _sliderAttachments.add(std::make_unique<sliderAttachment>(audioProcessor._treeState, audioProcessor._paramList.getParams()[index]._id, dial));
    _band1Dial.setTooltip("Rumble filter. This is a highpass filter with a range of 20Hz to 100Hz. The slider at the lowest position allows all low (rumble-y) to pass through and vice versa. Push the slider up if you have a lot of low frequency noise.");
    addAndMakeVisible(dial);
}

void HermesVoiceEQAudioProcessorEditor::updateSliderColors()
{
    for (auto& dial : _dials)
    {
        dial->setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        dial->setColour(juce::Slider::ColourIds::backgroundColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        dial->setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        dial->setColour(juce::Slider::ColourIds::textBoxTextColourId, _theme.getMainTextColor());
        dial->setColour(juce::Slider::ColourIds::trackColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        dial->setColour(juce::Slider::ColourIds::rotarySliderFillColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        dial->setColour(juce::Slider::ColourIds::thumbColourId, _theme.getAuxTextColor());
        dial->addMouseListener(this, false);
    }
}

#pragma mark Labels
void HermesVoiceEQAudioProcessorEditor::initLabelProps(juce::Label &label, int index)
{
    label.setColour(juce::Label::ColourIds::textColourId, _theme.getMainTextColor());
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

void HermesVoiceEQAudioProcessorEditor::updateLabelColors()
{
    for (auto& label : _dialLabels)
    {
        label->setColour(juce::Label::ColourIds::textColourId, _theme.getMainTextColor());
    }
}

void HermesVoiceEQAudioProcessorEditor::initTooltipLabel()
{
    _tooltipLabel.setText("", juce::dontSendNotification);
    _tooltipLabel.setJustificationType(juce::Justification::centred);
    _tooltipLabel.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    _tooltipLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::whitesmoke.withAlpha(0.25f));
    addAndMakeVisible(_tooltipLabel);
}

#pragma mark Settings
void HermesVoiceEQAudioProcessorEditor::setSettingsState(bool isActive)
{
    _settingsPage.setVisible(isActive);
    _settingsPage.setEnabled(isActive);
}

#pragma mark Tooltips
void HermesVoiceEQAudioProcessorEditor::mouseEnter(const juce::MouseEvent &event)
{
    //sliders
    for (int i = 0; i < _dials.size(); ++i)
    {
        if (event.eventComponent == _dials[i])
        {
            _tooltipLabel.setText(_sliderTooltips[i], juce::dontSendNotification);
        }
    }
}

void HermesVoiceEQAudioProcessorEditor::mouseExit(const juce::MouseEvent &event)
{
    //sliders
    for (int i = 0; i < _dials.size(); ++i)
    {
        if (event.eventComponent == _dials[i])
        {
            _tooltipLabel.setText("", juce::dontSendNotification);
        }
    }
}

void HermesVoiceEQAudioProcessorEditor::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (_settingsPage.getIsHighContrast())
    {
        _theme.setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kHighContrast);
    }
    
    else
    {
        _settingsPage.resetToNonContrast();
    }
    
    repaint();
}
