/*
Recieves a comma separated string of three integers (0-255) followed by a newline
These values are used to set three PWM outputs set to be moving coil meter readings

 */

// pins for the gauges
const int gauge_1 = 9;
const int gauge_2 = 10;
const int gauge_3 = 11;

// values for each gauge
int reading_1 = 0;
int reading_2 = 0;
int reading_3 = 0;

boolean input_complete = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(gauge_1, OUTPUT); 
  pinMode(gauge_2, OUTPUT); 
  pinMode(gauge_3, OUTPUT); 

}

void loop() {
  if(input_complete) {
    Serial.println("Normalised:");
    Serial.println(reading_1);
    Serial.println(reading_2);
    Serial.println(reading_3);
    
    // set meter readings 
    analogWrite(gauge_1, reading_1);
    analogWrite(gauge_2, reading_2);
    analogWrite(gauge_3, reading_3);
    
    //await further values
    input_complete = false;
  }
}
  

void serialEvent() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    reading_1 = Serial.parseInt(); 
    reading_2 = Serial.parseInt(); 
    reading_3 = Serial.parseInt(); 

    // look for the newline. That's the end of the sentence:
    if (Serial.read() == '\n') {
      // Raw readings
      Serial.println("Recieved:");
      Serial.println(reading_1);
      Serial.println(reading_2);
      Serial.println(reading_3);
      
      // constrain the values to 0 - 255
      reading_1 = constrain(reading_1, 0, 255);
      reading_2 = constrain(reading_2, 0, 255);
      reading_3 = constrain(reading_3, 0, 255);
      input_complete = true;
    }
  }
}








