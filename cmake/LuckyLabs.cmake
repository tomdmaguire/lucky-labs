# Shared code for the Lucky plugins. Include after JUCE is available:
#
#   set(LUCKY_LABS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lucky-labs" CACHE PATH "Lucky Labs shared code")
#   include("${LUCKY_LABS_DIR}/cmake/LuckyLabs.cmake")
#   target_link_libraries(MyPlugin PRIVATE lucky_ui lucky_dsp LuckyLabsFonts)
#
# lucky_ui needs LuckyLabsFonts linked to the same target (the look and feel embeds Barlow).

include_guard(GLOBAL)

set(LUCKY_LABS_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")

juce_add_module("${LUCKY_LABS_ROOT}/modules/lucky_ui")
juce_add_module("${LUCKY_LABS_ROOT}/modules/lucky_dsp")

juce_add_binary_data(LuckyLabsFonts
    HEADER_NAME LuckyLabsFonts.h
    NAMESPACE LuckyLabsFonts
    SOURCES
        "${LUCKY_LABS_ROOT}/Resources/Fonts/Barlow-Regular.ttf"
        "${LUCKY_LABS_ROOT}/Resources/Fonts/Barlow-Medium.ttf"
        "${LUCKY_LABS_ROOT}/Resources/Fonts/Barlow-SemiBold.ttf"
)
