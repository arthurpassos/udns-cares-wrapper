#include "UDNSPTRResolver.h"
#include <udns.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <system_error>
#include <cstring>
#include <array>

#define THROW_ERRNO	throw std::system_error(errno, std::system_category(), strerror(errno))

UDNSPTRResolver::UDNSPTRResolver() {
    init();
}

UDNSPTRResolver::~UDNSPTRResolver() {
    fini();
}

void UDNSPTRResolver::init() {
    dns_init(nullptr, 0);

    ctx_udns = dns_new(nullptr);
    if (!ctx_udns)
        throw std::system_error(ENOMEM, std::system_category(), strerror(ENOMEM));

    if (dns_init(ctx_udns, 0) < 0)
        THROW_ERRNO;

    if (dns_open(ctx_udns) < 0) {
        THROW_ERRNO;
    }
}

void UDNSPTRResolver::fini() {
    if (ctx_udns) {
        dns_free(ctx_udns);
        ctx_udns = nullptr;
    }
}

std::vector<std::string> UDNSPTRResolver::resolve(const std::string & ip) {

    if (auto result = query(ip)) {
        return mapResultsAndFreeMemory(result);
    }

    return {};
}

dns_rr_ptr * UDNSPTRResolver::query(const std::string & ip) {
    in_addr sa;
    inet_pton(AF_INET, ip.c_str(), &(sa.s_addr));

    return dns_resolve_a4ptr(ctx_udns, &sa);
}

std::vector<std::string> UDNSPTRResolver::mapResultsAndFreeMemory(const dns_rr_ptr * result) {
    std::vector<std::string> ptr_records;

    for (uint32_t i = 0; i < result->dnsptr_nrr; i++) {
        ptr_records.emplace_back(result->dnsptr_ptr[i]);
    }

    delete result;

    return ptr_records;
}
