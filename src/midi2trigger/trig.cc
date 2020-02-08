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

#include "midi2trigger/trig.h"
#include "midi2trigger/eemem.h"

namespace midi2trigger {

using namespace avrlib;

/* extern */
Trig trig;

/* <static> */
uint8_t Trig::value_;
uint8_t Trig::latched_value_;
uint8_t Trig::strobe_count_[kNumTriggers];
uint8_t Trig::strobe_ticks_;
uint8_t Trig::strobe_mask_;
uint8_t Trig::strobe_inv_;
/* </static> */

const prog_uint8_t strobe_ticks_from_width[] PROGMEM = {
  5,  // 1ms
  10, // 2ms
  15, // 3ms
  20, // 4ms
  25, // 5ms
  50, // 10ms
};

/* static */
void Trig::Init() {
  ports_.set_mode(DIGITAL_OUTPUT);
  ports_.Write(latched_value_);
  SetStrobeWidth(eemem.strobe_width());
}

/* static */
void Trig::Tick() {
  if (value_ != latched_value_) {
    Write(value_);
  }

  // Update strobe state
  if (strobe_mask_) {
    uint8_t mask = 1;
    for (uint8_t n = 0; n < kNumTriggers; n++, mask<<= 1) {
      if (strobe_mask_ & mask) {
        if (!strobe_count_[n] || --strobe_count_[n] == 0) {
          CLRFLAG(strobe_mask_, mask);
          CLRFLAG(value_, mask);
        }
      }
    }
  }
}

/* static */
void Trig::SetGate(uint8_t index, uint8_t value) {
  uint8_t mask = 1 << index;
  SETFLAGTO(value_, mask, value);
}

/* static */
void Trig::SetStrobe(uint8_t index) {
  uint8_t mask = 1 << index;
  SETFLAG(value_, mask);
  SETFLAG(strobe_mask_, mask);
  strobe_count_[index] = strobe_ticks_;
}

/* static */
void Trig::SetStrobeWidth(uint8_t width) {
  if (width < numbof(strobe_ticks_from_width)) {
    strobe_ticks_ = ResourcesManager::Lookup<uint8_t, uint8_t>(strobe_ticks_from_width, width);
  }
}

/* static */
uint8_t Trig::GetStrobeWidth() {
  for (uint8_t n = 0; n < numbof(strobe_ticks_from_width); n++) {
    if (pgm_read_byte(&strobe_ticks_from_width[n]) == strobe_ticks_)
      return n;
  }
  return kDefStrobeWidth;
}

}  // namespace midi2trigger                           `
