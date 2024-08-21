#include "LED.h"
#include "ArduinoQueue.h"

void testFunc()
{
  int pause = 0;
  int level = 7;
  int count = 0;
  bool flag = false;
  start = millis();
  pause = 4800;
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
}

void timer(int t)
{
  start = millis();
  while((millis()-start) < t)
  {
  }
}

void blinkTimer(int t)
{
  for (int i = 7; i >= 0; i--)
  {
    start = millis();
    while((millis()-start) < t)
    {
      if (i == 0)
      {
        LED(0,i,0,0,15,0);
      }
      else
      {
        LED(0,i,0,15,0,0);
      }
    }
  }
  for (int i = 7; i >= 0; i--)
  {
    LED(0,i,0,0,0,0);
  }
}

void rainWithSlices()
{
  ///// slices /////
  /*for (int l = 0; l <= 7; l++)
  {
    lightSliceX(l,0,0,15);
    delay(50);
    lightSliceX(l,0,0,0);
  }*/
  bool isSlicing = false;
  int sliceNum = 0;
  int sliceCount = 0;
  ///// slices /////

  int num = 512;

  // max 16 drops at once...
  led raindrops[16];
  byte* ranCo = getRandomColor();
  for (int n = 0; n < num; n++)
  {
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == -1)
      {
        LED(0, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 0;
        raindrops[i].r = 0;
        raindrops[i].g = 0;
        raindrops[i].b = 0;
      }
      if (!raindrops[i].isOn)
      {
        if (random(1,4) == 2)
        {
          //byte* ranCo = getRandomColor();
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 7;
          raindrops[i].r = ranCo[0];
          raindrops[i].g = ranCo[1];
          raindrops[i].b = ranCo[2];
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, raindrops[i].b);
    }
    if (isSlicing) {lightSliceX(sliceNum,0,0,15);}
    delay(50);
    if (isSlicing) {lightSliceX(sliceNum,0,0,0);}
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].isOn)
      {
        LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].lev--;
      }
    }

    if (n % 32 == 0)
    {
      isSlicing = true;
    }

    if (isSlicing)
    {
      if (sliceCount % 2 == 0)
      {
        sliceNum++;
      }
      sliceCount++;
      /*lightSliceX(sliceNum,0,0,15);
      delay(100);
      lightSliceX(sliceNum,0,0,0);*/
    }
    if (sliceNum == 8)
    {
      isSlicing = false;
      sliceNum = 0;
      sliceCount = 0;
    }
  }
}

void expandingSquare(int col)
{
  //int col = 0;
  int lowerBound, upperBound, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    lowerBound = 0 + i;
    upperBound = 7 - i;
    // Light LED:
    // if lev == bound, light inbetween bound
    // else, light only at bounds
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,15,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,15,0,0);
          }
        }
      }
    }
    delay(100);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        if (lev == lowerBound || lev == upperBound)
        {
          // light between
          if (row >= lowerBound && row <= upperBound)
          {
            LED(lev,row,col,0,0,0);
          }
        }
        else if (lev > lowerBound && lev < upperBound)
        {
          if ((row == lowerBound || row == upperBound))
          {
            LED(lev,row,col,0,0,0);
          }
        }
      }
    }
  }
}

void oneLedSpiral()
{
  int l = 7;
  int r = 0;
  int c = 0;
  int d = 5;
  for (l = 7; l >= 0; l--)
  {
    for (r = 0; r < 8; r++)
    {
      LED(l,r,c,0,0,15);
      delay(d);
      LED(l,r,c,0,0,0);
    }
    for (c = 0; c < 8; c++)
    {
      LED(l,r,c,0,0,15);
      delay(d);
      LED(l,r,c,0,0,0);
    }
    for (r = 7; r >= 0; r--)
    {
      LED(l,r,c,0,0,15);
      delay(d);
      LED(l,r,c,0,0,0);
    }
    for (c = 7; c >= 0; c--)
    {
      LED(l,r,c,0,0,15);
      delay(d);
      LED(l,r,c,0,0,0);
    }
  }
}

