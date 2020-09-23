/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "mapper/mapper.h"

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
    addAndMakeVisible(slider1);
    addAndMakeVisible(slider2);
    addAndMakeVisible(slider3);
    addAndMakeVisible(slider4);
    addAndMakeVisible(button1);
    addAndMakeVisible(button2);

    slider1.addListener(this);
    slider2.addListener(this);
    slider3.addListener(this);
    slider4.addListener(this);
    button1.addListener(this);
    button2.addListener(this);

    slider1Label.setText("slider1", juce::dontSendNotification);
    slider1Label.attachToComponent(&slider1, true);

    slider2Label.setText("slider2", juce::dontSendNotification);
    slider2Label.attachToComponent(&slider2, true);

    slider3Label.setText("slider3", juce::dontSendNotification);
    slider3Label.attachToComponent(&slider3, true);

    slider4Label.setText("slider4", juce::dontSendNotification);
    slider4Label.attachToComponent(&slider4, true);

    button1Label.setText("button1", juce::dontSendNotification);
    button1Label.attachToComponent(&button1, true);

    button2Label.setText("button2", juce::dontSendNotification);
    button2Label.attachToComponent(&button2, true);

    setSize(600, 400);

    // Create libmapper device
    dev = mpr_dev_new("mapperGUI", 0);

    // Create output signals
    float sliderMin = 0.0f, sliderMax = 1.0f;
    int buttonMin = 0, buttonMax = 1;

    slider1.setRange(sliderMin, sliderMax);
    slider2.setRange(sliderMin, sliderMax);
    slider3.setRange(sliderMin, sliderMax);
    slider4.setRange(sliderMin, sliderMax);

    sigSlider1 = mpr_sig_new(dev, MPR_DIR_OUT, "out/slider1", 1, MPR_FLT, 0,
                             &sliderMin, &sliderMax, 0, 0, 0);
    sigSlider2 = mpr_sig_new(dev, MPR_DIR_OUT, "out/slider2", 1, MPR_FLT, 0,
                             &sliderMin, &sliderMax, 0, 0, 0);
    sigSlider3 = mpr_sig_new(dev, MPR_DIR_OUT, "out/slider3", 1, MPR_FLT, 0,
                             &sliderMin, &sliderMax, 0, 0, 0);
    sigSlider4 = mpr_sig_new(dev, MPR_DIR_OUT, "out/slider4", 1, MPR_FLT, 0,
                             &sliderMin, &sliderMax, 0, 0, 0);
    sigButton1 = mpr_sig_new(dev, MPR_DIR_OUT, "out/button1", 1, MPR_INT32, 0,
                             &buttonMin, &buttonMax, 0, 0, 0);
    sigButton2 = mpr_sig_new(dev, MPR_DIR_OUT, "out/button2", 1, MPR_INT32, 0,
                             &buttonMin, &buttonMax, 0, 0, 0);

    // Create input signals

    inputSigSlider1 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/slider1", 1, MPR_FLT, 0, &sliderMin,
                    &sliderMax, 0, sliderHandler, MPR_SIG_UPDATE);

    inputSigSlider2 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/slider2", 1, MPR_FLT, 0, &sliderMin,
                    &sliderMax, 0, sliderHandler, MPR_SIG_UPDATE);
    inputSigSlider3 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/slider3", 1, MPR_FLT, 0, &sliderMin,
                    &sliderMax, 0, sliderHandler, MPR_SIG_UPDATE);
    inputSigSlider4 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/slider4", 1, MPR_FLT, 0, &sliderMin,
                    &sliderMax, 0, sliderHandler, MPR_SIG_UPDATE);
    inputSigButton1 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/button1", 1, MPR_INT32, 0, &buttonMin,
                    &buttonMax, 0, buttonHandler, MPR_SIG_UPDATE);
    inputSigButton2 =
        mpr_sig_new(dev, MPR_DIR_IN, "in/button2", 1, MPR_INT32, 0, &buttonMin,
                    &buttonMax, 0, buttonHandler, MPR_SIG_UPDATE);

    mpr_obj_set_prop(inputSigSlider1, MPR_PROP_DATA, 0, 1, MPR_PTR, &slider1,
                     0);
    mpr_obj_set_prop(inputSigSlider2, MPR_PROP_DATA, 0, 1, MPR_PTR, &slider2,
                     0);
    mpr_obj_set_prop(inputSigSlider3, MPR_PROP_DATA, 0, 1, MPR_PTR, &slider3,
                     0);
    mpr_obj_set_prop(inputSigSlider4, MPR_PROP_DATA, 0, 1, MPR_PTR, &slider4,
                     0);
    mpr_obj_set_prop(inputSigButton1, MPR_PROP_DATA, 0, 1, MPR_PTR, &button1,
                     0);
    mpr_obj_set_prop(inputSigButton2, MPR_PROP_DATA, 0, 1, MPR_PTR, &button2,
                     0);

    startTimer(10);
  }

  ~MainComponent() {}

  void timerCallback() override { mpr_dev_poll(dev, 0); }

  //==============================================================================
  void paint(Graphics& g) override {}

  void resized() override {
    auto area = getLocalBounds().reduced(96, 48);
    slider1.setBounds(area.removeFromTop(48));
    slider2.setBounds(area.removeFromTop(48));
    slider3.setBounds(area.removeFromTop(48));
    slider4.setBounds(area.removeFromTop(48));
    button1.setBounds(area.removeFromTop(48));
    button2.setBounds(area.removeFromTop(48));
  }

  void sliderValueChanged(Slider* slider) override {
    if (slider == &slider1) {
      float val = slider1.getValue();
      mpr_sig_set_value(sigSlider1, 0, 1, MPR_FLT, &val);
    } else if (slider == &slider2) {
      float val = slider2.getValue();
      mpr_sig_set_value(sigSlider2, 0, 1, MPR_FLT, &val);
    } else if (slider == &slider3) {
      float val = slider3.getValue();
      mpr_sig_set_value(sigSlider3, 0, 1, MPR_FLT, &val);
    } else if (slider == &slider4) {
      float val = slider4.getValue();
      mpr_sig_set_value(sigSlider4, 0, 1, MPR_FLT, &val);
    }
  }

  void buttonClicked(Button* button) override {}

  void buttonStateChanged(Button* button) override {
    if (button == &button1) {
      int val = button1.getToggleState();
      mpr_sig_set_value(sigButton1, 0, 1, MPR_INT32, &val);
    } else if (button == &button2) {
      int val = button2.getToggleState();
      mpr_sig_set_value(sigButton2, 0, 1, MPR_INT32, &val);
    }
  }

 private:
  Slider slider1;
  Label slider1Label;
  Slider slider2;
  Label slider2Label;
  Slider slider3;
  Label slider3Label;
  Slider slider4;
  Label slider4Label;
  ToggleButton button1;
  Label button1Label;
  ToggleButton button2;
  Label button2Label;
  mpr_dev dev;
  mpr_sig sigSlider1;
  mpr_sig sigSlider2;
  mpr_sig sigSlider3;
  mpr_sig sigSlider4;
  mpr_sig sigButton1;
  mpr_sig sigButton2;

  mpr_sig inputSigSlider1;
  mpr_sig inputSigSlider2;
  mpr_sig inputSigSlider3;
  mpr_sig inputSigSlider4;
  mpr_sig inputSigButton1;
  mpr_sig inputSigButton2;

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
