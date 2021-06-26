#define __DEBUG
#ifdef __DEBUG
    #define DEBUG(msg,...) printf(""__FILE__"[%d]: "msg"", __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG(msg,...)
#endif

