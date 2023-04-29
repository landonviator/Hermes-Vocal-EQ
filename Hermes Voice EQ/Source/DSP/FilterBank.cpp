#include "FilterBank.h"

template <typename SampleType>
FilterBank<SampleType>::FilterBank()
{
    _filterBank.push_back(std::move(_band1));
    _filterBank.push_back(std::move(_band2));
    _filterBank.push_back(std::move(_band3));
    _filterBank.push_back(std::move(_band4));
    _filterBank.push_back(std::move(_band5));
    _filterBank.push_back(std::move(_band6));
    
    _coefficients.push_back(std::move(_iirCoefficients1));
    _coefficients.push_back(std::move(_iirCoefficients2));
    _coefficients.push_back(std::move(_iirCoefficients3));
    _coefficients.push_back(std::move(_iirCoefficients4));
    _coefficients.push_back(std::move(_iirCoefficients5));
    _coefficients.push_back(std::move(_iirCoefficients6));
}

template <typename SampleType>
void FilterBank<SampleType>::prepare(const juce::dsp::ProcessSpec& spec) noexcept
{
    _sampleRate = spec.sampleRate;
    _blockSize = spec.maximumBlockSize;
    
    for (int i = 0; i < _filterBank.size(); ++i)
    {
        _coefficients[i] = juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _cutoffs[i], 0.1f, 1.0f);
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
//    if (_currentSampleRate > 0)
//    {
//        _drive.reset(_currentSampleRate, 0.02);
//        _drive.setTargetValue(1.0);
//        _resample.reset(_currentSampleRate, 0.02);
//        _resample.setTargetValue(50.0);
//        _mix.reset(_currentSampleRate, 0.02);
//        _mix.setTargetValue(1.0);
//        _output.reset(_currentSampleRate, 0.02);
//        _output.setTargetValue(0.0);
//    }
}

template <typename SampleType>
void FilterBank<SampleType>::updateFilter(int bandToUpdate, float newQ, float newGain)
{
    auto gain = juce::Decibels::decibelsToGain(newGain);
    *_coefficients[bandToUpdate] = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(_sampleRate, _cutoffs[bandToUpdate], newQ, gain);
}

template class FilterBank<float>;
template class FilterBank<double>;
