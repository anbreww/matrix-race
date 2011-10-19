# Track generation utilities

These short scripts provide functionality to generate race tracks as C source
files from a monochrome (1 bit) PNG file.

## How to generate the track

First, create a 1-bit PNG file using an image editor. The easiest way to do that
is probably to open the example file (track-0.png) and resize it. The image must
be 8 pixels wide, but can be as high as you like. The microcontroller should be
able to handle tracks several thousand lines long.

In the PNG, black pixels represent obstacles and white pixels are clear track.

Once you have generated the picture, use the following command to convert it to
a text file, where black is replaced with hashes (#) and white becomes spaces.

	./imgtohashes.py image.png > image.txt

If you wish, you can now edit your track in a text editor. Be warned though, the
error checking in these scripts is minimal, so you'll want to make sure your
lines are always 8 characters wide and you don't have any trailing whitespace,
or you may get some weird behaviour. I might add that later if I feel like it.

Anyway, once you have your text file, you can convert it to a source file that
you can then include in the project.

	./hashtocfile.py -f image.txt > new_track.h

This will generate a file with a variable which will be stored in program
memory. You can use switches `-x` to generate hex output instead of binary, and
`-n` if you want to output everything on one line. There isn't really much point
in that, unless you want to be able to copy and paste it more easily. It won't
actually make the file much smaller.


Andrew Watson, October 2011
