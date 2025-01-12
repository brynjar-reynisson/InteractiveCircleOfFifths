/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace std;
using namespace juce;
using namespace BinaryData;

static bool darkMode = false;
static bool halfWidth = false;
static bool circleModeDoRe = false;
static Colour darkModeForegroundColour(236, 236, 236);
static Colour darkModeBackgroundColour(36, 33, 33);
static Colour darkModeSelectedBackgroundColour(95, 95, 95);

static const String NOTES = "Notes";
static const String IONIAN = "Ionian (Major)";
static const String DORIAN = "Dorian";
static const String PHRYGIAN = "Phrygian";
static const String LYDIAN = "Lydian";
static const String MIXOLYDIAN = "Mixolydian";
static const String AEOLIAN = "Aeolian (Nat. minor)";
static const String LOCRIAN = "Locrian";
static const String HARMONIC_MINOR = "Harmonic minor";
static const String MELODIC_MINOR = "Melodic minor";

static std::vector<String> modes {
    NOTES,
    IONIAN,
    DORIAN,
    PHRYGIAN,
    LYDIAN,
    MIXOLYDIAN,
    AEOLIAN,
    LOCRIAN,
    HARMONIC_MINOR,
    MELODIC_MINOR
};

/*
enum SVGType
{
    Circle_C = 0,
    Circle_Do,
    Aeolian,
    Dorian,
    Ionian,
    Locrian,
    Lydian,
    Mixolydian,
    Phrygian,
    Modes_7ths,
    Modes_Background,
    Modes_Triads,
    Harmonic_minor,
    Harmonic_minor_7ths,
    Harmonic_minor_Background,
    Harmonic_minor_Triads,
    Melodic_minor,
    Melodic_minor_7ths,
    Melodic_minor_Background,
    Melodic_minor_Triads
};
*/

enum TriadsAndSevenths
{
    None,
    Triads,
    Sevenths
};

struct TriadsAndSeventhsState
{
    TriadsAndSevenths mode;
    String buttonText;
    String buttonTooltip;
};

static TriadsAndSeventhsState NONE = { None, " ", "Show triads" };
static TriadsAndSeventhsState TRIADS = { Triads, "T", "Show sevenths"};
static TriadsAndSeventhsState SEVENTHS = { Sevenths, "7", "Don't show triads and sevenths"};
static TriadsAndSeventhsState* currentTriadsAndSeventhsState = &SEVENTHS;

static const unique_ptr<Drawable> svg(const char* data, size_t numBytes)
{
    return Drawable::createFromImageData(data, numBytes);
}


//==============================================================================
class SVGManager
{
public:
    SVGManager();
    Drawable* getCircleSvg();
    Drawable* getModeBackground(String mode);
    Drawable* getModeImage(String mode);
    Drawable* getModeTriads(String mode);
    Drawable* getModeSevenths(String mode);

private:
    void replaceWrongDarkModeColour();

    std::unique_ptr<Drawable> dmAeolian = svg(DM_Aeolian_svg, DM_Aeolian_svgSize);

