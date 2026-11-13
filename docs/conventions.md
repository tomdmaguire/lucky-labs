# Lucky conventions

What makes a plugin look and feel like part of the family. Check a new plugin against this list and against the siblings' snapshots side by side.

## Product

- Few controls, done well. Every control on screen is used in normal work; anything else goes in the ••• menu or doesn't exist.
- Teach and reassure in plain words: say what is compared with what and which way ("3.4 dB quieter"), not just a number.
- A bit of delight: the visuals should be beautiful as well as correct (ripples, glows, smooth motion), never noisy.

## Window

- Base size 900 × 600, scaled as a whole by `ScaledEditor`; Window size menu with 100/125/150/175%, remembered per plugin.
- Background `theme::background`; top bar `theme::topBar`, 52 px high, separated from neighbouring sections by 1 px background-coloured lines.
- Top bar, left to right: seven-segment logo glyph and the name in Barlow semibold caps, then tabs on the right, then the ••• menu (`setUpMenuButton`).
- Hearing the input unprocessed (a bypass, or Lucky Comp's Compare with uncompressed) works the same everywhere: an item in the ••• menu with its key as the shortcut, the key toggles it, and a clickable [key] LABEL hint (`KeyHintButton`) sits at the right of the tip line. Name it for what you hear, in a few words ("Compare with uncompressed"), not "bypass" or "compare" alone, which beginners misread. While on, every accent turns `theme::greyedOut` and a `ToggleNotice` over the main view says what you're hearing, "Press [key] to switch back and forth", and offers a button back (some hosts keep key presses). No top-bar tab: it read as one more mode.
- The ••• menu starts with a section header "<Name> v<version>", then Window size, then the plugin's settings.

## Colour and type

- Barlow everywhere (`LuckyLookAndFeel`). Labels are small caps-style uppercase with slight letter spacing (`theme::labelFont`).
- The pastel palette (`theme::gold, pink, green, teal, blue, purple`): equal saturation and brightness. Gold is the family accent.
- Colour means something: a category, a slot or a mode. A control that only affects one thing wears that thing's colour.
- Use a real minus sign, µ and ≈ (`format::`).

## Controls

- Knobs in the Lucky Seven style (`Knob`): faint filled disc, thin ring, value arc and dot, value in the middle, label above, caption below. Drag vertically, Shift for fine, double-click to reset, wheel.
- On/off settings are `SmallSwitch`es with a label.
- Shortcuts are shown as keycaps with the product's own words (`paintKeyHint`).

## Keyboard and focus

- Never take the host's keys: no Space, no text focus unless a field is clicked. Handle only your own keys and let everything else through.

## Engineering

- JUCE 9 via CMake + Ninja, VST3 for Apple Silicon and Intel, macOS 13+. AGPLv3.
- Tests as `juce::UnitTest` run by CTest; a snapshot tool renders the editor to PNG for review.
- Don't install over a plugin a running DAW has loaded.
