
// Define interrupt pin
// In EasyIO shield is allways PIN 3
const byte interruptPin = 3;
volatile bool interruptFired = false;

void setup() {

  //Configuring pin 3 like INPUT_PULLUP, with internal pullup resistor
  pinMode(interruptPin, INPUT_PULLUP);

  // Plug pin 3 to the interrupt on falling edge
  // Interrupt is programmed to be done on falling edge of pin 3
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptRoutine, FALLING);
}

void loop() {
  // If the interrupt occurs and you have code that must not be executed inside the interrupt routine, simply log the interrupt using a variable and handle the code in the main loop.
  if (interruptFired) {
    interruptFired = false;
    //Write here the code...
  }
}


/* This the Interrupt Routine */
/* Never use delay() or Serial.print() inside this routine */
void interruptRoutine() {
  /*
  Write here the code of interrupt..........
  */
  //Or set a variable and use it in the main loop 
  interruptFired = true; 
}