    std::unique_ptr<Drawable> lmCircleC = svg(LM_Notes_circle_C_svg, LM_Notes_circle_C_svgSize);
    std::unique_ptr<Drawable> lmCircleDo = svg(LM_Notes_circle_Do_svg, LM_Notes_circle_Do_svgSize);
    std::unique_ptr<Drawable> lmAeolian = svg(LM_Aeolian_svg, LM_Aeolian_svgSize);
    std::unique_ptr<Drawable> lmDorian = svg(LM_Dorian_svg, LM_Dorian_svgSize);
    std::unique_ptr<Drawable> lmIonian = svg(LM_Ionian_svg, LM_Ionian_svgSize);
    std::unique_ptr<Drawable> lmLocrian = svg(LM_Locrian_svg, LM_Locrian_svgSize);
    std::unique_ptr<Drawable> lmLydian = svg(LM_Lydian_svg, LM_Lydian_svgSize);
    std::unique_ptr<Drawable> lmMixolydian = svg(LM_Mixolydian_svg, LM_Mixolydian_svgSize);
    std::unique_ptr<Drawable> lmPhrygian = svg(LM_Phrygian_svg, LM_Phrygian_svgSize);
    std::unique_ptr<Drawable> lmModesBackground = svg(LM_Modes_Background_svg, LM_Modes_Background_svgSize);
    std::unique_ptr<Drawable> lmModesTriads = svg(LM_Modes_Triads_svg, LM_Modes_Triads_svgSize);
    std::unique_ptr<Drawable> lmModes7ths = svg(LM_Modes_7ths_svg, LM_Modes_7ths_svgSize);
    std::unique_ptr<Drawable> lmHarmonicMinor = svg(LM_Harmonic_minor_svg, LM_Harmonic_minor_svgSize);
    std::unique_ptr<Drawable> lmHarmonicMinorBackground = svg(LM_Harmonic_minor_Background_svg, LM_Harmonic_minor_Background_svgSize);
    std::unique_ptr<Drawable> lmHarmonicMinorTriads = svg(LM_Harmonic_minor_Triads_svg, LM_Harmonic_minor_Triads_svgSize);
    std::unique_ptr<Drawable> lmHarmonicMinor7ths = svg(LM_Harmonic_minor_7ths_svg, LM_Harmonic_minor_7ths_svgSize);
    std::unique_ptr<Drawable> lmMelodicMinor = svg(LM_Melodic_minor_svg, LM_Melodic_minor_svgSize);
    std::unique_ptr<Drawable> lmMelodicMinorBackground = svg(LM_Melodic_minor_Background_svg, LM_Melodic_minor_Background_svgSize);
    std::unique_ptr<Drawable> lmMelodicMinorTriads = svg(LM_Melodic_minor_Triads_svg, LM_Melodic_minor_Triads_svgSize);
    std::unique_ptr<Drawable> lmMelodicMinor7ths = svg(LM_Melodic_minor_7ths_svg, LM_Melodic_minor_7ths_svgSize);

    std::unique_ptr<Drawable> dmCircleC = svg(DM_Notes_circle_C_svg, DM_Notes_circle_C_svgSize);
    std::unique_ptr<Drawable> dmCircleDo = svg(DM_Notes_circle_Do_svg, DM_Notes_circle_Do_svgSize);
    std::unique_ptr<Drawable> dmDorian = svg(DM_Dorian_svg, DM_Dorian_svgSize);
    std::unique_ptr<Drawable> dmIonian = svg(DM_Ionian_svg, DM_Ionian_svgSize);
    std::unique_ptr<Drawable> dmLocrian = svg(DM_Locrian_svg, DM_Locrian_svgSize);
    std::unique_ptr<Drawable> dmLydian = svg(DM_Lydian_svg, DM_Lydian_svgSize);
    std::unique_ptr<Drawable> dmMixolydian = svg(DM_Mixolydian_svg, DM_Mixolydian_svgSize);
    std::unique_ptr<Drawable> dmPhrygian = svg(DM_Phrygian_svg, DM_Phrygian_svgSize);
    std::unique_ptr<Drawable> dmModesBackground = svg(DM_Modes_Background_svg, DM_Modes_Background_svgSize);
    std::unique_ptr<Drawable> dmModesTriads = svg(DM_Modes_Triads_svg, DM_Modes_Triads_svgSize);
    std::unique_ptr<Drawable> dmModes7ths = svg(DM_Modes_7ths_svg, DM_Modes_7ths_svgSize);
    std::unique_ptr<Drawable> dmHarmonicMinor = svg(DM_Harmonic_minor_svg, DM_Harmonic_minor_svgSize);
    std::unique_ptr<Drawable> dmHarmonicMinorBackground = svg(DM_Harmonic_minor_Background_svg, DM_Harmonic_minor_Background_svgSize);
    std::unique_ptr<Drawable> dmHarmonicMinorTriads = svg(DM_Harmonic_minor_Triads_svg, DM_Harmonic_minor_Triads_svgSize);
    std::unique_ptr<Drawable> dmHarmonicMinor7ths = svg(DM_Harmonic_minor_7ths_svg, DM_Harmonic_minor_7ths_svgSize);
    std::unique_ptr<Drawable> dmMelodicMinor = svg(DM_Melodic_minor_svg, DM_Melodic_minor_svgSize);
    std::unique_ptr<Drawable> dmMelodicMinorBackground = svg(DM_Melodic_minor_Background_svg, DM_Melodic_minor_Background_svgSize);
    std::unique_ptr<Drawable> dmMelodicMinorTriads = svg(DM_Melodic_minor_Triads_svg, DM_Melodic_minor_Triads_svgSize);
    std::unique_ptr<Drawable> dmMelodicMinor7ths = svg(DM_Melodic_minor_7ths_svg, DM_Melodic_minor_7ths_svgSize);

};


