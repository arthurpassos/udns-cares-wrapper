#pragma once

#include <string>
#include <vector>

struct DNSPTRResolver {

    ~DNSPTRResolver() = default;

    virtual std::vector<std::string> resolve(const std::string & ip) = 0;

};