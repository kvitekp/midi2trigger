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
//
// -----------------------------------------------------------------------------
//
// Onboard EEPROM interface.

#ifndef MIDI2TRIGGER_EEMEM_H_
#define MIDI2TRIGGER_EEMEM_H_

#include "midi2trigger/midi2trigger.h"

namespace midi2trigger {

class Eemem {
 public:
  Eemem() {}
  static void Init();
  static void Reset();

  static uint8_t channel();
  static void set_channel(uint8_t channel);

  static uint8_t midi_thru();
  static void set_midi_thru(uint8_t midi_thru);

  static uint8_t strobe_width();
  static void set_strobe_width(uint8_t strobe_width);

  static uint8_t trigger_note(uint8_t index);
  static void set_trigger_note(uint8_t index, uint8_t note);

  static void trigger_notes(uint8_t notes[kNumTriggers]);
  static void set_trigger_notes(const uint8_t notes[kNumTriggers]);

 private:

  DISALLOW_COPY_AND_ASSIGN(Eemem);
};

extern Eemem eemem;

}  // namespace midi2trigger

#endif // MIDI2TRIGGER_EEMEM_H_
