/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>
#include <vector>

struct CustomRotarySlider : juce::Slider {
  CustomRotarySlider()
      : juce::Slider(SliderStyle::RotaryHorizontalVerticalDrag,
                     TextEntryBoxPosition::NoTextBox) {}
};

//==============================================================================
/**
 */
class SimpleEQAudioProcessorEditor : public juce::AudioProcessorEditor,
                                     juce::AudioProcessorParameter::Listener,
                                     juce::Timer {
public:
  SimpleEQAudioProcessorEditor(SimpleEQAudioProcessor &);
  ~SimpleEQAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics &) override;
  void resized() override;

  void parameterValueChanged(int parameterIndex, float newValue) override;

  void parameterGestureChanged(int parameterIndex,
                               bool gestureIsStarting) override {}

  void timerCallback() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  SimpleEQAudioProcessor &audioProcessor;

  juce::Atomic<bool> parameterChanged{false};

  CustomRotarySlider peakFreqSlider, peakGainSlider, peakQualitySlider,
      lowCutFreqSlider, highCutFreqSlider, lowCutSlopeSlider,
      highCutSlopeSlider;

  using APVTS = juce::AudioProcessorValueTreeState;
  using Attachment = APVTS::SliderAttachment;

  Attachment peakFreqSliderAttachment, peakGainSliderAttachment,
      peakQualitySliderAttachment, lowCutFreqSliderAttachment,
      highCutFreqSliderAttachment, lowCutSlopeSliderAttachment,
      highCutSlopeSliderAttachment;

  std::vector<juce::Component *> getComps();

  MonoChain monoChain;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SimpleEQAudioProcessorEditor)
};
