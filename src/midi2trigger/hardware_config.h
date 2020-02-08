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
// Hardware configuration.

#ifndef MIDI2TRIGGER_HARDWARE_CONFIG_H_
#define MIDI2TRIGGER_HARDWARE_CONFIG_H_

#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/serial.h"
#include "avrlib/parallel_io.h"
#include "avrlib/devices/switch.h"
#include "avrlib/devices/switch_array.h"

namespace midi2trigger {

using avrlib::Gpio;
using avrlib::LSB_FIRST;
using avrlib::MSB_FIRST;
using avrlib::PARALLEL_TRIPLE_LOW;
using avrlib::PARALLEL_HEXTUPLE_LOW;
using avrlib::PARALLEL_HEXTUPLE_HIGH;
using avrlib::DebouncedSwitch;
using avrlib::ParallelPort;
using avrlib::SwitchArray;
using avrlib::PortB;
using avrlib::PortC;
using avrlib::PortD;
using avrlib::SerialPort0;

// MIDI
typedef SerialPort0 MidiPort;

// Switches
typedef Gpio<PortB, 4> LearnSwitchPort;
typedef DebouncedSwitch< LearnSwitchPort > LearnSwitch;
typedef SwitchArray<6, PortC, PARALLEL_HEXTUPLE_LOW> TriggerSwitches;

// Triggers
typedef ParallelPort<PortD, PARALLEL_HEXTUPLE_HIGH> TriggerPorts;

// Accents
typedef ParallelPort<PortB, PARALLEL_TRIPLE_LOW> AccentPorts;

// LEDs
typedef Gpio<PortB, 5> Led1Port;
typedef Gpio<PortB, 3> Led2Port;

// IO
typedef Gpio<PortB, 0> IOPort;  // Reused Accent1

}  // namespace midi2trigger

#endif  // MIDI2TRIGGER_HARDWARE_CONFIG_H_
