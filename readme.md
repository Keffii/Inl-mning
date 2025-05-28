Uses Wokwi for simulation  
Init_blink(pin number, blink time)

## Platform

The project is developed for **Arduino Uno** (ATmega328P).

---

## Flash Instructions

1. Build the project using your preferred AVR compiler (e.g., avr-gcc).
2. Upload the hex file to the Arduino using e.g. `avrdude`:

   ```sh
   avrdude -c arduino -p m328p -P COMx -b 115200 -U flash:w:project.hex
   ```
   _Replace `COMx` with the correct port and `project.hex` with your hex file._

---

## Verification

- **Photo:**  
  Attach a photo of your Arduino with the LED blinking on the selected pin.

- **Serial log (if applicable):**  
  If you use UART for logging, attach a serial log showing the blinking activity.

---

**Example:**  
An LED connected to digital pin 13 blinks with a 1 second interval.