
// ZMPT101B AC Voltage Sensor Reading using ESP32
// Connected to ADC pin 32

#define ZMPT_PIN 32     // ADC pin for ZMPT101B
const int SAMPLES = 500; // Number of samples per reading
const float ADC_REF = 3.3;   // ADC reference voltage
const int ADC_RES = 4095;    // 12-bit ADC resolution

// Calibration factor (you must adjust this based on your real readings)
float calibrationFactor = 233.0 / 0.43;  // Example: 230V AC gives 1V RMS at output

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ZMPT101B AC Voltage Measurement");
}

void loop() {
  float voltage = getVPP();             // Peak-to-peak voltage (sensor output)
  float Vrms = (voltage / 2.0) * 0.707; // Convert to RMS
  float AC_voltage = Vrms * calibrationFactor; // Apply calibration

  Serial.print("Sensor Vrms: ");
  Serial.print(Vrms, 3);
  Serial.print(" V  |  AC Voltage: ");
  Serial.print(AC_voltage, 1);
  Serial.println(" V");

  delay(1000);
}

// Function to measure peak-to-peak voltage
float getVPP() {
  int minValue = ADC_RES;
  int maxValue = 0;
  unsigned long start_time = millis();

  while ((millis() - start_time) < 1000) { // sample for 1 second
    int readValue = analogRead(ZMPT_PIN);
    if (readValue > maxValue) maxValue = readValue;
    if (readValue < minValue) minValue = readValue;
  }

  float result = ((maxValue - minValue) * ADC_REF) / ADC_RES;
  return result;
}

