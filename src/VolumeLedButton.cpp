#include <Control_Surface.h>

class VolumeButton : public MIDIOutputElement {
public:
  /*
   * @brief   Create a new VolumeButton object on the given pin, with the 
   *          given address and velocity.
   * 
   * @param   pin
   *          The digital input pin to read from.  
   *          The internal pull-up resistor will be enabled.
   * @param   address
   *          The MIDI address to send to.
   * @param   velocity
   *          The MIDI note velocity [0, 127].
   */
  VolumeButton(pin_t pin, MIDIAddress address, uint8_t velocity, pin_t ledPin)
    : button(pin), address(address), velocity(velocity), ledPin(ledPin), buttonPressed(false) {}

public:
  // Initialize: enable the pull-up resistor for the button
  // This method is called once by `Control_Surface.begin()`.
  void begin() final override { 
    button.begin(); 
    pinMode(ledPin, OUTPUT);
  }

  // Update: read the button and send MIDI messages when appropriate.
  // This method is called continuously by `Control_Surface.loop()`.
  void update() final override {
    AH::Button::State state = button.update();
    if (state == AH::Button::Falling) {               // if pressed
      Control_Surface.sendControlChange(address, velocity);
      buttonPressed = true;
    }
  }

  // Check if the button has been pressed
  bool isButtonPressed() const {
    return buttonPressed;
  }

  // Reset the button state
  void resetButtonState() {
    buttonPressed = false;
  }

  // Get the LED pin
  pin_t getLedPin() const {
    return ledPin;
  }

private:
  AH::Button button;
  MIDIAddress address;
  uint8_t velocity;
  pin_t ledPin;  // Digital output pin to control an LED
  bool buttonPressed;  // Store the button state
};