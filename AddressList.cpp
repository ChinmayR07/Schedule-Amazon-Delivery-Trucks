#include "AddressList.h"

void AddressList::addAddress(const Address& address) {
    addresses.push_back(address);
}

const std::vector<Address>& AddressList::getAddresses() const {
    return addresses;
}
