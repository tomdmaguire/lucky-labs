# Lessons

Lessons that apply to every Lucky plugin, gathered from Lucky Reverb, Lucky Compressor and Lucky Reference. Plugin-specific lessons stay in each plugin's `tasks/lessons.md`.


## "X-style" UI requests: get the reference before building
- **Mistake:** asked for an "Ableton style EQ" with one screenshot, I built a band dot that moved both corners at once with 24 dB/oct slopes. Ableton's actual model has Lo Cut / Hi Cut toggles, a handle that sits on the curve, separate frequency and width readouts, and gentle slopes.
- **Rule:** when a request names another product's UI, list the specific interactions I'm assuming (controls, what dragging does, readouts) and confirm them, or ask for screenshots of each state, before writing code.

## Match a sibling product's UI conventions before building
- **Mistake:** Lucky Reference's first UI copied Lucky Reverb's colours but not its structure (outlined panels, top bar separators, three-dot icon, Window size menu, scaling), so it felt like a different product.
- **Rule:** when building a sibling, open its screenshots and editor code first and list the conventions to carry over; review snapshots side by side with the sibling's.

## Plans must account for every earlier suggestion
- **Mistake:** I suggested softening the *high* cut, then High Cut became Damping and the plan quietly dropped that idea. The user remembered "softening the low cut" and couldn't find it in the plan, and my replies didn't clear up which control I'd meant.
- **Rule:** when a plan supersedes something I proposed earlier, say so in the plan by name ("dropped: 6 dB/oct high cut, replaced by Damping"). When the user misremembers a suggestion, first restate exactly what I said and about which control, then answer.

## Phased plans still need the final design up front
- **Mistake:** for a feature-heavy plugin I proposed shipping in phases where each phase is a complete plugin, without first settling where the UI ends up.
- **Rule:** when splitting a complex build into phases, design the final UI and architecture first (prototype if useful), then phase the build toward that target so early phases leave room for later ones.

## Don't disturb a live DAW session
- **Mistake:** full-core builds starved the plugin's IR loader thread in the user's running Ableton set, so Damping seemed broken; I also nearly overwrote the installed plugin while Live had it loaded.
- **Rule:** while the user is testing in a DAW, build with `nice -n 19` and limited `-j`, build only test/tool targets, and install (full build) only after they have quit the host.
- **Mistake:** during the rename, I started a full VST3/AU build of Lucky Reference without checking its `*_INSTALL_AFTER_BUILD` option, which defaults to ON, so it would have overwritten the installed plugin. I caught it before that target ran.
- **Rule:** before building any `_VST3` or `_AU` target, run `grep INSTALL_AFTER build/CMakeCache.txt` in every repo involved and configure with the option OFF unless the user asked for an install.

## Async-loading test fixtures
- **Mistake:** waited for `Convolution::getCurrentIRSize() > 0`, but JUCE reports 1 (an identity impulse) before the real IR is installed, so the test ran against no IR.
- **Rule:** when waiting on async state, wait for the exact expected value (e.g. the IR length), not "non-zero".

## Never keep a pointer into a temporary
- **Mistake:** `if (const auto* list = JSON::parse (file).getArray())` and `const auto* entry = findEntry (library.getEntries(), key)` both pointed into a value destroyed at the end of the statement, so favourites silently failed to load and a test read garbage.
- **Rule:** when a call returns by value (`var`, `std::vector`, a `unique_ptr` from a factory), store it in a named local before taking a pointer or reference into it or into anything it owns. `makeProcessor()->getLibrary()` crashed the same way: the temporary processor was the shared library's last owner.

## Benchmark whole-file work on realistic lengths
- **Mistake:** JUCE's WindowedSincInterpolator took 0.9 s for a 24 s file (about 9 s per song); tests only used short signals, so nothing flagged it.
- **Rule:** time every whole-file step (decode, resample, analysis) on a 4-minute file at a mismatched sample rate before shipping; keep the benchmark tool.

## Never play a level-matched signal unmatched
- **Mistake:** the reference played at its full level until the mix had been measured, so every fresh session started with a loud commercial master.
- **Rule:** when a gain depends on a measurement that isn't ready, keep the signal silent (or at a safe level) and fade it in once the measurement exists.

## User-facing numbers need plain words
- **Mistake:** "Ref −3.4 dB" was correct but hard to read once on screen: it didn't say what was compared or which way.
- **Rule:** label what is compared with what ("YOUR MIX VS REF 2") and say the direction in words ("3.4 dB quieter"), with the raw values as detail.

## Feedback belongs to what changed
- **Mistake:** picking a reference while on the mix sent a white ripple from the MIX side, and LEVEL MATCH took the mix colour, though it only affects the reference.
- **Rule:** a ripple, glow or colour comes from the control that just changed, in that thing's colour. A control that only affects one thing always wears that thing's colour.

## Shortcut hints must look like keys
- **Mistake:** "1 2 3 SLOTS" read as labels, not number keys, and used an internal word.
- **Rule:** draw shortcuts as keycaps and label them with the product's own words ("reference", not "slot").

## Never take text focus in a plug-in unasked
- **Mistake:** the library focused its search box on open, so the host's space bar typed into it instead of stopping playback.
- **Rule:** a text field only takes focus when clicked, and clicking elsewhere gives it up. Panels hold focus themselves and handle only their own keys, so everything else reaches the host.

## Never take the host's keys
- **Mistake:** Lucky Compressor's first build toggled Bypass with Space and took keyboard focus on open, so Space stopped reaching the DAW's transport.
- **Rule:** never bind Space (or other transport keys) in a plug-in. Use letters or arrows for the plug-in's own shortcuts and pass every other key to the host.

## Visuals are part of the product
- **Mistake:** Lucky Compressor's waveforms were drawn as one-pixel columns: correct, but stepped, shimmering while scrolling and heavier than the prototype.
- **Rule:** draw curves as smoothed paths with anti-aliasing, keep scrolling bins anchored so they don't shimmer, and compare against the prototype or sibling at the real window size before calling a view done.

## Read the licence before measuring someone else's product
- **Why:** many licences forbid using a product's output as the basis for a competing product, or extracting data from it automatically, so measuring first and reading later can leave you with work you can't use.
- **Rule:** before measuring, benchmarking or modelling any third-party product to inform a Lucky plugin, read its licence for clauses on output, benchmarking, automated extraction and competing products. If they restrict it, use published specs, research or our own designs instead. Never commit third-party measurement data.
