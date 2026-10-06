#define DEBUG 1

#define DEBUGPORT TelnetServer
#define DEBUGBAUD 115200

#ifdef DEBUG
#define DEBUG_PRINT(x) DEBUGPORT.print(x)
#define DEBUG_PRINTLN(x) DEBUGPORT.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif