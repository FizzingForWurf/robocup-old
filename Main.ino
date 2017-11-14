#include "Compass.h"
#include "Infrared.h"

// Debug controls
//#define DEBUG_SENSOR_READINGS

#define BAUD_RATE 9600

// Motor pins
#define PIN_BL 45
#define PIN_FL 47
#define PIN_FR 51
#define PIN_BR 53

static Compass compass;
struct compassValues {
  int bearing;
} static cmp;

static Infrared infrared;
struct infraredValues {
  int direction;
  int strength;
} static ir;

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("Initializing...");

  Wire.begin();

  // Configure motors
  pinMode(PIN_FL, OUTPUT);
  pinMode(PIN_FR, OUTPUT);
  pinMode(PIN_BL, OUTPUT);
  pinMode(PIN_BR, OUTPUT);

  // Initialize sensors
  compass.init();
  infrared.init();

  Serial.println("Initialization complete!");
}

void loop() {
  // Read sensor values
  compass.read(&cmp.bearing);
  infrared.read(&ir.strength, &ir.direction);

#ifdef DEBUG_SENSOR_READINGS
  Serial.print("Bearing=");
  Serial.print(cmp.bearing);
  Serial.print("   Strength=");
  Serial.print(ir.strength);
  Serial.print("   Direction=");
  Serial.println(ir.direction);
#endif
}
