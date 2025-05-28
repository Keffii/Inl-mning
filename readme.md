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
<img width="251" alt="Screenshot 2025-05-28 111637" src="https://github.com/user-attachments/assets/c32533c2-c135-446c-a538-95bb4a6ca77d" />



---

**Example:**  
An LED connected to digital pin 1 blinks with a 1 second interval.
