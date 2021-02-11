# DOS RPG Game

Hello!

This is the source code for a DOS top-down RPG game. It's a work in progress and will remain so indefinetely.
If you want to contribute, please contact the author (intbeam) either here, on [Twitter](https://twitter.com/intbeam1), [Twitch](https://twitch.tv/intbeam), [Reddit](https://www.reddit.com/user/intbeam) or [YouTube](https://www.youtube.com/channel/UCH0guQFs0pg-JZdGS34gJbg)!

All the work that goes into this is open source and freely available for everyone.

Expected implementation order :

1. Sprites
2. Tiles
3. Input (keyboard / mouse)
4. Game loop timing / non-constant framerate
5. Game state machine
6. Scripting
7. Gameplay
8. Sound Effects (Sound Blaster)
9. Music (MT-32)

### Sprites

Sprites will be implemented by using a run-length encoded scheme. This means that rather than storing individual pixels (and copying row by row), pixels will be identified by segments which will be 3 or more pixels in a row. Pixels of the same color will be copied using the `STOSB` whereas pixels of varying colors will be copied using the `MOVSB` instruction. Whether this will be a performance benefit or not remains to be seen

### Tiles

In order to support Adaptive Tile Refresh, tiles cannot be stored using run length encoding, because tiles needs to be partially drawn on the edges of the screen. The offsets and data locations of tiles and sprites will be calculated using integer divison and modulo.

### Input

Standard C library functions for keyboard input aren't good enough, as they do not report anything other than ASCII values in the input buffer. We need to read when keys are pressed and released, as well as modifiers such as ctrl and alt.

### Game loop timing

The PC's that are the target does not contain a PET (Programmable Event Timer - introduced in modern PC's by a Microsoft initiative in the late 90's). Only a PIT (Programmable Interval Timer). We will see how this can be used to detect time between frames. Or something else.. The PIT is not very accurate and therefore not reliable enough that we could for example use it for multiplayer.

In modern gameplay loops, a difference value in time between current frame and last frame is used as a multiplier value for every movement, making it possible to support both low and high framerates without affecting the actual speed of the game.

### Game state machine

In order to support the fundamental gameplay mecahnics, a game state machine must be implemented that contains every object, action and movement on the map. This is done by create a service that contains a state, and that can accept (actions) and transmit messaages (events) to outside systems. After this is implemented, it will be possible to save and load games, and implement basic scripting.

### Scripting

In order to implement behavior for objects and actors, a scripting language will be implemented. Its main function will be receiving and generating messages for the game state.

### Gameplay

After all this is implemented, gameplay can be implemented

### Sound effects

Using Sound Blaster and the DMA controller we should be able to implement sound samples (Target 22kHz 16-bit Stereo)

### Music

Being a big fan of Roland MT-32, it would be incredibly cool to support MT-32 for midi music

## Wanted hardware support at some point

Sound Blaster 16  
Gravis Ultrasound  
Keyboard and mouse  
VGA (Mode 13, Mode X)  
CGA  
SVGA  
3Dfx Glide  
Roland MT-32 / MPU-401  
General Midi  
Etherlink III or NE2000  
  
Note : PC Speaker will likely not be supported as it requires the PIT which is likely needed for other cooler things

