#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" pkginfo AU "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo"
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" pkginfo AU "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo"
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" pkginfo AU "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo"
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" pkginfo AU "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo"
fi

