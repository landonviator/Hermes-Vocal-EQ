#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  make -f /Volumes/Land00m\ 1/GitHub/Hermes-Vocal-EQ/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  make -f /Volumes/Land00m\ 1/GitHub/Hermes-Vocal-EQ/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  make -f /Volumes/Land00m\ 1/GitHub/Hermes-Vocal-EQ/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Volumes/Land00m 1/GitHub/Hermes-Vocal-EQ/build"
  make -f /Volumes/Land00m\ 1/GitHub/Hermes-Vocal-EQ/build/CMakeScripts/ReRunCMake.make
fi

