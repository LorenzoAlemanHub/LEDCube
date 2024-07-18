//#include "LED.h"
//#include "ArduinoQueue.h"

void redBlueFlash()
{
  int d = 80;
  lightSliceY(4,15,0,0);
  delay(d);
  lightSliceY(4,0,0,15);
  delay(d);
}