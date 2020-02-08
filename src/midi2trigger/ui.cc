// Copyright 2015 Peter Kvitek.
//
// Author: Peter Kvitek (pete@kvitek.com)
//
// Based on Ambika code by Olivier Gillet (ol.gillet@gmail.com)
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

#include "midi2trigger/ui.h"
#include "midi2trigger/dev.h"
#include "midi2trigger/leds.h"
#include "midi2trigger/trig.h"
//#include "midi2trigger/sysex.h"

namespace midi2trigger {

using namespace avrlib;

/* <static> */
uint8_t Ui::learn_switch_reset_count_;
uint8_t Ui::disable_learn_switch_reset_;
uint8_t Ui::request_dev_save_;

LearnSwitch Ui::learn_switch_;
TriggerSwitches Ui::trigger_switches_;
avrlib::EventQueue<8> Ui::queue_;
/* </static> */

/* extern */
Ui ui;

/* static */
void Ui::Init() {
  trigger_switches_.Init();
  learn_switch_.Init();
}

/* static */
void Ui::PollSwitches() {

  trigger_switches_.Read();
  learn_switch_.Read();

  // Set triggers immediately
  for (uint8_t n = 0; n < kNumTriggers; n++) {
    if (trigger_switches_.lowered(n)) {
      trig.SetTrigger(n);
    }
  }

  // Handle learn switch
  if (learn_switch_.lowered()) {
    dev.set_learn_note_index(0);
  } else
  if (learn_switch_.raised()) {
    disable_learn_switch_reset_ = 0;
  }
}

/* static */
void Ui::DoEvents() {
  while (queue_.available()) {
    Event e = queue_.PullEvent();
    queue_.Touch();
    HandleEvent(e);
  }
  
  if (queue_.idle_time_ms() > 1000) {
    queue_.Touch();
    OnIdle();
  }
}

/* static */
void Ui::HandleEvent(const Event& e) {
  switch (e.control_type) {
    case CONTROL_REQUEST:
      HandleRequestEvent(e);
      break;
  }
}

/* static */
void Ui::HandleRequestEvent(const Event& e) {
  switch (e.control_id) {
    case REQUEST_UPDATE: break;
//  case REQUEST_SETSTROBEWIDTH: sysex.SendStrobeWidth(); break;
//  case REQUEST_SETDRUMNOTES: sysex.SendDrumNotes(); break;
  }
}

/* static */
void Ui::OnIdle() {
  // Save device state if requested
  if (request_dev_save_) {
    request_dev_save_ = 0;
    dev.Save();
  }

  // Reset device if LEARN switch is held for about 10 seconds
  if (learn_switch_.low() && !disable_learn_switch_reset_) {
    ++learn_switch_reset_count_;
    leds.FlashLed2();

    if (learn_switch_reset_count_ == 10) {
      learn_switch_reset_count_ = 0;
      disable_learn_switch_reset_ = 1;
      dev.Reset();
      
      // Flash leds to indicate reset
      for (uint8_t n = 0; n < 3; n++) {
        Led2::On(); _delay_ms(100);
        Led2::Off(); _delay_ms(100);
      }
    }
  } else
    learn_switch_reset_count_ = 0;
}

}  // namespace midi2trigger
