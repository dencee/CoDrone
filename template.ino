#include <CoDrone.h>

#define DEBUG 0

void JoystickControl()
{
  if (PAIRING == true)
  {
    YAW = -1 * CoDrone.AnalogScaleChange(analogRead(A3));
    THROTTLE  = CoDrone.AnalogScaleChange(analogRead(A4));
    ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(A5));
    PITCH = CoDrone.AnalogScaleChange(analogRead(A6));
 
    CoDrone.Control();
  }
}

void MorseCodeLetter( char letter, int timeUnitMs ) {
  if( letter == 'd' ) {
    
  } else if ( letter == 'a' ) {
    
  } else if ( letter == 'n' ) {
    
  } else if ( letter == 'i' ) {
    
  } else if ( letter == 'e' ) {
    
  } else if ( letter == 'l' ) {
    
  }
}

void MorseCodeWords( String message ) {
  int timeUnitMs = 500;

  for( int letter=0; letter < message.length(); letter++ ) {
//    Serial.println(message[letter]);
  }
  
}

void RightTurn( int delayMs = 1000 ) {
  CoDrone.Control();
  delay(delayMs);
}

void LeftTurn( int delayMs = 1000 ) {
  CoDrone.Control();
  delay(delayMs);
}

void Hover( int delayMs = 0 ) {
  CoDrone.Control();
  delay(delayMs);
}

void Straight( int delayMs = 1000 ) {
  CoDrone.Control();
  delay(delayMs);
}

void Up( int delayMs = 1000 ) {
  CoDrone.Control();
  delay(delayMs);
}

void Down( int delayMs = 1000 ) {
  CoDrone.Control();
  delay(delayMs);
}

void setup()
{
#IFDEF DEBUG
  Serial.begin(9600);
  MorseCodeWords("daniel");
#ELSE
  // Set the communication baud rate
  CoDrone.begin(115200);

  // This connects to a specific Drone address
  byte droneAddress[6] = {0x8E, 0xF9, 0xAE, 0x6A, 0x1B, 0xA8};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);

  // Enter additional setup code below!
  MorseCodeWords("daniel");

#ENDIF // DEBUG
}

void loop()
{
  // Check to see that we are paired before trying to fly
  if (PAIRING == true)
  {
    byte bt1 = digitalRead(11);
    byte bt4 = digitalRead(14);
    byte bt8 = digitalRead(18);

    // Kill switch - IR 11 covered only
    if (bt1 && !bt4 && !bt8)
    {
      CoDrone.FlightEvent(Stop);
    }

    if (!bt1 && !bt4 && !bt8) {
      // If no IR sensors are covered allow the joystick to be used
      JoystickControl();
    } else {
      // Your code here
        
    }
  }
}
