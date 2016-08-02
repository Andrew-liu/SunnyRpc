//
// Created by Andrew_liu on 16/8/1.
//

#include "commons.h"

namespace sunnyrpc {
    void set_nonblock(int fd) {
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags < 0) {
            ERR_EXIT("[DEBUG]: fcntl failed");
        }
        int ret = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
        if (ret < 0) {
            ERR_EXIT("[DEBUG]: fcntl failed");
        }
    }
}
