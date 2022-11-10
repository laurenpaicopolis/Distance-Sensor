#include <myADC.h>
#include <myGPIO.h>
#include <myTimer.h>
#include <my_ssd1306.h>

// defines pins numbers
const int trigPin = 5;  //D1
const int echoPin = 4;  //D2
const int VALUE_MIN = 2;
const int VALUE_MAX = 92;
long maxDistance;

enum states {idle,instructions,wait1,wait2,measureDistance,changeMaxDistance};
static states state=idle;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  
  // PB initialization
  init_gpio_b(3,0); // 11
  init_gpio_b(4,0); // 12

  // LED initialization
  init_gpio_d(7,1);
  init_gpio_d(6,1);

  // Turn off LED
  gpo_d(7,0);
  gpo_d(6,0);
  
  initSSD1306();
  initADC();
}

void loop() {
  whichState();
}

// Logic of Program
void whichState(){
  
  // defines variables
  long duration;
  long distance;
  uint16_t change;
  bool displayWelcome = true;

  // switch states logic
  switch(state) {

    // idle
    case idle:{
      clearDisplay();
      digitalWrite(trigPin, LOW);
      change=0;
      state=instructions;
      displayWelcome = true; 
      myDelay1ms(500);
    }
    break;

    // instructions - display instructions
    case instructions: {
      if (displayWelcome) {
        setLocation(0, 0);
        writeString("Welcome! Press the start button to begin recording the distance, or press the change distance button to use the potentiometer to change the distance");
      }
      displayWelcome = false;
      maxDistance = 0;

      // measure distance
      if (gpi_b(3)==0) {
        state=wait1; 
      }

      // change max distance
      if (gpi_b(4)==0) {
        state=wait2;
      }  
    }
    break;

    case wait1: {
      clearDisplay();
      state=measureDistance;
    }
    break;

    case wait2: {
      clearDisplay();
      state=changeMaxDistance;
    }
    break;

    // changeMaxDistance changes the minimum distance 
    // the LED will alert user
    case changeMaxDistance: {
      bool keepGoing = true;
      writeString ("Set the max distance by turning the potentiometer");
      setLocation(0, 0);
      myDelay1ms(2000);
      clearDisplay();
      
      while (keepGoing) {
        
        // gets data from potentiometer
        change=readADC(3);
        int distance = map(change, 0, 1023, VALUE_MIN, VALUE_MAX);
        setLocation(0, 0);

        // update max distance to display
        writeString("Max distance:");
        printHexWord(distance);
        myDelay1ms(1000);
        
        // set max distance
        if (gpi_b(3)==0) {
          clearDisplay();
          keepGoing = false;
          maxDistance = distance;
          setLocation(0, 0);
          writeString ("Max Distance Set! Max distance is now: ");
          printHexWord(maxDistance);
          myDelay1ms(1000);
          clearDisplay();
          state=wait1;         
        }

        // go back to start
        if (gpi_b(4)==0) {
          keepGoing = false;
          setLocation(0, 0);
          writeString ("Going back to instructions");
          myDelay1ms(1000);
          state=idle;      
        }
        myDelay1ms(1000);
      }
    }
    break;

    // measureDistance displays and records distance
    case measureDistance: {
      bool keepGoing = true;
      setLocation(0, 0);
      writeString ("We will now start recording the distance!");
      myDelay1ms(2000);
      clearDisplay();
      // illuminate LED when beginning recording
      gpo_d(6,1);

      while (keepGoing) {

        // go back to start
        if (gpi_b(3)==0) {
          keepGoing = false;
          clearDisplay();
          gpo_d(6,0);
          state = idle;
          break;
        }

        // changeMaxDistance
        if (gpi_b(4)==0) {
          keepGoing = false;
          clearDisplay();
          gpo_d(6,0);
          state = changeMaxDistance;
          break;
        }

        // measure distance
        int distance = recordDistance();
        
        // go back to start
        if (gpi_b(3)==0) {
            keepGoing = false;
            clearDisplay();
            gpo_d(6,0);
            state = idle;
            break;
        }

        // changeMaxDistance
        if (gpi_b(4)==0) {
          keepGoing = false;
          clearDisplay();
          gpo_d(6,0);
          state = changeMaxDistance;
          break;
        }
         
        // if within minimum distance, illuminate 
        // LED and display message on OLED
        if (distance <= maxDistance) {
           clearDisplay();
           setLocation(0, 0);
           gpo_d(7,1); 
           myDelay1ms(2000);
           writeString ("Minimum distance reached");
           myDelay1ms(2000);
           clearDisplay();    
        }
        else {
          gpo_d(7,0);
        }

        // print distance to OLED
        setLocation(0, 0);
        writeString ("Distance:"); 
        printHexWord(distance);

        // go back to start
        if (gpi_b(3)==0) {
          keepGoing = false;
          clearDisplay();
          gpo_d(6,0);
          state = idle;
          break;
        }

        // changeMaxDistance
        if (gpi_b(4)==0) {
          keepGoing = false;
          clearDisplay();
          gpo_d(6,0);
          state = changeMaxDistance;
          break;
        }
        myDelay1ms(1000);
    
      }
    }
  break;
  }  
}

// recordDistance records the duration from sensor
// and calculates distance
int recordDistance() {
  long duration, distance;

  // resets trigPin to low
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // send out pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigPin, LOW);

  // read pulse
  duration = pulseIn(echoPin, HIGH);
  
  // calculate distance
  distance = int((duration / 2) / 29.155);
  return distance;
}
