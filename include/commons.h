//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_COMMONS_H
#define SUNNYRPC_COMMONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>


#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct sockaddr SA;
const int MAX_CONN = 5;
const int BUF_SIZE = 1024;
const int MAX_KQUEUE_NUM = 1024;


void set_nonblock(int fd);


#endif //SUNNYRPC_COMMONS_H
