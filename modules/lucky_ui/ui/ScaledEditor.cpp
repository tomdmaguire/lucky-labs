namespace lucky
{

ScaledEditor::ScaledEditor (juce::AudioProcessor& owner, int width, int height)
    : AudioProcessorEditor (owner), baseWidth (width), baseHeight (height)
{
}

void ScaledEditor::setView (juce::Component& content)
{
    view = &content;
    addAndMakeVisible (content);

    setResizable (true, true);
    setResizeLimits (juce::roundToInt (static_cast<float> (baseWidth) * minScale), juce::roundToInt (static_cast<float> (baseHeight) * minScale),
                     juce::roundToInt (static_cast<float> (baseWidth) * maxScale), juce::roundToInt (static_cast<float> (baseHeight) * maxScale));
    getConstrainer()->setFixedAspectRatio (static_cast<double> (baseWidth) / baseHeight);

    setScale (juce::jlimit (minScale, maxScale, settings->getUiScale()));
    sizeRestored = true;
}

float ScaledEditor::getScale() const
{
    return static_cast<float> (getWidth()) / static_cast<float> (baseWidth);
}

void ScaledEditor::setScale (float scale)
{
    setSize (juce::roundToInt (static_cast<float> (baseWidth) * scale), juce::roundToInt (static_cast<float> (baseHeight) * scale));
}

void ScaledEditor::addWindowSizeMenu (juce::PopupMenu& menu)
{
    juce::PopupMenu sizes;
    const auto current = getScale();
    for (const auto preset : scalePresets)
        sizes.addItem (juce::String (juce::roundToInt (preset * 100.0f)) + "%", true, std::abs (current - preset) < 0.01f,
                       [safe = juce::Component::SafePointer<ScaledEditor> (this), preset]
                       {
                           if (safe != nullptr)
                               safe->setScale (preset);
                       });
    menu.addSubMenu ("Window size", sizes);
}

void ScaledEditor::resized()
{
    if (view == nullptr)
        return;

    const auto scale = getScale();
    view->setBounds (0, 0, baseWidth, baseHeight);
    view->setTransform (juce::AffineTransform::scale (scale));

    if (sizeRestored)
        settings->setUiScale (scale);
}

} // namespace lucky
