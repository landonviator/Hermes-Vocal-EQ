#include "PluginProcessor.h"
#include "PluginEditor.h"

HermesVoiceEQAudioProcessor::HermesVoiceEQAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
, _treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getSliderParams()[i]._id, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getButtonParams()[i]._id, this);
    }
}

HermesVoiceEQAudioProcessor::~HermesVoiceEQAudioProcessor()
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getSliderParams()[i]._id, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getButtonParams()[i]._id, this);
    }
}

//==============================================================================
const juce::String HermesVoiceEQAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HermesVoiceEQAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HermesVoiceEQAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HermesVoiceEQAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HermesVoiceEQAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HermesVoiceEQAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HermesVoiceEQAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HermesVoiceEQAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HermesVoiceEQAudioProcessor::getProgramName (int index)
{
    return {};
}

void HermesVoiceEQAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout HermesVoiceEQAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        //auto param = _parameterMap.getSliderParams()[i];
        //params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { param._id, 1 }, param._name, param._min, param._max, param._initial));
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        //auto param = _parameterMap.getButtonParams()[i];
        //auto male = ViatorParameters::voiceID;
        //params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { param._id, 1 }, param._name, param._id == male ? true : false));
    }
        
    return { params.begin(), params.end() };
}

void HermesVoiceEQAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)

{
}

void HermesVoiceEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _spec.sampleRate = sampleRate;
    _spec.maximumBlockSize = samplesPerBlock;
    _spec.numChannels = getTotalNumInputChannels();
    
    //prepareModules(_spec);
    updateFilters();
    _inputGainModule.setRampDurationSeconds(0.02);
    _outputGainModule.setRampDurationSeconds(0.02);
    updateParameters();
    
}

void HermesVoiceEQAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HermesVoiceEQAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HermesVoiceEQAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    updateFilters();
    updateParameters();
    
    // Update block size
    if (_spec.maximumBlockSize != buffer.getNumSamples())
    {
        _spec.maximumBlockSize = buffer.getNumSamples();
        prepareModules(_spec);
    }
    
    // Update samplerate
    if (_spec.sampleRate != getSampleRate())
    {
        _spec.sampleRate = getSampleRate();
        prepareModules(_spec);
    }
    
    // Process the filters
    juce::dsp::AudioBlock<float> mainBlock {buffer};
    _inputGainModule.process(juce::dsp::ProcessContextReplacing<float>(mainBlock));
    _filterBankModule.process(juce::dsp::ProcessContextReplacing<float>(mainBlock));
    _outputGainModule.process(juce::dsp::ProcessContextReplacing<float>(mainBlock));
}

void HermesVoiceEQAudioProcessor::prepareModules(juce::dsp::ProcessSpec &spec)
{
    _inputGainModule.prepare(spec);
    _filterBankModule.prepare(spec);
    _outputGainModule.prepare(spec);
}

void HermesVoiceEQAudioProcessor::updateFilters()
{
    // update filter voice
    const auto voiceID = _treeState.getRawParameterValue(ViatorParameters::voiceID)->load();
    _filterBankModule.setVoice(voiceID ? FilterBank<float>::Voice::kMale : FilterBank<float>::Voice::kFemale);
    
    // update filter gains and Q's
    const auto& sliderParams = _parameterMap.getSliderParams();
    for (int i = 0; i < sliderParams.size(); i++)
    {
        const auto& param = sliderParams[i];
        const auto& name = param._id;

        if (name == ViatorParameters::inputID || name == ViatorParameters::outputID)
            continue;

        _filterBankModule.updateFilter(i, param._q, _treeState.getRawParameterValue(param._id)->load(), -1.0);
    }
}

void HermesVoiceEQAudioProcessor::updateParameters()
{
    // update input gain
    _inputGainModule.setGainDecibels(_treeState.getRawParameterValue(ViatorParameters::inputID)->load());
    
    // update output gain
    _outputGainModule.setGainDecibels(_treeState.getRawParameterValue(ViatorParameters::outputID)->load());
}

//==============================================================================
bool HermesVoiceEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HermesVoiceEQAudioProcessor::createEditor()
{
    return new HermesVoiceEQAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void HermesVoiceEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream (stream);
}

void HermesVoiceEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
        
    if (tree.isValid())
    {
        _treeState.state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HermesVoiceEQAudioProcessor();
}
