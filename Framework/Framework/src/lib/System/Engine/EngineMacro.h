#define ENSURE(flag) if(flag){__debugbreak();}
#define CHECK(flag) if(flag){exit(-1);}

#if defined(KL_DEBUG) || defined(ENGINE_DEBUG)
#define DEBUG_ENABLE true
#else
#define DEBUG_ENABLE false
#endif

#if defined(ENGINE_DEBUG) || defined(ENGINE_RELEASE)
#define ENGINE_DEVELOP true
#else
#define ENGINE_DEVELOP false
#endif

#if (DEBUG_ENABLE || ENGINE_DEVELOP)
#define PACKAGE false
#else
#define PACKAGE true
#endif