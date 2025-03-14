/*
  ==============================================================================

   This file is part of the InteractiveCircleOfFifths plugin code.
   Copyright (c) Brynjar Reynisson

   The code included in this file is provided under the terms of the ISC license
   http://www.isc.org/downloads/software-support-policy/isc-license. Permission
   to use, copy, modify, and/or distribute this software for any purpose with or
   without fee is hereby granted provided that the above copyright notice and
   this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
   REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
   AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
   INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
   PERFORMANCE OF THIS SOFTWARE.

  ==============================================================================
*/
/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define M_PI       3.14159265358979323846

//==============================================================================

SVGManager::SVGManager()
{
    replaceWrongDarkModeColour();
}

Drawable* SVGManager::getCircleSvg()
{
    if (darkMode)
    {
        return !circleModeDoRe ?
            dmCircleC.get() :
            dmCircleDo.get();
    }
    else
    {
        return !circleModeDoRe ?
            lmCircleC.get() :
            lmCircleDo.get();
    }
}

Drawable* SVGManager::getModeBackground(String mode)
{
    if (mode == HARMONIC_MINOR)
        return darkMode ? dmHarmonicMinorBackground.get() : lmHarmonicMinorBackground.get();
    else if (mode == MELODIC_MINOR)
        return darkMode ? dmMelodicMinorBackground.get() : lmMelodicMinorBackground.get();
    else
        return darkMode ? dmModesBackground.get() : lmModesBackground.get();
}

Drawable* SVGManager::getModeImage(String mode)
{
    Drawable* drawable = nullptr;
    if (mode == HARMONIC_MINOR)
        drawable = darkMode ? dmHarmonicMinor.get() : lmHarmonicMinor.get();
    else if (mode == MELODIC_MINOR)
        drawable = darkMode ? dmMelodicMinor.get() : lmMelodicMinor.get();
    else if (mode == IONIAN)
        drawable = darkMode ? dmIonian.get() : lmIonian.get();
    else if (mode == DORIAN)
        drawable = darkMode ? dmDorian.get() : lmDorian.get();
    else if (mode == PHRYGIAN)
        drawable = darkMode ? dmPhrygian.get() : lmPhrygian.get();
    else if (mode == LYDIAN)
        drawable = darkMode ? dmLydian.get() : lmLydian.get();
    else if (mode == MIXOLYDIAN)
        drawable = darkMode ? dmMixolydian.get() : lmMixolydian.get();
    else if (mode == AEOLIAN)
        drawable = darkMode ? dmAeolian.get() : lmAeolian.get();
    else if (mode == LOCRIAN)
        drawable = darkMode ? dmLocrian.get() : lmLocrian.get();
    return drawable;
}

Drawable* SVGManager::getModeTriads(String mode)
{
    if (mode == HARMONIC_MINOR)
        return darkMode ? dmHarmonicMinorTriads.get() : lmHarmonicMinorTriads.get();
    else if (mode == MELODIC_MINOR)
        return darkMode ? dmMelodicMinorTriads.get() : lmMelodicMinorTriads.get();
    else
        return darkMode ? dmModesTriads.get() : lmModesTriads.get();
    return nullptr;
}
Drawable* SVGManager::getModeSevenths(String mode)
{
    if (mode == HARMONIC_MINOR)
        return darkMode ? dmHarmonicMinor7ths.get() : lmHarmonicMinor7ths.get();
    else if (mode == MELODIC_MINOR)
        return darkMode ? dmMelodicMinor7ths.get() : lmMelodicMinor7ths.get();
    else
        return darkMode ? dmModes7ths.get() : lmModes7ths.get();
    return nullptr;
}

static Colour wrongDarkModeColour((uint8)41, (uint8)43, (uint8)44, (uint8)255);
static void replaceDarkModeColour(Drawable* drawable)
{
    bool found = drawable->replaceColour(wrongDarkModeColour, darkModeBackgroundColour);
}

void SVGManager::replaceWrongDarkModeColour()
{
    replaceDarkModeColour(dmCircleC.get());
    replaceDarkModeColour(dmCircleDo.get());
    replaceDarkModeColour(dmAeolian.get());
    replaceDarkModeColour(dmDorian.get());
    replaceDarkModeColour(dmIonian.get());
    replaceDarkModeColour(dmLocrian.get());
    replaceDarkModeColour(dmLydian.get());
    replaceDarkModeColour(dmMixolydian.get());
    replaceDarkModeColour(dmPhrygian.get());
    replaceDarkModeColour(dmModesBackground.get());
    replaceDarkModeColour(dmModesTriads.get());
    replaceDarkModeColour(dmModes7ths.get());
    replaceDarkModeColour(dmHarmonicMinor.get());
    replaceDarkModeColour(dmHarmonicMinorBackground.get());
    replaceDarkModeColour(dmHarmonicMinorTriads.get());
    replaceDarkModeColour(dmHarmonicMinor7ths.get());
    replaceDarkModeColour(dmMelodicMinor.get());
    replaceDarkModeColour(dmMelodicMinorBackground.get());
    replaceDarkModeColour(dmMelodicMinorTriads.get());
    replaceDarkModeColour(dmMelodicMinor7ths.get());
}



