#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Debug/AU/Hermes Voice EQ.component/Contents"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Debug/AU/Hermes Voice EQ.component" -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Debug/AU/Hermes Voice EQ.component" -Ddest=/Users/land00m/Library/Audio/Plug-Ins/Components -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/copyDir.cmake"
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Release/AU/Hermes Voice EQ.component/Contents"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Release/AU/Hermes Voice EQ.component" -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/Release/AU/Hermes Voice EQ.component" -Ddest=/Users/land00m/Library/Audio/Plug-Ins/Components -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/copyDir.cmake"
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/MinSizeRel/AU/Hermes Voice EQ.component/Contents"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/MinSizeRel/AU/Hermes Voice EQ.component" -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/MinSizeRel/AU/Hermes Voice EQ.component" -Ddest=/Users/land00m/Library/Audio/Plug-Ins/Components -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/copyDir.cmake"
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake -E copy "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/JuceLibraryCode/HermesVoiceEQ_AU/PkgInfo" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/RelWithDebInfo/AU/Hermes Voice EQ.component/Contents"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/RelWithDebInfo/AU/Hermes Voice EQ.component" -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  /Applications/CMake.app/Contents/bin/cmake "-Dsrc=/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/HermesVoiceEQ_artefacts/RelWithDebInfo/AU/Hermes Voice EQ.component" -Ddest=/Users/land00m/Library/Audio/Plug-Ins/Components -P "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/modules/JUCE/extras/Build/CMake/copyDir.cmake"
fi

