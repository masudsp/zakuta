#include "common.h"
#include <pcap.h>
#include "clo.h"
#include "readpcap.h"


int
zk_pcap_read(void  *data)
{
    log_err("pcap input selected\n");

    return 0;
}

int
pcap_enable(zakuta_conf_t  *zkc, const char *optarg)
{

    struct stat fstat;

    if (!optarg) {
        log_err("This option requires an argument\n");
        return CLO_ERR;
    }

    if (stat(optarg, &fstat) == -1) {
        log_err("pcap file is not present\n");
        return CLO_ERR;
    }    

    zkc->input     = zk_pcap_read;
    zkc->pcap_name = optarg;

    return CLO_OK;
}

int
pcap_clo_register()
{
    int  ret;

    ret = zk_clo_register("pcap", '\0', required_argument, "load pcap", pcap_enable);

    return CLO_OK;
}





