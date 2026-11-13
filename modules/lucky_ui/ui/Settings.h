#pragma once

namespace lucky
{

/** Settings shared by every instance of one plugin, stored in ~/Library/Application Support/<plugin name>.
    Construct through juce::SharedResourcePointer so all open editors share one file. */
class Settings
{
public:
#ifdef JucePlugin_Name
    Settings() : Settings (JucePlugin_Name) {}
#endif

    explicit Settings (const juce::String& pluginName)
    {
        juce::PropertiesFile::Options options;
        options.applicationName = pluginName;
        options.filenameSuffix = ".settings";
        options.folderName = pluginName;
        options.osxLibrarySubFolder = "Application Support";
        options.millisecondsBeforeSaving = 1000;
        properties.setStorageParameters (options);
    }

    /** The editor scale last chosen, 1.0 by default. */
    float getUiScale() const { return static_cast<float> (file().getDoubleValue ("uiScale", 1.0)); }

    /** Remembers the editor scale for new windows. */
    void setUiScale (float scale)
    {
        if (! juce::approximatelyEqual (getUiScale(), scale))
            file().setValue ("uiScale", scale);
    }

    bool getBool (juce::StringRef key, bool fallback) const { return file().getBoolValue (key, fallback); }
    void setBool (juce::StringRef key, bool value) { file().setValue (key, value); }

    juce::String getString (juce::StringRef key, const juce::String& fallback = {}) const { return file().getValue (key, fallback); }
    void setString (juce::StringRef key, const juce::String& value) { file().setValue (key, value); }

private:
    juce::PropertiesFile& file() const { return *properties.getUserSettings(); }

    mutable juce::ApplicationProperties properties;
};

} // namespace lucky
