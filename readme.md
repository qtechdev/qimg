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

## todo
- add support for more image formats
- add support for mismatched image dimensions
- add support for different data encodings (1 greyscale pixel can be spread across 4 rgba channels, etc.)
- add dithering support for better hidden image quality

## footnote
`stb_image.h` and `stb_image_write.h` are public domain files from
http://nothings.org/stb.

The two images of kittens were found on wikimedia commons.
https://commons.wikimedia.org/wiki/File:Kitten_7.jpg
https://commons.wikimedia.org/wiki/File:Juvenile_Ragdoll.jpg
