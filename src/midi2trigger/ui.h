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

#ifndef MIDI2TRIGGER_UI_H_
#define MIDI2TRIGGER_UI_H_

#include "midi2trigger/midi2trigger.h"

#include "avrlib/ui/event_queue.h"

namespace midi2trigger {

using namespace avrlib;

enum ControlTypeEx {
  CONTROL_REQUEST = 10,
};

enum RequestControlId {
  REQUEST_UPDATE = 1, 
//REQUEST_SETSTROBEWIDTH,
//REQUEST_SETDRUMNOTES,
};

class Ui {
 public:
  static void Init();

  static void Poll() {
    PollSwitches();
  }

  static void AddRequest(uint8_t id = 0, uint8_t value = 0) {
    queue_.AddEvent(CONTROL_REQUEST, id, value);
  }

  static void TouchQueue() {
    queue_.Touch();
  }

  static void DisableLearnSwitchReset() { 
    disable_learn_switch_reset_ = 1;
  }

  static uint8_t LearnSwitchLow() {
    return learn_switch_.low();
  }

  static void RequestDevSave() {
    request_dev_save_ = 1;
  }

  static void DoEvents();

 private:

  static uint8_t learn_switch_reset_count_;
  static uint8_t disable_learn_switch_reset_;
  static uint8_t request_dev_save_;

  static LearnSwitch learn_switch_;
  static TriggerSwitches trigger_switches_;
  static avrlib::EventQueue<8> queue_;

  static void PollSwitches();

  static void HandleEvent(const Event& e);
  static void HandleRequestEvent(const Event& e);

  static void OnIdle();

};

extern Ui ui;

}  // namespace midi2trigger

#endif // MIDI2TRIGGER_UI_H_
