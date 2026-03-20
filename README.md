# 🔌 Analog to Digital Conversion using PIC16F877A

## 📌 Project Overview

This project demonstrates **Analog-to-Digital Conversion (ADC)** using the **PIC16F877A microcontroller**. The ADC module converts analog signals (like sensor outputs) into digital values that can be processed by the microcontroller.

This is useful in applications such as:

* Temperature sensing 🌡️
* Light intensity measurement 💡
* Voltage monitoring 🔋
* Sensor interfacing systems

---

## 🧠 Features

* Uses built-in **10-bit ADC** of PIC16F877A
* Supports multiple input channels (AN0–AN7)
* Simple and efficient ADC read function
* Compatible with MPLAB XC8 compiler
* Real-time analog signal conversion

---

## 🛠️ Hardware Requirements

* PIC16F877A Microcontroller
* Crystal Oscillator (16 MHz)
* Capacitors (22pF typically)
* Potentiometer / Analog Sensor
* Breadboard & Connecting Wires
* Power Supply (5V)
* LCD (optional for display)

---

## 💻 Software Requirements

* MPLAB X IDE
* XC8 Compiler
* Proteus (optional for simulation)

---

## ⚙️ Circuit Diagram

* Connect analog input (e.g., potentiometer) to **AN0 (RA0)**
* Connect Vref+ and Vref- properly (or use default VDD/VSS)
* Optional: Connect LCD for displaying ADC values

---

## 🧾 Code Explanation

### 🔹 ADC Initialization

```c
void adc_init()
{
    ADCON0 = 0x01;  // Enable ADC, select channel 0
    ADCON1 = 0x80;  // Right justified, Fosc/32
}
```

### 🔹 ADC Read Function

```c
unsigned int adc_read(unsigned int channel)
{
    if(channel > 7) return 0;

    ADCON0 &= 0xC5;              // Clear channel bits
    ADCON0 |= (channel << 3);    // Select channel

    __delay_us(20);              // Acquisition time

    GO_nDONE = 1;                // Start conversion
    while(GO_nDONE);             // Wait for completion

    return ((ADRESH << 8) + ADRESL); // Combine result
}
```

---

## 📊 How It Works

1. Analog signal is applied to an ADC channel (e.g., AN0)
2. ADC converts the analog voltage into a **10-bit digital value (0–1023)**
3. The result is stored in:

   * **ADRESH (High byte)**
   * **ADRESL (Low byte)**
4. Combined result gives full digital output

---

## ▶️ Usage

1. Initialize ADC using `adc_init()`
2. Call `adc_read(channel)` to get digital value
3. Use the value for:

   * Display (LCD/Serial)
   * Control systems
   * Decision making

---

## 📈 Example Output

| Analog Voltage | Digital Value |
| -------------- | ------------- |
| 0V             | 0             |
| 2.5V           | ~512          |
| 5V             | 1023          |

---

## 🚀 Applications

* Embedded systems
* Sensor interfacing
* Data acquisition systems
* Industrial automation

---

## 📚 Future Improvements

* Add LCD display output
* Implement UART for serial monitoring
* Add multiple sensor inputs
* Improve accuracy with calibration

---

## 👨‍💻 Author

**Akash RA**

---

## 📜 License

This project is open-source and available under the **MIT License**.

---

## ⭐ Support

If you found this project helpful, give it a ⭐ on GitHub!
