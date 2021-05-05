# base64

You are to write a simple C program that encodes binary data into
base64.  This program is designed to help you better understand the
various binary operators with C. Such operations include: bitwise and
(&). bitwise or (|), bitwise xor (^) and bitwise negate (~).  You also
need to use the shift operators: shift left (<<) and shift right (>>).

There exists a base64 command on ssh.sandbox.csun.edu that you can use
as an example and that can be used to test your program. In your
base64 program, you only have to perform base64 encoding, you do not
have to perform the decoding step nor do you need to implement any of
the options provided by the standard base64 command.

For more information see:

1. $ man base64
1. https://en.wikipedia.org/wiki/Base64
1. https://docs.google.com/spreadsheets/d/1Jlo2GmWvl4bxlPN9GzXsKnl4acyppBWYQjX2S_Bm9oQ/edit#gid=0

## Examples:

    $ which base64
    /usr/bin/base64
    $ /usr/bin/base64 <<< "This is my first input string"
    VGhpcyBpcyBteSBmaXJzdCBpbnB1dCBzdHJpbmcK

    $ echo "This is my second input string" | /usr/bin/base64
    VGhpcyBpcyBteSBzZWNvbmQgaW5wdXQgc3RyaW5nCg==

    $ cat >test_file
    This is my third input string
    ^d
    $ cat test_file | /usr/bin/base64
    VGhpcyBpcyBteSB0aGlyZCBpbnB1dCBzdHJpbmcNXmRUaGlzIGlzIG15IHRoaXJkIGlucHV0IHN0cmluZwo=


## Algorithmic Approach

Your base64 program should follow general approach:

    LOOP
        * read 24-bits (i.e., three bytes) from STDIN, say 'three_bytes'
        * marshall the three bytes into a single variable (of type int), say 'v'
        * decompose the 24 bits into a set of four 6-bit variables (each of type char), say 'w', 'x', 'y', and 'z'
        * map each of the four variables (w, x, y, z) into the appropriate base64 ascii character
        * write each of the four ascii variables (w, x, y, z) to STDOUT
    UNTIL EOF

### Exception:

If the size of the file is not an even multiple of 3 bytes, your last
interation of the above loop will be missing a number of bytes.  That
is to say, the read() system call will return a value of either '1' or
'2' even though your requested '3' bytes. (Reall a return value of '0'
denotes the end of file (EOF), and a value of '3' denotes normal
processing.)

To account for these missing bytes, you need to add appropriate
padding to the base64 oputput. In the case the read() subroutine
returns a '1', you need to:
1. ensure 'v' is padded on the right with 16 zero (0) bits
1. map both 'y' and 'z' to the padding character (=), and not to 'A'

In the case the read() subroutine returns a '2', you need to:
1. ensure 'v' is padded on the right with 8 zero (0) bits
1. map 'z' to the padding character ('='), and not to 'A'

Note that if you appropriately clear (set to all zeros (0)), the value
of three_chars during each loop interation, the variables 'y' and z'
will be padded appropriately.

## Files provided for you:

1. A Makefile to be used to make and test your submission
1. A header file, called: base64.h,
1. A skeleton C file, called base64.c, that you need to enhance to implements the base64() routine
1. A C file, called driver.c, that calls the base64() subroutine
1. A test script, called base64.tester, that you can use and enhance to test your program.


## Sample Make Execution

    $ make test
    cc    -c -o driver.o driver.c
    cc    -c -o base64.o base64.c
    cc -g -o base64 driver.o base64.o
    ./base64.tester
    Testing: "The quick brown fox"
    ... Base64 Encoding: "VGhlIHF1aWNrIGJyb3duIGZveAo="
    ... My Encoding:     "VGhlIHF1aWNrIGJyb3duIGZveAo="
    Success
     
    Testing: "jumped over the lazy dog"
    ... Base64 Encoding: "anVtcGVkIG92ZXIgdGhlIGxhenkgZG9nCg=="
    ... My Encoding:     "anVtcGVkIG92ZXIgdGhlIGxhenkgZG9nCg=="
    Success
 
    Testing: "Not once, but"
    ... Base64 Encoding: "Tm90IG9uY2UsIGJ1dAo="
    ... My Encoding:     "Tm90IG9uY2UsIGJ1dAo="
    Success
 
    Testing: "123,456,789 times"
    ... Base64 Encoding: "MTIzLDQ1Niw3ODkgdGltZXMK"
    ... My Encoding:     "MTIzLDQ1Niw3ODkgdGltZXMK"
    Success


