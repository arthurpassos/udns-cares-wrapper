#include <iostream>
#include "UDNSPTRResolver.h"
#include "CARESPTRResolver.h"

int main() {
    auto ip = "192.168.0.151";

    CARESPTRResolver cares_resolver;

    auto ptr_records = cares_resolver.resolve(ip);

    std::cout<<ip<<" resolves to:\n";

    for (const auto & record : ptr_records) {
        std::cout<<record<<"\n";
    }

    return 0;
}
