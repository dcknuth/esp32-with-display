#include <Arduino.h>

// Rotary Encoder Inputs
#define inputCLK 21
#define inputDT 22

int counter = 0; 
int currentStateCLK;
int previousStateCLK; 

String encdir ="";

void setup() { 
  // Set encoder pins as inputs  
  pinMode(inputCLK,INPUT);
  pinMode(inputDT,INPUT);

  Serial.begin(115200);
  // Read initial state
  previousStateCLK = digitalRead(inputCLK);
} 

void loop() {
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
  // If previous and current state are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK){ 
    // clockwise
    if (digitalRead(inputDT) != currentStateCLK) { 
      counter++;
      encdir = "CW";
    } else {
      // counterclockwise
      counter--;
      encdir = "CCW";
    }
    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
  } 
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK;
  // with our encoder we get +2 to our counter with a clockwise detent move
  // and minus two for a counterclockwise detent move
}