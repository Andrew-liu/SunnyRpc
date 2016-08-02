//
// Created by Andrew_liu on 16/7/31.
//

#include "rpc_socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <cstring>
#include "commons.cpp"

namespace sunnyrpc{
    Socket::Socket(uint16_t port) :
        _sockfd(0),
        _port(port) {
    }

    Socket::~Socket() {
        if (_sockfd != 0) {
            ::close(_sockfd);
        }
    }

    int Socket::init() {
        rpc_socket();
        set_reuse_port();
        rpc_bind();
        rpc_listen();
        return 0;
    }

    void Socket::set_reuse_port() {
        int on = 1;
        if (::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &on,
                         static_cast<socklen_t>(sizeof(on))) == -1) {
            ERR_EXIT("[DEBUG]:set reuse port");
        }
    }

    void Socket::rpc_socket() {
        int sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            ERR_EXIT("[DEBUG]:socket");
        }
        _sockfd = sockfd;
    }
    void Socket::rpc_bind() {
        struct sockaddr_in sock_addr;
        ::memset(&sock_addr, 0, sizeof(sock_addr));
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        sock_addr.sin_port = htons(_port);

        if (::bind(_sockfd, (SA*)&sock_addr, sizeof(sock_addr)) == -1) {
            ERR_EXIT("[DEBUG]: bind");
        }
    }

    void Socket::rpc_listen() {
        if (::listen(_sockfd, MAX_CONN) == -1) {
            ERR_EXIT("[DEBUG]: listen");
        }
    }

    int Socket::rpc_accept() {
        int peer_fd;
        if ((peer_fd = ::accept(_sockfd, NULL, NULL)) == -1) {
            ERR_EXIT("[DEBUG]: accept");
        }
        return peer_fd;
    }
}
