#include <Arduino.h>

#define PIN_GREEN 17
#define PIN_BLUE 2
#define PIN_RED 15
#define PIN_WHITE 13
#define PIN_DIAL 12     

#define BAUD_RATE 9600

// Double press setup
unsigned long pressTimeGreen = 0;
bool longPressGreen = false;
bool shortPressGreen = false;

unsigned long pressTimeBlue = 0;
bool longPressBlue = false;
bool shortPressBlue = false;

// Single press setup
int buttonStateBlue = LOW;
int lastButtonStateBlue = LOW;
unsigned long lastChangeTimeBlue = 0;

int buttonStateRed = LOW;
int lastButtonStateRed = LOW;
unsigned long lastChangeTimeRed = 0;

int buttonStateWhite = LOW;
int lastButtonStateWhite = LOW;
unsigned long lastChangeTimeWhite = 0;


// Potentiometer setup
int curDialState;
int lastDialState;
unsigned long dialChangeTime = 0;
int sumSamples = 0;
int countSamples = 0;

void setup() {
  // Start serial monitor
  Serial.begin(BAUD_RATE);
  Serial.println("BEGIN");


  // Buttons
  pinMode(PIN_GREEN, INPUT_PULLDOWN); 
  pinMode(PIN_BLUE, INPUT_PULLDOWN);
  pinMode(PIN_RED, INPUT_PULLDOWN);
  pinMode(PIN_WHITE, INPUT_PULLDOWN);
}

void loop() {

  greenButton();
  blueButton();
  redButton();
  whiteButton();
  dial();

}

// void blueButton() {
//   // Single press checker

//   int nowButtonStateBlue = digitalRead(PIN_BLUE);

//   // If button pin state has changed, record the time point
//   if (nowButtonStateBlue != lastButtonStateBlue) {
//     lastChangeTimeBlue = millis();
//   }

//   if (millis() - lastChangeTimeBlue > 10) {
//     if (buttonStateBlue != nowButtonStateBlue) {
//       buttonStateBlue = nowButtonStateBlue;

//       // Button was pressed
//       if (buttonStateBlue == HIGH) {
//         Serial.println("space");
//       }
//     } 
//   }
//   lastButtonStateBlue = nowButtonStateBlue; // Save the state of last button
// }


void redButton() {
  // Single press checker

  int nowButtonStateRed = digitalRead(PIN_RED);

  // If button pin state has changed, record the time point
  if (nowButtonStateRed != lastButtonStateRed) {
    lastChangeTimeRed = millis();
  }

  if (millis() - lastChangeTimeRed > 10) {
    if (buttonStateRed != nowButtonStateRed) {
      buttonStateRed = nowButtonStateRed;

      // Button was pressed
      if (buttonStateRed == HIGH) {
        Serial.println("delete");
      }
    } 
  }
  lastButtonStateRed = nowButtonStateRed; // Save the state of last button
}

void whiteButton() {
  // Single press checker

  int nowButtonStateWhite = digitalRead(PIN_WHITE);

  // If button pin state has changed, record the time point
  if (nowButtonStateWhite != lastButtonStateWhite) {
    lastChangeTimeWhite = millis();
  }

  if (millis() - lastChangeTimeWhite > 10) {
    if (buttonStateWhite != nowButtonStateWhite) {
      buttonStateWhite = nowButtonStateWhite;

      // Button was pressed
      if (buttonStateWhite == HIGH) {
        Serial.println("playpause");
      }
    } 
  }
  lastButtonStateWhite = nowButtonStateWhite; // Save the state of last button
}


void greenButton() {
    // Check green button press
   if (digitalRead(PIN_GREEN) == LOW) {
      
      pressTimeGreen = 0;

      // Check if button was being pressed
      if (longPressGreen) {
        Serial.println("-");
        longPressGreen = false;
        shortPressGreen = false;
      } else if (shortPressGreen) {
        Serial.println(".");
        shortPressGreen = false;
      }

    } else { 
      // Start press
      if (pressTimeGreen == 0) {
        pressTimeGreen = millis();
      }

      unsigned long elapsedTime = millis() - pressTimeGreen;

      // Check for long press
      if (!longPressGreen) {
        if (elapsedTime > 500) {
          longPressGreen = true;
        }
      }

      // Check for short press
      if (!shortPressGreen) {
        if (elapsedTime > 10) {
          shortPressGreen = true;
        }
      }
    }
}


void blueButton() {
    // Check green button press
   if (digitalRead(PIN_BLUE) == LOW) {
      
      pressTimeBlue = 0;

      // Check if button was being pressed
      if (longPressBlue) {
        Serial.println("doublespace");
        longPressBlue = false;
        shortPressBlue = false;
      } else if (shortPressBlue) {
        Serial.println("space");
        shortPressBlue = false;
      }

    } else { 
      // Start press
      if (pressTimeBlue == 0) {
        pressTimeBlue = millis();
      }

      unsigned long elapsedTime = millis() - pressTimeBlue;

      // Check for long press
      if (!longPressBlue) {
        if (elapsedTime > 500) {
          longPressBlue = true;
        }
      }

      // Check for short press
      if (!shortPressBlue) {
        if (elapsedTime > 10) {
          shortPressBlue = true;
        }
      }
    }
}


void dial() {
  int newDialState = map(analogRead(PIN_DIAL), 0, 4096, 0, 10);
  sumSamples += newDialState;
  countSamples += 1;

  if (countSamples > 50) {
    double avgDialState = sumSamples / countSamples;

    if (avgDialState != lastDialState && millis() - dialChangeTime > 25) {
      Serial.printf("dial %.2f\n", avgDialState);
      lastDialState = avgDialState;
      dialChangeTime = millis();
    }

    sumSamples = 0;
    countSamples = 0;
  }
}