#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_Standalone/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Debug/Standalone/Audio Plugin Example.app/Contents"
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_Standalone/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Release/Standalone/Audio Plugin Example.app/Contents"
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_Standalone/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/MinSizeRel/Standalone/Audio Plugin Example.app/Contents"
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_Standalone/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/RelWithDebInfo/Standalone/Audio Plugin Example.app/Contents"
fi

