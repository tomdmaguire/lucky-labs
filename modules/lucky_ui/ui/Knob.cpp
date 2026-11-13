
namespace lucky
{
namespace
{
constexpr float startAngle = juce::degreesToRadians (-140.0f);
constexpr float endAngle = juce::degreesToRadians (140.0f);
constexpr float ringRadius = 38.0f;
constexpr float labelOutset = 14.0f;

float angleAt (float position)
{
    return startAngle + juce::jlimit (0.0f, 1.0f, position) * (endAngle - startAngle);
}
} // namespace

Knob::Knob()
{
    setWantsKeyboardFocus (false);
}

void Knob::setSpec (Spec newSpec)
{
    spec = std::move (newSpec);
    setMouseCursor (editable() ? juce::MouseCursor::UpDownResizeCursor : juce::MouseCursor::NormalCursor);
    repaint();
}

void Knob::setValue (float newValue)
{
    if (! juce::approximatelyEqual (value, newValue))
    {
        value = newValue;
        repaint();
    }
}

void Knob::setColour (juce::Colour newColour)
{
    colour = newColour;
    repaint();
}

juce::Rectangle<float> Knob::dialBounds() const
{
    return getLocalBounds().toFloat().withTrimmedTop (labelHeight).withHeight (dialSize).withSizeKeepingCentre (dialSize, dialSize);
}

void Knob::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds().toFloat();
    g.setColour (theme::textDim);
    g.setFont (theme::labelFont (12.0f));
    g.drawText (spec.label.toUpperCase(), bounds.withHeight (labelHeight), juce::Justification::centred);

    const auto dial = dialBounds();
    const auto centre = dial.getCentre();
    const auto unavailable = spec.look == Look::unavailable;
    const auto shown = unavailable ? theme::textDim : colour;
    const auto position = juce::jlimit (0.0f, 1.0f, spec.toPosition (value));
    const auto angle = angleAt (position);

    g.setColour (shown.withAlpha (0.07f));
    g.fillEllipse (juce::Rectangle<float> (ringRadius * 2.0f + 4.0f, ringRadius * 2.0f + 4.0f).withCentre (centre));

