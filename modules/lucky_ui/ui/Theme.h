#pragma once

/** The Lucky family's colours and label font. */
namespace lucky::theme
{

inline const juce::Colour background { 0xff1b1c20 };
inline const juce::Colour topBar { 0xff26272c };
inline const juce::Colour strip { 0xff222328 };
inline const juce::Colour panel { 0xff1b1c20 };
inline const juce::Colour panelRaised { 0xff2e3036 };
inline const juce::Colour outline { 0xff34363d };
inline const juce::Colour grid { 0xff26282e };
inline const juce::Colour text { 0xffe6e6e8 };
inline const juce::Colour textDim { 0xff83858e };

/** What every accent turns into while a plugin plays its input unprocessed (bypass, compare), so the whole UI
    reads as off at a glance. */
inline const juce::Colour greyedOut { 0xff8e9098 };

/** The pastel palette: equal saturation and brightness, hues spread round the wheel. Gold is the family accent. */
inline const juce::Colour gold { 0xffd6b785 };
inline const juce::Colour pink { 0xffd685be };
inline const juce::Colour green { 0xff85d68f };
inline const juce::Colour teal { 0xff85d6d6 };
inline const juce::Colour blue { 0xff85aad6 };
inline const juce::Colour purple { 0xffa785d6 };
inline const juce::Colour accent = gold;

/** Small label font used across the UI (uppercase labels, values, captions). */
inline juce::FontOptions labelFont (float height = 11.0f)
{
    return juce::FontOptions (height).withStyle ("Medium").withKerningFactor (0.08f);
}

/** Height of the top bar every Lucky plugin shares. */
inline constexpr int topBarHeight = 52;

} // namespace lucky::theme
