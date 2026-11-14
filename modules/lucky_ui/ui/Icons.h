#pragma once

namespace lucky
{

/** Three dots for the top bar's menu button, as on Lucky Seven. */
inline std::unique_ptr<juce::Drawable> makeMenuIcon (juce::Colour colour)
{
    juce::Path path;
    for (const auto x : { 4.0f, 11.0f, 18.0f })
        path.addEllipse (x - 1.6f, 9.4f, 3.2f, 3.2f);

    auto drawable = std::make_unique<juce::DrawablePath>();
    drawable->setPath (path);
    drawable->setFill (colour);
    return drawable;
}

/** Sets up a DrawableButton as the top bar's ••• menu button; edgeIndent sets the icon's inset in its cell. */
inline void setUpMenuButton (juce::DrawableButton& button, int edgeIndent = 17)
{
    const auto idle = makeMenuIcon (theme::textDim);
    const auto hover = makeMenuIcon (theme::text);
    button.setImages (idle.get(), hover.get());
    button.setEdgeIndent (edgeIndent);
    button.setWantsKeyboardFocus (false);
}

} // namespace lucky
