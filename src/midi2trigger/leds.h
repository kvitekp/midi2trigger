// Copyright 2013 Peter Kvitek.
//
// Author: Peter Kvitek (pete@kvitek.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef MIDI2TRIGGER_LEDS_H_
#define MIDI2TRIGGER_LEDS_H_

#include "avrlib/devices/led.h"
#include "midi2trigger/hardware_config.h"

namespace midi2trigger {

using avrlib::Led;
using avrlib::LED_SOURCE_CURRENT;

typedef Led<Led1Port, LED_SOURCE_CURRENT> Led1;
typedef Led<Led2Port, LED_SOURCE_CURRENT> Led2;
  
class Leds {
 public:
  Leds() {}
  static void Init();
  static void Tick();

  static void FlashMidiIn() { FlashLed1(); }
  static void FlashTrigger() { FlashLed2(); }

  static void FlashLed1();
  static void FlashLed2();

 private:

  DISALLOW_COPY_AND_ASSIGN(Leds);
};

extern Leds leds;

}  // namespace midi2trigger

#endif  // MIDI2TRIGGER_LEDS_H_
