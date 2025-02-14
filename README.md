# C++ Toolkit (cpptoolkit)

![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Version](https://img.shields.io/badge/version-0.1.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

C++ Toolkit is a lightweight and versatile C++ library that provides essential utilities for common development tasks. It includes modules for time management, threading, inter-process communication (IPC), configuration I/O, and logging.

Unlike traditional error-handling methods that rely on status or error codes, C++ Toolkit uses an exception-driven approach for more intuitive error reporting.

Additionally, C++ Toolkit can serve as a valuable reference or foundation for C++ projects, as it covers various stages of software development—including requirements gathering, design, implementation, requirement linking, testing, building, and release.

## Main Features

- **Exception Oriented:** Exception oriented error/status approach.
- **Time Management:** Accurate and convenient time management utilities. (`CtTimer`)
- **Threading:** Simplified thread pool, worker and service management. (`CtThread`, `CtWorker`, `CtWorkerPool`, `CtService`, `CtServicePool`)
- **Configuration I/O:** A flexible configuration file parser and writer. (`CtConfig`)
- **Logging:** Simple logging with log levels and timestamp. (`CtLogger`)
- **Interprocess Communication (IPC):** Simple UDP socket communication. (`CtSocketUdp`)
- **Event handling:** Implements an object-oriented event trigger and catch mechanism. (`CtObject`)
- **File I/O** Provides easy-to-use file read/write utilities. (`CtFileInput`, `CtFileOutput`)

## Roadmap
- [ ] Develop TCP socket communication
- [ ] Implement support for various RTBM (Real-Time Big Data Management) systems

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

3. Run cmake and generate build files in a /build directory:

    ```bash
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    ```

4. Build the library, test and examples:

    ```bash
    cmake --build build --config Release
    ```

5. Run the tests:

    ```bash
    ctest --test-dir build -C Release
    ```

6. Create build library products (.so & header files) to build/out:

    ```bash
    cmake --install build
    ```
## Contributing

If you're interested in improving C++ Toolkit, feel free to:
- Report issues or suggest new features via the issue tracker.
- Submit pull requests with bug fixes, enhancements, or new features.
- Improve documentation or examples to make the library more accessible.

## Purpose

C++ Toolkit was originally created for educational purposes.

## License

C++ Toolkit is released under the MIT License. You are free to use and distribute this library within the terms of the license.