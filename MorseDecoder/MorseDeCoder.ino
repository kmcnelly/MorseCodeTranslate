#include"MorseCodes.h"

const int buttonPin = 2;
const int UNIT = 1000;

unsigned long tStart = 0; //time start when button pressed
unsigned long tEnd = 0; //time end when button released
long duration = 0; //time button held for

String code = ""; //string containing inputted morse
String wordStr = ""; //string containing inputted letters

//update LED
int lightPin = 13;
int delta  = UNIT / 2;
unsigned long nextTime = 0;
unsigned long now = 0;
boolean isLit = false;

//debounce button
boolean currPress = false;
boolean prevPress = false;

unsigned long lastPressTime = 0;
unsigned long lastReleaseTime = 0;
unsigned long debounceDelay = 50;

boolean isTiming = true;

unsigned long isReleased = 0; //timer that tracks for end-of-word gap
boolean isPrinted = false; //if wordstring has been printed
boolean isDecoded = false; //if code string decoded

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);
}


void convertIncomingMorseCodeToChars() {

  duration = tEnd - tStart;

  if (duration > 0)
  {
    if (duration > (0.66 * UNIT) && duration < (1.33 * UNIT))
    {
      //dot
      code += ".";
      Serial.println("#.#");
    }
    else if (duration > (0.66 * 3 * UNIT) && duration < (1.33 * 3 * UNIT))
    {
      //dash
      code += "-";
      Serial.println("#-#");
    }
    else
    {
      if (duration < (0.66 * UNIT))
      {
        //too short
        Serial.println("#Too short for a dot! Ignored!#");
      }
      else if (duration > (1.33 * UNIT) && duration < (0.66 * 3 * UNIT))
      {
        //too long for dot
        Serial.println("#Too long for a dot, but too short for a dash! Ignored!#");
      }
      else
      {
        //too long for dash
        Serial.println("#Too long for a dash! Ignored!#");
      }
    }
  }
  else //duration is negative *new tStart after tEnd
  {
    if (duration > (-0.66 * UNIT) )
    {
      Serial.println("#Too short of a gap between dot/dash!#");
    }
    else if (duration > (-0.66 * 3 * UNIT) && duration < (-1.33 * 3 * UNIT))
    {
      //end of sequence for a letter
      char letter = morseDecode(code);
      if ((int)letter == 0)
      {
        //print invalid morsecode
        Serial.println("#Not a valid Morse Code!#");
      }
      else
      {
        //print letter
        Serial.print("#Letter: #");
        Serial.println(letter);
        wordStr += letter;
      }
      code = "";
    }
    else {
      if (duration > (-1.33 * UNIT) && duration < (-0.66 * 3 * UNIT)) {
        //invalid space
        Serial.println("#Too long of a gap between dot/dash!#");
      }
      else {
        Serial.println("");
      }
    }
  }
}

void updateLED() {
  now = millis();
  if (now > nextTime)
  {
    if (isLit)
    {
      digitalWrite(lightPin, LOW);
    }
    else
    {
      digitalWrite(lightPin, HIGH);
    }
    isLit = !isLit;
    nextTime = now + delta;
  }
}

void loop() {

  updateLED();

  //resets prevPress check
  if (millis() > lastPressTime)
  {
    prevPress = digitalRead(buttonPin);
    lastPressTime  = millis() + debounceDelay;
  }
  //resets currPress check
  currPress = digitalRead(buttonPin);

  //check if button is pressed=======================
  if (!currPress && !prevPress && isTiming)
  {
    tStart = millis();
    isTiming =  !isTiming;

    isReleased = false;

    convertIncomingMorseCodeToChars();
  }

  //check if button is released======================
  else if (currPress && prevPress && !isTiming)
  {
    tEnd = millis();
    isTiming =  !isTiming;

    isReleased = true;
    isReleased = millis();

    isDecoded = false;
    isPrinted = false;


    convertIncomingMorseCodeToChars();
  }

  //check for invalid code string
  if(code.length() > 6)
  {
    wordStr = "";
    Serial.println("#Code too long to be valid! Dropping all!#");
  }

  //checks gap for end of letter and end of word
  if ((millis() - isReleased > 3 * UNIT && isReleased && !isDecoded))
  {
    //end of sequence for a letter
    char letter = morseDecode(code);
    if ((int)letter == 0)
    {
      //print invalid morsecode
      Serial.println("#Not a valid Morse Code!#");
    }
    else
    {
      //print letter
      Serial.print("#Letter: #");
      Serial.println(letter);
      wordStr += letter;
    }
    code = "";
    isDecoded = !isDecoded;
  }
  //checks if end of word
  else if ((millis() - isReleased > 7 * UNIT && isReleased && !isPrinted))
  {
    //print word
    Serial.println("#space#");
    Serial.print("#Word: #");
    Serial.println(wordStr);
    wordStr = "";
    isPrinted = true;
  }

  // Extra credit: Merge in your convertIncomingCharsToMorseCode() to have a
  // complete encoder/decoder
}
