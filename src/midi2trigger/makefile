# Copyright 2011 Olivier Gillet.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

MCU_NAME       = 328
TARGET         = midi2trigger
PACKAGES       = avrlib avrlib/i2c avrlib/devices midi2trigger
RESOURCES      = midi2trigger/resources
EXTRA_DEFINES  = -DDISABLE_DEFAULT_UART_RX_ISR -DxENABLE_DEBUG_OUTPUT

LFUSE          = ff
HFUSE          = d4
EFUSE          = fd
LOCK           = 2f

include avrlib/makefile.mk

include $(DEP_FILE)
