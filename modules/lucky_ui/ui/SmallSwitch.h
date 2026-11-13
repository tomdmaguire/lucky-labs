#pragma once


namespace lucky
{

/** A small on/off switch with a label, a little cousin of the MIX | REF switch: the knob sits right and the track
    fills with the colour when on, and sits left on a grey track when off. Clicking anywhere on it flips it. */
class SmallSwitch final : public juce::Component,
                          public juce::SettableTooltipClient
{
public:
    explicit SmallSwitch (const juce::String& labelText) : label (labelText)
    {
        setMouseCursor (juce::MouseCursor::PointingHandCursor);
        setWantsKeyboardFocus (false);
    }

    /** Called with the new state when clicked. */
    std::function<void (bool on)> onToggle;

    void setOn (bool shouldBeOn)
    {
        if (on != shouldBeOn)
        {
            on = shouldBeOn;
            repaint();
        }
    }

    void setColour (juce::Colour newColour)
    {
        colour = newColour;
        repaint();
    }

    /** Shows the switch's keyboard shortcut as a keycap after the label. */
    void setKeyHint (const juce::String& key)
    {
        keyHint = key;
        repaint();
    }

    void paint (juce::Graphics& g) override
    {
        const auto bounds = getLocalBounds().toFloat();
        const auto track = bounds.withWidth (trackWidth).withSizeKeepingCentre (trackWidth, trackHeight);
        g.setColour (on ? colour.withAlpha (hover ? 0.85f : 0.7f) : theme::outline.brighter (hover ? 0.5f : 0.3f));
        g.fillRoundedRectangle (track, trackHeight * 0.5f);

        const auto knobSize = trackHeight - 4.0f;
        const auto knobX = on ? track.getRight() - knobSize - 2.0f : track.getX() + 2.0f;
        g.setColour (on ? theme::text : theme::textDim);
        g.fillEllipse (knobX, track.getY() + 2.0f, knobSize, knobSize);

        g.setColour (on ? theme::text : theme::textDim);
        g.setFont (labelFont());
        g.drawText (label, bounds.withTrimmedLeft (trackWidth + 10.0f), juce::Justification::centredLeft);

        if (keyHint.isNotEmpty())
        {
            const auto x = trackWidth + 10.0f + juce::GlyphArrangement::getStringWidth (labelFont(), label) + keyGap;
            paintKeycap (g, juce::Rectangle<float> (x, 0.0f, keycapWidth (keyHint, keyHeight), keyHeight).withCentre ({ x + keycapWidth (keyHint, keyHeight) * 0.5f, bounds.getCentreY() }), keyHint);
        }
    }

    void mouseEnter (const juce::MouseEvent&) override { hover = true; repaint(); }
    void mouseExit (const juce::MouseEvent&) override { hover = false; repaint(); }

    void mouseUp (const juce::MouseEvent& event) override
    {
        if (getLocalBounds().contains (event.getPosition()) && onToggle)
            onToggle (! on);
    }

    /** Width of the track, the label and any keycap, for laying it out. */
    int getIdealWidth() const
    {
        const auto keyWidth = keyHint.isEmpty() ? 0.0f : keyGap + keycapWidth (keyHint, keyHeight);
        return static_cast<int> (trackWidth + 10.0f + juce::GlyphArrangement::getStringWidth (labelFont(), label) + keyWidth) + 2;
    }

private:
    static juce::FontOptions labelFont() { return theme::labelFont (12.0f).withStyle ("Bold"); }

    static constexpr float trackWidth = 38.0f, trackHeight = 22.0f, keyGap = 10.0f, keyHeight = 18.0f;
    const juce::String label;
    juce::String keyHint;
    bool on = true, hover = false;
    juce::Colour colour = theme::accent;
};

} // namespace lucky
