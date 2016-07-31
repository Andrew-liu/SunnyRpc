//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_COMMONS_H
#define SUNNYRPC_COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct sockaddr SA;
const int MAX_CONN = 5;

#endif //SUNNYRPC_COMMONS_H
