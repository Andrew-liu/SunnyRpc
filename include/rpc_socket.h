//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_RPC_SOCKET_H
#define SUNNYRPC_RPC_SOCKET_H

#include <cstdint>
#include "boost/core/noncopyable.hpp"

namespace sunnyrpc {
    class Socket : private boost::noncopyable {
    public:
        // construction method
        explicit Socket(uint16_t port);
        // destruction method
        ~Socket();
        // return _sockfd
        int fd() const { return _sockfd; }
        // init socket
        int init();

        // set port reuse in TIME_WAIT
        void set_reuse_port();

    private:
        // create socket
        void rpc_socket();
        // bind addr to socket
        void rpc_bind();
        // listen
        void rpc_listen();
        // accept connection
        int rpc_accept();

    private:
        int _sockfd;
        uint16_t _port;
    };
}

#endif //SUNNYRPC_RPC_SOCKET_H
