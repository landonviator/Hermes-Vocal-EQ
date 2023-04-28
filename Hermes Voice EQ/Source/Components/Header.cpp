#include <JuceHeader.h>
#include "Header.h"

Header::Header()
{
    _dropShadow = std::make_unique<juce::DropShadower>(juce::DropShadow(juce::Colours::black.withAlpha(_shadowAlpha), 5, {}));
    _dropShadow->setOwner(this);
}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    g.setColour(_auxBackgroundColor);
    g.fillAll();
}

void Header::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
