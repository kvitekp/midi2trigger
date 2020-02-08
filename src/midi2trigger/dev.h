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
// Device model declaration.

#ifndef MIDI2TRIGGER_DEV_H_
#define MIDI2TRIGGER_DEV_H_

#include "avrlib/base.h"

#include "midi2trigger/midi2trigger.h"
#include "midi2trigger/midi_out.h"

namespace midi2trigger {

class Dev {
 public:
  Dev() {}

  static void Init() { Load(); }
  
  // Operations

  static void Load();
  static void Save();
  static void Reset();
  
  // MIDI event handlers
  static void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  static void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
  static void OnAftertouch(uint8_t channel, uint8_t note, uint8_t velocity);
  static void OnAftertouch(uint8_t channel, uint8_t velocity);
  static void OnControlChange(uint8_t channel, uint8_t controller, uint8_t value);
  static void OnProgramChange(uint8_t channel, uint8_t program);
  static void OnPitchBend(uint8_t channel, uint16_t pitch_bend);
  static void OnSysExByte(uint8_t sysex_byte);
  static void OnClock();
  static void OnStart();
  static void OnContinue();
  static void OnStop();

  static void OnRawByte(uint8_t byte);

  static void OnRawMidiData(
    uint8_t status,
    uint8_t* data,
    uint8_t data_size,
    uint8_t accepted_channel);
  
  // Device parameter accessors

  #define DEFINE_ACCESSORS(type, name) \
    static type name() { return name##_; } \
    static void set_##name(type name) { name##_ = name; } 

  DEFINE_ACCESSORS(uint8_t, channel)
  DEFINE_ACCESSORS(uint8_t, midi_thru)
  DEFINE_ACCESSORS(uint8_t, learn_note_index)

  #undef DEFINE_ACCESSORS

  static void trigger_notes(uint8_t notes[kNumTriggers]) { memcpy(notes, trigger_notes_, sizeof(trigger_notes_)); }
  static void set_trigger_notes(const uint8_t notes[kNumTriggers]) { memcpy(trigger_notes_, notes, sizeof(trigger_notes_)); }

  // Output helpers

  static void SendNow(uint8_t byte) {
    midi_out.Send(byte);
  }

  static void Send(uint8_t status, uint8_t* data, uint8_t size);
  static void Send2(uint8_t a, uint8_t b);
  static void Send3(uint8_t a, uint8_t b, uint8_t c);

  static void FlushOutputBuffer(uint8_t size);

 private:

  // Persistent data
  static uint8_t channel_;
  static uint8_t midi_thru_;
  static uint8_t trigger_notes_[kNumTriggers];
  static uint8_t learn_note_index_;

  // Volatile data

  DISALLOW_COPY_AND_ASSIGN(Dev);
};

extern Dev dev;

}  // namespace midi2trigger

#endif // MIDI2TRIGGER_DEV_H_
