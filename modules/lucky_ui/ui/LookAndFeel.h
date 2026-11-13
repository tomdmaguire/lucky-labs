#pragma once


namespace lucky
{

/** Flat dark look with the bundled Barlow typeface.
    Shared by every open editor via SharedResourcePointer, and installed as the default look while alive
    so that menus, tooltips and every default-named font also render in Barlow. */
class LuckyLookAndFeel final : public juce::LookAndFeel_V4
{
public:
    LuckyLookAndFeel();
    ~LuckyLookAndFeel() override;

    juce::Typeface::Ptr getTypefaceForFont (const juce::Font&) override;

    void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour& backgroundColour,
                               bool isMouseOver, bool isButtonDown) override;

    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;

    void drawButtonText (juce::Graphics&, juce::TextButton&, bool isMouseOver, bool isButtonDown) override;

    /** Callouts (a small panel pointing at the control that opened it): raised panel colour, a hairline outline
        and a soft shadow, instead of JUCE's black box with a white edge. */
    void drawCallOutBoxBackground (juce::CallOutBox&, juce::Graphics&, const juce::Path&, juce::Image&) override;
    int getCallOutBoxBorderSize (const juce::CallOutBox&) override { return 14; }
    float getCallOutBoxCornerSize (const juce::CallOutBox&) override { return 6.0f; }

private:
    juce::Typeface::Ptr regular, medium, semiBold;
};

} // namespace lucky
