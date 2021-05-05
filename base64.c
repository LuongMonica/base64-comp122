//Monica Luong
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "base64.h"

#define STDIN (0)
#define STDOUT (1)
#define BYTE char

// The base64_mapping() subroutine effectively performs a lookup in the base64 table.
// The input table is the index into the base64 table, and the output of this subroutine
// is the corresponding ASCII value.
//     (Note that the padding charater is not associated with this mapping process.)
static BYTE base64_mapping (char input) {
  char output;
  switch (input) {
      case 0 ... 25: // 'A' .. 'Z'
	output = input + ('A' - 0);
	break;
	
      case 26 ... 51: // 'a' .. 'z'
	output = input + ('a' - 26);
	break;
	
      case 52 ... 61: // '0' .. '9'
	output = input + ('0' - 52);
	break;
	
      case 62: // '+'
	 output = input + ('+' - 62);
         break;

      case 63: // '/'
	 output = input + ('/' - 63);
	 break;

      default:
         break;
  }
  return output;
}

// The base64() subroutine performs the base64 encoding of binary input.
// This subroutine obtains input from stdin and emits output to stdout.
// The general algorthim of this subroutine is:
//   1. Read three bytes from stdin
//   2. Marshall the three bytes into a single variable, say 'v'
//   3. Decompose the 24 bits into 4 six-bit units, say 'w', 'x', 'y', and 'z'
//   4. Map each of the variables into the appropriate base64 character
//   5. Fix the values of w, x, y, and z to address the need to pad the output
//   6. Write out the four 6-bit units
    
#define SIX_BIT_MASK (0x3F)
#define W_MASK       (0x3F000000)
#define X_MASK       (0x003F0000)
#define Y_MASK       (0x00003F00)
#define Z_MASK       (0x0000003F)

extern int base64(void) {
  ssize_t bytes_read = 0;
  char three_bytes[3];


  // 1. Read three individual bytes
  bytes_read = read(STDIN, &three_bytes, sizeof(BYTE)*3);
  while (bytes_read != 0) {

    // 2. Marshall the three bytes into a single variable, say 'v'
    int v = ( (three_bytes[0] << (16) ) | ( three_bytes[1] << 8 ) | three_bytes[2] ); 
    
    // 3. Decompose the 24 bits into 4 six-bit units, say 'w', 'x', 'y', and 'z'
    char w, x, y, z;
    w = (char)((v & W_MASK) >> (18) );// use a MASK, bitwise operators and a shift to obtain the value of w
    x = (char)((v & X_MASK) >> (12) );
    y = (char)((v & Y_MASK) >> (6) );
    z = (char)(v & Z_MASK);
      
    // 4. Map each of the variables into the appropriate base64 character
    w = base64_mapping(w);
    x = base64_mapping(x);
    y = base64_mapping(y);
    z = base64_mapping(z);    
    
     // 5. Fix the values of w, x, y, and z to address the need to pad the output
    switch (bytes_read) {
      case 1:
        
	// Add the last padding value
        y = '=';
        z = '=';   	
        // merge;
        break;
      case 2:
	
        // Add the next to last padding value
	z = '=';
        break;

      case 3:
      default:
	// No padding is necessary 
	break;
    }

    // 6. Write out the four 6-bit units
    write(STDOUT, &w, sizeof(BYTE));
    write(STDOUT, &x, sizeof(BYTE));
    write(STDOUT, &y, sizeof(BYTE));
    write(STDOUT, &z, sizeof(BYTE));
    
    // Setup for the next loop
    /*for (int i =0; i<3; i++) {
      three_bytes[i] = (0);
    }*/
    /*w = (0);
    x=(0);
    y=(0);
    z=(0);*/
    bytes_read = read(STDIN, &three_bytes, sizeof(BYTE)*3);
  }
  char w = '\n';
  write(STDOUT, &w, sizeof(BYTE));
  return 0;
}