static Rectangle<float> adjustedCircleBounds(Rectangle<int> circleBounds)
{
    int buttonHeight = getButtonHeight(circleBounds);
    int buttonSpace = buttonHeight * 0.1;
    float radiusX2 = circleBounds.getWidth() - buttonSpace * 16;
    Rectangle<float> adjusted = Rectangle<float>(radiusX2, radiusX2);
    adjusted.setCentre(circleBounds.getCentreX(), circleBounds.getCentreX());
    return adjusted;
}

CircleComponent::CircleComponent(ComboBox* modeMenu)
{
    setWantsKeyboardFocus(true);
    this->modeMenu = modeMenu;
    noteToCircleIndexMap[0] = 0;
    noteToCircleIndexMap[7] = 1;
    noteToCircleIndexMap[2] = 2;
    noteToCircleIndexMap[9] = 3;
    noteToCircleIndexMap[4] = 4;
    noteToCircleIndexMap[11] = 5;
    noteToCircleIndexMap[6] = 6;
    noteToCircleIndexMap[1] = 7;
    noteToCircleIndexMap[8] = 8;
    noteToCircleIndexMap[3] = 9;
    noteToCircleIndexMap[10] = 10;
    noteToCircleIndexMap[5] = 11;
}

void CircleComponent::paint(Graphics& g)
{    
    Rectangle<int> circleBounds = getBounds();
    Rectangle<float> adjustedBounds = adjustedCircleBounds(circleBounds);

    int modeItemId = modeMenu->getSelectedId();
    String selectedMode = modeMenu->getText();
    if (modeItemId > 1)
        svgManager.getModeBackground(selectedMode)->drawWithin(g, adjustedBounds, RectanglePlacement::centred, 1.0);
    
    //rotate based on the selected circle index
    Drawable* notesCircleSvg = svgManager.getCircleSvg();
    if (selectedRadians != 0)
    {
        float centreX = notesCircleSvg->getWidth()/2.0;
        float centreY = notesCircleSvg->getHeight()/2.0;
        float radians = -(selectedCircleIndex * 30 * (M_PI / 180));
        AffineTransform transform(AffineTransform::rotation(radians, centreX, centreY));
        notesCircleSvg->setTransform(transform);
    }        
    notesCircleSvg->drawWithin(g, adjustedBounds, RectanglePlacement::centred, 1.0);

    if (modeItemId > 1)
    {
        svgManager.getModeImage(selectedMode)->drawWithin(g, adjustedBounds, RectanglePlacement::centred, 1.0);
        if (currentTriadsAndSeventhsState == &TRIADS || currentTriadsAndSeventhsState == &SEVENTHS)
        {
            svgManager.getModeTriads(selectedMode)->drawWithin(g, adjustedBounds, RectanglePlacement::centred, 1.0);
            if (currentTriadsAndSeventhsState == &SEVENTHS)
            {
                svgManager.getModeSevenths(selectedMode)->drawWithin(g, adjustedBounds, RectanglePlacement::centred, 1.0);
            }
        }        
    }
}

 

void CircleComponent::mouseDown(const MouseEvent& event)
{
    Rectangle<float> adjustedCircleBounds(adjustedCircleBounds(getBounds()));
    int centreX = adjustedCircleBounds.getCentreX();
    int centreY = adjustedCircleBounds.getCentreY();

    //Find out if the point is inside the circle
    //(x-center_x)^2 + (y - center_y)^2 < radius^2
    int radius = adjustedCircleBounds.getWidth() / 2;
    int mouseX = event.getMouseDownX();
    int mouseY = event.getMouseDownY();
    bool isInsideCircle = ((mouseX - centreX) * (mouseX - centreX)) + ((mouseY - centreY) * (mouseY - centreY)) < radius * radius;
    if (!isInsideCircle)
        return;

    int deltaX = mouseX - centreX;
    int deltaY = mouseY - centreY;
    float rad = std::atan2(deltaY, deltaX);
    float deg = rad * (180 / 3.14) + 90;
    if (deg < 0)
        deg += 360;
    
    newCircleDegreeSelected(deg);
}

