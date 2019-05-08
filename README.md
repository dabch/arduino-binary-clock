# arduino-binary-clock
This is a simple binary clock to hang onto your wall. It's driven by an Arduino Nano and a DS1307 RTC module (both from a cheap Chinese seller in my case).

Two versions of this project exists: The bare-bone, original version using four shift registers and plain 3mm LEDs and resistors, and one using WS2812b digital LED strips. The former ist in the master branch, the latter can be found in the ws2812 branch.

Time is displayed in a mix of binary and decimal: Each column of leds represents a binary-coded decimal digit. 10:24 would be shown as "1" in the leftmost column, "0" in the second, "2" in the third and "4" in the rightmost colum, each in binary.

The digital-led version supports different colors (and thus, brightnesses) for day and night views. This is necessary because WS2812B LEDs are *very* bright and that's not nice in the bedroom. This version also supports a small physical switch between two arduino pins for quick and easy DST support.
