#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" header "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/Debug/Defs.txt" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/JuceHeader.h"
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" header "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/Release/Defs.txt" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/JuceHeader.h"
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" header "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/MinSizeRel/Defs.txt" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/JuceHeader.h"
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" header "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/RelWithDebInfo/Defs.txt" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/JuceHeader.h"
fi

