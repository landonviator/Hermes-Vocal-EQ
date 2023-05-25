#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" binarydata BinaryData BinaryData.h "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode/input_file_list"
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" binarydata BinaryData BinaryData.h "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode/input_file_list"
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" binarydata BinaryData BinaryData.h "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode/input_file_list"
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ"
  "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/modules/JUCE/tools/extras/Build/juceaide/juceaide_artefacts/Debug/juceaide" binarydata BinaryData BinaryData.h "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode" "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build/juce_binarydata_AudioPluginData/JuceLibraryCode/input_file_list"
fi

