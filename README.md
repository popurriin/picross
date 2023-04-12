# Picross
By Baraa Al-Chalabi & Shannon Jones

Picross, otherwise known as Nonogram, is a picture based puzzle game that requires the user to fill in boxes in a grid according to the numbers on the sides to reveal a picture in the end. 

We utilized DE1-SoC's VGA, private timer, audio and PS/2 in C for this project.

In our version of the game, users control where they are in the grid using the WASD keys on the PS/2 keyboard and select boxes using the spacebar. Their current location on the grid is highlighted in black. To fill in the box, simply press the spacebar once. To X out a box (equivalent to being not filled in), press the spacebar again on a filled square. To go back to a completely blank square, press the spacebar one more time.

There are 3 stages total which loop over after being completed.