void spirals()
{
  led leds[4];
  int count = 0;
  for (auto& led : leds)
  {
    led.lev = 7;
    led.row = 1;
    led.col = 0;
    led.r = 0;
    led.g = 0;
    led.b = 0;
    led.isOn = false;
  }

  for (int n = 0; n <= 2048; n++)
  {
    // start the next led spiraling down
    if (count % 128 == 0)
    {
      for (auto& led : leds)
      {
        if (!led.isOn)
        {
          led.isOn = true;
          led.b = 15;
        }
      }
    }

    // light LED if on
    for (auto& led : leds)
    {
      if (led.isOn)
      {
        LED(led.lev,led.row,led.col,led.r,led.g,led.b);
      }
    }
    delay(25);

    // update LED position
    for (auto& led : leds)
    {
      if (led.isOn)
      {
        // need algo to update leds in a spiral lol
        if (led.row > led.col)
        {

        }
      }
    }

    count++;
  }
}

void slices()
{
  byte r = 15;
  byte g = 15;
  byte b = 15;
  for (int z = 0; z < 8; z++)
  {
    lightLevel(z, r, g, b);
    delay(30);
    lightLevel(z, 0, 0, 0);
  }
}

void otherTwinkle()
{
  led twinks[10];
  for (int i = 0; i < 10; i++)
  {
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = 15;
    newLed.g = 15;
    newLed.b = 15;
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    //blinkQ.enqueue(newLed);
    twinks[i] = newLed;
  }

  int r = 0;

  for (int j = 0; j < 500; j++)
  {
    delay(50);
    r = random(10);
    led off = twinks[r];
    LED(off.lev, off.row, off.col, 0, 0, 0);

    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = 15;
    newLed.g = 15;
    newLed.b = 15;
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    twinks[r] = newLed;
  }
}

void fillWhite()
{
  for (int i = 0; i <8; i++)
  {
    for (int j = 0; j <8; j++)
    {
      for (int k = 0; k <8; k++)
      {
        //waitForSerial();
        LED(i,j,k,15,15,15);
        //redPrint();
        delay(50);
      }
    }
  }
}

void bouncyLines(int time)
{
  randomSeed(analogRead(A0));
  bool x,y,z = true;
  led one;
  one.lev = random(7);
  one.row = random(7);
  one.col = random(7);
  one.r = 15;
  one.g = 15;
  one.b = 15;
  randomSeed(analogRead(A1));
  bool xx,yy,zz = false;
  led two;
  two.lev = random(7);
  two.row = random(7);
  two.col = random(7);
  two.r = 15;
  two.g = 15;
  two.b = 15;
  int sel = 0;
  int idx = 0;
  led leds[12];
  led leds2[12];

  start = millis();
  while((millis()-start) < time)
  {
    if (idx == 12)
    {
      idx = 0;
    }
    LED(leds[idx].lev, leds[idx].row, leds[idx].col, 0, 0, 0);
    LED(leds2[idx].lev, leds2[idx].row, leds2[idx].col, 0, 0, 0);
    sel = random(3);
    if (sel == 0)
    {
      if (x)
      {
        one.row++;
      }
      else if (!x && (one.row > 0))
      {
        one.row--;
      }
      if (xx)
      {
        two.row++;
      }
      else if (!xx && (two.row > 0))
      {
        two.row--;
      }
    }
    else if (sel == 1)
    {
      if (y)
      {
        one.col++;
      }
      else if (!y && (one.col > 0))
      {
        one.col--;
      }
      if (yy)
      {
        two.col++;
      }
      else if (!yy && (two.col > 0))
      {
        two.col--;
      }
    }
    else
    {
      if (z)
      {
        one.lev++;
      }
      else if (!z && (one.lev > 0))
      {
        one.lev--;
      }
      if (zz)
      {
        two.lev++;
      }
      else if (!zz && (two.lev > 0))
      {
        two.lev--;
      }
    }
    leds[idx] = one;
    leds2[idx] = two;
    LED(leds[idx].lev, leds[idx].row, leds[idx].col, leds[idx].r, leds[idx].g, leds[idx].b);
    LED(leds2[idx].lev, leds2[idx].row, leds2[idx].col, leds2[idx].r, leds2[idx].g, leds2[idx].b);
    delay(20);
    if (one.row == 7)
    {
      x = false;
    }
    if (one.row == 0)
    {
      x = true;
    }
    if (one.col == 7)
    {
      y = false;
    }
    if (one.col == 0)
    {
      y = true;
    }
    if (one.lev == 7)
    {
      z = false;
    }
    if (one.lev == 0)
    {
      z = true;
    }

    if (two.row == 7)
    {
      xx = false;
    }
    if (two.row == 0)
    {
      xx = true;
    }
    if (two.col == 7)
    {
      yy = false;
    }
    if (two.col == 0)
    {
      yy = true;
    }
    if (two.lev == 7)
    {
      zz = false;
    }
    if (two.lev == 0)
    {
      zz = true;
    }

    idx++;
  }
  clean();
}

