// This is how the brightness for every LED is stored,  
// Each LED only needs a 'bit' to know if it should be ON or OFF, so 64 Bytes gives you 512 bits= 512 LEDs
// Since we are modulating the LEDs, using 4 bit resolution, each color has 4 arrays containing 64 bits each
byte red0[64], red1[64], red2[64], red3[64];
byte blue0[64], blue1[64], blue2[64], blue3[64];
byte green0[64], green1[64], green2[64], green3[64];

// Color definitions:
const int colorNum    = 14;
const byte RED[3]     = {15,0,0};
const byte ORANGE[3]  = {15,7,0};
const byte YELLOW[3]  = {15,15,0};
const byte GREEN[3]   = {0,15,0};
const byte LIME[3]    = {7,15,0};
const byte SEAFOAM[3] = {0,15,7};
const byte CYAN[3]    = {0,15,15};
const byte SKYBLUE[3] = {0,7,15};
const byte BLUE[3]    = {0,0,15};
const byte PURPLE[3]  = {7,0,15};
const byte MAGENTA[3] = {15,0,15};
const byte FUCHSIA[3] = {15,0,7};
const byte WHITE[3]   = {15,15,15};
const byte BLACK[3]   = {0,0,0};

byte *colors[colorNum] = {RED,ORANGE,YELLOW,LIME,GREEN,SEAFOAM,CYAN,SKYBLUE,BLUE,PURPLE,MAGENTA,FUCHSIA,WHITE,BLACK};

// For a millis timer to cycle through the animations
unsigned long start;
unsigned long workingDelay;
unsigned long current;

// Common brightness setting
int varBright = 0;

struct led
{
  int lev = 0;
  int row = 0;
  int col = 0;
  byte r = 0;
  byte g = 0;
  byte b = 0;
  bool isOn = false;
  /*bool lmax = (lev == 7);
  bool lmin = (lev == 0);
  bool rmax = (row == 7);
  bool rmin = (row == 0);
  bool cmax = (col == 7);
  bool cmin = (col == 0);*/
  //bool dir = true;
};

// This routine is how LEDs are updated, with the inputs for the LED location and its R G and B brightness levels
// LED(level you want 0-7, row you want 0-7, column you want 0-7, red brighness 0-15, green brighness 0-15, blue brighness 0-15);
void LED(int level, int row, int column, byte red, byte green, byte blue)
{


  // First, check and make sure nothing went beyond the limits, just clamp things at either 0 or 7 for location, and 0 or 15 for brightness
  if(level<0) 
  level=0;
  if(level>7)
  level=7;
  if(row<0)
  row=0;
  if(row>7)
  row=7;
  if(column<0)
  column=0;
  if(column>7)
  column=7;  
  if(red<0)
  red=0;
  if(red>15)
  red=15;
  if(green<0)
  green=0;
  if(green>15)
  green=15;
  if(blue<0)
  blue=0;
  if(blue>15)
  blue=15;  
  
  
  //There are 512 LEDs in the cube, so when we write to level 2, column 5, row 4, that needs to be translated into a number from 0 to 511
  
  //This looks confusing, I know...
  int whichbyte = int(((level*64)+(row*8)+column)/8);
  
  // The first level LEDs are first in the sequence, then 2nd level, then third, and so on
  //the (level*64) is what indexes the level's starting place, so level 0 are LEDs 0-63, level 1 are LEDs 64-127, and so on
  
  //The column counts left to right 0-7 and the row is back to front 0-7
  //This means that if you had level 0, row 0, the bottom back row would count from 0-7, 
  
  //so if you looked down on the cube, and only looked at the bottom level
  // 00 01 02 03 04 05 06 07
  // 08 09 10 11 12 13 14 15
  // 16 17 18 19 20 21 22 23
  // 24 25 26 27 28 29 30 31
  // 32 33 34 35 36 37 38 39
  // 40 41 42 43 44 45 46 47  
  // 48 49 50 51 52 53 54 55  
  // 56 57 58 59 60 61 62 63

  //Then, if you incremented the level, the top right of the grid above would start at 64
  //The reason for doing this, is so you don't have to memorize a number for each LED, allowing you to use level, row, column

  //Now, what about the divide by 8 in there?
  //...well, we have 8 bits per byte, and we have 64 bytes in memory for all 512 bits needed for each LED, so
  //we divide the number we just found by 8, and take the integ7er of it, so we know which byte, that bit is located
  //confused? that's ok, let's take an example, if we wanted to write to the LED to the last LED in the cube, we would write a 7, 7, 7
  // giving (7*64)+(7*8)=7 = 511, which is right, but now let's divide it by 8, 511/8 = 63.875, and take the int of it so, we get 63,
  //this is the last byte in the array, which is right since this is the last LED
  
  // This next variable is the same thing as before, but here we don't divide by 8, so we get the LED number 0-511
  int wholebyte=(level*64)+(row*8)+column;
  //This will all make sense in a sec
 
 //This is 4 bit color resolution, so each color contains x4 64 byte arrays, explanation below:
  bitWrite(red0[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 0));
  bitWrite(red1[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 1));
  bitWrite(red2[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 2)); 
  bitWrite(red3[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 3)); 

  bitWrite(green0[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 0));
  bitWrite(green1[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 1));
  bitWrite(green2[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 2)); 
  bitWrite(green3[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 3));

  bitWrite(blue0[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 0));
  bitWrite(blue1[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 1));
  bitWrite(blue2[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 2)); 
  bitWrite(blue3[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 3));
  
  //Are you now more confused?  You shouldn't be!  It's starting to make sense now.  Notice how each line is a bitWrite, which is,
  //bitWrite(the byte you want to write to, the bit of the byte to write, and the 0 or 1 you want to write)
  //This means that the 'whichbyte' is the byte from 0-63 in which the bit corresponding to the LED from 0-511
  //Is making sense now why we did that? taking a value from 0-511 and converting it to a value from 0-63, since each LED represents a bit in 
  //an array of 64 bytes.
  //Then next line is which bit 'wholebyte-(8*whichbyte)'  
  //This is simply taking the LED's value of 0-511 and subracting it from the BYTE its bit was located in times 8
  //Think about it, byte 63 will contain LEDs from 504 to 511, so if you took 505-(8*63), you get a 1, meaning that,
  //LED number 505 is is located in bit 1 of byte 63 in the array

  //is that it?  No, you still have to do the bitRead of the brightness 0-15 you are trying to write,
  //if you wrote a 15 to RED, all 4 arrays for that LED would have a 1 for that bit, meaning it will be on 100%
  //This is why the four arrays read 0-4 of the value entered in for RED, GREEN, and BLUE
  //hopefully this all makes some sense?

}// LED()

