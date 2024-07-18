//#include "LED.h"
//#include "ArduinoQueue.h"

void blueDownwardRain(int d)
{
  // max 16 drops at once...
  led raindrops[16];
  for (int n = 0; n < 512; n++)
  {
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == -1)
      {
        LED(0, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 7;
        raindrops[i].b = 0;
      }
      if (!raindrops[i].isOn)
      {
        if (random(1,4) == 2)
        {
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 7;
          raindrops[i].b = 15;
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, raindrops[i].b);
    }
    delay(d);
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].isOn)
      {
        LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, 0);
        raindrops[i].lev--;
      }
    }
  }
}

void blueUpwardRain(int d)
{
  // max 16 drops at once...
  led raindrops[16];
  for (int n = 0; n < 512; n++)
  {
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == 8)
      {
        LED(7, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 0;
        raindrops[i].b = 0;
      }
      if (!raindrops[i].isOn)
      {
        if (random(1,4) == 2)
        {
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 0;
          raindrops[i].b = 15;
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, raindrops[i].b);
    }
    delay(d);
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].isOn)
      {
        LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, 0);
        raindrops[i].lev++;
      }
    }
    
  }
}

void blueRain()
{
  // max 16 drops at once...
  led raindrops[16];
  start = millis();
  unsigned long count = 0;
  int rainSpeed = 80;
  int downTime = 15000;
  bool done = false;
  int rainUpdate = 4;

  ///////// down rain //////////

  while((millis()-start) < downTime)
  {
    count = millis() - start;
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == -1)
      {
        //LED(0, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 7;
        raindrops[i].b = 0;
        raindrops[i].g = 0;
      }
      if (!raindrops[i].isOn && !done)
      {
        if (random(1,4) == 2)
        {
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 7;
          raindrops[i].b = 15;
          raindrops[i].g = 15;
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, 0, raindrops[i].g, raindrops[i].b);
    }
    // this wont do since i dont know how many times it will have rainspeed at each defined speed
    // now thinking of something like having a number to count up to in order to update the drops
    // like update drops every 4 counts while between 11s-11.5s, 8 counts between 11.5s-12s, etc.
    if (count >= 11000 && count <= 12500)
    {
      rainSpeed = 180;
    }
    if (count >= 12500 && count <= 13000)
    {
      rainSpeed = 280;
    }
    if (count >= 13000 && count <= 13500)
    {
      rainSpeed = 380;
    }
    if (count >= 13500 && count <= 13800)
    {
      rainSpeed = 480;
    }
    if (count >= 14000 && !done)
    {
      rainSpeed = 2500;
      done = true;
    }
    workingDelay = millis();
    while((millis()-workingDelay) < rainSpeed)
    {}

    if (!done)
    {
      for (int i = 0; i < 16; i++)
      {
        if (raindrops[i].isOn)
        {
          LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, 0, 0, 0);
          raindrops[i].lev--;
        }
      }
    }
  }

  ///////// up rain //////////

  start = millis();
  count = 0;
  rainSpeed = 150;
  int upTime = 12000;
  done = false;

  while((millis()-start) < upTime)
  {
    count = millis() - start;
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == 8)
      {
        //LED(0, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 0;
        raindrops[i].b = 0;
        raindrops[i].g = 0;
      }
      if (!raindrops[i].isOn)
      {
        if (random(1,4) == 2)
        {
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 0;
          raindrops[i].b = 15;
          raindrops[i].g = 15;
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, 0, raindrops[i].g, raindrops[i].b);
    }
    //delay(d);
    if (count < 1000)
    {
      rainSpeed = 120;
    }
    if (count >= 1000 && count <= 2000)
    {
      rainSpeed = 100;
    }
    if (count >= 2000 && count <= 3000)
    {
      rainSpeed = 80;
    }
    if (count >= 3000 && count <= 8000)
    {
      rainSpeed = 70;
    }
    if (count >= 8000)
    {
      rainSpeed = 40;
    }
    workingDelay = millis();
    while((millis()-workingDelay) < rainSpeed)
    {}

    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].isOn)
      {
        LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].lev++;
      }
    }
  }

  ///////// red blinks /////////////
  // 3s blinking
}

void blinkColor(int blinkTime, byte* color)
{
  //byte *ryb[3] = {RED, YELLOW, BLUE};
  //byte *randomColor = ryb[random(3)];
  int numLeds = 20;
  led twinks[numLeds];
  for (int i = 0; i < numLeds; i++)
  {
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = color[0];
    newLed.g = color[1];
    newLed.b = color[2];
    twinks[i] = newLed;
  }

  start = millis();
  while((millis()-start) < blinkTime)
  {
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, twinks[i].r, twinks[i].g, twinks[i].b);
    }
    delay(50);
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
    }
    delay(50);
  }

  for (int i = 0; i < numLeds; i++)
  {
    LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
  }
}