void CircleComponent::newCircleDegreeSelected(float deg)
{
    //Now we know the degree
    //The last selected note decides the next jump
    selectedRadians = -(deg * (3.14 / 180));
    if (deg >= 345 || deg < 15)
    {
        //same as current selection, no change needed
        return;
    }

    int adder = 0;
    if (deg >= 15)
        adder += 7;
    if (deg >= 45)
        adder += 7;
    if (deg >= 75)
        adder += 7;
    if (deg >= 105)
        adder += 7;
    if (deg >= 135)
        adder += 7;
    if (deg >= 165)
        adder += 7;
    if (deg >= 195)
        adder += 7;
    if (deg >= 225)
        adder += 7;
    if (deg >= 255)
        adder += 7;
    if (deg >= 285)
        adder += 7;
    if (deg >= 315)
        adder += 7;

    int nextNoteIndex = (selectedNoteIndex + adder) % 12;
    int nextCircleIndex = noteToCircleIndexMap[nextNoteIndex];
    selectedNoteIndex = nextNoteIndex;
    selectedCircleIndex = nextCircleIndex;
    repaint();
}

InteractiveCircleOfFifthsAudioProcessorEditor::InteractiveCircleOfFifthsAudioProcessorEditor (InteractiveCircleOfFifthsAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), circleComponent(&modeMenu)
{
    setWantsKeyboardFocus(true);    
    lightLookAndFeel.setLightModeLookAndFeel();
    darkLookAndFeel.setDarkModeLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(&lightLookAndFeel);

    setSize (400, 440);
    updateConstrainer();
    setConstrainer(&constrainer);
    setResizable(true, true);

    for (int idx = 0; idx < modes.size(); idx++)
    {
        modeMenu.addItem(modes[idx], idx + 1);
    }
    modeMenu.setSelectedId(1);
    modeMenu.onChange = [this] { modeMenuChanged(); };

    circleModeButton.setButtonText("C");
    circleModeButton.setTooltip("Show Do Re Mi");
    circleModeButton.addListener(this);

    setSeventhsButtonNextState();
    seventhsButton.setEnabled(false);
    seventhsButton.addListener(this);

    darkModeButton.setButtonText("D");
    darkModeButton.setTooltip("Dark mode");
    darkModeButton.setToggleable(true);
    darkModeButton.setToggleState(false, false);
    darkModeButton.addListener(this);

    halfWidthButton.setButtonText("H");
    halfWidthButton.setTooltip("Half circle");
    halfWidthButton.setToggleable(true);
    halfWidthButton.setToggleState(false, false);
    halfWidthButton.addListener(this);

    addAndMakeVisible(modeMenu);
    addAndMakeVisible(circleModeButton);
    addAndMakeVisible(seventhsButton);
    addAndMakeVisible(darkModeButton);
    addAndMakeVisible(halfWidthButton);
    addAndMakeVisible(circleComponent);
}

InteractiveCircleOfFifthsAudioProcessorEditor::~InteractiveCircleOfFifthsAudioProcessorEditor()
{
}

void InteractiveCircleOfFifthsAudioProcessorEditor::setSeventhsButtonNextState()
{
    TriadsAndSeventhsState* lastState = currentTriadsAndSeventhsState;
    switch (lastState->mode)
    {
    case None:
        currentTriadsAndSeventhsState = &TRIADS;
        break;
    case Triads:
        currentTriadsAndSeventhsState = &SEVENTHS;
        break;
    case Sevenths:
        currentTriadsAndSeventhsState = &NONE;
        break;
    }
    seventhsButton.setButtonText(currentTriadsAndSeventhsState->buttonText);
    seventhsButton.setTooltip(currentTriadsAndSeventhsState->buttonTooltip);
}

void InteractiveCircleOfFifthsAudioProcessorEditor::updateModeMenuSelection(bool up)
{
    int selectedItemId = modeMenu.getSelectedId();
    if (up)
    {
        if (selectedItemId > 1)
        {
            selectedItemId--;
            modeMenu.setSelectedId(selectedItemId);
            repaint();
        }
    }
    else
    {
        if (selectedItemId < 10)
        {
            selectedItemId++;
            modeMenu.setSelectedId(selectedItemId);
            repaint();
        }
    }
}

bool InteractiveCircleOfFifthsAudioProcessorEditor::keyPressed(const KeyPress& k)
{
    if (k.getKeyCode() == k.leftKey)
    {
        circleComponent.newCircleDegreeSelected(30);
    }
    else if (k.getKeyCode() == k.rightKey)
    {
        circleComponent.newCircleDegreeSelected(330);
    }
    else if (k.getKeyCode() == k.upKey)
    {
        if (ModifierKeys::currentModifiers.isShiftDown())
        {
            setSeventhsButtonNextState();
            repaint();
        }
        else
        {
            updateModeMenuSelection(true);
        }

    }
    else if (k.getKeyCode() == k.downKey && !ModifierKeys::currentModifiers.isShiftDown())
    {
        updateModeMenuSelection(false);
    }
    else
        return false;
    return true;
}

