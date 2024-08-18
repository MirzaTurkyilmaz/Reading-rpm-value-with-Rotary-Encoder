/*    RPM READING AND COUNTING   */

// Encoder A and B phase pins
const int encoderPinA = 2;
const int encoderPinB = 3;
// Time interval for RPM calculation (in milliseconds)
const unsigned long interval = 100;

// Variables
volatile long pulseCount = 0;
unsigned long lastTime = 0;
long lastPulseCount = 0;
float rpm = 0.0;

void setup() {
  // Start serial communication
  Serial.begin(9600);
  
  // Set encoder pins as input with pull-up resistors
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  
  // Initialize interrupts for both phases (A and B) on change
  attachInterrupt(digitalPinToInterrupt(encoderPinA), countPulseA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), countPulseB, CHANGE);
  
  // Set the initial time
  lastTime = millis();
}

void loop() {
  unsigned long currentTime = millis();

  // Calculate RPM every interval (100 ms in this case)
  if (currentTime - lastTime >= interval) {
    // Number of pulses in the elapsed time
    long currentPulseCount = pulseCount;
    
    // Calculate RPM based on pulse count difference
    rpm = (float)(currentPulseCount - lastPulseCount) * 60.0 / 1600.0; // 1600, encoder CPR x 4 (400 x 4)
    
    // Update variables for the next calculation
    lastPulseCount = currentPulseCount;
    lastTime = currentTime;
    
    // Print the RPM value to the Serial Monitor
    Serial.print("RPM: ");
    Serial.println(rpm);
  }
}

void countPulseA() {
  // Check the status of phase B
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    pulseCount++;
  } else {
    pulseCount--;
  }
}

void countPulseB() {
  // Check the status of phase A
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    pulseCount--;
  } else {
    pulseCount++;
  }
}
