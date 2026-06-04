#if SERIAL_ENABLED == true
    #define ENABLE_SERIAL(baudrate) Serial.begin(baudrate)
    #define LOG_LN(...) Serial.println(__VA_ARGS__)
    #define LOG(...) Serial.print(__VA_ARGS__)
#else
    #define ENABLE_SERIAL(baudrate)
    #define LOG(...)
    #define LOG_LN(...)
#endif
