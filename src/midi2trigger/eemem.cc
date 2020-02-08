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

#include "midi2trigger/eemem.h"

#include <avr/eeprom.h>

namespace midi2trigger {

using namespace avrlib;

/* extern */
Eemem eemem;

static const uint16_t kEememMagic = 0xdef0;

struct EememData {
  uint16_t magic_;
  uint16_t size_;
  uint8_t channel_;
  uint8_t midi_thru_;
  uint8_t strobe_width_;
  uint8_t trigger_notes_[kNumTriggers];
};

EememData EEMEM eememData;

/* static */
void Eemem::Init() {
  // Check if already initialized
  uint16_t initialized_size = 0;
  if (eeprom_read_word(&eememData.magic_) == kEememMagic) {
    initialized_size = eeprom_read_word(&eememData.size_);
    if (initialized_size == sizeof(EememData))
      return;
  }

  #define FIXSIZE(field) \
    if (initialized_size > sizeof(field)) initialized_size-= sizeof(field); \
    else initialized_size = 0;

  // Init initialization controls
  eeprom_update_word(&eememData.magic_, kEememMagic); FIXSIZE(eememData.magic_);
  eeprom_update_word(&eememData.size_, sizeof(EememData)); FIXSIZE(eememData.size_);

  // Init channel
  if (initialized_size < sizeof(eememData.channel_)) {
    set_channel(kDefChannel);
  } FIXSIZE(eememData.channel_);

  // Init midi_thru
  if (initialized_size < sizeof(eememData.midi_thru_)) {
    set_midi_thru(kDefMidiThru);
  } FIXSIZE(eememData.midi_thru_);

  // Init strobe_width
  if (initialized_size < sizeof(eememData.strobe_width_)) {
    set_strobe_width(kDefStrobeWidth);
  } FIXSIZE(eememData.strobe_width_);

  // Init trigger_note
  if (initialized_size < sizeof(eememData.trigger_notes_)) {
    for (uint8_t n = 0; n < sizeof(eememData.trigger_notes_); n++) {
      set_trigger_note(n, kDefBaseTriggerNote + n);
    }
  } FIXSIZE(eememData.trigger_notes_);

  #undef FIXSIZE
}

/* static */
void Eemem::Reset() {
  eeprom_update_word(&eememData.magic_, ~kEememMagic);
  Init();
}

// Channel

/* static */
uint8_t Eemem::channel() {
  uint8_t channel = eeprom_read_byte(&eememData.channel_);
  if (channel < kMinChannel || channel > kMaxChannel) channel = kDefChannel;
  return channel;
}

/* static */
void Eemem::set_channel(uint8_t channel) {
  eeprom_update_byte(&eememData.channel_, channel);
}

// MidiThru

/* static */
uint8_t Eemem::midi_thru() {
  uint8_t midi_thru = eeprom_read_byte(&eememData.midi_thru_);
  if (midi_thru < kMinMidiThru || midi_thru > kMaxMidiThru) midi_thru = kDefMidiThru;
  return midi_thru;
}

/* static */
void Eemem::set_midi_thru(uint8_t midi_thru) {
  eeprom_update_byte(&eememData.midi_thru_, midi_thru);
}

// StrobeWidth

/* static */
uint8_t Eemem::strobe_width() {
  uint8_t strobe_width = eeprom_read_byte(&eememData.strobe_width_);
  if (strobe_width < kMinStrobeWidth || strobe_width > kMaxStrobeWidth) strobe_width = kDefStrobeWidth;
  return strobe_width;
}

/* static */
void Eemem::set_strobe_width(uint8_t strobe_width) {
  eeprom_update_byte(&eememData.strobe_width_, strobe_width);
}

// TriggerNotes

/* static */
uint8_t Eemem::trigger_note(uint8_t index) {
  uint8_t trigger_note = eeprom_read_byte(&eememData.trigger_notes_[index]);
  if (trigger_note > 0x7f) trigger_note = kDefBaseTriggerNote + index;
  return trigger_note;
}

/* static */
void Eemem::set_trigger_note(uint8_t index, uint8_t trigger_note) {
  eeprom_update_byte(&eememData.trigger_notes_[index], trigger_note);
}

/* static */
void Eemem::trigger_notes(uint8_t notes[kNumTriggers]) {
  eeprom_read_block(notes, &eememData.trigger_notes_, sizeof(eememData.trigger_notes_));
  for (uint8_t n = 0; n < kNumTriggers; n++) {
    if (notes[n] > 0x7f) notes[n] = kDefBaseTriggerNote + n;
  }
}

/* static */
void Eemem::set_trigger_notes(const uint8_t notes[kNumTriggers]) {
  eeprom_update_block(notes, &eememData.trigger_notes_, sizeof(eememData.trigger_notes_));
}

}  // namespace midi2trigger

