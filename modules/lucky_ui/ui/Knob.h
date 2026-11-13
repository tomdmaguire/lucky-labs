#pragma once


namespace lucky
{

/** A labelled knob in the Lucky Seven style: label on top, value in the middle, a caption underneath.
    It works on an abstract value that the owner maps to and from a 0-1 position. The scale can stay the same
    while only part of it is usable (drawn as a brighter band), so different modes can be compared on one dial. */
class Knob final : public juce::Component,
                   public juce::SettableTooltipClient
{
public:
    enum class Look
    {
        /** Draggable. */
        normal,
        /** Shows a value the mode fixes: dotted ring, not draggable. */
        fixed,
        /** Shows a value that moves on its own: dotted ring, not draggable. */
        follows,
        /** Greyed out, no value. */
        unavailable,
    };

    struct Spec
    {
        juce::String label;
        Look look = Look::normal;
        std::function<float (float value)> toPosition = [] (float v) { return v; };
        std::function<float (float position)> fromPosition = [] (float p) { return p; };
        /** For a switched control, the values it clicks between (empty = continuous). */
        std::vector<float> stepValues;
        /** The stretch of the dial this control can reach, as positions; the rest of the ring stays faint. */
        float usableFrom = 0.0f, usableTo = 1.0f;
        /** A reference point marked with a tick on the ring (a position 0-1), e.g. the measured unit's own amount;
            negative for none. */
        float tickAt = -1.0f;
        /** A detent at the tick: positions this close to it (0-1) land exactly on it, so the reference is easy
            to find again by dragging. 0 for none. */
        float tickDetent = 0.0f;
        /** Labels at the two ends of the ring, e.g. "10 µs" and "100 ms". */
        juce::String startLabel, endLabel;
        float defaultValue = 0.0f;
        std::function<juce::String (float value)> text = [] (float v) { return juce::String (v); };
        std::function<juce::String (float value)> caption = [] (float) { return juce::String(); };
        /** Shown instead of the caption while the knob is held, e.g. what the value does ("Punchy"): useful while
            turning it, clutter the rest of the time. None if empty. */
        std::function<juce::String (float value)> heldCaption;
    };

    Knob();

    void setSpec (Spec);
    const Spec& getSpec() const noexcept { return spec; }

    /** Shows a value; doesn't call onChange. */
    void setValue (float);
    float getValue() const noexcept { return value; }

    void setColour (juce::Colour);

    /** Called with each new value while the user drags, scrolls or resets. */
    std::function<void (float value)> onChange;
    std::function<void()> onGestureStart, onGestureEnd;

    void paint (juce::Graphics&) override;
    void mouseDown (const juce::MouseEvent&) override;
    void mouseDrag (const juce::MouseEvent&) override;
    void mouseUp (const juce::MouseEvent&) override;
    void mouseDoubleClick (const juce::MouseEvent&) override;
    void mouseWheelMove (const juce::MouseEvent&, const juce::MouseWheelDetails&) override;

    static constexpr int labelHeight = 18, dialSize = 96, captionHeight = 18;

private:
    juce::Rectangle<float> dialBounds() const;
    bool editable() const noexcept { return spec.look == Look::normal; }
    void moveTo (float position);
    void nudge (int direction);
    void change (float newValue);

    Spec spec;
    float value = 0.0f, dragStartPosition = 0.0f;
    bool held = false;
    juce::Colour colour = theme::accent;
};

} // namespace lucky
