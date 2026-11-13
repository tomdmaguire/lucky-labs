#pragma once

namespace lucky
{

/** An editor that shows a fixed-size view scaled to the window, keeps the aspect ratio, remembers the scale
    for new windows and installs the Lucky look. The derived editor owns the view and calls setView(). */
class ScaledEditor : public juce::AudioProcessorEditor
{
public:
    static constexpr float minScale = 0.75f;
    static constexpr float maxScale = 2.0f;
    static constexpr std::array<float, 4> scalePresets { 1.0f, 1.25f, 1.5f, 1.75f };

    ScaledEditor (juce::AudioProcessor&, int baseWidth, int baseHeight);

    /** Adds the view, sizes the window to the saved scale and makes it resizable. */
    void setView (juce::Component&);

    float getScale() const;
    void setScale (float);

    /** Adds 100% ... 175% items, ticking the current one. */
    void addWindowSizeMenu (juce::PopupMenu&);

    void resized() override;

private:
    juce::SharedResourcePointer<LuckyLookAndFeel> lookAndFeel;
    juce::SharedResourcePointer<Settings> settings;
    juce::Component* view = nullptr;
    const int baseWidth, baseHeight;
    bool sizeRestored = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScaledEditor)
};

} // namespace lucky