    const auto banded = spec.look == Look::normal && (spec.usableFrom > 0.001f || spec.usableTo < 0.999f);
    juce::Path ring;
    ring.addCentredArc (centre.x, centre.y, ringRadius, ringRadius, 0.0f, startAngle, endAngle, true);
    g.setColour (shown.withAlpha (banded ? 0.08f : 0.25f));
    if (spec.look == Look::fixed || spec.look == Look::follows)
    {
        juce::Path dotted;
        const float dashes[] { 2.0f, 4.0f };
        juce::PathStrokeType (1.5f).createDashedStroke (dotted, ring, dashes, 2);
        g.fillPath (dotted);
    }
    else
    {
        g.strokePath (ring, juce::PathStrokeType (1.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    if (banded)
    {
        juce::Path band;
        band.addCentredArc (centre.x, centre.y, ringRadius, ringRadius, 0.0f, angleAt (spec.usableFrom), angleAt (spec.usableTo), true);
        g.setColour (colour.withAlpha (0.45f));
        g.strokePath (band, juce::PathStrokeType (2.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    if (spec.look == Look::normal && spec.tickAt >= 0.0f)
    {
        g.setColour (theme::text.withAlpha (0.6f));
        const auto outer = centre.getPointOnCircumference (ringRadius + 5.0f, angleAt (spec.tickAt));
        const auto inner = centre.getPointOnCircumference (ringRadius + 1.5f, angleAt (spec.tickAt));
        g.drawLine ({ inner, outer }, 1.5f);
    }

    if (spec.look == Look::normal)
    {
        g.setColour (colour.withAlpha (0.55f));
        for (const auto step : spec.stepValues)
            g.fillEllipse (juce::Rectangle<float> (3.0f, 3.0f).withCentre (centre.getPointOnCircumference (ringRadius, angleAt (spec.toPosition (step)))));
    }

    if (! unavailable)
    {
        const auto arcColour = spec.look == Look::normal ? colour : colour.withAlpha (0.6f);
        const auto arcStart = banded ? spec.usableFrom : 0.0f;
        if (position > arcStart + 0.002f)
        {
            juce::Path arc;
            arc.addCentredArc (centre.x, centre.y, ringRadius, ringRadius, 0.0f, angleAt (arcStart), angle, true);
            g.setColour (arcColour);
            g.strokePath (arc, juce::PathStrokeType (2.5f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        }
        g.setColour (arcColour);
        g.fillEllipse (juce::Rectangle<float> (7.0f, 7.0f).withCentre (centre.getPointOnCircumference (ringRadius, angle)));
    }

    g.setColour (unavailable ? theme::textDim : theme::text);
    g.setFont (theme::labelFont (14.0f));
    g.drawText (unavailable ? format::emDash : spec.text (value),
                dial.reduced (12.0f), juce::Justification::centred);

    g.setColour (theme::textDim.withAlpha (0.8f));
    g.setFont (theme::labelFont (10.0f));
    for (const auto& [label, endAngleOfLabel] : { std::pair { spec.startLabel, startAngle }, std::pair { spec.endLabel, endAngle } })
    {
        if (label.isEmpty())
            continue;
        const auto at = centre.getPointOnCircumference (ringRadius, endAngleOfLabel);
        const auto outward = endAngleOfLabel < 0.0f ? -labelOutset : labelOutset;
        g.drawText (label, juce::Rectangle<float> (56.0f, 12.0f).withCentre ({ at.x + outward, at.y + 10.0f }), juce::Justification::centred);
    }

    g.setColour (theme::textDim);
    g.setFont (theme::labelFont (12.0f));
    g.drawText (held && spec.heldCaption ? spec.heldCaption (value) : spec.caption (value), bounds.withTop (dial.getBottom() + 2.0f).withHeight (captionHeight),
                juce::Justification::centred);
}

void Knob::change (float newValue)
{
    if (juce::approximatelyEqual (newValue, value))
        return;
    value = newValue;
    repaint();
    if (onChange)
        onChange (value);
}

void Knob::moveTo (float position)
{
    if (spec.stepValues.empty())
    {
        const auto snapped = spec.tickAt >= 0.0f && std::abs (position - spec.tickAt) < spec.tickDetent ? spec.tickAt : position;
        change (spec.fromPosition (juce::jlimit (spec.usableFrom, spec.usableTo, snapped)));
        return;
    }

    const auto nearest = std::min_element (spec.stepValues.begin(), spec.stepValues.end(), [&] (float a, float b)
                                           { return std::abs (spec.toPosition (a) - position) < std::abs (spec.toPosition (b) - position); });
    change (*nearest);
}

void Knob::nudge (int direction)
{
    if (spec.stepValues.empty())
    {
        moveTo (spec.toPosition (value) + 0.02f * static_cast<float> (direction));
        return;
    }

    const auto here = std::min_element (spec.stepValues.begin(), spec.stepValues.end(), [this] (float a, float b)
                                        { return std::abs (spec.toPosition (a) - spec.toPosition (value)) < std::abs (spec.toPosition (b) - spec.toPosition (value)); });
    const auto index = juce::jlimit (0, static_cast<int> (spec.stepValues.size()) - 1, static_cast<int> (here - spec.stepValues.begin()) + direction);
    change (spec.stepValues[static_cast<size_t> (index)]);
}

void Knob::mouseDown (const juce::MouseEvent&)
{
    if (! editable())
        return;
    dragStartPosition = spec.toPosition (value);
    held = true;
    repaint();
    if (onGestureStart)
        onGestureStart();
}

void Knob::mouseDrag (const juce::MouseEvent& event)
{
    if (! editable())
        return;
    const auto pixelsPerRange = event.mods.isShiftDown() ? 800.0f : 200.0f;
    moveTo (dragStartPosition - static_cast<float> (event.getDistanceFromDragStartY()) / pixelsPerRange);
}

void Knob::mouseUp (const juce::MouseEvent&)
{
    if (held)
    {
        held = false;
        repaint();
    }
    if (editable() && onGestureEnd)
        onGestureEnd();
}

void Knob::mouseDoubleClick (const juce::MouseEvent&)
{
    if (! editable())
        return;
    if (onGestureStart)
        onGestureStart();
    moveTo (spec.toPosition (spec.defaultValue));
    if (onGestureEnd)
        onGestureEnd();
}

void Knob::mouseWheelMove (const juce::MouseEvent&, const juce::MouseWheelDetails& wheel)
{
    if (! editable() || juce::approximatelyEqual (wheel.deltaY, 0.0f))
        return;
    if (onGestureStart)
        onGestureStart();
    if (spec.stepValues.empty())
        moveTo (spec.toPosition (value) + wheel.deltaY * 0.3f);
    else
        nudge (wheel.deltaY > 0.0f ? 1 : -1);
    if (onGestureEnd)
        onGestureEnd();
}

} // namespace lucky
