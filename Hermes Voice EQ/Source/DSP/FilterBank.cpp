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
    _filterBank.push_back(std::move(_auxMudFilter));
    
    _coefficients.push_back(std::move(_rumbleCoefficients));
    _coefficients.push_back(std::move(_mudCoefficients));
    _coefficients.push_back(std::move(_muffleCoefficients));
    _coefficients.push_back(std::move(_clarityCoefficients));
    _coefficients.push_back(std::move(_airCoefficients));
    _coefficients.push_back(std::move(_noiseCoefficients));
    _coefficients.push_back(std::move(_auxMudCoefficients));
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
        
        else if (i == 6)
        {
            _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _maleCutoffs[i], 0.6f, 1.0f);
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
void FilterBank<SampleType>::reset() noexcept
{
    
}

template <typename SampleType>
void FilterBank<SampleType>::updateFilter(const int bandToUpdate, const float newQ, const float newGain, const float newCutoff)
{
    _currentFilter = static_cast<FilterStuff>(bandToUpdate);
    auto gain = juce::Decibels::decibelsToGain(newGain);
    auto negativeGain = juce::Decibels::decibelsToGain(-newGain);

    switch (_currentFilter)
    {
        case kRumble:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeHighPass(_sampleRate, newCutoff, newQ);
            break;

        case kMud:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], newQ, gain);
            *_coefficients[6] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[6], newQ, (newGain > 0.0) ? negativeGain : 1.0f);
            break;

        case kMuffle:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], newQ, gain);
            break;
            
        case kClarity:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, getCurrentCutoffs()[bandToUpdate], newQ, gain);
            break;

        case kAir:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeHighShelf(_sampleRate, getCurrentCutoffs()[bandToUpdate], newQ, gain);
            break;

        case kNoise:
            *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makeLowPass(_sampleRate, newCutoff, newQ);
            break;
    }
}

template <typename SampleType>
void FilterBank<SampleType>::setVoice(const Voice newVoice)
{
    jassert(newVoice == Voice::kMale || newVoice == Voice::kFemale);
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
