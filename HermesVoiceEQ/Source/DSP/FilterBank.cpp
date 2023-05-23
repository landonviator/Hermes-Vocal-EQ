#include "FilterBank.h"

template <typename SampleType>
FilterBank<SampleType>::FilterBank()
{
    _filterBank.push_back(std::move(_rumbleFilter));
    _filterBank.push_back(std::move(_mudFilter));
    _filterBank.push_back(std::move(_muffleFilter));
    _filterBank.push_back(std::move(_clarityFilter));
    _filterBank.push_back(std::move(_airFilter));
    _filterBank.push_back(std::move(_noiseFilter));
    
    _coefficients.push_back(std::move(_rumbleCoefficients));
    _coefficients.push_back(std::move(_mudCoefficients));
    _coefficients.push_back(std::move(_muffleCoefficients));
    _coefficients.push_back(std::move(_clarityCoefficients));
    _coefficients.push_back(std::move(_airCoefficients));
    _coefficients.push_back(std::move(_noiseCoefficients));
}

template <typename SampleType>
void FilterBank<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    _blockSize = spec.maximumBlockSize;
    
    for (int i = 0; i < _filterBank.size(); ++i)
    {
        if (i == 0)
        {
            _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makeHighPass(_sampleRate, _maleCutoffs[i], 0.1f);
        }
        
        else if (i == 4)
        {
            _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makeHighShelf(_sampleRate, _maleCutoffs[i], 0.3f, 1.0f);
        }
        
        else if (i == 5)
        {
            _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, _maleCutoffs[i], 0.1f);
        }
        
        else
        {
            _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _maleCutoffs[i], 0.6f, 1.0f);
        }
        
        _filterBank[i].reset (new juce::dsp::IIR::Filter<juce::dsp::SIMDRegister<float>> (_coefficients[i]));
    }

    _interleaved = juce::dsp::AudioBlock<juce::dsp::SIMDRegister<float>> (_interleavedBlockData, 1, spec.maximumBlockSize);
    _zero        = juce::dsp::AudioBlock<float> (_zeroData, juce::dsp::SIMDRegister<float>::size(), spec.maximumBlockSize);

    _zero.clear();

    auto monoSpec = spec;
    monoSpec.numChannels = 1;
    
    for (auto& filter : _filterBank)
    {
        filter->prepare (monoSpec);
    }
}

template <typename SampleType>
void FilterBank<SampleType>::reset(const float newSamplerate) noexcept
{
    _sampleRate = newSamplerate;
}

template <typename SampleType>
void FilterBank<SampleType>::updateFilter(const int bandToUpdate, const float newQ, const float newGain, const float newCutoff)
{
    _currentFilter = static_cast<FilterStuff>(bandToUpdate);
    auto rawGain = newGain;
    
    if (bandToUpdate != 4)
    {
        rawGain = juce::jmap(newGain, 0.0f, 100.0f, 0.0f, 10.0f);
    }
    
    const auto filterGain = juce::Decibels::decibelsToGain(rawGain);
    const auto negativeFilterGain = juce::Decibels::decibelsToGain(-rawGain);
    const auto scaledGain = juce::jmap(std::abs(newGain), 0.0f, 15.0f, 0.0f, 1.0f);

    switch (_currentFilter)
    {
        case kRumble:
        {
            const auto cutoff = juce::jmap(newGain, 0.0f, 100.0f, 20.0f, 100.0f);
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeHighPass(_sampleRate, cutoff, newQ);
            break;
        }

        case kDepth:
        {
            const auto filterQ = std::pow(10, scaledGain * 0.05) - 0.8;
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], filterQ, filterGain);
            break;
        }

        case kHollow:
        {
            const auto filterQ = std::pow(10, scaledGain * 0.075) - 0.9;
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], filterQ, negativeFilterGain);
            break;
        }
            
        case kNasal:
        {
            const auto filterQ = std::pow(10, scaledGain * 0.05) - 0.7;
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], filterQ, negativeFilterGain);
            break;
        }

        case kSparkle:
        {
            const auto filterQ = std::pow(10, scaledGain * 0.05) - 0.6;
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(_sampleRate, getCurrentCutoffs()[bandToUpdate], filterQ, filterGain);
            break;
        }

        case kNoise:
        {
            const auto cutoff = juce::jmap(newGain, 0.0f, 100.0f, 20000.0f, 1000.0f);
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, cutoff, newQ);
            break;
        }
    }
}

template <typename SampleType>
void FilterBank<SampleType>::setVoice(const Voice newVoice)
{
    _currentVoice = newVoice;
}

template <typename SampleType>
std::vector<float> FilterBank<SampleType>::getCurrentCutoffs()
{
    std::vector<float> _cutoffs;
    _cutoffs.clear();
    
    for (int i = 0; i < _maleCutoffs.size(); i++)
    {
        if (_currentVoice == Voice::kMale)
        {
            _cutoffs.push_back(_maleCutoffs[i]);
        }
        
        else
        {
            _cutoffs.push_back(_femaleCutoffs[i]);
        }
    }
    
    return _cutoffs;
}

template class FilterBank<float>;
template class FilterBank<double>;
