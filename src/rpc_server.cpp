//
// Created by Andrew_liu on 16/7/31.
//

#include "rpc_server.h"

#include "dispatcher.h"
#include "rpc_socket.h"

namespace sunnyrpc {
    RpcServer::RpcServer(uint16_t port) {
        _socket.reset(new Socket(port));
        _socket.reset(new Dispatcher());
    }

    int RpcServer::init() {
        int ret = _socket->init();
        if (ret != 0) {
            std::cout << "[DEBUG]: RpcServer::init socket error" << std::endl;
            return -1;
        }
        ret = _dispatcher->init(this);
        if (ret != 0) {
            std::cout << "[DEBUG]: RpcServer::init dispatcher error" << std::endl;
            return -1;
        }
        return 0;
    }

    void RpcServer::run() {
        _dispatcher->start_server();
    }

    void RpcServer::on_accept(int fd) {

    }

    void RpcServer::on_read(int fd) {

    }

    void RpcServer::on_write(int fd) {
        
    }
}