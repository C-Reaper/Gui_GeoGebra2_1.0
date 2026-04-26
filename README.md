# Project README

## Overview
- A simple C project that creates a graphical window displaying a mathematical function using the Window API.
- The application is designed to run on both Linux and Windows platforms.

## Features
- Create a graphical window with a title "Geogebra 2.1".
- Display a mathematical function (y = -f(x)) graphically in the window.
- Update the display in real-time as the mouse moves across the window, showing coordinates at the cursor position.

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC)
- Make utility
- Standard development tools
- Libraries needed: X11 for Linux (`libX11-dev`), Windows API (`user32`, `gdi32`, `winmm`) for Windows, Wine for cross-compilation to Windows

## Build & Run

### Building on Linux
To build the project on a Linux system:

```bash
cd <Project>
make -f Makefile.linux all
```

This will compile the source code and produce an executable file in the `build` directory. To run it:

```bash
make -f Makefile.linux exe
```

### Building on Windows
To build the project on a Windows system, you need to ensure that MSYS2 or Cygwin is installed with GCC and MinGW installed.

```cmd
cd <Project>
make -f Makefile.windows all
```

This will compile the source code and produce an executable file in the `build` directory. To run it:

```bash
make -f Makefile.windows exe
```

### Building for Wine
To build the project using Wine to create a Windows executable:

```cmd
cd <Project>
make -f Makefile.wine all
```

This will compile the source code and produce an executable file in the `build` directory. To run it:

```bash
make -f Makefile.wine exe
```

### Building for WebAssembly
To build the project using Emscripten to create a WebAssembly module:

```cmd
cd <Project>
make -f Makefile.web all
```

This will compile the source code and produce an HTML file along with associated JavaScript files in the `build` directory. To run it, start a web server and navigate to the generated HTML file.

### Clean Build
To clean up any build artifacts:

```bash
make -f Makefile.linux clean
```

This will remove all compiled object files and the executable from the `build` directory.