void twinkleRedYellowBlue()
{
  int blinkNum = 60;
  byte *ryb[3] = {RED, YELLOW, BLUE};
  // First thought of a queue, now thinking I could just make an array
  // of 10 leds, pick one at random to turn off, then light it again somewhere else?
  ArduinoQueue<led> blinkQ(blinkNum);
  for (int i = 0; i < blinkNum; i++)
  {
    byte *randomColor = ryb[random(3)];
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = randomColor[0];
    newLed.g = randomColor[1];
    newLed.b = randomColor[2];
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    blinkQ.enqueue(newLed);
  }

  for (int j = 0; j < 1000; j++)
  {
    delay(10);
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);

    byte *randomColor = ryb[random(3)];
    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    newLed.r = randomColor[0];
    newLed.g = randomColor[1];
    newLed.b = randomColor[2];
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    blinkQ.enqueue(newLed);
  }
  while (!blinkQ.isEmpty())
  {
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);
  }
}

void twinkleWhite()
{
  // First thought of a queue, now thinking I could just make an array
  // of 10 leds, pick one at random to turn off, then light it again somewhere else?
  int ledNum = 60;
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

  for (int j = 0; j < 1000; j++)
  {
    delay(50);
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

void twinkleColorful()
{
  // First thought of a queue, now thinking I could just make an array
  // of 10 leds, pick one at random to turn off, then light it again somewhere else?
  ArduinoQueue<led> blinkQ(24);
  for (int i = 0; i < 8; i++)
  {
    led newLed1;
    newLed1.lev = random(8);
    newLed1.row = random(8);
    newLed1.col = random(8);
    newLed1.r = random(16);
    newLed1.g = random(16);
    newLed1.b = 0;
    LED(newLed1.lev, newLed1.row, newLed1.col, newLed1.r, newLed1.g, newLed1.b);
    blinkQ.enqueue(newLed1);

    led newLed2;
    newLed2.lev = random(8);
    newLed2.row = random(8);
    newLed2.col = random(8);
    newLed2.r = random(16);
    newLed2.g = 0;
    newLed2.b = random(16);
    LED(newLed2.lev, newLed2.row, newLed2.col, newLed2.r, newLed2.g, newLed2.b);
    blinkQ.enqueue(newLed2);

    led newLed3;
    newLed3.lev = random(8);
    newLed3.row = random(8);
    newLed3.col = random(8);
    newLed3.r = 0;
    newLed3.g = random(16);
    newLed3.b = random(16);
    LED(newLed3.lev, newLed3.row, newLed3.col, newLed3.r, newLed3.g, newLed3.b);
    blinkQ.enqueue(newLed3);
  }

  for (int j = 0; j < 1000; j++)
  {
    delay(50);
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);

    led newLed;
    newLed.lev = random(8);
    newLed.row = random(8);
    newLed.col = random(8);
    if (j % 3 == 0)
    {
      newLed.r = 0;
      newLed.g = random(16);
      newLed.b = random(16);
    }
    if (j % 3 == 1)
    {
      newLed.r = random(16);
      newLed.g = 0;
      newLed.b = random(16);
    }
    if (j % 3 == 2)
    {
      newLed.r = random(16);
      newLed.g = random(16);
      newLed.b = 0;
    }
    LED(newLed.lev, newLed.row, newLed.col, newLed.r, newLed.g, newLed.b);
    blinkQ.enqueue(newLed);
  }
  while (!blinkQ.isEmpty())
  {
    led off = blinkQ.dequeue();
    LED(off.lev, off.row, off.col, 0, 0, 0);
  }
}

void myRain(int it)
{
  // max 16 drops at once...
  led raindrops[16];
  //byte* ranCo = getRandomColor();
  for (int n = 0; n < it; n++)
  {
    for (int i = 0; i < 16; i++)
    {
      if (raindrops[i].lev == -1)
      {
        LED(0, raindrops[i].row, raindrops[i].col, 0, 0, 0);
        raindrops[i].isOn = false;
        raindrops[i].col = 0;
        raindrops[i].row = 0;
        raindrops[i].lev = 0;
        raindrops[i].r = 0;
        raindrops[i].g = 0;
        raindrops[i].b = 0;
      }
      if (!raindrops[i].isOn)
      {
        if (random(1,4) == 2)
        {
          byte* ranCo = getRandomColor();
          raindrops[i].isOn = true;
          raindrops[i].col = random(8);
          raindrops[i].row = random(8);
          raindrops[i].lev = 7;
          raindrops[i].r = ranCo[0];
          raindrops[i].g = ranCo[1];
          raindrops[i].b = ranCo[2];
        }
      }
      LED(raindrops[i].lev, raindrops[i].row, raindrops[i].col, raindrops[i].r, raindrops[i].g, raindrops[i].b);
    }
    delay(50);
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

void fillColor(byte color[])
{
  int r = color[0];
  int g = color[1];
  int b = color[2];
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j <8; j++)
    {
      for (int k = 0; k <8; k++)
      {
        LED(i,j,k,r,g,b);
      }
    }
  }
}

void expandingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 3; i >= 0; i--) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void contractingCube(int d)
{
  int col = 0;
  int min, max, b1, b2;
  bool light = false;
  for (int i = 0; i <= 3; i++) // 4 cubes, 2,4,6,8 cubed
  {
    min = 0 + i;
    max = 7 - i;
    // Light LED when it is along one of the 3 axis within the bounds
    // x: (col == min || col == max) && (row >= min && row <= max)
    // y: (row == min || row == max) && (col >= min && col <= max)
    // z: (lev == min || lev == max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,15,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,15,0,0);
              }
        }
      }
    }
    delay(d);
    for (int lev = 0; lev <= 7; lev++)
    {
      for (int row = 0; row <= 7; row++)
      {
        for (int col = 0; col <= 7; col++)
        {
          /*if ((lev == min || lev == max) && (((col == min || col == max) && (row >= min && row <= max)) || ((row == min || row == max) && (col >= min && col <= max))))
          {
            LED(lev,row,col,0,0,0);
          }*/
          if (((lev == min || lev == max) && (col == min || col == max) && (row >= min && row <= max)) ||
              ((lev == min || lev == max) && (row == min || row == max) && (col >= min && col <= max)) ||
              ((lev >= min && lev <= max) && ((row == min && col == min) || (row == min && col == max) || (row == max && col == min) || (row == max && col == max))))
              {
                LED(lev,row,col,0,0,0);
              }
        }
      }
    }
  }
}

