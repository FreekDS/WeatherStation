## WeatherStation

### Overview

Simple embedded application for environmental sensing and reporting implemented in modern C++17 for small microcontroller boards. The project collects temperature, humidity, pressure, light, soil moisture, and ultraviolet intensity then formats measurements as JSON for downstream consumption.

#### Repository Layout

1. `platformio.ini` Configuration for build targets and board definitions
2. `include` Public header files used across modules
3. `lib` Libraries organized per feature
   1. `JsonStreamer` Lightweight JSON output helper
   2. `MeasurementBuffer` Ring buffer for sample storage
   3. `Sensors` Sensor abstractions and device specific code
   4. `TaskManager` Cooperative task scheduler utilities
   5. `Utils` Small helper templates and logging utilities
4. `src` Application entry point `main.cpp`

#### Build and Run

Use the PlatformIO integration in the editor to build and to upload firmware. The project defines an environment named `uno` intended for AVR UNO class boards. Build from the editor tasks or from the PlatformIO user interface.

#### Configuration

Edit `platformio.ini` to change board settings or to add new environments. Sensor wiring and hardware specific constants are declared in `include/constants.h` and in the sensor headers under `lib/Sensors`.
