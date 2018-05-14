# balancing_game

A balancing game, using an Arduino and accelerometer, it has 6 LEDs to show your
"score", the longer you stay balanced more LEDs light up once all the LEDs
light up you win and it flashes all the LEDs in "celebration".
If you lose balance and the accelerometer tilts, the Arduino resets you progress
and turns off all the LEDs.

This code works by measuring tilt on the y axis of an MPU 6050 accelerometer,
if the raw tilt value stays within the threshold set in the code
(mine is set to 1500 to -1500) the Arduino starts turning on the LEDs with a 1 second
interval in between. If the raw tilt value exceeds 1500 or goes below -1500 then
all the LEDs turn off and the Arduino starts the game from the beginning.

Wiring diagrams and stuff is here: https://aaalearn.mystagingwebsite.com/?p=342&preview=true

## Using the code
You will need the Arduino IDE to upload the code to your Arduino.

* Clone or download this repo.
* Open the `following_robot.ino` file in the Arduino IDE.
* Select your board from *tools>board*.
* Upload the code to the board by pressing the Upload button,
  it's the arrow in a circle, at the top left corner of the IDE.

This is my version of this thing I saw on twitter:https://twitter.com/morrill_rob/status/993850732485918720?s=09
