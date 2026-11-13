#pragma once

namespace lucky
{

/** A small circled "i" that explains the thing next to it in its tooltip, shown as soon as the mouse is over it
    (through the editor's TooltipWindow, which shows other tooltips after its usual delay). */
class InfoDot final : public juce::Component,
                      public juce::SettableTooltipClient
{
public:
    static constexpr int size = 16;

    InfoDot()
    {
        setRepaintsOnMouseActivity (true);
        setWantsKeyboardFocus (false);
    }

    void paint (juce::Graphics& g) override
    {
        const auto bounds = getLocalBounds().toFloat().reduced (1.0f);
        const auto colour = isMouseOver() ? theme::text : theme::textDim;
        g.setColour (colour.withAlpha (0.8f));
        g.drawEllipse (bounds, 1.0f);
        g.setFont (juce::FontOptions (10.0f).withStyle ("Bold"));
        g.drawText ("i", bounds.translated (0.0f, 0.5f), juce::Justification::centred);
    }

    void mouseEnter (const juce::MouseEvent&) override
    {
        if (auto* window = findTooltipWindow(); window != nullptr && getTooltip().isNotEmpty())
            window->displayTip (getScreenBounds().getCentre(), getTooltip());
    }

    void mouseExit (const juce::MouseEvent&) override
    {
        if (auto* window = findTooltipWindow())
            window->hideTip();
    }

private:
    juce::TooltipWindow* findTooltipWindow() const
    {
        for (auto* ancestor = getParentComponent(); ancestor != nullptr; ancestor = ancestor->getParentComponent())
            for (auto* child : ancestor->getChildren())
                if (auto* window = dynamic_cast<juce::TooltipWindow*> (child))
                    return window;
        return nullptr;
    }
};

} // namespace lucky
