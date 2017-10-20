#include"MorseCodes.h"

const int buttonPin = 2;
boolean allows = true; //debounce 
const int UNIT = 1000;

unsigned long tStart = 0; //time start when button pressed
unsigned long tEnd = 0; //time end when button released
long duration = 0; //time button held for

unsigned long tWord = 0; //timer that tracks for end-of-word gap
boolean printed = false; //if wordstring has been printed

String code = ""; //string containing inputted morse
String wordStr = ""; //string containing inputted letters

void buttonPressed() {
  if (allows)
  {
    Serial.println("Interrupt");
    tStart = millis();
    allows = !allows;
  }
}
void buttonReleased() {
  if (!allows)
  {
    Serial.println("Interrupt");
    tEnd = millis();
    allows = !allows;
    
    tWord = 0;//resets endofword timer
    printed = false;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonReleased, RISING);
}


void convertIncomingMorseCodeToChars() {
  duration = tEnd - tStart;
  if (duration > 0)
  {
    if (duration > (0.66 * UNIT) && duration < (1.33 * UNIT))
    {
      //dot
      code += ".";
    }
    else if (duration > (0.66 * 3 * UNIT) && duration < (1.33 * 3 * UNIT))
    {
      //dash
      code += "-";
    }
    else
    {
      if (duration < (0.66 * UNIT))
      {
        //too short
      }
      else if (duration > (1.33 * UNIT) && duration < (0.66 * 3 * UNIT))
      {
        //too long for dot
      }
      else
      {
        //too long for dash
      }
    }
  }
  else //duration is negative *new tStart after tEnd
  {
    if (duration < (-0.66 * UNIT) && duration > (-1.33 * UNIT))
    {
      //space
      code += " ";
    }
    else if (duration > (-0.66 * 3 * UNIT) && duration < (-1.33 * 3 * UNIT))
    {
      //end of sequence for a letter
      char letter = morseDecode(code);
      if ((int)letter == 0)
      {
        //print invalid morsecode
        wordStr += letter;
      }
      else
      {
        //print letter
      }
      code = "";
    }
  }
}

void updateLED() {
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingMorseCodeToChars()" and "updateLED()"
  updateLED();
  convertIncomingMorseCodeToChars();
  unsigned long now = millis();
  if((now - tWord) > (7*UNIT) && !printed)
  {
    //print word
    wordStr = "";
    printed = true;
    
  }
  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a
  // complete encoder/decoder
}
