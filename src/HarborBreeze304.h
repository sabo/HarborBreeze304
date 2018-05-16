/* HarborBreeze304.h */

#ifndef HarborBreeze304_h
#define HarborBreeze304_h

#include "Arduino.h"
#include "./types.h"

class HarborBreeze304
{
  public:
    HarborBreeze304(flag flag);
    void set_light(int l);
    void set_fan(fan_speed f);
    fan_speed get_fan();
    int get_light();
    uint32_t get_state_code();
    bool light_on;
    bool fan_on;
  private:
    flag _flag;
    int _light_state;
    fan_speed _fan_state;
};

#endif
