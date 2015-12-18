
#define   ZK_DEFAULT_CONFIG_PATH    "/etc/zakuta/zakuta.conf"

typedef int (*input_t)(void *zkc);

struct zakuta_conf {
    input_t     input;
    const char  *pcap_name;
};


typedef struct zakuta_conf  zakuta_conf_t;



