# C++ Toolkit (cpptoolkit)

![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

C++ Toolkit is a lightweight and versatile C++ library that provides essential utilities for common tasks in C++ development. It includes modules for time management, threading, IPC, configuration io and logging.

## Features

- **Time Management:** Accurate and convenient time management utilities.
- **Threading:** Simplified thread pool and worker management.
- **Configuration IO:** A flexible configuration file parser and writer.
- **Logging:** Simple logging with log levels and timestamp.
- **Interprocess Communication (IPC):** Simple UDP socket communication.
- **Event handling:** Simplified object oriented trigger and catch event mechanism.

## Todo
- [ ] Implement unit tests using gtest.
- [ ] Design and develop TCP socket communication.
- [ ] Check Windows compatibility.
- [ ] Refactor CtSink to inherit CtBlock (similar to CtSource).

## Installation

### Prerequisites

- C++11 or later
- CMake

### Building from Source

1. Clone the repository:

    ```bash
    git clone https://github.com/panosmouze/cpptoolkit.git
    ```

2. Navigate to the project directory:

    ```bash
    cd cpptoolkit
    ```

3. Create a build directory:

    ```bash
    mkdir build && cd build
    ```

4. Run CMake:

    ```bash
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_ENABLE_TESTS=OFF
    ```

5. Build the project:

    ```bash
    make
    ```

## Purpose

C++ Toolkit started primarily for educational purposes.

## License

C++ Toolkit is released under the MIT License. You are free to use and distribute this library within the terms of the license.