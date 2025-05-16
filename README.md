# 📘 Application Note: Libelium Gas Sensor

This repository contains an application note on the **Libelium Gas Sensor Board**. It documents the full process of research, implementation, and evaluation of a specific technical application.

---

## 📌 Table of Contents

1. [Introduction](#1-introduction)  
2. [Project Goal](#2-project-goal)  
3. [Collected Information](#3-collected-information)  
4. [What Went Well](#4-what-went-well)  
5. [Challenges](#5-challenges)  
6. [Conclusion and Reflection](#6-conclusion-and-reflection)  
7. [Repository Structure](#7-repository-structure)  
8. [Requirements](#8-requirements)  
9. [License](#9-license)  
10. [Contact / Feedback](#10-contact--feedback)

---

## 1. 🧭 Introduction

We are two students studying **Electronics-ICT**, and this GitHub repository documents our project for the course **Electronic Systems 2**.

As part of the assignment, we were placed into teams of two and asked to work on a technical project. In this repository, we guide you through our progress — including the information we gathered, what went well, and which parts were more challenging.

You’ll also find a conclusion where we reflect on the overall experience:  
- What could have been improved  
- What worked well  
- And how others could potentially continue building on this project

We hope this documentation is helpful for anyone interested in working with similar sensor boards, microcontrollers, or smart home integration.

---

## 2. 🎯 Project Goal

In this project, we aim to get the **Libelium Gas Sensor Board** working — with or without the connection board (*interface board*).  
We tested both setups, but eventually continued **without using the connection board**.

Instead, we connected the gas sensor board **directly to an Arduino or ESP microcontroller** to read the sensor data.

The sensor board includes **six sensors**:
- 🌡️ Temperature sensor  
- 💧 Humidity sensor  
- 🟢 CO₂ (Carbon Dioxide) sensor  
- 🟡 NO₂ (Nitrogen Dioxide) sensor  
- 🟣 O₃ (Ozone) sensor  
- 🔴 CO (Carbon Monoxide) sensor

Once we successfully read the data, the next goal was to **send this data over Wi-Fi** to a **Loxone control unit**, which would then **receive and process the information**.

This project focuses on monitoring air quality and making the sensor data available wirelessly for use in smart building or automation systems.

---

## 3. 📚 Collected Information

During the project, we used the following sources:

- **Datasheets**:
  - [Component name] ([link])
- **Application notes**:
  - [Title – Manufacturer – link]
- **Tutorials and guides**:
  - [YouTube / blog articles / etc.]
- **Own measurements and testing**

---

## 5. ✅ What Went Well

Although there is a lot of information available about the Libelium Gas Sensor Board through GitHub repositories and forums, there isn’t really a clear or structured guide on how to program and use the board step-by-step.

One of the early decisions we made was to **use an Arduino with built-in Wi-Fi** instead of relying on the official Libelium connection board. This turned out to be a smart move and was one of the smoother parts of the project.

Since both of us were already familiar with Arduino, this made it much easier to work with. Using a platform we knew allowed us to:
- Quickly understand how to connect and power the sensor board
- Write and test basic code without needing external libraries or complex drivers
- Troubleshoot faster and with more confidence

At one point, we briefly switched back to the connection board to explore its potential. However, we quickly realized it was taking too much time and didn’t provide significant advantages for our goal. Choosing to move on and focus on the Arduino setup helped us stay efficient and productive.

Once we had the correct hardware configuration — Arduino plus direct-wired sensor board — we began reading out sensor data one by one. The first two sensors were especially easy to set up, and we were able to get valid readings from them in a very short time.


## 5. ⚠️ Challenges

- [❌ Issue 1: Unstable power supply → fixed using a capacitor]
- [❌ Issue 2: I2C timeout problems → solved with logic analyzer debugging]
- [❌ Incomplete documentation for component X → resolved by trial and error]

---

## 6. 🧾 Conclusion and Reflection

In summary, we were able to [short summary of what was achieved].  
What we learned:

- [Lesson 1]
- [Lesson 2]

Recommendations for future development:

- [Improvement idea 1]
- [Improvement idea 2]

---

## 7. 📁 Repository Structure

