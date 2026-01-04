---
# PulseSync IoT – Hardware Design

This directory contains the complete hardware design for the PulseSync IoT heart-rate monitoring system, developed using KiCad.

## Design Overview
- Interfaces a Grove ear-clip heart-rate sensor with an Arduino Uno
- Integrates an ESP-01S Wi-Fi module for wireless data transmission
- Includes onboard LED indication synchronized to detected heartbeats
- Designed with a focus on reliable sensor interfacing and power integrity

## Design Tools
- **EDA Tool:** KiCad
- **Design Stages:** Schematic capture, I/O mapping, power regulation, and layout verification

## Directory Structure
- **kicad/**  
  Contains native KiCad project files, including schematics and PCB layout files, along with any custom symbols, footprints, and 3D models used in the design.

- **fabrication/**  
  Manufacturing outputs generated from KiCad, including Gerber files and drill files required for PCB fabrication.

- **outputs/**  
  Human-readable exports such as schematic PDFs, bill of materials (BOM), and rendered PCB views.

## Notes
- Design Rule Checking (DRC) was performed to verify layout correctness
- Fabrication files are provided for reference and demonstration of PCB manufacturing readiness

