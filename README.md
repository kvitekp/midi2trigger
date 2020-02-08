# MIDI2Trigger

This is a quick and dirty project created for a friend who wanted to use it with DIY Syncussion clone.
- Receive MIDI note events on a pre-selected MIDI Channel (by default MIDI Channel 10).
- Recognize 6 note values (by default starting at #24 C1) and generate positive 5V 10ms pulse when a trigger note is received.
- Detect LEARN switch press and if a MIDI note event is received while it is pressed, assume the event’s MIDI Channel and subsequent notes as triggers.
- Holding down LEARN switch for 10+ seconds without any MIDI Events received resets all device settings to defaults.
- Booting up with the LEARN switch down starts unit in firmware update mode in which firmware can be updated by a SysEx Message.
- Persist MIDI receive channel and trigger note values in non-volatile memory.
- Soft MIDI THRU output -- pass MIDI Events on all other channels to MIDI OUT.
- MIDI IN LED, OUTPUT trigger LED.
- 6 trigger switches.
- 8 level accent (3 port pins).

#### Learn feature
Hold down LEARN switch and press 6 notes to remember as drum triggers then release the switch.

#### Reset to defaults
Hold down LEARN switch for 10+ seconds. The output trigger LED will shortly blink every second counting to 10, then blink rapidly three times to confirm firmware reset.

