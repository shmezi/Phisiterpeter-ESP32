# SD Card Structure Guide

This document outlines the required directory structure and file organization for the SD card storage.

## Visual Hierarchy

```text
ROOT/
├── hoists/          # Deployment Configs
│   └── project.hoist
├── scripts/         # Logic Files (.ezra)
│   └── script.ezra
├── index.html       # Web Interface (Remote Editor)
└── config.json      # Device Registry (MAC Mapping)
```

---

## Directory & File Details

### 📂 /hoists

Contains configuration files (`.json`) that allow for easy deployment by end users.

* **Purpose**: Defines which script files are associated with a specific project.
* **Function**: Allows users to specify device names and link logic without modifying the core system.

### 📂 /scripts

The storage location for the functional logic files.

* **Format**: All files must use the `.ezra` extension.
* **Role**: These scripts are interpreted and executed by the EzraScript runtime.

### 📄 index.html.gz

The core web interface for the project.

* **Usage**: Runs on the display to serve as a remote code editor.
* **Features**: Enables remote script modifications over the network.

### 📄 config.json

A critical mapping file for system coordination.

* **Mapping**: Links physical **MAC addresses** to their respective codebases and device names.
* **Importance**: Essential for identifying and managing hardware nodes.

---

## Technical Reference

| Component     | Extension | Primary Role          |
|:--------------|:----------|:----------------------|
| Configuration | `.json`   | User-facing setup     |
| Logic         | `.ezra`   | Script execution      |
| Registry      | `.json`   | Device identification |
| Interface     | `.html`   | Web editor UI         |