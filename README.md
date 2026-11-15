# Lucky Labs

Shared code, conventions and lessons for the Lucky plugins: [Lucky Reverb](https://github.com/tomdmaguire/lucky-reverb), [Lucky Compressor](https://github.com/tomdmaguire/lucky-compressor) and [Lucky Reference](https://github.com/tomdmaguire/lucky-reference). The [Lucky Labs site](https://tomdmaguire.github.io/lucky-labs/) is in `docs/`.

## What's here

| | |
|---|---|
| `modules/lucky_ui` | JUCE module: the palette and label font (`theme`), number formatting (`format`), `LuckyLookAndFeel` with Barlow, `Settings` (per-plugin settings file), `Knob`, `SmallSwitch`, `ToggleNotice` (the panel shown while a key-toggled state such as bypass is on, with a button to turn it off), `KeyHintButton` (a clickable [key] LABEL hint), `InfoDot` (a circled i with an explaining tooltip), `LabelTabs` (MIX | BLEND style tabs in place of a knob label), the ripple logo (`ripple::paint`), the ••• menu icon, keycap shortcut hints and `ScaledEditor` (fixed-size view scaled to the window, Window size menu, remembered scale). |
| `modules/lucky_dsp` | JUCE module: `KWeighting` (BS.1770). |
| `cmake/LuckyLabs.cmake` | Adds both modules and the `LuckyLabsFonts` binary data. |
| `Resources/Fonts` | Barlow (SIL OFL). |
| `docs/conventions.md` | How a Lucky plugin looks and behaves. |
| `docs/lessons.md` | Lessons that apply to every Lucky plugin. |

## Using it

After JUCE is available in a plugin's `CMakeLists.txt`:

```cmake
set(LUCKY_LABS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lucky-labs" CACHE PATH "Lucky Labs shared code")
include("${LUCKY_LABS_DIR}/cmake/LuckyLabs.cmake")
target_link_libraries(MyPlugin PRIVATE lucky_ui lucky_dsp LuckyLabsFonts)
```

Then `#include <lucky_ui/lucky_ui.h>` / `<lucky_dsp/lucky_dsp.h>`. Everything lives in `namespace lucky`.

The repos sit side by side in one folder for now. Once they're published, `LUCKY_LABS_DIR` can point at a FetchContent checkout instead.

## Status

Lucky Reverb, Lucky Compressor and Lucky Reference are all built on it.

## Licence

Copyright (C) 2026 Tom Maguire. Free software under the [GNU Affero General Public License v3.0](LICENSE), with no warranty. Barlow is under the SIL Open Font License (`Resources/Fonts/OFL.txt`). `Resources/THIRD-PARTY-NOTICES.txt` holds the licences of the third-party code JUCE compiles into every Lucky plug-in; release workflows ship it inside each bundle. Regenerate it with `tools/make-third-party-notices.py` when JUCE is updated.
