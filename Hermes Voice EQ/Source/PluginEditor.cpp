#include "PluginProcessor.h"
#include "PluginEditor.h"

HermesVoiceEQAudioProcessorEditor::HermesVoiceEQAudioProcessorEditor (HermesVoiceEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), _headerComp(audioProcessor)
{
    setName("Editor");
    
    // Window sizing
    setWindowSizeLogic();
    
    auto faderIndex = 0;

    // Init sliders
    for (auto& fader : _faders)
    {
        initFaderProps(*fader, faderIndex);
        faderIndex++;
    }
    
    auto dialIndex = 0;
    
    for (auto& dial : _dials)
    {
        initDialProps(*dial, dialIndex);
        dialIndex++;
    }
    
    _sliderAttachments.add(std::make_unique<sliderAttachment>(audioProcessor._treeState, ViatorParameters::inputID, _inputDial));
    _sliderAttachments.add(std::make_unique<sliderAttachment>(audioProcessor._treeState, ViatorParameters::outputID, _outputDial));
    
    // Init Labels
    for (auto i = 0; i < _faderLabels.size(); i++)
    {
        initFaderLabelProps(*_faderLabels[i], i);
    }
    
    for (auto i = 0; i < _dialLabels.size(); i++)
    {
        initDialLabelProps(*_dialLabels[i], i);
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
    juce::Rectangle<int> rect = getLocalBounds();
    juce::Point<float> center = rect.getCentre().toFloat();
    juce::ColourGradient gradient(bgColor.brighter(0.02f), center.x, center.y, bgColor.darker(0.5f), rect.getRight(), rect.getBottom(), true);

    g.setGradientFill(gradient);
    g.fillRect(rect);
    
    auto isContrast = _settingsPage.getIsHighContrast();
    _tooltipLabel.setColour(juce::Label::ColourIds::textColourId,  isContrast ? _theme.getWidgetFillColor() : juce::Colours::whitesmoke.withAlpha(0.25f));
    
    g.setColour(juce::Colours::whitesmoke.withAlpha(0.05f));
    g.drawLine(_band6Dial.getRight(), _headerComp.getBottom() * 2.0, _band6Dial.getRight(), getHeight() - _headerComp.getBottom(), 1.0f);
}

void HermesVoiceEQAudioProcessorEditor::resized()
{
    auto topMargin = getHeight() * 0.25;
    auto faderWidth = getWidth() * 0.13;
    auto faderHeight = getHeight() * 0.7;
    auto leftMargin = juce::jmax(5.0f, getWidth() * 0.01f);
    
    // Header
    _headerComp.setBounds(0, 0, getWidth(), getHeight() * 0.12);
    
    // Settings
    setSettingsState(_headerComp.isSettingsActive());
    _settingsPage.setBounds(getWidth() * 0.66, _headerComp.getBottom() + 10, getWidth() * 0.34 - 10, getHeight() - _headerComp.getHeight() - 20);
    
    // Sliders
    for (int i = 0; i < _faders.size(); i++)
    {
        if (i == 0)
        {
            _faders[i]->setBounds(leftMargin, topMargin, faderWidth, faderHeight);
        }
        
        else
        {
            _faders[i]->setBounds(_faders[i - 1]->getRight(), topMargin, faderWidth, faderHeight);
        }
    }
    
    auto spaceBetween = faderWidth * 0.4;
    auto dialWidth = (getWidth() - _band6Dial.getRight()) * 0.75;
    _inputDial.setBounds(getWidth() - dialWidth * 1.125, _headerComp.getBottom() * 1.8, dialWidth, dialWidth);
    _outputDial.setBounds(_inputDial.getX(), _inputDial.getBottom() + spaceBetween, dialWidth, dialWidth);
    
    // tooltip label
    auto labelHeight = getHeight() - _band1Dial.getBottom();
    _tooltipLabel.setBounds(0, _band1Dial.getBottom(), getWidth(), labelHeight);
    _tooltipLabel.setFont(juce::Font("Helvetica", labelHeight * 0.6, juce::Font::FontStyleFlags::bold));
    
    // Label font
    for (auto i = 0; i < _faderLabels.size(); i++)
    {
        _faderLabels[i]->setFont(juce::Font("Helvetica", faderWidth * 0.1, juce::Font::FontStyleFlags::bold));
    }
    
    for (auto i = 0; i < _dialLabels.size(); i++)
    {
        _dialLabels[i]->setFont(juce::Font("Helvetica", faderWidth * 0.1, juce::Font::FontStyleFlags::bold));
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
    setResizeLimits(width * 0.75, height * 0.75, width * 1.25, height * 1.25);
}

#pragma mark Sliders
void HermesVoiceEQAudioProcessorEditor::initFaderProps(viator_gui::Fader &fader, int index)
{
    _band1Dial.setTextValueSuffix(" %");
    _band6Dial.setTextValueSuffix(" %");
    _sliderAttachments.add(std::make_unique<sliderAttachment>(audioProcessor._treeState, audioProcessor._parameterMap.getSliderParams()[index]._id, fader));
    fader.setComponentID("fader" + juce::String(index));
    fader.addMouseListener(this, false);
    addAndMakeVisible(fader);
}

void HermesVoiceEQAudioProcessorEditor::initDialProps(viator_gui::Dial &dial, int index)
{
    dial.setComponentID("fader" + juce::String(index));
    dial.addMouseListener(this, false);
    addAndMakeVisible(dial);
}

void HermesVoiceEQAudioProcessorEditor::updateSliderColors()
{
    for (auto& fader : _faders)
    {
        fader->setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        fader->setColour(juce::Slider::ColourIds::backgroundColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        fader->setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        fader->setColour(juce::Slider::ColourIds::textBoxTextColourId, _theme.getMainTextColor());
        fader->setColour(juce::Slider::ColourIds::trackColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        fader->setColour(juce::Slider::ColourIds::rotarySliderFillColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        fader->setColour(juce::Slider::ColourIds::thumbColourId, _theme.getAuxTextColor());
    }
    
    for (auto& dial : _dials)
    {
        dial->setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        dial->setColour(juce::Slider::ColourIds::backgroundColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        dial->setColour(juce::Slider::ColourIds::rotarySliderOutlineColourId, _theme.getAuxBackgroundColor().withAlpha(0.35f));
        dial->setColour(juce::Slider::ColourIds::textBoxTextColourId, _theme.getMainTextColor());
        dial->setColour(juce::Slider::ColourIds::trackColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        dial->setColour(juce::Slider::ColourIds::rotarySliderFillColourId, _theme.getWidgetFillColor().withAlpha(0.75f));
        dial->setColour(juce::Slider::ColourIds::thumbColourId, _theme.getAuxTextColor());
    }
}

#pragma mark Labels
void HermesVoiceEQAudioProcessorEditor::initFaderLabelProps(juce::Label &label, int index)
{
    label.setColour(juce::Label::ColourIds::textColourId, _theme.getMainTextColor());
    label.setText(*_faderLabelNames[index], juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(_faders[index], false);
    addAndMakeVisible(label);
}

void HermesVoiceEQAudioProcessorEditor::initDialLabelProps(juce::Label &label, int index)
{
    label.setColour(juce::Label::ColourIds::textColourId, _theme.getMainTextColor());
    label.setText(*_dialLabelNames[index], juce::dontSendNotification);
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
    for (auto& label : _faderLabels)
    {
        label->setColour(juce::Label::ColourIds::textColourId, _theme.getMainTextColor());
    }
    
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
    // faders
    for (int i = 0; i < _faders.size(); ++i)
    {
        if (event.eventComponent == _faders[i])
        {
            _tooltipLabel.setText(_faderTooltips[i], juce::dontSendNotification);
        }
    }
    
    // dials
    for (int i = 0; i < _dials.size(); ++i)
    {
        if (event.eventComponent == _dials[i])
        {
            _tooltipLabel.setText(_dialTooltips[i], juce::dontSendNotification);
        }
    }
}

void HermesVoiceEQAudioProcessorEditor::mouseExit(const juce::MouseEvent &event)
{
    // faders
    for (int i = 0; i < _faders.size(); ++i)
    {
        if (event.eventComponent == _faders[i])
        {
            _tooltipLabel.setText("", juce::dontSendNotification);
        }
    }
    
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
    // high contrast
    if (_settingsPage.getIsHighContrast())
    {
        _theme.setCurrentTheme(ViatorThemes::ViatorThemeData::Theme::kHighContrast);
    }
    
    else
    {
        _settingsPage.resetToNonContrast();
    }
    
    // tooltips
    _headerComp.enableToolTips(_settingsPage.getShouldUseTooltips());
    _tooltipLabel.setVisible(_settingsPage.getShouldUseTooltips());
    
    repaint();
}
