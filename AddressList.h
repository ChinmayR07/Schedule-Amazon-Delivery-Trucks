#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#include <vector>
#include "Address.h"


class AddressList {
public:
    AddressList() {}

    void addAddress(const Address& address);
    const std::vector<Address>& getAddresses() const;

private:
    std::vector<Address> addresses;
};

#endif // ADDRESSLIST_H