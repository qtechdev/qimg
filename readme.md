# qlsb
A tool for manipulating the least significant bit in an image file.

## usage
- `qlsb -i <string> -o <string> -s <string>`

Hides the `-s` file within the `-i` file and saves at `-o`.

- `qlsb -i <string> -o <string> -x`

Extracts the hidden data from `-i` and saves at `-o`.

## notes
- both images must be of the same dimensions
- only supports png

## footnote
`stb_image.h` and `stb_image_write.h` are public domain files from
http://nothings.org/stb.

The two images of kittens were found on wikimedia commons.
https://commons.wikimedia.org/wiki/File:Kitten_7.jpg
https://commons.wikimedia.org/wiki/File:Juvenile_Ragdoll.jpg
