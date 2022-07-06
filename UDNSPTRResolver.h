#pragma once

#include <string>
#include <vector>
#include <udns.h>
#include "DNSPTRResolver.h"

class UDNSPTRResolver : public DNSPTRResolver {
public:
    UDNSPTRResolver();

    ~UDNSPTRResolver();

    std::vector<std::string> resolve(const std::string & ip) override;

private:
    void init();
    void fini();

    dns_rr_ptr * query(const std::string & ip);

    std::vector<std::string> mapResultsAndFreeMemory(const dns_rr_ptr * result);

    struct dns_ctx * ctx_udns = nullptr;
};
