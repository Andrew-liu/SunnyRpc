//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_DISPATCHER_H
#define SUNNYRPC_DISPATCHER_H

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include "boost/shared_ptr.hpp"

#include "rpc_server.h"
#include "commons.h"

namespace sunnyrpc {
    class Dispatcher {
    public:
        Dispatcher();
        ~Dispatcher();

        // init dispatcher
        int init(RpcServer *rpc_server);
        // start kevent loop
        void start_server();

        // add client fd to monitor
        int add_event(int fd);
//        void remove_event(int fd);
    private:
        int _kqueue_fd;  // kqueue fd
        bool _shutdown;  // switch
        boost::shared_ptr<RpcServer> _rpc_server;
        int _index;  // monitor index
        struct kevent _events[MAX_KQUEUE_NUM];
        struct kevent _changes[MAX_KQUEUE_NUM];
    };
}

#endif //SUNNYRPC_DISPATCHER_H
