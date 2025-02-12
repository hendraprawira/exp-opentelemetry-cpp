/*
 * Copyright PT LEN INNOVATION TECHNOLOGY
 *
 * THIS SOFTWARE SOURCE CODE AND ANY EXECUTABLE DERIVED THEREOF ARE PROPRIETARY
 * TO PT LEN INNOVATION TECHNOLOGY, AS APPLICABLE, AND SHALL NOT BE USED IN ANY WAY
 * OTHER THAN BEFOREHAND AGREED ON BY PT LEN INNOVATION TECHNOLOGY, NOR BE REPRODUCED
 * OR DISCLOSED TO THIRD PARTIES WITHOUT PRIOR WRITTEN AUTHORIZATION BY
 * PT LEN INNOVATION TECHNOLOGY, AS APPLICABLE.
 */

/*
 =================================================================================================================
 Name        : ir_video_control_controller.h
 Author      : Angga Gemilang
 Version     : 0.2.0 27/06/2024
 Description : Controller for IR Video Power Control setting
 =================================================================================================================
*/

#pragma once
#include <string>
#include <condition_variable>
#include "messages.grpc.pb.h"

class MessagesController final 
    : public grpc_example::Greeter::Service
{
public:
    MessagesController();
    grpc::Status Greet
    (
        grpc::ServerContext* context,
        const grpc_example::GreetRequest* request,
        grpc_example::GreetResponse* reply
    ) override;
private:

    grpc::Status get_messages_response
    (
        const grpc_example::GreetRequest* request,
        grpc_example::GreetResponse* reply,
        const std::string &resp
    );
};
