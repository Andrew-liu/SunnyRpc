//
// Created by Andrew_liu on 16/7/31.
//

#ifndef SUNNYRPC_RPC_METHOD_H
#define SUNNYRPC_RPC_METHOD_H

#include "google/protobuf/service.h"
#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/stubs/common.h"

namespace sunnyrpc {
    struct RpcMethod {
        RpcMethod(google::protobuf::Service* serv,
                google::protobuf::Message* req,
                google::protobuf::Message* resp,
                google::protobuf::MethodDescriptor* mtd) :
            service(serv),
            request(req),
            response(resp),
            method(mtd) {
        };

        google::protobuf::Service* service;
        google::protobuf::Message* request;
        google::protobuf::Message* response;
        google::protobuf::MethodDescriptor* method;
    };
}

#endif //SUNNYRPC_RPC_METHOD_H
