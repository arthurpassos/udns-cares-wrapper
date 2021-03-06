#pragma once

#include "DNSPTRResolver.h"
#include "ares.h"

class CARESPTRResolver : public DNSPTRResolver {

public:
    CARESPTRResolver();
    ~CARESPTRResolver();

    std::vector<std::string> resolve(const std::string & ip) override;

private:

    void init();
    void deinit();
    void wait();

    void resolve(const std::string & ip, std::vector<std::string> & response);

    ares_channel channel;
};
