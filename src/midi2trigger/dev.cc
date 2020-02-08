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
// Device model implementation.

#include "midi2trigger/midi2trigger.h"
#include "midi2trigger/midi_handler.h"
#include "midi2trigger/eemem.h"
#include "midi2trigger/trig.h"
#include "midi2trigger/leds.h"
#include "midi2trigger/dev.h"
#include "midi2trigger/ui.h"

namespace midi2trigger {

using namespace avrlib;

/* extern */
Dev dev;

/* <static> */
uint8_t Dev::channel_ = kDefChannel;
uint8_t Dev::midi_thru_ = kDefMidiThru;
uint8_t Dev::trigger_notes_[kNumTriggers];
uint8_t Dev::learn_note_index_;
/* </static> */

///////////////////////////////////////////////////////////////////////////////
// Device object handling

/* static */
void Dev::Load() {
  set_channel(eemem.channel());
  set_midi_thru(eemem.midi_thru());
  eemem.trigger_notes(trigger_notes_);
}

/* static */
void Dev::Save() {
  eemem.set_channel(channel_);
  eemem.set_midi_thru(midi_thru_);
  eemem.set_trigger_notes(trigger_notes_);
}

/* static */
void Dev::Reset() {
  eemem.Reset();
  trig.Init();
  Load();
}

///////////////////////////////////////////////////////////////////////////////
// MIDI event handlers

/* static */
void Dev::OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (ui.LearnSwitchLow()) {
    channel_ = channel;
    if (learn_note_index_ >= numbof(trigger_notes_)) learn_note_index_ = 0;
    trigger_notes_[learn_note_index_++] = note;
    ui.DisableLearnSwitchReset();
    ui.RequestDevSave();
  } else

  if (channel != channel_)
    return;

  for (uint8_t n = 0; n < kNumTriggers; n++) {
    if (note == trigger_notes_[n]) {
      AccentPorts::Write(velocity >> 4);
      trig.SetTrigger(n);
    }
  }
}

/* static */
void Dev::OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnAftertouch(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnAftertouch(uint8_t channel, uint8_t velocity) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnControlChange(uint8_t channel, uint8_t controller, uint8_t value) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnProgramChange(uint8_t channel, uint8_t program) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnPitchBend(uint8_t channel, uint16_t pitch_bend) {
  if (channel != channel_)
    return;

  // FIXME: later...
}

/* static */
void Dev::OnSysExByte(uint8_t sysex_byte) {
}

/* static */
void Dev::OnClock() {
}

/* static */
void Dev::OnStart() {
}

/* static */
void Dev::OnContinue() {
}

/* static */
void Dev::OnStop() {
}

/* static */
void Dev::OnRawByte(uint8_t byte) {
}

/* static */
void Dev::OnRawMidiData(
  uint8_t status,
  uint8_t* data,
  uint8_t data_size,
  uint8_t accepted_channel) {
  // Forward all if appropriate
  if (midi_thru_) {
    Send(status, data, data_size);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Output helpers

/* static */
void Dev::Send2(uint8_t a, uint8_t b) {
  FlushOutputBuffer(2);
  MidiHandler::OutputBuffer::Write(a);
  MidiHandler::OutputBuffer::Write(b);
}

/* static */
void Dev::Send3(uint8_t a, uint8_t b, uint8_t c) {
  FlushOutputBuffer(3);
  MidiHandler::OutputBuffer::Write(a);
  MidiHandler::OutputBuffer::Write(b);
  MidiHandler::OutputBuffer::Write(c);
}

/* static */
void Dev::Send(uint8_t status, uint8_t* data, uint8_t size) {
  FlushOutputBuffer(1 + size);
  MidiHandler::OutputBuffer::Write(status);
  while (size--) {
    MidiHandler::OutputBuffer::Write(*data++);
  }
}

/* static */
void Dev::FlushOutputBuffer(uint8_t requested_size) {
  while (MidiHandler::OutputBuffer::writable() < requested_size) {
    midi_out.Send(MidiHandler::OutputBuffer::Read());
  }
}

}  // namespace midi2trigger
