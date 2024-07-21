
#include <SPI.h>// SPI Library used to clock data out to the shift registers
#include "LorenzoFunctions.h"
#include "DarrahAnimations.h"
#include "PorterRobinsonMirror.h"
#include "MadeonHypermania.h"
#include "PorterRobinsonKnockYourselfOut.h"

#define latch_pin 2   // can use any pin you want to latch the shift registers
#define blank_pin 4   // same, can use any pin you want for this, just make sure you pull up via a 1k to 5V
#define data_pin 11   // used by SPI, must be pin 11 (51 on arduino mega)
#define clock_pin 13  // used by SPI, must be 13 (52 on arduino mega)

/* These variables are used by multiplexing and Bit Angle Modulation Code */

// Used in the code a lot in for(i= type loops
int shift_out;

// Byte to write to the anode shift register, 8 of them, shifting the ON level in each byte in the array
byte anode[8];

// Keeps track of which level we are shifting data to
int level=0;

// This increments through the anode levels
int anodelevel=0;

// Bit Angle Modulation variables to keep track of things
int BAM_Bit, BAM_Counter=0;

/* Other variables */

void setup()
{
  // Most Significant Bit First
  SPI.setBitOrder(MSBFIRST);

  // Mode 0 Rising edge of data, keep clock low  
  SPI.setDataMode(SPI_MODE0);

  // Run the data in at 16MHz/2 - 8MHz
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  // If you need it?
  Serial.begin(9600);
  
  // Kill interrupts until everybody is set up
  noInterrupts();

  /* We use Timer 1 to refresh the cube */

  // Register A all 0's since we're not toggling any pins
  TCCR1A = B00000000;
  
  // Bit 3 set to place in CTC mode, will call an interrupt on a counter match
  // Bits 0 and 1 are set to divide the clock by 64, so 16MHz/64=250kHz
  TCCR1B = B00001011;

  // Bit 1 set to call the interrupt on an OCR1A match  
  TIMSK1 = B00000010;

  // You can play with this, but I set it to 30, which means:
  // Our clock runs at 250kHz, which is 1/250kHz = 4us
  // With OCR1A set to 30, this means the interrupt will be called every (30+1)x4us=124us
  // This gives a multiplex frequency of about 8kHz
  OCR1A=40;

  // Set up the anode array, this is what's written to the anode shift register, to enable each level
  anode[0]=B00000001;
  anode[1]=B00000010;
  anode[2]=B00000100;
  anode[3]=B00001000;
  anode[4]=B00010000;
  anode[5]=B00100000;
  anode[6]=B01000000;
  anode[7]=B10000000;

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); // anode
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);

  // Set up the outputs
  pinMode(latch_pin, OUTPUT); // Latch
  pinMode(data_pin, OUTPUT);  // MOSI DATA
  pinMode(clock_pin, OUTPUT); // SPI Clock
  SPI.begin();                // Start up the SPI library
  interrupts();               // Start multiplexing

} // setup()


void loop()
{
  //blinkTimer(500);
  //timer(5000);
  //oneLedSpiral();
  //gradualBlink(0,0,7,3,1,0,500);
  //wipe_out();
  //basic_rgb_cycle(50);
  //testFunc();
  //blinkRed();
  //fireflies();
  //myRain(500);
  //timeTest(1000);
  ///porterMirror();
  //testFunc();
  //fireworks(10,10,10);
  //expandingCube(50);
  //contractingCube(50);
  //expandingSquare(2);
  //rgbCube();
  //otherTwinkle();
  //twinkleWhite();
  //twinkleColorful();
  //twinkleRedYellowBlue();
  //sinwaveTwo();
  //folder();
  //greenPrint();
  //bluePrint();
  //oneColorFill(10,'r');
  //oneColorFill(10,'g');
  //oneColorFill(10,'b');
  //rainVersionTwo();
  //colorScramble();
  //slices();
  //fillColor(WHITE);
  //bouncyvTwoWhite();
  //bouncyLines();
  //clean();
  //wipe_out();
}// loop()

//This routine is called in the background automatically at frequency set by OCR1A
//In this code, I set OCR1A to 30, so this is called every 124us, giving each level in the cube 124us of ON time
//There are 8 levels, so we have a maximum brightness of 1/8, since the level must turn off before the next level is turned on
//The frequency of the multiplexing is then 124us*8=992us, or 1/992us= about 1kHz
ISR(TIMER1_COMPA_vect)
{
  PORTD |= 1<<blank_pin;//The first thing we do is turn all of the LEDs OFF, by writing a 1 to the blank pin
  //Note, in my bread-boarded version, I was able to move this way down in the cube, meaning that the OFF time was minimized
  //due to signal integrity and parasitic capcitance, my rise/fall times, required all of the LEDs to first turn off, before updating
  //otherwise you get a ghosting effect on the previous level

  //This is 4 bit 'Bit angle Modulation' or BAM, There are 8 levels, so when a '1' is written to the color brightness, 
  //each level will have a chance to light up for 1 cycle, the BAM bit keeps track of which bit we are modulating out of the 4 bits
  //Bam counter is the cycle count, meaning as we light up each level, we increment the BAM_Counter
  if(BAM_Counter==8)
  BAM_Bit++;
  else
  if(BAM_Counter==24)
  BAM_Bit++;
  else
  if(BAM_Counter==56)
  BAM_Bit++;

  BAM_Counter++;//Here is where we increment the BAM counter

  // The BAM bit will be a value from 0-3, and only shift out the arrays corresponding to that bit, 0-3
  // Here's how this works, each case is the bit in the Bit angle modulation from 0-4, 
  // Next, it depends on which level we're on, so the byte in the array to be written depends on which level, but since each level contains 64 LED,
  // we only shift out 8 bytes for each color
  switch (BAM_Bit) 
  {
    case 0:
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(red0[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(green0[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(blue0[shift_out]);
      }
      break;
    case 1:
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(red1[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(green1[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(blue1[shift_out]);
      }
      break;
    case 2:
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(red2[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(green2[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(blue2[shift_out]);
      }
      break;
    case 3:
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(red3[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(green3[shift_out]);
      }
      for (shift_out=level; shift_out<level+8; shift_out++) {
        SPI.transfer(blue3[shift_out]);
      }

      // Here is where the BAM_Counter is reset back to 0, it's only 4 bit, but
      // since each cycle takes 8 counts, it goes 0 8 16 32, and when
      // BAM_counter hits 64 we reset the BAM
      if (BAM_Counter==120) {
        BAM_Counter=0;
        BAM_Bit=0;
      }
      break;
  }

  SPI.transfer(anode[anodelevel]);//finally, send out the anode level byte

  PORTD |= 1<<latch_pin;//Latch pin HIGH
  PORTD &= ~(1<<latch_pin);//Latch pin LOW
  PORTD &= ~(1<<blank_pin);//Blank pin LOW to turn on the LEDs with the new data

  anodelevel++;//inrement the anode level
  level = level+8;//increment the level variable by 8, which is used to shift out data, since the next level woudl be the next 8 bytes in the arrays

  if(anodelevel==8)//go back to 0 if max is reached
  anodelevel=0;
  if(level==64)//if you hit 64 on level, this means you just sent out all 63 bytes, so go back
  level=0;
  pinMode(blank_pin, OUTPUT);//moved down here so outputs are all off until the first call of this function
}// Multiplex BAM
