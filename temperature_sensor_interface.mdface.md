🌡️ Temperature Measurement using PIC16F877A (ADC + LCD)
📌 Project Overview

This project demonstrates how to measure temperature using the PIC16F877A microcontroller by utilizing its built-in Analog-to-Digital Converter (ADC) and displaying the result on a 16x2 LCD.

The analog signal (from a temperature sensor like LM35) is converted into a digital value and processed to display temperature in Celsius.

🧰 Features

Uses internal ADC of PIC16F877A

Displays real-time temperature on LCD

Simple and efficient embedded C code

Compatible with MPLAB + XC8 Compiler

Easy to simulate in Proteus

⚙️ Hardware Requirements

PIC16F877A Microcontroller

16x2 LCD Display

Temperature Sensor (e.g., LM35)

16 MHz Crystal Oscillator

Power Supply (5V)

Connecting Wires

💻 Software Requirements

MPLAB X IDE

XC8 Compiler

Proteus (for simulation)

🔌 Circuit Connections
LCD Connections
LCD Pin	PIC Pin
RS	RB0
E	RB2
D0-D7	PORTD
ADC Input
Sensor Output	PIC Pin
Analog Signal	RA0 (AN0)
🧠 Working Principle

The temperature sensor outputs an analog voltage proportional to temperature.

The ADC inside PIC converts this analog signal into a 10-bit digital value (0–1023).

The temperature is calculated using:

Temperature = (ADC_Value × 5.0 × 100) / 1023

The result is displayed on the LCD.

🔢 ADC Formula Explanation

ADC Resolution = 10-bit → (0 to 1023)

Reference Voltage = 5V

LM35 Output = 10mV per °C

So:

Temp (°C) = (ADC_Value × 5 / 1023) × 100
📂 Code Structure
LCD Functions

lcd_cmd() → Send command to LCD

lcd_data() → Send data to LCD

lcd_string() → Print string

lcd_init() → Initialize LCD

ADC Functions

adc_init() → Initialize ADC module

adc_read(channel) → Read analog value

Main Logic

Read ADC value from channel 0

Convert to temperature

Display on LCD

▶️ How to Run

Open MPLAB X IDE

Create a new XC8 project

Paste the code

Build the project

Upload HEX file to PIC (or simulate in Proteus)

📸 Output Example
Temperature:
27.45 C
🚀 Applications

Temperature monitoring systems

Industrial control systems

Embedded sensor projects

IoT-based environmental monitoring

📌 Notes

Ensure proper ADC reference voltage (5V)

Use delay for stable ADC readings

Sensor calibration may be required

👨‍💻 Author

Akash RA

📜 License

This project is open-source and free to use for educational purposes.
