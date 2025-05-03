extern "C" unsigned char __heap_base;

extern "C" void log_string(const char * value);
extern "C" void log_int(uint32_t value);
extern "C" void log_error(const char * value);
extern "C" void exit_wasm(uint32_t code);
extern "C" void * fetch(const char * url, const char * request_body, void(*)(const char * body));
