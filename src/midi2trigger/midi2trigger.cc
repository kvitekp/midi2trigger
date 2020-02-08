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

#include "avrlib/gpio.h"
#include "avrlib/boot.h"
#include "avrlib/time.h"
#include "avrlib/timer.h"
#include "avrlib/serial.h"
#include "avrlib/watchdog_timer.h"

#include "midi2trigger/midi_out.h"
#include "midi2trigger/midi_handler.h"
#include "midi2trigger/eemem.h"
#include "midi2trigger/trig.h"
#include "midi2trigger/leds.h"
#include "midi2trigger/ui.h"

#include <util/delay.h>

using namespace avrlib;
using namespace midi;
using namespace midi2trigger;

Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
MidiStreamParser<MidiHandler> midi_parser;

// Timer2 ISR: midi i/o and ui

inline void PollMidiIn() {
  // Receive midi input
  if (midi_io.readable()) {
    uint8_t byte = midi_io.ImmediateRead();
    if (byte != 0xfe) {
      if (byte != 0xf8) leds.FlashMidiIn();
      midi_parser.PushByte(byte);
    }
  }
}

inline void SendMidiOut() {
  // Send midi output
  if (MidiHandler::OutputBuffer::readable() && midi_io.writable()) {
    uint8_t byte = MidiHandler::OutputBuffer::ImmediateRead();
    //if (byte != 0xf8) leds.FlashTrigger();
    midi_io.Overwrite(byte);
  }
}

// Sysetem tick timer @4.9KHz

ISR(TIMER2_OVF_vect, ISR_NOBLOCK) {

  trig.Tick();
  PollMidiIn();
  SendMidiOut();

  // Handle lower priority tasks
  static uint8_t sub_clock;
  ++sub_clock;
  if ((sub_clock & 1) == 0) {
    // 2.45KHz
    ui.Poll();
    if ((sub_clock & 3) == 0) {
      // 1.225KHz
      TickSystemClock();
      leds.Tick();
    }
  }
}

void Init() {
  sei();
  UCSR0B = 0;

  // System tick timer @4.9kHz
  Timer<2>::set_prescaler(2);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();

  AccentPorts::set_mode(DIGITAL_OUTPUT);
  AccentPorts::Write(0);

  eemem.Init();
  leds.Init();
  trig.Init();
  dev.Init();
  ui.Init();

  midi_io.Init();
  midi_out.Init();
}

int main(void) {
  ResetWatchdog();
  Init();

  while (1) {
    ui.DoEvents();
  }
}
