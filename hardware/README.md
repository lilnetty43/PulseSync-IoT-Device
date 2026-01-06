# PulseSync IoT – Hardware Design

This directory contains the complete hardware design artifacts for the PulseSync IoT heart-rate monitoring system, developed using KiCad.

---

## Design Overview

- Interfaces a Grove ear-clip heart-rate sensor with an Arduino Uno
- Integrates an ESP-01S (ESP8266) Wi-Fi module for wireless data transmission
- Includes onboard LED indication synchronized to detected heartbeats
- Implemented as a two-layer PCB with top-layer signal routing and a bottom-layer ground fill
- A routed PCB layout view is provided in the `images/` directory for reference

---
## Schematic Overview

![PulseSync IoT Schematic](hardware/outputs/schematic/PulseSync_IoT_Schematic.png)

*Exported schematic view showing sensor interface, ESP-01S integration, power regulation, and I/O mapping.*


## Design Tools

- **EDA Tool:** KiCad  
- **Design Stages:** Schematic capture, I/O mapping, power regulation, PCB layout, and design rule verification

---

## Directory Structure

### `kicad/`
Intended to contain editable KiCad project source files, including schematics, PCB layout files, custom symbols, footprints, and 3D models used in the design.

#### Project Archival Note
The original KiCad project source files (`.kicad_sch` and `.kicad_pcb`) were not preserved during early fabrication submissions. As a result, the editable schematic and PCB source files are no longer available.

The finalized design is instead represented through the manufacturing-ready outputs (Gerber and drill files) and human-readable documentation provided elsewhere in this directory.
Exported schematic PDFs are included in the `outputs/` directory to preserve circuit-level design intent.


---

### `fabrication/`
Manufacturing outputs generated from KiCad, including:

- Gerber layer files
- Excellon drill files and drill maps

These files represent the finalized, fabrication-ready version of the PCB and were used for board manufacturing.

---

### `outputs/`
Human-readable design documentation, including:

- Exported schematic PDFs
- Bill of Materials (BOM)
- Rendered PCB views and visual references

These files preserve design intent and enable review, verification, and documentation of the hardware design despite the absence of editable source files.

---

## Notes

- Design Rule Checking (DRC) was performed to verify layout correctness prior to fabrication
- Fabrication files are provided for reference and demonstration of PCB manufacturing readiness
