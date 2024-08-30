# Getting Started with an esp32-with-display
How to get started with a ESP32-3248S035 capacitive 3.5 inch display with an esp32

## Out of the Box
The board was listed on Amazon like this
```
3.5" inch ESP32 Display ESP-WROOM-32 Capacitive Touch Screen TFT LCD Module 320x480 ST7796 ESP32-3248S035C Development Board for Arduino IDE
```
at [this link](https://www.amazon.com/gp/product/B0C4KSKW96)

The front looks like this
![Front](esp32-3248s035_02.png)
The back looks like this
![Back](esp32-3248s035_01.png)

If you power it on it has an image with some buttons in the tabs that look like this
![Profile](esp32-3248s035_03.png)
![Analytics](esp32-3248s035_04.png)
![Shop](esp32-3248s035_05.png)
and has some system stats in the corner also. The LED has turned on with a dim, red. I assume this means it's working.

## Run an Example
The next thing to do is run an example. I have not used PlatformIO for a bit, but that will be my target via VS Code. There seems to be some information [here](https://registry.platformio.org/libraries/rzeldent/esp32_smartdisplay) with an active repo [here](https://github.com/rzeldent/esp32-smartdisplay-demo)

I started by using Git Desktop on Windows to clone the repo, but it seems that both the repo and PlatformIO would like the actual Git to be installed, so I did that by following the links that popped up in VS Code

Since I have not run PlatformIO in a while, it also wanted to run some updates, so I waited for all of that to happen. It seems to want a Microsoft C++ compiler also, but I must have had something the last time I used it. I also seem to be missing Arduino.h (and some other .h files), but again, I should have had this before.

The project wanted to get lvgl (and some other items), which took about 20 minutes.

The Arduino.h error is still there, but the project must have successfully pulled other dependencies as the other .h issues in main.cpp have resolved

A search says that a build still might work, so I plugged in the board via USB and tried the PlatformIO upload button. A lot of errors trying to compile a lot of items, but no change to the header status and no upload to the board

I may have needed to install the driver for the board which one can find [here](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all#drivers-if-you-need-them)
Yep, after installing the driver and relaunching VS Code, I can see the board in the PlatformIO devices list

I tried the upload arrow again, but the build is still not working. Still have the the Arduino.h issue, but it seems to be missing a sub-dependancy, arduino_pins.h.
[This](https://community.platformio.org/t/fatal-error-pins-arduino-h-no-such-file-or-directory/19634/5) says to exit VS Code, remove the .platformio directory and restart VS Code
You will have to wait for PlatformIO to reinstall. There was some CMakeLists.txt dropdown thing going on, but the install seemed to finish and it configured the project and the Arduino.h error is now gone

Getting this far I have also run into [this](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display/blob/main/SETUP.md) helpful repo for an older version of the board. This is where the driver information came from.

The compile is going better and trying to upload to the board now, but it seems to be trying to do all boards.
We need to go to the platformio.ini and uncomment this line to set our board as the default
```
default_envs = esp32-3248S035C
```
This will also trigger a project configuration, which we will have to wait for

This will now compile and upload to the board successfully, but it's just blank now

My earlier attempts may have screwed up the .pio folder that is created. Docs from the example say to delete the directory if there are any changed to the lv_conf.h file. So I will delete that and recompile.
This seems to trigger a long (like 20 min) reinstallation of lvgl. It does compile and load, but it's still blank after this.
It also seemed to need a restart of VS Code to see some of the .h files again.

After finding the screen driver for this board I changed this line in lv_conf.h
```
#define LV_USE_ST7796		1
```
However, it did not seem to help. It did rebuild the .pio directory much faster this time.

## Reset, Back to Basics
I tried a number of things to try to jump to a working example with many features of the board, but none of them would work. So I went back to [this old video](https://dronebotworkshop.com/platformio/) on how to use PlatformIO. Then I got the Sunton (the manufacturer of the board) zip file with this Python code:
```
"""
Download a zip file
"""
import requests, os
from zipfile import ZipFile
from io import BytesIO

url = 'http://pan.jczn1688.com/directlink/1/ESP32%20module/3.5inch_ESP32-3248S035.zip'
dest = 'C:/Users/dave/Downloads'

os.chdir(dest)

# Send a GET request to the URL
response = requests.get(url)

# Check if the request was successful
if response.status_code == 200:
    with ZipFile(BytesIO(response.content)) as zip_file:
        zip_file.extractall()
    print("Files extracted successfully")
else:
    print(f"Failed to download file: {response.status_code}")
```
since browsers now stop you from downloading a zip from a non-https URL. I combined the hello and LED example scripts with a bit of modification and following the video's setup for a project. [This](esp32-hello-world) worked. Now I will have to start layering on features one-by-one the slow, hard way.