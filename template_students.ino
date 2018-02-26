#include <CoDrone.h>

void JoystickControl()
{
  YAW = -1 * CoDrone.AnalogScaleChange(analogRead(22));
  THROTTLE  = CoDrone.AnalogScaleChange(analogRead(23));
  ROLL = -1 * CoDrone.AnalogScaleChange(analogRead(24));
  PITCH = CoDrone.AnalogScaleChange(analogRead(25));
 
  CoDrone.Control();
}

void setup()
{
  // Set the communication baud rate
  CoDrone.begin(115200);

  // This connects to any nearby drone
  //CoDrone.AutoConnect(NearbyDrone);

  // This connects to a specific Drone address
  //CoDrone.PrintDroneAddress();
  byte droneAddress[6] = {0x8E, 0xF9, 0xAE, 0x6A, 0x1B, 0xA8};
  CoDrone.AutoConnect(AddressInputDrone, droneAddress);

  // Reset Trim if drone has trouble holding flight
//  CoDrone.Set_TrimReset();

  // Enter additional setup code below!

}

void loop()
{
  // Check to see that we are paired before trying to fly
  if( PAIRING == true ) {
    byte bt2 = digitalRead(12);
    byte bt4 = digitalRead(14);
    byte bt8 = digitalRead(18);

    if( !bt2 && !bt4 && !bt8 ){
      // If no IR sensors are covered allow the joystick to be used
      JoystickControl();
    } else {
      // Kill switch - only IR 18 covered
      if( !bt2 && !bt4 && bt8 ){
        CoDrone.FlightEvent(Stop);
      }

      // Add code below!
      
    }
  }
}
