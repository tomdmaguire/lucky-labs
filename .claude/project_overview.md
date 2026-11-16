# Lucky Labs: project overview

Shared code, conventions and lessons for the Lucky plugins (Lucky Reverb in `../lucky-reverb`, Lucky Compressor in `../lucky-compressor`, Lucky Reference in `../lucky-reference`). Not a plugin itself. See README.md for usage.

- `modules/lucky_ui/` JUCE module (`lucky_ui.h` includes everything; `lucky_ui.cpp` compiles the .cpp files). Files under `ui/` have no includes of their own: the module header provides JUCE and the other headers in order. `LookAndFeel.cpp` includes `LuckyLabsFonts.h`, so consumers must link `LuckyLabsFonts`. `Settings` default-constructs from `JucePlugin_Name`.
- `modules/lucky_dsp/` JUCE module, header-only `KWeighting`.
- `cmake/LuckyLabs.cmake` registers both modules (`juce_add_module`) and the fonts binary data; include-guarded.
- `docs/conventions.md` (family look and behaviour), `docs/lessons.md` (shared lessons; read at the start of work on any Lucky plugin).
- All three plugins use `lucky_ui`; the top-bar logo is `ripple::paint` (`ui/RippleGlyph.h`) in each plugin's accent colour.
- There is no build of its own; build any plugin to compile it.
