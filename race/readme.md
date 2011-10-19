# Race game track

This folder contains the code specific to the racing game to be played on the 
LED matrix.

It will contain the C code for the main application to load pieces of track into
 memory, and possibly some parts of the game logic. The track can be drawn as a
 1-bit PNG file, then processed with the Python script provided, which will
 convert the image to a text file made of hashes and spaces. The track can also
 be directly input as hashes and spaces (# == 1, _ == 0), using your favourite
 text editor.
 
 Once the track has been converted to hashes, the second python script
 %% TODO: write these scripts and update this file with the correct filenames
 will convert that to a C source file, which contains an array to be stored in
 progmem. 
 
With the current game logic, it is possible to address up to 65K track segments.
The limit will obviously come from the microcontroller's memory limit. The 
Atmega164p has 16K Bytes of memory. The maximum track size will depend on the 
size of the game code, but will necessarily be under 16 thousand lines.