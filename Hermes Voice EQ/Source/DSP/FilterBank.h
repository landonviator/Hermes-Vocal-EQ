#ifndef FilterBank_h
#define FilterBank_h

#include <JuceHeader.h>

#if JUCE_USE_SIMD
 
//==============================================================================
template <typename T>
static T* toBasePointer (juce::dsp::SIMDRegister<T>* r) noexcept
{
    return reinterpret_cast<T*> (r);
}
 
constexpr auto registerSize = juce::dsp::SIMDRegister<float>::size();

template <typename SampleType>
auto prepareChannelPointers (const juce::dsp::AudioBlock<SampleType>& block, juce::dsp::AudioBlock<float>& zero)
{
    std::array<SampleType*, registerSize> result {};

    for (size_t ch = 0; ch < result.size(); ++ch)
        result[ch] = (ch < block.getNumChannels() ? block.getChannelPointer (ch) : zero.getChannelPointer (ch));

    return result;
}

template <typename SampleType>
class FilterBank
{
public:
    
    FilterBank();
    
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept;
    
    void reset() noexcept;
    
    void process (const juce::dsp::ProcessContextReplacing<float>& context) noexcept
    {
        jassert (context.getInputBlock().getNumSamples()  == context.getOutputBlock().getNumSamples());
        jassert (context.getInputBlock().getNumChannels() == context.getOutputBlock().getNumChannels());
 
        const auto& input  = context.getInputBlock(); // [9]
        const auto numSamples = (int) input.getNumSamples();
 
        auto inChannels = prepareChannelPointers (input, _zero); // [10]
 
        using Format = juce::AudioData::Format<juce::AudioData::Float32, juce::AudioData::NativeEndian>;
 
        juce::AudioData::interleaveSamples (juce::AudioData::NonInterleavedSource<Format> { inChannels.data(),                                 registerSize, },
                                            juce::AudioData::InterleavedDest<Format>      { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                            numSamples); // [11]
 
        for (auto& filter : _filterBank)
        {
            if (_interleaved.getNumSamples() == _blockSize)
            {
                filter->process (juce::dsp::ProcessContextReplacing<juce::dsp::SIMDRegister<float>> (_interleaved));
            }
        }
 
        auto outChannels = prepareChannelPointers (context.getOutputBlock(), _zero); // [13]
 
        juce::AudioData::deinterleaveSamples (juce::AudioData::InterleavedSource<Format>  { toBasePointer (_interleaved.getChannelPointer (0)), registerSize },
                                              juce::AudioData::NonInterleavedDest<Format> { outChannels.data(),                                registerSize },
                                              numSamples); // [14]
    }
    
    void updateFilter(const int bandToUpdate, const float newQ, const float newGain, const float newCutoff);
    
    enum class Voice
    {
        kMale,
        kFemale
    };
    
    void setVoice(const Voice newVoice);
    
    enum FilterStuff
    {
        kRumble,
        kMud,
        kMuffle,
        kClarity,
        kAir,
        kNoise
    };
    
private:
    float _sampleRate {44100.0f};
    float _blockSize;
    
    juce::dsp::IIR::Coefficients<float>::Ptr
    _rumbleCoefficients, _mudCoefficients, _muffleCoefficients,
    _clarityCoefficients, _airCoefficients, _noiseCoefficients,
    _auxMudCoefficients;
    
    std::vector<juce::dsp::IIR::Coefficients<float>::Ptr> _coefficients;
    
    std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>>
    _rumbleFilter, _mudFilter, _muffleFilter, _clarityFilter, _airFilter, _noiseFilter,
    _auxMudFilter;
    
    std::vector<std::unique_ptr<juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>>>> _filterBank;
 
    juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> _interleaved;
    juce::dsp::AudioBlock<float> _zero;
 
    juce::HeapBlock<char> _interleavedBlockData, _zeroData;
    
    std::vector<const float> _maleCutoffs
    {
        20.0f, 150.0f, 900.0f, 2000.0f, 8000.0f, 20000.0f, 250.0f
    };
    
    std::vector<const float> _femaleCutoffs
    {
        20.0f, 300.0f, 1200.0f, 3000.0f, 12000.0f, 20000.0f, 250.0f
    };
    
    Voice _currentVoice = Voice::kMale;
    FilterStuff _currentFilter = FilterStuff::kRumble;
    std::vector<float> getCurrentCutoffs();
};
#endif /* FilterBank_h */
#endif

