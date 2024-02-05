#pragma once
#include <string>

class ResponseStatus {
public:
    bool status;
    std::string error_msg;

    ResponseStatus(const bool&& status, const std::string&& error_msg) {
        this->status = status;
        this->error_msg = error_msg;
    }
};
