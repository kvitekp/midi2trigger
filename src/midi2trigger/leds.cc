// Copyright 2013 Peter Kvitek.
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

#include "midi2trigger/leds.h"

namespace midi2trigger {

using namespace avrlib;

/* extern */
Leds leds;

static FlashLed< Led1, 2> led1;
static FlashLed< Led2, 2> led2;

/* static */
void Leds::Init() {
  led1.Init();
  led2.Init();
}

/* static */
void Leds::Tick() {
  led1.Tick();
  led2.Tick();
}

/* static */
void Leds::FlashLed1() {
  led1.On();
}

/* static */
void Leds::FlashLed2() {
  led2.On();
}

}  // namespace midi2trigger
