# Automated Cooling System through Movement Monitoring


## Introduction
Singapore is a hot and humid nation where one must be wary of their body temperature if significant portion of the day is spent moving around ourdoors. This leads to a probable chance of inducing heatsroke or other forms of heat injury in the process. The product seeks to cool the bodies of the user by increasing rate of sweat evaporation when non-stantionary. An Arduino System is embedded to the user and functionalities cna be controlled by a Android application.
The system comprises of an app-based user interfacce, a database hosted on a cloud and a embedded system using an Arduino Development Board embedded with a WiFi module. The individual modules communicates using WiFi communication protocols. 

## Bill Of Materials

| Index         | Component      | Description   |
| --   | ------------- | ------------- |
| 1  | Arduino MKR WiFi 1010  | Development Board to control input and output modules  | 
| 2  | Phone with Android OS  | User Interface(MIT App Inventor 2) to allow user to adjust settings   |
| 3  | SparkFun H3LIS331DL Triple Axis Accelerometer Breakout  | Provide X,Y,Z acceleration readings to detect user's motion   |
| 4  | LED (Green) | Status light to indicate key events | 
| 5  | 3V DC Motor | Power the fan to cool the body| 
| 6  | Fan Blade | Generate directional wind current to increase rate of sweat ecaporation| 

*insert diagram*

## Specifications

### Arduino MKR WiFI 1010

<img src="https://static.cytron.io/image/catalog/products/ARDUINO-MKR-1010/ARDUINO-MKR-1010-b.jpg" width="200" height="280">

* Board Input Voltage : 5V
* Communication: Wifi & Bluetooth
* Dimensions:61.5mm x 25mm

### SparkFun H3LIS331DL Triple Axis Accelerometer Breakout
<img src="https://cdn.sparkfun.com//assets/parts/1/2/5/3/2/14480-01.jpg" width="200" height="280" align="center">

* Board Input Voltage: 2.16V to 3.6V
* Digital Output: I2C & SPI

### User Interface
<img src="https://github.com/jiasheng-ooi/pdsproj.github.io/blob/main/media/applayout.jpg?raw=true" width="350" height="680">

* Android OS
* Built using MIT App Inventor 2


##  System Architecture
### Circuit Diagram
![img](https://github.com/jiasheng-ooi/pdsproj.github.io/blob/main/media/circuit%20diagram.jpeg?raw=true)

### Database
![db](https://github.com/jiasheng-ooi/pdsproj.github.io/blob/main/media/database.JPG?raw=true)
The database provides a middleman platfrom for the Android application and the Arduino system to facilitate communication. THe database uses the Firebase api, specifically its realtime database.

### Communication
![comms](https://github.com/jiasheng-ooi/pdsproj.github.io/blob/main/media/communication.JPG?raw=true)

*Enable: Controls whether the fan can be activated or not, if the user is in motion.
*Power: Controls the fan speed when the fan is on.
*Pitch: The rotation around X axis measured by the accelerometer
*Roll: The rotation around Y axis measured by the accelerometer

## Wrokflow of Product

### Setup

Ensure that a realtime database has been set up and is ready to be used.

## Code


### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
