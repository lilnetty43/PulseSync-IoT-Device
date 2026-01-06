---
# PulseSync IoT – Hardware Design

This directory contains the complete hardware design for the PulseSync IoT heart-rate monitoring system, developed using KiCad.

## Design Overview
- Interfaces a Grove ear-clip heart-rate sensor with an Arduino Uno
- Integrates an ESP-01S Wi-Fi module for wireless data transmission
- Includes onboard LED indication synchronized to detected heartbeats
- Routing was completed using a two-layer PCB with top-layer signal routing and bottom-layer ground fill. A routed layout view is provided in the `images/` directory for reference.

## Design Tools
- **EDA Tool:** KiCad
- **Design Stages:** Schematic capture, I/O mapping, power regulation, and layout verification

## Directory Structure
- **kicad/**  
  Contains KiCad project files, including schematics and PCB layout files, along with custom symbols, footprints, and 3D models used in the design.

     ### Project Archival Note
  The original KiCad project source files (.kicad_sch and .kicad_pcb) were not preserved during early fabrication submissions. The available Gerber and drill files represent the finalized manufacturing-ready design and are provided for reference and verification.


- **fabrication/**  
  Manufacturing outputs generated from KiCad, including Gerber files and drill files required for PCB fabrication.

- **outputs/**  
  Human-readable exports such as schematic PDFs, bill of materials (BOM), and rendered PCB views.

## Notes
- Design Rule Checking (DRC) was performed to verify layout correctness
- Fabrication files are provided for reference and demonstration of PCB manufacturing readiness