//==============================================================================
class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
    }

    void setLightModeLookAndFeel();
    void setDarkModeLookAndFeel();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider);
    void drawComboBox(Graphics& g, int width, int height, bool,
        int, int, int, int, ComboBox& box);
    int getSliderPopupPlacement(Slider& slider)
    {
        return BubbleComponent::below;
    }

private:
    bool darkMode = false;
};


//==============================================================================
class CircleComponent : public Component
{
public:
    CircleComponent(ComboBox* modeMenu);
    void paint(Graphics& g);
    void mouseDown(const MouseEvent& event) override;
    void newCircleDegreeSelected(float deg);

private:
    const std::unique_ptr<Drawable> lmModesGeneralBackgroundSvg = Drawable::createFromImageData(BinaryData::Modes_general_background_svg, BinaryData::Modes_general_background_svgSize);
    const std::unique_ptr<Drawable> lmNotesCircleSvg = Drawable::createFromImageData(BinaryData::Notes_circle_svg, BinaryData::Notes_circle_svgSize);

    const std::unique_ptr<Drawable> lmModeLydianSvg = Drawable::createFromImageData(BinaryData::Mode_Lydian_svg, BinaryData::Mode_Lydian_svgSize);
    const std::unique_ptr<Drawable> lmModeDorianSvg = Drawable::createFromImageData(BinaryData::Mode_Dorian_svg, BinaryData::Mode_Dorian_svgSize);
    const std::unique_ptr<Drawable> lmModeLocrianSvg = Drawable::createFromImageData(BinaryData::Mode_Locrian_svg, BinaryData::Mode_Locrian_svgSize);
    const std::unique_ptr<Drawable> lmModeAeolianSvg = Drawable::createFromImageData(BinaryData::Mode_Aeolian_svg, BinaryData::Mode_Aeolian_svgSize);
    const std::unique_ptr<Drawable> lmModeIonianSvg = Drawable::createFromImageData(BinaryData::Mode_Ionian_svg, BinaryData::Mode_Ionian_svgSize);
    const std::unique_ptr<Drawable> lmModePhrygianSvg = Drawable::createFromImageData(BinaryData::Mode_Phrygian_svg, BinaryData::Mode_Phrygian_svgSize);
    const std::unique_ptr<Drawable> lmModeMixolydianSvg = Drawable::createFromImageData(BinaryData::Mode_Mixolydian_svg, BinaryData::Mode_Mixolydian_svgSize);

    std::vector<Drawable*> lmModes{
        nullptr,
        lmModeLydianSvg.get(),
        lmModeDorianSvg.get(),
        lmModeLocrianSvg.get(),
        lmModeAeolianSvg.get(),
        lmModeIonianSvg.get(),
        lmModePhrygianSvg.get(),
        lmModeMixolydianSvg.get()    
    };

    const unique_ptr<Drawable> dmNotesCircleSvg = svg(Notes_circle_Dark_mode_svg, Notes_circle_Dark_mode_svgSize);

    float selectedRadians = 0;
    int selectedNoteIndex = 0;
    int selectedCircleIndex = 0;
    std::map<int, int> noteToCircleIndexMap;
    ComboBox* modeMenu;
    SVGManager svgManager;
};
//==============================================================================
class InteractiveCircleOfFifthsAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Button::Listener
{
public:
    InteractiveCircleOfFifthsAudioProcessorEditor (InteractiveCircleOfFifthsAudioProcessor&);
    ~InteractiveCircleOfFifthsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void modeMenuChanged();
    void buttonClicked(juce::Button* button) override;
    bool keyPressed(const KeyPress& k) override;
private:
    void setSeventhsButtonNextState();
    void updateModeMenuSelection(bool up);
    void updateConstrainer();
    void toggleHalfWidth();

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    InteractiveCircleOfFifthsAudioProcessor& audioProcessor;

    ComboBox modeMenu;
    TextButton circleModeButton;
    TextButton seventhsButton;
    TextButton darkModeButton;
    TextButton halfWidthButton;
    CircleComponent circleComponent;
    TooltipWindow tooltipWindow{ this }; // instance required for ToolTips to work
    ComponentBoundsConstrainer constrainer;

    CustomLookAndFeel darkLookAndFeel;
    CustomLookAndFeel lightLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InteractiveCircleOfFifthsAudioProcessorEditor)
};

static int getButtonHeight(juce::Rectangle<int> bounds)
{
    int minButtonHeight = 17;
    int calculatedButtonHeight = bounds.getWidth() * 0.05;
    return std::max((int)calculatedButtonHeight, minButtonHeight);
}
