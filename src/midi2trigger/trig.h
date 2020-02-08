// Copyright 2015 Peter Kvitek.
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

#ifndef MIDI2TRIGGER_TRIG_H_
#define MIDI2TRIGGER_TRIG_H_

#include "midi2trigger/midi2trigger.h"
#include "midi2trigger/leds.h"

namespace midi2trigger {

class Trig {
 public:
  Trig() {}
  static void Init();
  static void Tick();

  static void SetTrigger(uint8_t index) {
    SetStrobe(index);
    leds.FlashTrigger();
  }

  static void SetGate(uint8_t index, uint8_t value);
  static void SetStrobe(uint8_t index);
  
  static void SetStrobeWidth(uint8_t width);
  static uint8_t GetStrobeWidth();

 private:

  static uint8_t value_;
  static uint8_t latched_value_;
  static uint8_t strobe_count_[kNumTriggers];
  static uint8_t strobe_ticks_;
  static uint8_t strobe_mask_;
  static uint8_t strobe_inv_;

  static TriggerPorts ports_;

  static void Write(uint8_t value) {
    ports_.Write(value ^ strobe_inv_);
    latched_value_ = value_;
  }

  static uint8_t get() { return value_; }
  static void set(uint8_t value) { value_ = value; }

  DISALLOW_COPY_AND_ASSIGN(Trig);
};

extern Trig trig;

}  // namespace midi2trigger

#endif  // MIDI2TRIGGER_TRIG_H_
