

# RPM Measurement Using an Optical Encoder and Arduino

## Overview

This project demonstrates how to measure the RPM (Revolutions Per Minute) of a rotating object using an optical encoder with an Arduino. The code counts pulses generated by the encoder and calculates the RPM in real-time, displaying the results via the Serial Monitor.

## Features

- **Real-Time RPM Calculation:** Measures RPM based on pulse counts from an optical encoder.
- **Interrupt-Driven Pulse Counting:** Utilizes hardware interrupts to accurately count pulses from the encoder’s A and B phases.
- **Serial Monitor Output:** Displays the calculated RPM values on the Serial Monitor, providing real-time feedback.

## How It Works

1. **Encoder Pin Setup:** The encoder's A and B phase signals are connected to Arduino's interrupt-capable pins (pins 2 and 3 in this example). These pins are configured as inputs with pull-up resistors.
  
2. **Interrupt Service Routines:** Two interrupt service routines (ISRs) are used to monitor the changes in the encoder's phases. The direction of rotation is determined by comparing the states of the A and B phases, and the pulse count is incremented or decremented accordingly.
  
3. **RPM Calculation:** The RPM is calculated every 100 milliseconds based on the difference in pulse count over that time interval. The calculation considers the encoder’s CPR (Counts Per Revolution), with adjustments made for quadrature encoding.
  
4. **Output:** The calculated RPM is sent to the Serial Monitor for display.

## Code Explanation

```cpp
const int encoderPinA = 2;
const int encoderPinB = 3;
const unsigned long interval = 100;
volatile long pulseCount = 0;
unsigned long lastTime = 0;
long lastPulseCount = 0;
float rpm = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), countPulseA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), countPulseB, CHANGE);
  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= interval) {
    long currentPulseCount = pulseCount;
    rpm = (float)(currentPulseCount - lastPulseCount) * 60.0 / 1600.0;
    lastPulseCount = currentPulseCount;
    lastTime = currentTime;
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
}

void countPulseA() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    pulseCount++;
  } else {
    pulseCount--;
  }
}

void countPulseB() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    pulseCount--;
  } else {
    pulseCount++;
  }
}
```

## Hardware Required

- **Arduino Board (e.g., Mega, Uno, etc.)**
- **Optical Encoder**
- **Jumper Wires**
- **Power Supply for Motor (if needed)**

## Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/yourusername/rpm-measurement
   ```

2. Upload the code to your Arduino using the Arduino IDE.

3. Connect the optical encoder's A and B phase pins to the specified Arduino pins.

4. Open the Serial Monitor to view the real-time RPM readings.

## Usage

This code can be used in various projects where precise RPM measurement is required, such as motor control systems, robotics, and automation projects.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.