/*******************************************************************************
 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 lucky_ui
  vendor:             Lucky Labs
  version:            0.1.0
  name:               Lucky Labs UI
  description:        The shared look of the Lucky plugins: palette, fonts, logo, knob, switch, settings and window scaling.
  license:            AGPLv3
  minimumCppStandard: 20

  dependencies:       juce_gui_basics, juce_data_structures, juce_audio_processors

 END_JUCE_MODULE_DECLARATION
*******************************************************************************/

#pragma once
#define LUCKY_UI_H_INCLUDED

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_data_structures/juce_data_structures.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "ui/Theme.h"
#include "ui/Format.h"
#include "ui/LookAndFeel.h"
#include "ui/Settings.h"
#include "ui/RippleGlyph.h"
#include "ui/KeyHint.h"
#include "ui/SmallSwitch.h"
#include "ui/ToggleNotice.h"
#include "ui/InfoDot.h"
#include "ui/LabelTabs.h"
#include "ui/Knob.h"
#include "ui/Icons.h"
#include "ui/ScaledEditor.h"
