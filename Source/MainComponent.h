/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "MapLooper/MapLooper.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component,
                      Slider::Listener,
                      Button::Listener,
                      Timer {
 public:
  //==============================================================================
  MainComponent() {
    addAndMakeVisible(inputSlider);
    addAndMakeVisible(outputSlider);
    addAndMakeVisible(lengthSlider);
    addAndMakeVisible(modulationSlider);
    addAndMakeVisible(divisionSlider);
    addAndMakeVisible(tempoSlider);
    addAndMakeVisible(muteButton);

    loop.reset(mapLooper.createLoop("loop1"));

    inputSlider.addListener(this);
    lengthSlider.addListener(this);
    modulationSlider.addListener(this);
    outputSlider.addListener(this);
    divisionSlider.addListener(this);
    tempoSlider.addListener(this);
    muteButton.addListener(this);

    inputSliderLabel.setText("input", juce::dontSendNotification);
    inputSliderLabel.attachToComponent(&inputSlider, true);

    lengthSliderLabel.setText("length", juce::dontSendNotification);
    lengthSliderLabel.attachToComponent(&lengthSlider, true);

    modulationSliderLabel.setText("noise", juce::dontSendNotification);
    modulationSliderLabel.attachToComponent(&modulationSlider, true);

    outputSliderLabel.setText("output", juce::dontSendNotification);
    outputSliderLabel.attachToComponent(&outputSlider, true);
    outputSlider.setEnabled(false);

    divisionSliderLabel.setText("division", juce::dontSendNotification);
    divisionSliderLabel.attachToComponent(&divisionSlider, true);

    tempoSliderLabel.setText("tempo", juce::dontSendNotification);
    tempoSliderLabel.attachToComponent(&tempoSlider, true);

    muteButtonLabel.setText("muted", juce::dontSendNotification);
    muteButtonLabel.attachToComponent(&muteButton, true);

    setSize(600, 400);

    inputSlider.setRange(0, 1);
    lengthSlider.setRange(0, 16.0);
    lengthSlider.setTextValueSuffix(" beats");
    lengthSlider.setNumDecimalPlacesToDisplay(2);
    divisionSlider.setRange(2, 96, 1);
    divisionSlider.setTextValueSuffix(" ppqn");
    tempoSlider.setRange(20, 255);
    tempoSlider.setNumDecimalPlacesToDisplay(1);
    tempoSlider.setTextValueSuffix(" bpm");
    modulationSlider.setRange(0, 1);
    outputSlider.setRange(0, 1);

    startTimer(10);
  }

  ~MainComponent() {}

  void timerCallback() override {
    mapLooper.update(0);
    const void* val = mpr_sig_get_value(loop->getOutputSignal(), 0, 0);
    if (val) {
      const MessageManagerLock mmLock;
      inputSlider.setValue(*((float*) mpr_sig_get_value(loop->getInputSignal(), 0, 0)), dontSendNotification);
      lengthSlider.setValue(*((float*) mpr_sig_get_value(loop->getLengthSignal(), 0, 0)), dontSendNotification);
      modulationSlider.setValue(*((float*) mpr_sig_get_value(loop->getModulationSignal(), 0, 0)), dontSendNotification);
      outputSlider.setValue(*((float*) val), dontSendNotification);
      tempoSlider.setValue(mapLooper.getTempo());
      divisionSlider.setValue(*((float*) mpr_sig_get_value(loop->getDivisionSignal(), 0, 0)), dontSendNotification);
    }
  }

  //==============================================================================
  void paint(Graphics& g) override {}

  void resized() override {
    const int spacing = 40;
    auto area = getLocalBounds().reduced(96, spacing);
    inputSlider.setBounds(area.removeFromTop(spacing));
    outputSlider.setBounds(area.removeFromTop(spacing));
    lengthSlider.setBounds(area.removeFromTop(spacing));
    modulationSlider.setBounds(area.removeFromTop(spacing));
    divisionSlider.setBounds(area.removeFromTop(spacing));
    tempoSlider.setBounds(area.removeFromTop(spacing));
    muteButton.setBounds(area.removeFromTop(spacing));
  }

  void sliderValueChanged(Slider* slider) override {
    if (slider == &inputSlider) {
      float val = slider->getValue();
      mpr_sig_set_value(loop->getInputSignal(), 0, 1, MPR_FLT, &val);
    } else if (slider == &lengthSlider) {
      float val = slider->getValue();
      mpr_sig_set_value(loop->getLengthSignal(), 0, 1, MPR_FLT, &val);
    } else if (slider == &modulationSlider) {
      float val = slider->getValue();
      mpr_sig_set_value(loop->getModulationSignal(), 0, 1, MPR_FLT, &val);
    } else if (slider == &divisionSlider) {
      int val = slider->getValue();
      mpr_sig_set_value(loop->getDivisionSignal(), 0, 1, MPR_INT32, &val);
    } else if (slider == &tempoSlider) {
      float val = slider->getValue();
      mapLooper.setTempo(val);
    }
  }

  void sliderDragStarted(Slider* slider) override {
    float val = 1.0f;
    if (slider == &inputSlider) {
      mpr_sig_set_value(loop->getRecordSignal(), 0, 1, MPR_FLT, &val);
    }
  }

  void sliderDragEnded(Slider* slider) override {
    float val = 0.0f;
    if (slider == &inputSlider) {
      mpr_sig_set_value(loop->getRecordSignal(), 0, 1, MPR_FLT, &val);
    }
  }

  void buttonClicked(Button* button) override {}

  void buttonStateChanged(Button* button) override {
    if (button == &muteButton) {
      int val = muteButton.getToggleState();
      mpr_sig_set_value(loop->getMuteSignal(), 0, 1, MPR_INT32, &val);
    }
  }

 private:
  Slider inputSlider;
  Label inputSliderLabel;
  Slider lengthSlider;
  Label lengthSliderLabel;
  Slider modulationSlider;
  Label modulationSliderLabel;
  Slider outputSlider;
  Label outputSliderLabel;
  Slider divisionSlider;
  Label divisionSliderLabel;
  Slider tempoSlider;
  Label tempoSliderLabel;
  ToggleButton muteButton;
  Label muteButtonLabel;
  MapLooper::MapLooper mapLooper;
  std::unique_ptr<MapLooper::Loop> loop;

  static void sliderHandler(mpr_sig sig, mpr_sig_evt evt, mpr_id inst,
                            int length, mpr_type type, const void* value,
                            mpr_time time) {
    const MessageManagerLock mmLock;
    Slider* slider = (Slider*)mpr_obj_get_prop_as_ptr(sig, MPR_PROP_DATA, 0);
    slider->setValue(*(float*)value);
  }

  static void buttonHandler(mpr_sig sig, mpr_sig_evt evt, mpr_id inst,
                            int length, mpr_type type, const void* value,
                            mpr_time time) {
    const MessageManagerLock mmLock;
    ToggleButton* button =
        (ToggleButton*)mpr_obj_get_prop_as_ptr(sig, MPR_PROP_DATA, 0);
    button->setToggleState(*(int*)value, dontSendNotification);
  }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
