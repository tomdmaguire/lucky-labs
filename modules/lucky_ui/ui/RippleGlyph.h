#pragma once


namespace lucky
{

/** The Lucky family logo: a dot sending out three rings that fade as they spread. */
namespace ripple
{
/** Draws the logo in a square, in the given colour. */
inline void paint (juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour colour)
{
    const auto scale = bounds.getWidth() / 64.0f;
    const auto centre = bounds.getCentre();

    struct Ring { float radius, alpha; };
    static constexpr Ring rings[] { { 11.5f, 0.75f }, { 18.0f, 0.45f }, { 24.5f, 0.2f } };

    for (const auto& ring : rings)
    {
        const auto radius = ring.radius * scale;
        g.setColour (colour.withMultipliedAlpha (ring.alpha));
        g.drawEllipse (juce::Rectangle<float> (radius * 2.0f, radius * 2.0f).withCentre (centre), 3.0f * scale);
    }

    const auto dot = 5.0f * scale;
    g.setColour (colour);
    g.fillEllipse (juce::Rectangle<float> (dot * 2.0f, dot * 2.0f).withCentre (centre));
}
} // namespace ripple

} // namespace lucky
