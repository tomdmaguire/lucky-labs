#pragma once

namespace lucky
{

/** Width of a keycap for a key's label. */
inline float keycapWidth (const juce::String& key, float height = 20.0f)
{
    return std::max (height, juce::GlyphArrangement::getStringWidth (theme::labelFont (11.0f), key) + 12.0f);
}

/** Draws one keycap. */
inline void paintKeycap (juce::Graphics& g, juce::Rectangle<float> cap, const juce::String& key)
{
    g.setColour (theme::outline.brighter (0.3f));
    g.drawRoundedRectangle (cap.reduced (0.5f), 4.0f, 1.0f);
    g.setColour (theme::textDim);
    g.setFont (theme::labelFont (11.0f));
    g.drawText (key, cap, juce::Justification::centred);
}

/** Draws a shortcut hint as keycaps followed by a label in the product's own words, e.g. [B] BYPASS.
    Returns the width used. */
inline float paintKeyHint (juce::Graphics& g, juce::Point<float> topLeft, const juce::StringArray& keys, const juce::String& label,
                           float height = 20.0f)
{
    const auto font = theme::labelFont (11.0f);
    auto x = topLeft.x;
    for (const auto& key : keys)
    {
        const auto width = keycapWidth (key, height);
        paintKeycap (g, { x, topLeft.y, width, height }, key);
        x += width + 4.0f;
    }

    const auto labelWidth = juce::GlyphArrangement::getStringWidth (font, label.toUpperCase());
    g.setColour (theme::textDim);
    g.setFont (font);
    g.drawText (label.toUpperCase(), juce::Rectangle<float> (x + 4.0f, topLeft.y, labelWidth + 2.0f, height), juce::Justification::centredLeft);
    return x + 6.0f + labelWidth - topLeft.x;
}

/** A shortcut hint you can also click, e.g. [B] BYPASS: clicking it does what the key does. */
class KeyHintButton final : public juce::Button
{
public:
    KeyHintButton (const juce::String& keyToShow, const juce::String& labelToShow)
        : juce::Button (labelToShow), key (keyToShow), label (labelToShow)
    {
        setWantsKeyboardFocus (false);
        setMouseCursor (juce::MouseCursor::PointingHandCursor);
    }

    int getIdealWidth() const
    {
        const auto labelWidth = juce::GlyphArrangement::getStringWidth (theme::labelFont (11.0f), label.toUpperCase());
        return juce::roundToInt (2.0f * padding + keycapWidth (key, capHeight) + 10.0f + labelWidth);
    }

    void paintButton (juce::Graphics& g, bool isMouseOver, bool) override
    {
        if (isMouseOver)
        {
            g.setColour (theme::text.withAlpha (0.05f));
            g.fillRoundedRectangle (getLocalBounds().toFloat(), 4.0f);
        }
        paintKeyHint (g, { padding, (static_cast<float> (getHeight()) - capHeight) * 0.5f }, { key }, label, capHeight);
    }

private:
    static constexpr float padding = 6.0f, capHeight = 18.0f;
    juce::String key, label;
};

} // namespace lucky
