#include <getopt.h>

#define     MAX_CLO       30

enum {
    CLO_OK = 0,
    CLO_ERR,
    CLO_EXIT
};

typedef int (*clo_callback_t)(const char *optarg);

typedef struct clo_info {
    /* short option */
    char   opt;

    /* Description of the command */
    char  *desc;
 
    /* Callback function for opt match */
    clo_callback_t clo_callback;
} clo_info_t;



int zk_clo_init(void);
void zk_clo_fini(void);

void zk_clo_show(void);

int zk_clo_register(char *long_opt, char opt, uint8_t has_arg,
                    char *desc, clo_callback_t clo_callback);

int zk_clo_parse(int argc, char **argv);


