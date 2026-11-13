#pragma once

namespace lucky
{

/** Small tabs that stand in for a knob's label when the knob has more than one meaning (MIX | BLEND, as on
    Lucky Seven's output knob): the chosen one is bright and underlined in the colour. */
class LabelTabs final : public juce::Component,
                        public juce::TooltipClient
{
public:
    static constexpr float underlineOffset = 17.0f;

    explicit LabelTabs (juce::StringArray names) : labels (std::move (names))
    {
        setRepaintsOnMouseActivity (true);
        setMouseCursor (juce::MouseCursor::PointingHandCursor);
        setWantsKeyboardFocus (false);
    }

    /** Called with the index of the tab clicked. */
    std::function<void (int index)> onChoose;

    void setChosen (int index)
    {
        if (chosen != index)
        {
            chosen = index;
            repaint();
        }
    }

    void setColour (juce::Colour newColour)
    {
        colour = newColour;
        repaint();
    }

    /** One tooltip per tab. */
    void setTooltips (juce::StringArray texts) { tooltips = std::move (texts); }

    juce::String getTooltip() override
    {
        const auto index = indexAt (getMouseXYRelative().toFloat());
        return index >= 0 && index < tooltips.size() ? tooltips[index] : juce::String();
    }

    void paint (juce::Graphics& g) override
    {
        const auto font = theme::labelFont (12.0f);
        const auto hovered = isMouseOver() ? indexAt (getMouseXYRelative().toFloat()) : -1;
        for (int i = 0; i < labels.size(); ++i)
        {
            const auto area = tabArea (i);
            const auto on = i == chosen;
            const auto text = labels[i].toUpperCase();
            g.setColour (on || i == hovered ? theme::text : theme::textDim);
            g.setFont (font);
            g.drawText (text, area, juce::Justification::centredTop);
            if (on)
            {
                const auto width = juce::GlyphArrangement::getStringWidth (font, text) + 8.0f;
                g.setColour (colour);
                g.fillRect (juce::Rectangle<float> (width, 2.0f).withCentre ({ area.getCentreX(), area.getY() + underlineOffset }));
            }
        }
    }

    void mouseMove (const juce::MouseEvent&) override { repaint(); }

    void mouseUp (const juce::MouseEvent& event) override
    {
        const auto index = indexAt (event.position);
        if (index >= 0 && onChoose)
            onChoose (index);
    }

private:
    juce::Rectangle<float> tabArea (int index) const
    {
        const auto width = static_cast<float> (getWidth()) / static_cast<float> (std::max (1, labels.size()));
        return { width * static_cast<float> (index), 0.0f, width, static_cast<float> (getHeight()) };
    }

    int indexAt (juce::Point<float> point) const
    {
        for (int i = 0; i < labels.size(); ++i)
            if (tabArea (i).contains (point))
                return i;
        return -1;
    }

    juce::StringArray labels, tooltips;
    int chosen = 0;
    juce::Colour colour = theme::accent;
};

} // namespace lucky
