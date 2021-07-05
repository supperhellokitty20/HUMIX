# HUMIX  
 A DIY humid and temperature  from **Arduino Uno** and **DHT11** , **HD8788 16x02 LCD**  and sum **breadthboard**
 Project was done in a boring rainy day .  

    (づ◡﹏◡)づ

 
## Wiring 
 Mine have 3 pins built in with on board resistor  so connect with the following connection  .  
 DHT11 : 
    * VCC -> 5v power current  
    * GND -> Arduino GND 
    * Signal (S)  ->  digital pin 2   
LCD using i2c module : 
    * VCC -> 5v power current  
    * GND -> Arduino GND 
    * SDA -> A4  
    * SCL -> A5 

## Features
-  Measuring air realative air humidity and log to the lcd screen .  
-  Done using platform io core , a fast and easier experience than arduino ide . 
- You dont need to install any arduino external libs just download and test  
- Datasheet of the components are widely available on the internet just google 
## Run Locally
Installing Platform io core 
* MacOS 
```bash
    brew install platformio 
```
* As a python package
```bash
    pip install -U platformio
```

Clone the project
```bash
  git clone https://github.com/supperhellokitty20/HUMIX.git 
```

Go to the project directory

```bash
  cd HUMIX  
```

Go brum brum .Great things about platformio is that it's auto detect Port  from the arduino.  
```bash
    pio run --target upload  
```
Wait for it to install dependency and upload the sketch to arduino ....  
  
## Demo 
  in assets dỉrectory 
