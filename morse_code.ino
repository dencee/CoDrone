#include <CoDrone.h>
//#define DEBUG

int gMorseCodeTimeUnitMs = 500;

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

void SetLedColor( String color ) {
  if( color.equals("red") ) {
    CoDrone.LedColor( ArmHold, Red, 255 );
  } else if( color.equals("green") ) {
    CoDrone.LedColor( ArmHold, Green, 255 );
  } else if( color.equals("blue") ) {
    CoDrone.LedColor( ArmHold, Blue, 255 );
  } else if( color.equals("off") ) {
    CoDrone.LedColor( ArmNone, Black, 0 );
  }
}

void MorseCodeDash( String color ) {
  SetLedColor(color);
  delay( 3*gMorseCodeTimeUnitMs );
}

void MorseCodeDot( String color ) {
  SetLedColor(color);
  delay( gMorseCodeTimeUnitMs );
}

void MorseCodeSpace() {
  SetLedColor("off");
  delay( gMorseCodeTimeUnitMs );
}

void MorseCodeSpaceLetters() {
  SetLedColor("off");
  delay( 3*gMorseCodeTimeUnitMs );
}

void MorseCodeLetter( String color, char letter ) {
  if( letter == 'd' ) {
    MorseCodeDash( color );
    MorseCodeSpace();
    MorseCodeDot( color );
    MorseCodeSpace();
    MorseCodeDot( color );
  } else if ( letter == 'a' ) {
    MorseCodeDot( color );
    MorseCodeSpace();
    MorseCodeDash( color );
  } else if ( letter == 'n' ) {
    MorseCodeDash( color );
    MorseCodeSpace();
    MorseCodeDot( color );
  } else if ( letter == 'i' ) {
    MorseCodeDot( color );
    MorseCodeSpace();
    MorseCodeDot( color );
  } else if ( letter == 'e' ) {
    MorseCodeDot( color );
  } else if ( letter == 'l' ) {
    MorseCodeDot( color );
    MorseCodeSpace();
    MorseCodeDash( color );
    MorseCodeSpace();
    MorseCodeDot( color );
    MorseCodeSpace();
    MorseCodeDot( color );
  }

  delay(100);
  SetLedColor("off");
}

void MorseCodeWord( String message ) {
  String color[] = {"red", "blue", "green"};

  CoDrone.LedColor( EyeNone, Black, 0 );

  for( int letter=0; letter < message.length(); letter++ ) {
    MorseCodeLetter( color[ letter % 3 ], message[letter] );
    MorseCodeSpaceLetters();
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
#ifdef DEBUG
  Serial.begin(9600);
#else
  // Set the communication baud rate
  CoDrone.begin(115200);

  // This connects to a specific Drone address
  byte droneAddress[6] = {0x8E, 0xF9, 0xAE, 0x6A, 0x1B, 0xA8};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);

  // Enter additional setup code below!

#endif // DEBUG
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
    if( bt1 && !bt4 && !bt8 ) {
      CoDrone.FlightEvent(Stop);
    }

    if( !bt1 && !bt4 && !bt8 ) {
      // If no IR sensors are covered allow the joystick to be used
      JoystickControl();
    } else {
      // Your code here

      if( !bt1 && bt4 && !bt8 ) {
        MorseCodeWord("daniel");
      }
      if( !bt1 && !bt4 && bt8 ) {
        CoDrone.LedColor( ArmHold, Red, 255 );
        delay(2000);
        CoDrone.LedColor( ArmHold, Green, 255 );
        delay(2000);
        CoDrone.LedColor( ArmHold, Blue, 255 );
        delay(2000);
        CoDrone.LedColor( ArmNone, Black, 0 );
        delay(2000);
      }
    }
  }
}
