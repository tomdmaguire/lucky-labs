#pragma once

namespace lucky
{

/** A panel over the main view while a key-toggled state is on, such as hearing the input unprocessed: a title, a
    line on what you hear, "Press [key] to switch back and forth", and a button that turns it off (some hosts keep
    key presses for themselves). The plugin greys out its accents (theme::greyedOut) while it shows. */
class ToggleNotice final : public juce::Component
{
public:
    static constexpr int width = 360, height = 140;

    ToggleNotice (const juce::String& titleText, const juce::String& keyToShow, const juce::String& buttonText)
        : title (titleText), key (keyToShow), button (buttonText)
    {
        button.getProperties().set ("outline", true);
        button.getProperties().set ("primary", true);
        button.setColour (juce::Slider::rotarySliderFillColourId, theme::text);
        button.setWantsKeyboardFocus (false);
        button.setMouseCursor (juce::MouseCursor::PointingHandCursor);
        button.onClick = [this] { if (onTurnOff) onTurnOff(); };
        addAndMakeVisible (button);
        setSize (width, height);
    }

    /** Called by the button. */
    std::function<void()> onTurnOff;

    /** The line under the title, saying what you hear. */
    void setBody (const juce::String& text)
    {
        if (body != text)
        {
            body = text;
            repaint();
        }
    }

    void paint (juce::Graphics& g) override
    {
        const auto bounds = getLocalBounds().toFloat().reduced (0.5f);
        g.setColour (theme::panelRaised.withAlpha (0.96f));
        g.fillRoundedRectangle (bounds, 6.0f);
        g.setColour (theme::outline.brighter (0.2f));
        g.drawRoundedRectangle (bounds, 6.0f, 1.0f);

        auto area = getLocalBounds().toFloat().reduced (16.0f, 14.0f);
        g.setColour (theme::text);
        g.setFont (theme::labelFont (14.0f).withStyle ("Bold"));
        g.drawText (title.toUpperCase(), area.removeFromTop (20.0f), juce::Justification::centred);
        area.removeFromTop (6.0f);

        const auto font = juce::FontOptions (13.5f);
        g.setColour (theme::textDim);
        g.setFont (font);
        g.drawFittedText (body, area.removeFromTop (20.0f).toNearestInt(), juce::Justification::centred, 1, 0.9f);
        area.removeFromTop (4.0f);

        const auto line = area.removeFromTop (22.0f);
        const juce::String before ("Press"), after ("to switch back and forth");
        const auto beforeWidth = juce::GlyphArrangement::getStringWidth (font, before);
        const auto afterWidth = juce::GlyphArrangement::getStringWidth (font, after);
        const auto capWidth = keycapWidth (key, 18.0f);
        auto x = line.getCentreX() - (beforeWidth + capWidth + afterWidth + 12.0f) * 0.5f;
        g.drawText (before, juce::Rectangle<float> (x, line.getY(), beforeWidth + 1.0f, line.getHeight()), juce::Justification::centredLeft);
        x += beforeWidth + 6.0f;
        paintKeycap (g, { x, line.getCentreY() - 9.0f, capWidth, 18.0f }, key);
        x += capWidth + 6.0f;
        g.setColour (theme::textDim);
        g.setFont (font);
        g.drawText (after, juce::Rectangle<float> (x, line.getY(), afterWidth + 1.0f, line.getHeight()), juce::Justification::centredLeft);
    }

    void resized() override
    {
        button.setBounds (getLocalBounds().removeFromBottom (14 + 28).removeFromTop (28).withSizeKeepingCentre (170, 28));
    }

private:
    juce::String title, body, key;
    juce::TextButton button;
};

} // namespace lucky
