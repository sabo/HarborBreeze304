#include "Arduino.h"
#include "HarborBreeze304.h"

HarborBreeze304::HarborBreeze304(flag fl) {
  _flag = fl;
}

void HarborBreeze304::set_fan(fan_speed fs) {
  if (fs == OFF) {
      fan_on = false;
  };
  _fan_state = fs;
}

fan_speed HarborBreeze304::get_fan() {
  return _fan_state;
}

void HarborBreeze304::set_light(int percentage) {
  // Takes light as a percentage, uses it to set the state.
  // Divide by 2 and subtract 10 to get meaningful integral steps
  if (percentage <= 0) {
    // Set off
    light_on = false;
  }
  else {
    light_on = true;
    if (percentage < 20) {
      // 20 percent is the smallest we go
      percentage = 20;
    }
    int steps = ((int) (percentage / 2)) - 10;
    // Light state's max value is actually the dimmest level:
    // 41 = 20% --> 1 = 100%
    // So, for example, 100% -> steps = 40 -> light_state = 41 - 40 = 1
    _light_state = 41 - steps;
  }
}

int HarborBreeze304::get_light() {
  // Returns current light state as a percentage
  int l = (_light_state + 10) * 2;
  return l;
}

uint32_t HarborBreeze304::get_state_code() {
  // Build the state part of the message
  int light_state;
  int fan_state;
  if (light_on) {
      light_state = _light_state;
  } else {
      light_state = 0;
  }

  if (fan_on) {
      fan_state = _fan_state;
  } else {
      fan_state = 0;
  }

  int state = (light_state << 2) | fan_state;
  // Calculate the checksum part.
  // This was arrived at by a whole lot of trial and error, so ymmv
  // Add together the flag and the state
  // Sum mod 16 the dividend and the remainder of the message's numerical value 
  // divided by 16
  int dividend = ((_flag << 1) + state) / 16;
  int rem = ((_flag << 1) + state) % 16;
  int ck = dividend + rem;
  if (ck < 0) {
    ck += 16;
  }
  else if (ck >= 16) {
    ck -= 16;
  }
  // Assemble the message:
  // Start by shifting the flag 8 bits left:
  // one for the padding, and 8 to make room for the state
  uint32_t message = _flag << 9;
  // OR the state and the message, then lbs 5 for the padding + checksum 
  message |= state;
  message <<= 5;
  message |= ck;
  // Last little bit of padding
  message <<= 2;

  return message;
}
