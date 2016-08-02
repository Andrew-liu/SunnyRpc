//
// Created by Andrew_liu on 16/8/1.
//
#include <netinet/in.h>

#include "dispatcher.h"

namespace sunnyrpc {
    Dispatcher::Dispatcher() :
            _kqueue_fd(-1),
            _shutdown(true),
            _index(0) {

    }

    Dispatcher::~Dispatcher() {
        if (_kqueue_fd != -1) {
            close(_kqueue_fd);
        }
    }

    int Dispatcher::init(RpcServer* rpc_server) {
        _rpc_server.reset(rpc_server);
        _kqueue_fd = kqueue();
        if (_kqueue_fd == -1) {
            ERR_EXIT("[DEBUG]: kqueue init error");
        }
        EV_SET(&_changes[_index++],
               _rpc_server->listen_fd(),
               EVFILT_READ | EVFILT_WRITE,
               EV_ADD | EV_ENABLE,
               0,
               0,
               (void*)(intptr_t)(_rpc_server->listen_fd()));
        return 0;
    }

    void Dispatcher::start_server() {
        int events_num;
        if (!_shutdown) {
            return;
        }
        _shutdown = false;
        while(!_shutdown) {
            events_num = kevent(_kqueue_fd,
                         _changes,  // 监视列表
                         MAX_KQUEUE_NUM,  //长度
                         _events,  //用于返回已经就绪的事件列表
                         MAX_KQUEUE_NUM,  //长度
                         NULL);  // 超时限制
            if (events_num == -1) {
                ERR_EXIT("[DEBUG]:kevent() error");
            } else if (events_num > 0) {
                for (int i = 0; i < events_num; ++i) {
                    struct kevent event = _events[i];
                    if( event.flags & EV_ERROR) {
                        printf("event error");
                    }
                    int ev_fd = (int)(intptr_t)_events[i].udata;
                    int events = _events[i].filter;
                    if (events == EVFILT_READ) {
                        if (ev_fd == _rpc_server->listen_fd()) {
                            struct sockaddr_in client_addr;
                            socklen_t len = sizeof(client_addr);
                            int conn_fd = accept(ev_fd, (SA*)&client_addr, &len);
                            if (conn_fd < 0) {
                                printf("accept client fd error!");
                                continue;
                            }
                            _rpc_server->on_accept(conn_fd);
                        } else {
                            _rpc_server->on_read(ev_fd);
                        }
                    } else if (events == EVFILT_WRITE) {
                        _rpc_server->on_write(ev_fd);
                    } else {
                        printf("kqueue unknown event");
                        continue;
                    }
                }
            }
        }
    }

    int Dispatcher::add_event(int fd) {
        EV_SET(&_changes[_index++],
               fd,
               EVFILT_READ | EVFILT_WRITE,
               EV_ADD | EV_ENABLE,
               0,
               0,
               (void*)(intptr_t)fd);
        return 0;
    }

}