void newLED(int level, int row, int column, byte color[])
{
  byte red = color[0];
  byte green = color[1];
  byte blue = color[2];
  // Clamp location between 0 or 7
  // Clamp brightness between 0 or 15
  if (level<0)   level=0;
  if (level>7)   level=7;
  if (row<0)     row=0;
  if (row>7)     row=7;
  if (column<0)  column=0;
  if (column>7)  column=7;
  if (red<0)     red=0;
  if (red>15)    red=15;
  if (green<0)   green=0;
  if (green>15)  green=15;
  if (blue<0)    blue=0;
  if (blue>15)   blue=15;

  int whichbyte = int(((level*64)+(row*8)+column)/8);
  int wholebyte=(level*64)+(row*8)+column;
 
  bitWrite(red0[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 0));
  bitWrite(red1[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 1));
  bitWrite(red2[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 2)); 
  bitWrite(red3[whichbyte], wholebyte-(8*whichbyte), bitRead(red, 3)); 

  bitWrite(green0[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 0));
  bitWrite(green1[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 1));
  bitWrite(green2[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 2)); 
  bitWrite(green3[whichbyte], wholebyte-(8*whichbyte), bitRead(green, 3));

  bitWrite(blue0[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 0));
  bitWrite(blue1[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 1));
  bitWrite(blue2[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 2)); 
  bitWrite(blue3[whichbyte], wholebyte-(8*whichbyte), bitRead(blue, 3));

}// newLED()

void lightLED(int level, int row, int column, byte red, byte green, byte blue, int d)
{
  LED(level,row,column,red,green,blue);
  delay(d);
}

void clean(){
  int ii, jj, kk;
  for(ii=0; ii<8; ii++)
  {
    for(jj=0; jj<8; jj++)
    {
      for(kk=0; kk<8; kk++)
      {
        LED(ii,jj,kk,0,0,0);
      }
    }
  }
}

void lightLevel(int level, byte r, byte g, byte b)
{
  for (int x = 0; x < 8; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      LED(level, x, y, r, g, b);
    }
  }
}

void lightSliceX(int sliceX, byte r, byte g, byte b)
{
  for (int z = 0; z < 8; z++)
  {
    for (int y = 0; y < 8; y++)
    {
      LED(z, sliceX, y, r, g, b);
    }
  }
}

void lightSliceY(int sliceY, byte r, byte g, byte b)
{
  for (int z = 0; z < 8; z++)
  {
    for (int x = 0; x < 8; x++)
    {
      LED(z, x, sliceY, r, g, b);
    }
  }
}

byte* getRandomColor()
{
  return colors[random(13)];
}