# CASA0016 "Wine Fermentation Monitor"

**Wanna make your own wine at home, but without experience and afraid that you could not control the fermentation process?  I believe this monitor can give you a favor?**

You can follow this document and the repository to help build your own wine fermentation monitor to help you have better control of the fermentation environment. It will introduce the  hardware, software, and some instructions.



## 1. Hardware

**Here are all the hardware you need:**

* Arduino Uno x 1 
* Circuit board x 1 
* 220Ω Resistor x 1 
* 10kΩ Resistor x 1
* Dupont wire x n
* DHT22 x 1 
* MQ135 x 1
* LDR x 1 
* Buzzer x 1 
* LCD x 1

You should assemble them as the follow diagram:

![diagram1](https://github.com/Hazzd12/casa0016-coursework/blob/main/images/circuit%20diagram.png?raw=true)

****

## 2. Software and Instruction

**IDE:** Arduino IDE

**File Structure:** 

```lua
|-- MQ135/              # the file to get MQ135 R0
|   |-- MQ135.ino
|-- main/          		# main source file
|   |-- main.ino
|-- Optimised version/  # the optimised source file based on the main one   
|   |-- optimised.ino
|-- README.md      	    #README file
|-- images				#image folder
```

### 2.1 MQ135

* **Required Library**: MQ135-master

You can download this library through the [link](https://link.jianshu.com/?t=https://codeload.github.com/GeorgK/MQ135/zip/master) or the library manager in the IDE.

Before you use the `main.ino` to build the monitor, you should use the `MQ135.ino`  to energize, and preheat **MQ135** for **12-24** hours, after which the following procedures are performed at **20°C/35%** air temperature. 

Then you should run the `MQ135.ino` and read **R0** value. After that, go to the  `MQ135-master`->`MQ135.h` and change the R0 value.

For more information about MQ135, please check out this [link](https://hackaday.io/project/3475-sniffing-trinket/log/12363-mq135-arduino-library).

### 2.2 Main

* **Required Library**:
  * MQ135-master
  * LiquidCrystal
  * DHT
  * Wire

The main file, after changing the R0 value, you can upload this one to your Arduino Uno. Then if you have already assemble all the components and make the enclosure. Now, it is time to power your monitor and let it work.🎉

⚠Limitation: It suits the places where the CO2 PPM is around 420.

### 2.3 Optimised Version

* **Required Library**： Same as `Main`

Compared to the `Main` , this version optimises the detection of airtightness. It greatly decreases the delay of effectiveness of the detection, and can be put anywhere without the limitation of CO2 PPM.

****

## 3. Future work

*  Add a PH sensor: The pH value is one of the key indicators of yeast and  bacterial activity during the fermentation process. By monitoring the pH, the  wine maker can assess the progress of fermentation and take necessary  corrective measures. 
* Add an Air valve and air pressure sensor: During the grape fermentation  process, a significant amount of gas is generated. By detecting the pressure  with an air pressure sensor, the valve opens when it exceeds a certain  threshold, allowing the release of some gas to prevent the container from  exploding 

****

## 4. Info

Please report any bugs you find on the github repository!