void doubleBlinkColor(int blinkTime, byte* color1, byte* color2)
{
  //byte *ryb[3] = {RED, YELLOW, BLUE};
  //byte *randomColor = ryb[random(3)];
  int numLeds = 20;
  led twinks[numLeds];
  for (int i = 0; i < numLeds; i++)
  {
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    if (i % 2 == 0)
    {
      newLed.r = color1[0];
      newLed.g = color1[1];
      newLed.b = color1[2];
    }
    else
    {
      newLed.r = color2[0];
      newLed.g = color2[1];
      newLed.b = color2[2];
    }
    twinks[i] = newLed;
  }

  start = millis();
  while((millis()-start) < blinkTime)
  {
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, twinks[i].r, twinks[i].g, twinks[i].b);
    }
    delay(50);
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
    }
    delay(50);
  }

  for (int i = 0; i < numLeds; i++)
  {
    LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
  }
}

void timeTest(int t)
{
  start = millis();
  while((millis()-start) < t)
  {
    LED(0,0,0,15,0,0);
  }

  start = millis();
  while((millis()-start) < t)
  {
    LED(0,0,0,0,0,0);
  }
}

void blinkTest()
{
  int numLeds = 20;
  byte *ryb[3] = {RED, YELLOW, BLUE};
  byte *randomColor = ryb[random(3)];
  led twinks[numLeds];
  for (int i = 0; i < numLeds; i++)
  {
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = randomColor[0];
    newLed.g = randomColor[1];
    newLed.b = randomColor[2];
    twinks[i] = newLed;
  }

  for (int n = 0; n <= 100; n++)
  {
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, twinks[i].r, twinks[i].g, twinks[i].b);
    }
    delay(50);
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
    }
    delay(50);
  }

  for (int i = 0; i < numLeds; i++)
  {
    LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
  }
}

void randomLEDs()
{
  int numLeds = 18;
  byte *ryb[6] = {RED, YELLOW, BLUE, WHITE, GREEN, ORANGE};
  
  led twinks[numLeds];
  for (int i = 0; i < numLeds; i++)
  {
    byte *randomColor = ryb[random(6)];
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = randomColor[0];
    newLed.g = randomColor[1];
    newLed.b = randomColor[2];
    twinks[i] = newLed;
  }

  /*for (int n = 0; n <= beats; n++)
  {
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, twinks[i].r, twinks[i].g, twinks[i].b);
    }
    delay(100);
    for (int i = 0; i < numLeds; i++)
    {
      LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
    }
    delay(100);
  }*/
  for (int i = 0; i < numLeds; i++)
  {
    LED(twinks[i].lev, twinks[i].row, twinks[i].col, twinks[i].r, twinks[i].g, twinks[i].b);
  }
  delay(260);
  for (int i = 0; i < numLeds; i++)
  {
    LED(twinks[i].lev, twinks[i].row, twinks[i].col, 0, 0, 0);
  }
  delay(260);

}

void whiteTwinkle()
{
  // First thought of a queue, now thinking I could just make an array
  // of 10 leds, pick one at random to turn off, then light it again somewhere else?
  int ledNum = 32;
  ArduinoQueue<led> blinkQ(ledNum);
  for (int i = 0; i < ledNum; i++)
  {
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = 15;
    newLed.g = 15;
    newLed.b = 15;
    //newLed.g = 7;
    //newLed.b = 1;
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    blinkQ.enqueue(newLed);
  }

  for (int j = 0; j < 128; j++)
  {
    delay(10);
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);

    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = 15;
    newLed.g = 15;
    newLed.b = 15;
    //newLed.g = 7;
    //newLed.b = 1;
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    blinkQ.enqueue(newLed);
  }
  while (!blinkQ.isEmpty())
  {
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);
  }
}

void porterMirror()
{
  int pause = 0;
  int level = 7;
  int count = 0;
  bool flag = false;
  blueRain();
  ///////// pause before color blinks /////////////
  start = millis();
  pause = 4950;
  while((millis()-start) < pause)
  {
    if (!flag)
    {
      count++;
      if (level < 0)
      {
        level = 7;
        flag = !flag;
        continue;
      }
      lightSliceY(level,15,15,15);
      if (count == 110)
      {
        lightSliceY(level,0,0,0);
        count = 0;
        level--;
      }
    }
  }
  lightSliceY(level,0,0,0);
  blinkColor(2800, RED);
  start = millis();
  pause = 200;
  while((millis()-start) < pause)
  {}
  blinkColor(1000, BLUE);
  blinkColor(3000, RED);
  start = millis();
  pause = 1200;
  while((millis()-start) < pause)
  {}
  blinkColor(2000, YELLOW);
  start = millis();
  pause = 300;
  while((millis()-start) < pause)
  {}
  blinkColor(1950, BLUE);
  blinkColor(2850, RED);
  doubleBlinkColor(500,BLUE,YELLOW);
  doubleBlinkColor(1000,BLUE,RED);
  for (int i = 0; i <= 24; i++)
  {
    randomLEDs();
  }
  start = millis();
  pause = 3800;
  flag = false;
  count = 0;
  level = 7;
  while((millis()-start) < pause)
  {
    if (!flag)
    {
      count++;
      if (level < 0)
      {
        level = 7;
        flag = !flag;
        continue;
      }
      lightSliceY(level,15,15,15);
      if (count == 180)
      {
        lightSliceY(level,0,0,0);
        count = 0;
        level--;
      }
    }
  }
  lightSliceY(level,0,0,0);
  whiteTwinkle();
  //bouncyvTwoWhite();
  //blinkColor(1400, WHITE);
}