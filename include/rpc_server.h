//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_RPC_SERVER_H
#define SUNNYRPC_RPC_SERVER_H

#include <iostream>
#include <map>
#include "boost/shared_ptr.hpp"
#include "boost/core/noncopyable.hpp"
#include "google/protobuf/service.h"

#include "rpc_socket.h"
#include "rpc_method.h"

namespace sunnyrpc {

    class Dispatcher;

    class RpcServer : private boost::noncopyable {
    public:
        typedef std::map<uint16_t, RpcMethod*> RpcMethodMap;
        RpcServer(uint16_t port);

        virtual ~RpcServer();

        void register_service();

        int init();

        void run();

        void on_accept(int fd);
        void on_read(int fd);
        void on_write(int fd);

        int listen_fd() {
            return _socket->fd();
        }
    private:
        boost::shared_ptr<Socket> _socket;
        boost::shared_ptr<Dispatcher> _dispatcher;
        RpcMethodMap _rpc_method_map;
    };

}  //namespace

#endif //SUNNYRPC_RPC_SERVER_H
