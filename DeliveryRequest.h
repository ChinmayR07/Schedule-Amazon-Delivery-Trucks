#ifndef DELIVERYREQUEST_H
#define DELIVERYREQUEST_H

#include "Address.h"


class DeliveryRequest {
public:
    DeliveryRequest(const Address& address, bool isPrime, int deadline);

    const Address& getAddress() const;
    bool getIsPrime() const;
    int getDeadline() const;

private:
    Address address;
    bool isPrime;
    int deadline;
};

#endif // DELIVERYREQUEST_H