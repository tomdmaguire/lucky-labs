#pragma once

/** Numbers as people read them, with real typographic signs. */
namespace lucky::format
{

inline const juce::String minus = juce::String (juce::CharPointer_UTF8 ("\xe2\x88\x92"));
inline const juce::String micro = juce::String (juce::CharPointer_UTF8 ("\xc2\xb5"));
inline const juce::String approx = juce::String (juce::CharPointer_UTF8 ("\xe2\x89\x88"));
inline const juce::String middleDot = juce::String (juce::CharPointer_UTF8 ("\xc2\xb7"));
inline const juce::String emDash = juce::String (juce::CharPointer_UTF8 ("\xe2\x80\x94"));

/** A time given in ms: "20 µs", "3.0 ms", "150 ms", "1.2 s". */
inline juce::String time (float ms)
{
    if (ms < 1.0f)
        return juce::String (juce::roundToInt (ms * 1000.0f)) + " " + micro + "s";
    if (ms < 10.0f)
        return juce::String (ms, 1) + " ms";
    if (ms < 1000.0f)
        return juce::String (juce::roundToInt (ms)) + " ms";
    return juce::String (ms / 1000.0f, 1) + " s";
}

/** Decibels with a real minus and a + for gains: "−24 dB", "+3.5 dB"; one decimal below 10. */
inline juce::String decibels (float db)
{
    const auto magnitude = std::abs (db);
    const auto rounded = magnitude < 10.0f ? juce::String (magnitude, 1) : juce::String (juce::roundToInt (magnitude));
    const auto sign = db <= -0.05f ? minus : (db >= 0.05f ? juce::String ("+") : juce::String());
    return sign + rounded + " dB";
}

} // namespace lucky::format
