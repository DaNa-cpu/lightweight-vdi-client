# Lightweight Cloud Workspace Client and Integration Agent for Linux

A modern, lightwight C++/Qt 6 Thin Client workspace interface design for Linux enterprise environments.

## Features (Implemented so far)
- **Qt 6 GUI**: Modern Dark Mode user interface.
- **Dynamic Configuration**: JSON parser loading VDI session profile on startup.
- **Clean Architecture**: C++ Object-Oriented design, separating data models, configuration loaders, and UI logic.

## Prerequisites and Dependecies
Specify the packages required to build and run the core application:
- C++17 Compiler (`g++`/`clang`)
- CMake >= 3.16
- Qt 6 (Core, Widgets)

##How to Build and Run

```bash
# 1. Clone the repository
git clone https://github.com/DaNa-cpu/lightweight-vdi-client.git
cd lightweight-vdi-client

# 2. Create build directory and copile
cmake -S . -B build
cmake --build build

# 3. Run the application
./build/LightweightVdiClient
