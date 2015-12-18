

enum {
    LOG_CRIT=0,
    LOG_ERR,
    LOG_WARN,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
};

#ifndef  LOG_LEVEL
#define  LOG_LEVEL    5 /* default level */
#endif

#ifdef   _SYS_LOG_

//#define  log_

#else

#define  log_crit(...)  fprintf(stderr, __VA_ARGS__);

#if   LOG_LEVEL > 0
#define  log_err(...)  fprintf(stderr, __VA_ARGS__);
#else
#define  log_err(...)  
#endif

#if   LOG_LEVEL > 1
#define  log_warn(...)  fprintf(stderr, __VA_ARGS__);
#else
#define  log_warn(...)  
#endif

#if   LOG_LEVEL > 2
#define  log_notice(...)  fprintf(stdout, __VA_ARGS__);
#else
#define  log_notice(...)  
#endif

#if   LOG_LEVEL > 3
#define  log_info(...)  fprintf(stdout, __VA_ARGS__);
#else
#define  log_info(...)  
#endif

#if   LOG_LEVEL > 4
#define  log_debug(...)  fprintf(stdout, __VA_ARGS__);
#else
#define  log_debug(...)  
#endif

#endif
