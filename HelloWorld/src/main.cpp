#include <Arduino.h>
#include <Stepper.h>
//#include <HalfStepper.h>



// put function declarations here:
int myFunction(int, int);
void moveSteps(bool, int, byte);
void moveOneStep(bool);

const int led = 2;
const int betweenSteps = 100;

int outPorts[] = {26,25,33,32};

void setup()
{
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(25, OUTPUT);
  Serial.begin(921600);
  Serial.println("hello from setup");
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
}

void loop() {
  delay(1000);
  digitalWrite(led, HIGH);
  digitalWrite(25, LOW);
  moveSteps(true, 4*60, betweenSteps);
  Serial.println("hello from loop");
  delay(1000);
  digitalWrite(led, LOW);
  digitalWrite(25, HIGH);
  moveSteps(false, 4*60, betweenSteps);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

void moveSteps(bool dir, int steps, byte ms) {
for (int i = 0; i < steps; i++) {
 moveOneStep(dir); // Rotate a step
 delay(ms); // Control the speed
}
}

void moveOneStep(bool dir) {
// Define a variable, use four low bit to indicate the state of port
  static byte out = 0x01;
  // Decide the shift direction according to the rotation direction
  if (dir) {
    // ring shift left
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {
    // ring shift right
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }

  // Output singal to each port
  for (int i = 0; i < 4; i++) {
    int value = (out & (0x01 << i)) ? HIGH : LOW;
    digitalWrite(outPorts[i], value);
    Serial.print(value);
  }
  Serial.println();
}