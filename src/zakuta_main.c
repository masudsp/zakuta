/**
 * Copyright (c) 2015, Masood Mehmood <sp@linux.com>
 * 3-clause (or "modified") BSD license
 *
 * \file   zakuta_main.c
 * \brief  main entry file
 *
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "common.h"
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>

#include "clo.h"

static int
show_version(zakuta_conf_t *zkc, const char *optarg)
{
    log_notice("Version %d.%d\n", RELEASE, VERSION);

    return CLO_EXIT;
}

static int
help(zakuta_conf_t  *zkc, const char *optarg)
{
    log_notice("Version %d.%d\n", RELEASE, VERSION);
    log_notice("Usage: zakuta [options]\n");
    zk_clo_show();

    return CLO_EXIT;
}

int
zakuta_clo_register()
{

    /* basic command line option code will go here */
    zk_clo_register("version", 'v', no_argument, "show version", show_version);
    zk_clo_register("help", 'h', no_argument, "show help", help);

    return 0;
}

static int
zk_init()
{
    /* command line option initialization */
    zk_clo_init();

    return 0;
}

int
main(int argc, char **argv)
{
    int   ret;
    zakuta_conf_t zkc;

    memset(&zkc, 0, sizeof(zakuta_conf_t));

    ret = zk_init();
    if (ret) {
        return ret;
    }

    ret = zk_clo_parse(&zkc, argc, argv);
    if (ret == 1) {
        //help(NULL, argv[0]);
        return -1;
    } else
    if (ret == 2) {
        return 0;
    }

    log_info("Argument parsed\n");

    if (zkc.input == NULL) {
        log_err("Please specify an input\n");
        help(NULL, argv[0]);
        return -1;
    }

    zkc.input(&zkc);

    return 0;
}

