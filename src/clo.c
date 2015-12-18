/**
 * Copyright (c) 2015-Now Masood Mehmood <sp@linux.com>
 *
 * 3-clause (or "modified") BSD license
 *
 * Command line options.
 *
 * The purpose of this code is to provide a way for easily adding new zakuta's
 * command line options. It will also make the main file clean and more readable
 * with less ifdef and less useless code to read about.
 */

#include "common.h"
#include "zakuta.h"
#include "clo.h"


/*********GLobals*******/

static   int  total_opt;
static char           valid_options[MAX_CLO * 2];
static struct option  long_opts[MAX_CLO];
static clo_info_t     clo_info[MAX_CLO];
/**********************/


int
zk_clo_register(char *long_opt, char opt, uint8_t has_arg,
                char *desc, clo_callback_t clo_callback)
{

    char  opt_val[3];

    if (!clo_callback) {
        log_err("Please provide option callback function\n");
        return -1;
    }

    if (!desc) {
        log_err("Please provide description of option\n")
        return -1;
    }

    if (!long_opt && !opt) {
        log_err("option and long option both can't be null\n");
        return -1;
    }

    if (total_opt >= MAX_CLO) {
        log_err("Unable to register clo, please increase static options size\n");
        return -1;
    }


    if (long_opt) {
        long_opts[total_opt].name    = long_opt;
        long_opts[total_opt].has_arg = has_arg;
        long_opts[total_opt].flag    = NULL;
        long_opts[total_opt].val     = total_opt;
        log_debug("Registering clo: %s\n", long_opt);
    }

    if (opt) {
        opt_val[0] = opt;
        if (has_arg == required_argument) {
            opt_val[1] = ':';
        } else {
            opt_val[1] = '\0';
        }
        opt_val[2] = '\0';
        strcat(valid_options, opt_val);
    }

    clo_info[total_opt].opt          = opt;
    clo_info[total_opt].clo_callback = clo_callback;
    clo_info[total_opt].desc         = desc;

    total_opt++;

    return 0;
}

int
zk_clo_parse(zakuta_conf_t *zkc, int argc, char **argv)
{
    int ch;
    int ret = 0;
    int i;
    int optidx = -1;

    if (argc < 2) {
        log_err("Please provide argument(s)\n");
        ret = CLO_ERR;
        goto DONE;
    }

    optind = 1;
    /* process short options first */
    while ((ch = getopt_long(argc, argv, valid_options, long_opts, &optidx)) != -1) {
        if (ch == '?') {
            ret = CLO_EXIT;
            log_debug("invalid short option\n");
            goto DONE;
        }
        for (i = 0; i < total_opt; i++) {
            if (ch != clo_info[i].opt) {
                continue;
            }
            ret = clo_info[i].clo_callback(zkc, optarg);
            if (ret) {
                goto DONE;
            }
        }
    }

    optind =  1;
    optidx = -1;
    /* Process long options */
    while ((ch = getopt_long(argc, argv, "", long_opts, &optidx)) != -1) {
        if (ch == '?') {
            ret = CLO_EXIT;
            log_debug("invalid long option\n");
            goto DONE;
        }
        if (ch >= total_opt) {
            log_err("Invalid command line option\n");
            ret = CLO_ERR;
            goto DONE;
        }
        ret = clo_info[ch].clo_callback(zkc, optarg);
        if (ret) {
            goto DONE;
        }
    }

DONE:
    return ret;
}

void
zk_clo_show()
{
    int i;

    for (i = 0; i < total_opt; i ++) {
        log_notice("\t-%c\t--%s\t%s\n",
                  (clo_info[i].opt)?clo_info[i].opt:' ',
                  (long_opts[i].name)?long_opts[i].name:"",
                  clo_info[i].desc);
    }

    return;
}

int
zk_clo_init()
{
    zakuta_clo_register();
    pcap_clo_register();

    return 0;
}

void
zk_clo_fini()
{
    return;
}


