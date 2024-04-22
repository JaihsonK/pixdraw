# Pixdraw: a free and simple canvas

Pixdraw is a free and simple canvas. Use a mouse or stylus, along with your keyboard to make simple drawings. Drawings are exported in the RGBA format (compatible with the [Dodge Graphics Library](https://github.com/JaihsonK/DGL)).

Pixdraw uses [Raylib](https://www.raylib.com/) as a dependency.

Build with

```sh
make
```

Install to /usr/bin/ with

```sh
make install
```

## Usage

It is best to run Pixdraw through the Terminal. When opening Pixdraw:

- Enter `pixdraw` with no arguments. This will open a 500x500px canvas with a transparent background.
- Enter `pixdraw <width> <height>`. This will open a width*height px canvas with a transparent background.
- Enter `pixdraw <filename>` to open a file for editing.
- Enter `pixdraw stat <filename>` to get statistics on a file.

When you are done drawing, press ctrl+D to exit. You will have a chance to save your drawing through a prompt in the Terminal.

The canvas' background is transparent. The default brush size is 1px,  and the default colour is white. 

The keypad keys 1 through 9 will adjust the brush size; for example if you press 9, your brush will be 9x9 pixels in size.

To change the color, use the following keys:

| Colour | Key |
|-----|-----|
|White   | W|
|Yellow|Y|
|Orange|O|
|Pink|P|
|Red|R|
|Maroon|M|
|Green|G|
|Blue|B|
|Violet|V|
|Black|C|
|Eraser (transparent ink)|E|
|Custom colour|N|

When you use the custom colour option, go to the terminal and follow the prompts. It will ask you to enter a 8-digit hex code. Usually when you are given a hex colour representation, you will get a 6-digit hex code. **If you have a 6-digit code, just add "FF" to the end of the code.** The last two digits are for transparency.