void InteractiveCircleOfFifthsAudioProcessorEditor::modeMenuChanged()
{
    int modeItemId = modeMenu.getSelectedId();
    if (modeItemId > 1)
        seventhsButton.setEnabled(true);
    else
        seventhsButton.setEnabled(false);
    repaint();
}

void InteractiveCircleOfFifthsAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &circleModeButton)
    {
        circleModeDoRe = !circleModeDoRe;
        circleModeButton.setButtonText(circleModeDoRe ? "Do" : "C");
        circleModeButton.setTooltip(circleModeDoRe ? "Show C D E" : "Show Do Re Mi");
    }
    else if (button == &seventhsButton)
    {
        setSeventhsButtonNextState();
    }
    else if (button == &darkModeButton)
    {
        bool nextMode = !darkMode;
        LookAndFeel::setDefaultLookAndFeel(
            nextMode ?
            &darkLookAndFeel :
            &lightLookAndFeel
        );
        darkMode = nextMode;
        darkModeButton.setToggleState(darkMode, false);
    }
    else if (button == &halfWidthButton)
    {
        toggleHalfWidth();
    }
    repaint();
}

static bool firstTime = true;

//==============================================================================
void InteractiveCircleOfFifthsAudioProcessorEditor::paint (juce::Graphics& g)
{
    if (firstTime) {
        grabKeyboardFocus();
        firstTime = false;
    }
    if (darkMode)
    {
        g.fillAll(darkModeBackgroundColour);
        g.setColour(darkModeForegroundColour);
    }
    else {
        g.fillAll(Colours::white);
        g.setColour(Colours::black);
    }
}

void InteractiveCircleOfFifthsAudioProcessorEditor::resized()
{
    Rectangle<int> bounds = getBounds();
    int buttonHeight = getButtonHeight(bounds);
    int buttonSpace = buttonHeight * 0.1;

    updateConstrainer();

    modeMenu.setBounds(Rectangle<int>(buttonSpace, buttonSpace, buttonHeight * 5, buttonHeight));
    circleModeButton.setBounds(Rectangle<int>(buttonHeight * 5 + buttonSpace * 2, buttonSpace, buttonHeight * 1.5, buttonHeight));
    seventhsButton.setBounds(Rectangle<int>(buttonHeight * 6.5 + buttonSpace * 3, buttonSpace, buttonHeight, buttonHeight));
    darkModeButton.setBounds(Rectangle<int>(buttonHeight * 7.5 + buttonSpace * 4, buttonSpace, buttonHeight, buttonHeight));
    halfWidthButton.setBounds(Rectangle<int>(buttonHeight * 8.5 + buttonSpace * 5, buttonSpace, buttonHeight, buttonHeight));

    Rectangle<int> circleBounds = Rectangle<int>(
        bounds.getX(),// + buttonSpace,
        bounds.getY() + buttonHeight + buttonSpace,
        bounds.getWidth(),// - buttonSpace * 2,
        bounds.getHeight() - buttonHeight - buttonSpace * 2
    );
    circleComponent.setBounds(circleBounds);
}

void InteractiveCircleOfFifthsAudioProcessorEditor::updateConstrainer()
{
    Rectangle<int> bounds = getBounds();
    if (halfWidth)
    {
        constrainer.setMinimumWidth(320);
        constrainer.setMinimumHeight(175);
        int maxHeight = jmax(constrainer.getMinimumHeight(), (int)(bounds.getWidth() * 0.55));
        int maxWidth = jmax(constrainer.getMinimumWidth(), (int)(bounds.getHeight() * 2.5));
        constrainer.setMaximumHeight(maxHeight);
        constrainer.setMaximumWidth(maxWidth);
    }
    else
    {
        constrainer.setMaximumHeight(bounds.getWidth() * 1.1);
        constrainer.setMaximumWidth(bounds.getHeight() / 1.06);
        constrainer.setMinimumWidth(320);
        constrainer.setMinimumHeight(352);
    }
}

void InteractiveCircleOfFifthsAudioProcessorEditor::toggleHalfWidth()
{
    halfWidth = !halfWidth;
    halfWidthButton.setToggleState(halfWidth, false);
    updateConstrainer();
    setSize(getBounds().getWidth(), constrainer.getMaximumHeight());
    resized();
    repaint();
}