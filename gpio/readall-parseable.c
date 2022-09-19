// same as readall, however in a parseable output format

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <wiringPi.h>

extern int wpMode ;

#ifndef TRUE
#  define       TRUE    (1==1)
#  define       FALSE   (1==2)
#endif

/*
 * doReadallParseable:
 *	Read all the GPIO pins
 *	We also want to use this to read the state of pins on an externally
 *	connected device, so we need to do some fiddling with the internal
 *	wiringPi node structures - since the gpio command can only use
 *	one external device at a time, we'll use that to our advantage...
 *********************************************************************************
 */

static char *alts [] =
{
  "IN", "OUT", "ALT5", "ALT4", "ALT0", "ALT1", "ALT2", "OFF"
} ;

// guenter anfang
static int physToWpi [64] =
{
  -1,        // 0
  -1,  -1,   // 1, 2
   8,  -1,   // 3, 4
   9,  -1,   // 5, 6
   7,  15,   // 7, 8
  -1,  16,   // 9, 10
   0,   1,   //11, 12
   2,  -1,   //13, 14
   3,   4,   //15, 16
  -1,   5,   //17, 18
  12,  -1,   //19, 20
  13,   6,   //21, 22
  14,  10,   //23, 24
  -1,  11,   //25, 26
  30,  31,   //27, 28
  21,  -1,   //29, 30
  22,  26,   //31, 32
  23,  -1,   //33, 34
  24,  27,   //35, 36
  25,  28,   //37, 38
  -1,  29,   //39, 40
  -1,  -1, 32, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 41 -> 55
  -1,  -1, -1, -1, -1, -1, -1, -1 // 56 -> 63
} ;
//guenter ende

//guenter orange pi
/*
static char *physNames [64] =
{

  NULL,

  "3.3v", "5v",
  "SDA.0", "5v",
  "SCL.0", "0v",
  "GPIO.7", "TxD1",
  "0v", "RxD1",
  "TxD2", "GPIO.1",
  "RTS2", "0v",
  "CTS2", "RTS1",
  "3.3v", "CTS1",
  "MOSI", "0v",
  "MISO", "RxD2",
  "SCLK", "SPI0_CS",
  "0v", "SPDIFOUT",
  "SDA.1", "SCL.1",
  "PCM0DOUT", "0v",
  "PCM0DIN", "GPIO.26",
  "GPIO.23", "0v",
  "CTS3", "TxD3",
  "GPIO.25", "RTS3",
  "0v", "RxD3",

  "0v", "5v",
  "TxD0", "RxD0",

  NULL, NULL,
  NULL, NULL,
  NULL, NULL,

  "GPIO.17", "GPIO.18",
  "GPIO.19", "GPIO.20",

  NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,

} ;
*/
// guenter ende


/*
 * readallPhys:
 *	Given a physical pin output the data on it
 *  wPi, Mode, Value, Physical
 *********************************************************************************
 */

static void readallPhys (int physPin)
{
  int pin ;

  if (physPinToGpio (physPin) == -1) {
    return;
  }
  else {
    printf ("%d, ", physToWpi [physPin]) ;
  }

  //printf ("%s, ", physNames [physPin]) ;

  if (physToWpi [physPin] == -1)
    printf (", , ") ;
  else
  {
    if (wpMode == WPI_MODE_GPIO)
      pin = physPinToGpio (physPin) ;
    else if (wpMode == WPI_MODE_PHYS)
      pin = physPin ;
    else
      pin = physToWpi [physPin] ;

    printf ("%s, ", alts [getAlt (pin)]) ;
    printf ("%d, ", digitalRead (pin)) ;
  }

  // Pin numbers:

  printf("%d", physPin);
  printf("\n");

}


//guenter
void NanoPiReadAllParseable(void)
{
  int pin ;

  //printf ("Pin, Name, Mode, Value, Physical Pin\n") ;
  printf ("; Pin, Mode, Value, Physical Pin\n") ;

  for (pin = 1 ; pin <= 24 ; pin++)
    readallPhys (pin);

  for (pin = 41 ; pin < 45 ; pin++) {
    readallPhys (pin);
  }

}
//guenter ende

void doReadallParseable (void)
{

  NanoPiReadAllParseable();

}
