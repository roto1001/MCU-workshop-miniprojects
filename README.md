# Microelectronics Workshop Repository

Welcome to the Microelectronics Workshop Repository! This repository was created as part of a university course in a Master's program in Informatics. The goal of the course was for each student to design and deliver a 1.5-hour workshop on a technical topic in computer science. My chosen topic was microcontrollers and embedded systems, which I am deeply passionate about, and for which I have an extensive collection of microcontrollers, sensors, and other components.

---

### About This Workshop
This workshop is designed for people who are already experienced in programming but have little or no experience in microelectronics. My aim was to introduce students to the exciting world of microcontrollers and give them hands-on experience with embedded systems. The workshop structure is intended to engage students by balancing theory and practical work.

---

### Workshop Structure
The workshop is split into two main parts:
- **Theory (45 minutes)**: Covers the essentials of microelectronics and the foundational knowledge needed to understand the practical exercises.
- **Practical Work (45 minutes)**: Pairs of students work on hands-on mini-projects to apply the theory they've just learned.

Instead of diving into long theoretical lectures, I created a smooth, interactive approach. Each topic is introduced briefly, then applied directly in a mini-project, ensuring students stay engaged and can immediately test what they’ve learned, 10 minutes of theory followed by 10 minutes of hands-on activity.

---

### Mini-Projects Overview
To ensure maximum engagement, I developed five mini-projects, each available in two identical sets so that each of the 20 students (in pairs) can choose a project to work on. Each mini-project folder in this repository contains an exercise sheet in the README. This sheet includes:
- Controller pinouts and circuit diagrams for each project.
- An introduction to Arduino basics and required libraries.
- Step-by-step guidance, providing all the essentials for those who are new to microelectronics yet skilled in programming.

The exercises are structured to be simple and approachable, even for those who have never worked with microelectronics. Each project was designed to be achievable within approximately 45 minutes. This timeframe was intentionally challenging, as it includes everything from familiarizing themselves with Arduino, understanding the libraries, setting up the hardware, wiring the circuit, and writing the code. 

---

### Code Samples and Solutions
Each project also includes a sample solution, typically found in a single file within the project's main folder. These solutions, ranging from 50 to 200 lines of code, demonstrate best practices with the libraries in use. They’re designed to be as streamlined as possible, focusing on simplicity and readability rather than a full object-oriented approach, to align with the workshop’s goals. The objective here is to introduce students to the hands-on basics of microelectronics and embedded programming without overwhelming them with complex software design requirements.

# Overview of Mini-Projects

Each mini-project in this repository is designed to introduce students to fundamental concepts in microelectronics and embedded systems with hands-on practice. Below are brief descriptions of each project to give you an idea of what to expect. Click into each project folder to find detailed exercise sheets, setup guides, and sample solutions. These exercises are approachable for those with programming experience, even if you're new to microelectronics.

---

### Arduino Analog-Thermometer Project

![analog-thermometer-project-gif](analog-thermometer/assets/analog-thermometer.gif)

In this project, you’ll use a DHT22 temperature sensor to control a servo motor. The servo adjusts its position based on temperature readings, providing a visual representation of temperature changes.

---

### Arduino Persistent-Credentials MicroSD Project

![persistent-credentials-microsd-project-gif](persistent-credentials-microsd/assets/persistent-credentials-microsd.gif)

This project introduces data persistence with an SD card module, allowing users to store Wi-Fi credentials that remain saved even after powering off. You’ll learn how to read and write credentials on an sd-card. Aswell as updating credentials displayed on an OLED screen, and use the serial monitor to modify settings directly, making this project an excellent demonstration of stored configuration data.

---

### Arduino RFID Door Opener System

![rfid-door-opener-project-gif](rfid-door-opener/assets/rfid-door-opener.gif)

This project replicates a simple RFID-based access control system. By using an RFID reader to scan cards, you’ll control access based on a card's unique ID, with visual and audio feedback for authorized and unauthorized cards. Perfect for learning about RFID technology and scanning nfc chips.

---

### Arduino Timer Start-Stop-Reset Project

![timer-start-stop-reset-project-gif](timer-start-stop-reset/assets/timer-start-stop-reset.gif)

In this project, you’ll build a digital timer with start, stop, and reset functionality using physical buttons. The timer displays the seconds counted on a 7-segment display, teaching you about timing and 7 segement display control in embedded systems, as well as debouncing buttons for reliable user input.

---

### Arduino Ultrasonic Radar Tower Project

![ultrasonic-radar-tower-project-gif](ultrasonic-radar-tower/assets/ultrasonic-radar-tower.gif)

Simulating a radar system, this project combines an ultrasonic sensor and a servo motor to measure distances at various angles. By controlling the servo with a potentiometer, you can sweep the sensor across an area and read the distance to obstacles in real-time, giving you a taste of motion control and distance sensing.

---

These projects are designed to be completed within approximately 45 minutes, providing a balanced introduction to coding, wiring, and troubleshooting in Arduino and microelectronics.

Ultimately, this workshop is about sparking curiosity in microelectronics and giving students a foundation to build upon. This repository is a resource not just for the workshop itself but for students to revisit and explore further as they continue their journey into the world of microcontrollers and embedded systems.

Explore each project folder to access the exercise sheets, and have fun experimenting!
