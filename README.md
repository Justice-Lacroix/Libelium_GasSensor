# 📘 Application Note: Libelium Gas Sensor

This repository contains an application note on the Libelium Gas Sensor Board. It documents the full process of research, implementation, and evaluation of a specific technical application.

---

## 📌 Table of Contents

- [Introduction](#1-introduction)  
- [Project Goal](#2-%F0%9F%8E%AF-project-goal)  
- [Collected Information](#3-%F0%9F%93%9A-collected-information)  
- [What Went Well](#5-%E2%9C%85-what-went-well)  
- [Challenges](#5-%E2%9A%A0%EF%B8%8F-challenges)  
- [Conclusion and Reflection](#6-%F0%9F%A7%BE-conclusion-and-reflection)  

---

## 1. 🧭 Introduction

We are two students studying Electronics-ICT, and this GitHub repository documents our project for the course Electronic Systems 2.

As part of the assignment, we were placed into teams of two and asked to work on a technical project. In this repository, we guide you through our progress — including the information we gathered, what went well, and which parts were more challenging.

You’ll also find a conclusion where we reflect on the overall experience:

- What could have been improved  
- What worked well  
- And how others could potentially continue building on this project  

We hope this documentation is helpful for anyone interested in working with similar sensor boards, microcontrollers, or smart home integration.

---

## 2. 🎯 Project Goal

In this project, we aim to get the Libelium Gas Sensor Board working — with or without the connection board (interface board).  
We tested both setups, but eventually continued without using the connection board.

Instead, we connected the gas sensor board directly to an Arduino or ESP microcontroller to read the sensor data.

The sensor board includes six sensors:

- 🌡️ Temperature sensor  
- 💧 Humidity sensor  
- 🟢 CO₂ (Carbon Dioxide) sensor  
- 🟡 NO₂ (Nitrogen Dioxide) sensor  
- 🟣 O₃ (Ozone) sensor  
- 🔴 CO (Carbon Monoxide) sensor  

Once we successfully read the data, the next goal was to send this data over Wi-Fi to a Loxone control unit, which would then receive and process the information.

This project focuses on monitoring air quality and making the sensor data available wirelessly for use in smart building or automation systems.

---

## 3. 📚 Collected Information

During the project, we used the following sources:

- Datasheets:  
  [Component name] ([link])  
- Application notes:  
  [Title – Manufacturer – link]  
- Tutorials and guides:  
  [YouTube / blog articles / etc.]  
- Own measurements and testing  

---

## 5. ✅ What Went Well

Although there is a lot of information available about the Libelium Gas Sensor Board through GitHub repositories and forums, there isn’t really a clear or structured guide on how to program and use the board step-by-step.

One of the early decisions we made was to use an Arduino with built-in Wi-Fi instead of relying on the official Libelium connection board. This turned out to be a smart move and was one of the smoother parts of the project.

Since both of us were already familiar with Arduino, this made it much easier to work with. Using a platform we knew allowed us to:

- Quickly understand how to connect and power the sensor board  
- Write and test basic code without needing external libraries or complex drivers  
- Troubleshoot faster and with more confidence  

At one point, we briefly switched back to the connection board to explore its potential. However, we quickly realized it was taking too much time and didn’t provide significant advantages for our goal. Choosing to move on and focus on the Arduino setup helped us stay efficient and productive.

Once we had the correct hardware configuration — Arduino plus direct-wired sensor board — we began reading out sensor data one by one. The first two sensors were especially easy to set up, and we were able to get valid readings from them in a very short time.

---

## 5. ⚠️ Challenges

- It was difficult to find precise information about the board. While there is a lot of general information available online, very little explains exactly how the board works or what it does.  
- Downloading and installing the software went fairly smoothly. However, inside the IDE we saw almost no meaningful results, and the board continuously entered a reset loop. We were not able to identify the root cause of this issue.  
- Working with Arduino also presented several challenges. It took us quite some time to figure out the correct pinout for the board.  
- After that, we still had to determine how to properly communicate with the sensors.  
- Overall, the board started to feel like a 'black box' — difficult to understand, with very limited documentation or practical examples available.  
- This turned out to be the most time-consuming part of the project.

---

## 6. 🧾 Conclusion and Reflection

In summary, we were able to get 3 out of 6 sensors working reliably using the Arduino. Initially, we attempted to use an intermediate board, but this setup did not provide stable readings. Switching to the Arduino allowed us to achieve stable data acquisition and successfully transmit sensor values over Wi-Fi to the Loxone system. This fulfilled the original goal of the project, although it is unfortunate that we couldn't get all sensors operational.

### What we learned:

- How to effectively search for technical information and quickly assess whether it is useful or not for the project.  
- The importance of dividing tasks within the team to work more efficiently and stay organized.  
- Working with the Libelium IDE was new for us, but since it closely resembles the Arduino IDE, the transition was smooth.  
- The most significant and valuable learning experience was understanding how to control and read sensors on the GasBoard. This was completely new to us and formed a core part of the technical growth during the project.

### Recommendations for future development:

- Design a custom PCB integrating the required sensors instead of using the current board.  
- Take advantage of the abundant documentation and example schematics available for the individual sensors.  
- Working directly with the sensors on a custom board will be much more straightforward and accessible.  
- Creating a custom board is expected to reduce complexity and save significant development time compared to troubleshooting the existing board.
