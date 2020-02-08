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

#ifndef MIDI2TRIGGER_MIDI2TRIGGER_H_
#define MIDI2TRIGGER_MIDI2TRIGGER_H_

#include "avrlib/base.h"

#include <string.h>

#ifdef ENABLE_DEBUG_OUTPUT
#include <stdlib.h>
#include <stdio.h>
#endif

#include "midi2trigger/hardware_config.h"
#include "midi2trigger/resources.h"

namespace midi2trigger {

#define MIDI2TRIGGER_VERSION "0.01"

// Configuration

static const uint8_t kNumTriggers = 6;

static const uint8_t kDefBaseTriggerNote = 24;  // C1

static const uint8_t kDefChannel = 10 - 1;
static const uint8_t kMinChannel = 0;
static const uint8_t kMaxChannel = 0xf;

static const uint8_t kDefMidiThru = 1;
static const uint8_t kMinMidiThru = 0;
static const uint8_t kMaxMidiThru = 1;

static const uint8_t kDefStrobeWidth = 5;
static const uint8_t kMinStrobeWidth = 0;
static const uint8_t kMaxStrobeWidth = 5;

// Useful declarations

#define numbof(a)  (sizeof(a)/sizeof(a[0]))
#define lengof(s)  (numbof(s) - 1)

#define max(a,b)  (((a) > (b)) ? (a) : (b))
#define min(a,b)  (((a) < (b)) ? (a) : (b))

#define SETFLAG(f,b)  (f)|= (b)
#define CLRFLAG(f,b)  (f)&=~(b)
#define SETFLAGTO(f,b,c)  if (c) SETFLAG(f,b); else CLRFLAG(f,b);

#define PSTRN(str) PSTR(str), lengof(str)

#ifdef _MSC_VER
#define OFFSETOF(s,m) (uint16_t)offsetof(s,m)
#else
#define OFFSETOF(s,m) (uint16_t)&reinterpret_cast<const volatile char&>((((s *)0)->m))
#endif

#ifndef _MSC_VER
#define assert(expr)  (void)0
#endif

// 50ns @20MHz
static inline void nop() { 
  __asm__ volatile (
    "nop"
    ); 
}

// count*160ns @20MHz, 0=38us
static inline void Delay(uint8_t count) {
  __asm__ volatile (
    "1: dec %0" "\n\t"
    "brne 1b"
    : "=r" (count)
    : "0" (count)
  );
}

// Disable interrupts
class DisableInterrupts {
  uint8_t sreg_;
 public:
   DisableInterrupts() { sreg_= SREG; cli(); }
   ~DisableInterrupts() { SREG = sreg_; }
};

// Profiling aids
struct RaiseDebugPort {
  typedef IOPort DebugPort;
  RaiseDebugPort() { DebugPort::High(); }
  RaiseDebugPort(uint8_t count) { DebugPort::High(); Delay(count); }
  ~RaiseDebugPort() { DebugPort::Low(); }
};

}  // namespace midi2trigger

#endif  // MIDI2TRIGGER_MIDI2TRIGGER_H_