void fireworks (int iterations, int n, int delayx) {
  clean();

  int i, f, e, x;

  float origin_x = 3;
  float origin_y = 3;
  float origin_z = 3;

  int rand_y, rand_x, rand_z;

  float slowrate, gravity;

  // Particles and their position, x,y,z and their movement, dx, dy, dz
  float particles[n][6];
  float lastpart[n][3];

  for (i=0; i < iterations; i++) {
    origin_x = rand() % 4;
    origin_y = rand() % 4;
    origin_z = rand() % 2;
    origin_z +=5;
    origin_x +=2;
    origin_y +=2;
    byte* randColor = colors[random(13)];
    int r = randColor[0];
    int g = randColor[1];
    int b = randColor[2];

    // shoot a particle up in the air
    for (e=0; e < origin_z; e++) {
      LED(e, origin_x, origin_y, r, g, b);
      //x = (50 * e);
      delay(30);
      LED(e, origin_x, origin_y, 0, 0, 0);
      //clean();
    }

    // Fill particle array
    for (f=0; f < n; f++) {
      // Position
      particles[f][0] = origin_x;
      particles[f][1] = origin_y;
      particles[f][2] = origin_z;

      rand_x = rand() % 200;
      rand_y = rand() % 200;
      rand_z = rand() % 200;

      // Movement
      particles[f][3] = 1 - (float)rand_x / 100; // dx
      particles[f][4] = 1 - (float)rand_y / 100; // dy
      particles[f][5] = 1 - (float)rand_z / 100; // dz
    }

    // explode
    for (e=0; e < 25; e++) {
      slowrate = 1 + tan((e + 0.1) / 20) * 10;
      gravity = tan((e + 0.1) / 20) / 2;


      for (f=0; f < n; f++) {
        particles[f][0] += particles[f][3] / slowrate;
        particles[f][1] += particles[f][4] / slowrate;
        particles[f][2] += particles[f][5] / slowrate;
        particles[f][2] -= gravity;

        LED(particles[f][2],particles[f][0],particles[f][1],r,g,b);
        lastpart[f][2]=particles[f][2];
        lastpart[f][0]=particles[f][0];
        lastpart[f][1]=particles[f][1];
      }

      delay(20);
      for (f=0; f < n; f++) {
        LED(lastpart[f][2], lastpart[f][0], lastpart[f][1], 0, 0, 0);
      }
    }
  }
}

