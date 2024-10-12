#include <Arduino.h>
#include <Control_Surface.h>
#include "VolumeLedButton.cpp"

USBMIDI_Interface midi;

const int NUMBER_OF_BUTTONS = 2;
const pin_t volumeButtonPins[] = { 15, 17 };
const pin_t volumeLedPins[] = { 14, 16 };
const uint8_t volumeVelocities[] = { 0x14, 0x1E };

VolumeButton volumeButtons[NUMBER_OF_BUTTONS] = {
  { volumeButtonPins[0], { MIDI_CC::Channel_Volume, Channel_1 }, volumeVelocities[0], volumeLedPins[0] },
  { volumeButtonPins[1], { MIDI_CC::Channel_Volume, Channel_1 }, volumeVelocities[1], volumeLedPins[1] }
};

void setup() {
  Control_Surface.begin();
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
    pinMode(volumeLedPins[i], OUTPUT);
  }
}

void loop() {
  Control_Surface.loop();

  // Turn off all volume LEDs and light only the selected one
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
    if (volumeButtons[i].isButtonPressed()) {
      // Turn off all LEDs
      for (int j = 0; j < NUMBER_OF_BUTTONS; ++j) {
        digitalWrite(volumeButtons[j].getLedPin(), LOW);
      }
      // Turn on the LED for the pressed button
      digitalWrite(volumeButtons[i].getLedPin(), HIGH);
      // Reset the button state
      volumeButtons[i].resetButtonState();
    }
  }
}