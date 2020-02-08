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

#ifndef MIDI2TRIGGER_MIDI_OUT_H_
#define MIDI2TRIGGER_MIDI_OUT_H_

#include "midi2trigger/midi2trigger.h"

namespace midi2trigger {

class MidiOut {
 public:
  MidiOut() {}
  static void Init();

  static void Send(uint8_t byte);

 private:

  DISALLOW_COPY_AND_ASSIGN(MidiOut);
};

extern MidiOut midi_out;

}  // namespace midi2trigger

#endif  // MIDI2TRIGGER_MIDI_OUT_H_
