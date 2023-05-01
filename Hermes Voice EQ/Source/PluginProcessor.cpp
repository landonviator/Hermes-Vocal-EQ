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
    for (int i = 0; i < _paramList.getParams().size(); i++)
    {
        _treeState.addParameterListener(_paramList.getParams()[i]._id, this);
    }
}

HermesVoiceEQAudioProcessor::~HermesVoiceEQAudioProcessor()
{
    for (int i = 0; i < _paramList.getParams().size(); i++)
    {
        _treeState.removeParameterListener(_paramList.getParams()[i]._id, this);
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
    
    for (int i = 0; i < _paramList.getParams().size(); i++)
    {
        auto param = _paramList.getParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { param._id, 1 }, param._name, param._min, param._max, param._initial));
    }
        
    return { params.begin(), params.end() };
}

void HermesVoiceEQAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)

{
    for (int i = 0; i < _paramList.getParams().size(); ++i)
    {
        if (parameterID == _paramList.getParams()[i]._id)
        {
            // Calculate proportional q based on gain
            auto newQ = 0.1;
            newQ = std::pow(10.0, std::abs(newValue) * 0.05);
            
            // Update filter based on which gain moved
            std::string bandToUpdate = remove_non_digits(_paramList.getParams()[i]._id.toStdString());
            _filterBank.updateFilter(std::stoi(bandToUpdate) - 1, newQ, newValue);
        }
    }
}

inline bool not_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

std::string HermesVoiceEQAudioProcessor::remove_non_digits(const std::string& input) {
    std::string result;
    std::copy_if(input.begin(), input.end(),
        std::back_inserter(result),
        not_digit);
    return result;
}

void HermesVoiceEQAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    _filterBank.prepare(spec);
    updateFilters();
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
    if (spec.maximumBlockSize != buffer.getNumSamples())
    {
        spec.maximumBlockSize = buffer.getNumSamples();
        _filterBank.prepare(spec);
    }
    
    if (spec.sampleRate != getSampleRate())
    {
        spec.sampleRate = getSampleRate();
        _filterBank.prepare(spec);
    }
    
    juce::dsp::AudioBlock<float> mainBlock {buffer};
    _filterBank.process(juce::dsp::ProcessContextReplacing<float>(mainBlock));
}

void HermesVoiceEQAudioProcessor::updateFilters()
{
    for (int i = 0; i < _paramList.getParams().size(); i++)
    {
        _filterBank.updateFilter(i, 0.3, _treeState.getRawParameterValue(_paramList.getParams()[i]._id)->load());
    }
}

//==============================================================================
bool HermesVoiceEQAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HermesVoiceEQAudioProcessor::createEditor()
{
    //return new HermesVoiceEQAudioProcessorEditor (*this);
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void HermesVoiceEQAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HermesVoiceEQAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HermesVoiceEQAudioProcessor();
}
