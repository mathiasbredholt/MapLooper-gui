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
    addAndMakeVisible(delaySlider);
    addAndMakeVisible(modulationSlider);
    addAndMakeVisible(outputSlider);
    addAndMakeVisible(muteButton);
    // addAndMakeVisible(button2);

    loop = mapLooper.createLoop("loop1");

    inputSlider.addListener(this);
    delaySlider.addListener(this);
    modulationSlider.addListener(this);
    outputSlider.addListener(this);
    muteButton.addListener(this);
    button2.addListener(this);

    inputSliderLabel.setText("input", juce::dontSendNotification);
    inputSliderLabel.attachToComponent(&inputSlider, true);

    delaySliderLabel.setText("delay", juce::dontSendNotification);
    delaySliderLabel.attachToComponent(&delaySlider, true);

    modulationSliderLabel.setText("mod", juce::dontSendNotification);
    modulationSliderLabel.attachToComponent(&modulationSlider, true);

    outputSliderLabel.setText("output", juce::dontSendNotification);
    outputSliderLabel.attachToComponent(&outputSlider, true);

    muteButtonLabel.setText("muted", juce::dontSendNotification);
    muteButtonLabel.attachToComponent(&muteButton, true);

    button2Label.setText("button2", juce::dontSendNotification);
    button2Label.attachToComponent(&button2, true);

    setSize(600, 400);

    inputSlider.setRange(0, 1);
    delaySlider.setRange(-100, -1, 1);
    delaySlider.setValue(-100);
    modulationSlider.setRange(0, 1);
    outputSlider.setRange(0, 1);

    startTimer(10);
  }

  ~MainComponent() {}

  void timerCallback() override {
    mapLooper.update(0);
    const void* val = mpr_sig_get_value(loop->sigOut, 0, 0);
    if (val) {
      const MessageManagerLock mmLock;
      outputSlider.setValue(*((float*)val));
    }
  }

  //==============================================================================
  void paint(Graphics& g) override {}

  void resized() override {
    auto area = getLocalBounds().reduced(96, 48);
    inputSlider.setBounds(area.removeFromTop(48));
    delaySlider.setBounds(area.removeFromTop(48));
    modulationSlider.setBounds(area.removeFromTop(48));
    outputSlider.setBounds(area.removeFromTop(48));
    muteButton.setBounds(area.removeFromTop(48));
    button2.setBounds(area.removeFromTop(48));
  }

  void sliderValueChanged(Slider* slider) override {
    if (slider == &inputSlider) {
      float val = inputSlider.getValue();
      mpr_sig_set_value(loop->sigIn, 0, 1, MPR_FLT, &val);
    } else if (slider == &delaySlider) {
      float val = delaySlider.getValue();
      mpr_sig_set_value(loop->sigDelay, 0, 1, MPR_FLT, &val);
    } else if (slider == &modulationSlider) {
      float val = modulationSlider.getValue();
      mpr_sig_set_value(loop->sigMod, 0, 1, MPR_FLT, &val);
    }
  }

  void sliderDragStarted(Slider* slider) override {
    float val = 1.0f;
    if (slider == &inputSlider) {
      mpr_sig_set_value(loop->sigRecord, 0, 1, MPR_FLT, &val);
    }
  }

  void sliderDragEnded(Slider* slider) override {
    float val = 0.0f;
    if (slider == &inputSlider) {
      mpr_sig_set_value(loop->sigRecord, 0, 1, MPR_FLT, &val);
    }
  }

  void buttonClicked(Button* button) override {}

  void buttonStateChanged(Button* button) override {
    if (button == &muteButton) {
      int val = muteButton.getToggleState();
      mpr_sig_set_value(loop->sigMute, 0, 1, MPR_INT32, &val);
    } else if (button == &button2) {
      int val = button2.getToggleState();
      // mpr_sig_set_value(sigButton2, 0, 1, MPR_INT32, &val);
    }
  }

 private:
  Slider inputSlider;
  Label inputSliderLabel;
  Slider delaySlider;
  Label delaySliderLabel;
  Slider modulationSlider;
  Label modulationSliderLabel;
  Slider outputSlider;
  Label outputSliderLabel;
  ToggleButton muteButton;
  Label muteButtonLabel;
  ToggleButton button2;
  Label button2Label;
  MapLooper::MapLooper mapLooper;
  MapLooper::Loop* loop;

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
