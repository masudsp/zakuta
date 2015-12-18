#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include "zkconfig.h"
#include "log.h"

#define safe_free(x) do { if ((x) != NULL) {free(x); x=NULL;} } while(0)