void fireflies()
{
  int lev = random(8);
  int row = random(8);
  int col = random(8);
  LED(lev,row,col,15,15,15);
  delay(340);
  LED(lev,row,col,0,0,0);
  lev = random(8);
  row = random(8);
  col = random(8);
  LED(lev,row,col,15,15,15);
  delay(310);
  LED(lev,row,col,0,0,0);
}

void rgbCube()
{
  byte rgbColor[3];

  // Start off with red.
  rgbColor[0] = 15;
  rgbColor[1] = 0;
  rgbColor[2] = 0;  

  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1)
  {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 15; i += 1)
    {
      rgbColor[decColour] -= 1;
      rgbColor[incColour] += 1;
      
      //newLED(0,0,7,rgbColor);
      fillColor(rgbColor);
      //lightSliceX(0, rgbColor[0],rgbColor[1],rgbColor[2]);
      delay(20);
    }
  }
}

void colorScramble()
{
  int k,m = 0;
  for(m=0; m<3; m++)
  {
    for(k=0; k<200; k++)
    {
      LED(random(8),random(8),random(8),random(16),random(16),0);
      LED(random(8),random(8),random(8),random(16),0 ,random(16));
      LED(random(8),random(8),random(8),0, random(16),random(16));
    }
    for(k=0; k<200; k++)
    {
      LED(random(8),random(8),random(8),0,0,0);
      LED(random(8),random(8),random(8),0,0,0);
      LED(random(8),random(8),random(8),0,0,0);
    }
  }
}

void blink()
{
  int d = 500;
  LED(0,0,7,15,0,0);
  delay(d);
  LED(0,0,7,0,0,0);
  delay(d);
}

void gradualBlink(int level, int row, int col, byte r, byte g, byte b, int d)
{
  byte color[3] = {r,g,b};
  LED(level,row,col,color[0],color[1],color[2]);
  delay(d);
  LED(level,row,col,0,0,0);
  delay(d);
  /*for (int m = 0; m < 15; m++)
  {
    LED(0,0,7,m,m,m);
    delay(d);
  }
  for (int n = 15; n > 0; n--)
  {
    LED(0,0,7,n,n,n);
    delay(d);
  }*/
}

void waitForSerial()
{
  while(Serial.available()){Serial.read();}
  while (!Serial.available()) { }
  //Serial.println(Serial.read());
}

void oneColorFill(int d, char color)
{
  int i,j,k;

  if (color == 'w')
  {
    for (i = 0; i <8; i++)
    {
      for (j = 0; j <8; j++)
      {
        for (k = 0; k <8; k++)
        {
          //waitForSerial();
          LED(i,j,k,15,15,15);
          //redPrint();
          delay(d);
        }
      }
    }
  }

  if (color == 'r')
  {
    for (i = 0; i <8; i++)
    {
      for (j = 0; j <8; j++)
      {
        for (k = 0; k <8; k++)
        {
          //waitForSerial();
          LED(i,j,k,15,0,0);
          //redPrint();
          delay(d);
        }
      }
    }
  }

  if (color == 'g')
  {
    for (i = 0; i <8; i++)
    {
      for (j = 0; j <8; j++)
      {
        for (k = 0; k <8; k++)
        {
          //waitForSerial();
          LED(i,j,k,0,15,0);
          //greenPrint();
          delay(d);
        }
      }
    }
  }

  if (color == 'b')
  {
    for (i = 0; i <8; i++)
    {
      for (j = 0; j <8; j++)
      {
        for (k = 0; k <8; k++)
        {
          //waitForSerial();
          LED(i,j,k,0,0,15);
          delay(d);
        }
      }
    }
  }
}

void rgb_cycle(int d)
{
  int i,j;
  //int d = 5;
  
  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      LED(i,7,j,15,0,0);
      delay(d);
    }
    delay(d);
  }
  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      LED(i,7,j,0,15,0);
      delay(d);
    }
    delay(d);
  }
  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      LED(i,7,j,0,0,15);
      delay(d);
    }
    delay(d);
  }
}

void basic_rgb_cycle(int del)
{
  int i,j,k;

  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      for (k = 0; k <8; k++)
      {
        LED(i,j,k,15,0,0);
        delay(del);
      }
    }
  }
  
  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      for (k = 0; k <8; k++)
      {
        LED(i,j,k,0,15,0);
        delay(del);
      }
    }
  }
  for (i = 0; i <8; i++)
  {
    for (j = 0; j <8; j++)
    {
      for (k = 0; k <8; k++)
      {
        LED(i,j,k,0,0,15);
        delay(del);
      }
    }
  }
}