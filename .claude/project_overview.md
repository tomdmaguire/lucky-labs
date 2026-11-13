# Lucky Labs: project overview

Shared code, conventions and lessons for the Lucky plugins (Lucky Seven, Lucky Reference, Lucky Comp in sibling folders). Not a plugin itself. See README.md for usage.

- `modules/lucky_ui/` JUCE module (`lucky_ui.h` includes everything; `lucky_ui.cpp` compiles the .cpp files). Files under `ui/` have no includes of their own: the module header provides JUCE and the other headers in order. `LookAndFeel.cpp` includes `LuckyLabsFonts.h`, so consumers must link `LuckyLabsFonts`. `Settings` default-constructs from `JucePlugin_Name`.
- `modules/lucky_dsp/` JUCE module, header-only `KWeighting`.
- `cmake/LuckyLabs.cmake` registers both modules (`juce_add_module`) and the fonts binary data; include-guarded.
- `docs/conventions.md` (family look and behaviour), `docs/lessons.md` (shared lessons; read at the start of work on any Lucky plugin).
- Lucky Comp is the only consumer so far; Lucky Seven and Lucky Reference still have their own copies (Theme, LookAndFeel, SmallSwitch, SegmentGlyph, Settings, K-weighting in Reference's LoudnessMeter).
- There is no build of its own; build Lucky Comp to compile it.
