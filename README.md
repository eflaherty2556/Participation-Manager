# Participation-Manager

## What is FRC Participation Manager?

This project is a RaspberryPi-based system designed to log hours for [FIRST Robotics Competition](https://www.firstinspires.org/robotics/frc) participants. It includes code that runs on Raspberry Pi (or similar device) to facilitate the physical action of logging in as well as a web interface for members of a team to view their hour contributions. Through the use of this system, FRC teams can improve their sign-in process and generate useful data insights for team management. This device is intended to help growing teams accommodate for increasing team sizes while also improving their experience all around. In the end, teams should be able to use quantitative data 

The device:

<img src="https://github.com/JFlaherty347/Participation-Manager/blob/master/images/device.png" alt="device" width="500">

The web interface:

<img src="https://github.com/JFlaherty347/Participation-Manager/blob/master/images/webApp.png" alt="web app" width="500">

## How can a team use this system?

<img src="https://github.com/JFlaherty347/Participation-Manager/blob/master/images/flowchart.png" alt="usage flowchart" width="750">

## Features

* Users can scan a QR or Barcode to sign in and out of meetings via a camera on the device
* Users can log into the web application to view their hours
* Admins can view everyone's hours on the web app
* Super Admins can modify users and their data
* Users can determine if their login was successful via an LCD screen

## Testing

### Convenience
To determine how convenient the device is to use, multiple timed attempts to sign-in on the device were compared to how long a sign-in took on pen and paper.

The average time using this system was 3.652 seconds whereas pen and paper sign-ins took on average 14.948 seconds to sign in. With an average time save of over 10 seconds, it can be concluded that the device succeeds in its objective to make the sign-in process quicker and easier.

### Reliability
To determine how reliable the device is, several different QR and Barcodes were scanned and averaged their success rate. The device performed with a 100% successful reading rate and no occurrences of a failed reads were witnessed. Hence, it can be determined that the device is reliable enough for use by teams.

### Durability
With all of the wear and tear that the build season may bring, durability was another important objective of the device. Several different methods of dropping,  shaking, and placing weight on the device all failed to inhibit the device's usability. The device can be considered durable enough to survive reasonable wear that could be experienced in an FRC team's workspace.

## Future improvements should be implemented if time permits

* A way to add a user via the web application
* An easy way to create ID cards from the web application
* Improved data tracking and better graphics and analysis tools for the web application
