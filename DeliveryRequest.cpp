// DeliveryRequest.cpp

#include "DeliveryRequest.h"

// Constructor implementation (assuming you have already defined it)
DeliveryRequest::DeliveryRequest(const Address& address, bool isPrime, int deadline)
    : address(address), isPrime(isPrime), deadline(deadline) {}

// Get the address associated with the delivery request
const Address& DeliveryRequest::getAddress() const {
    return address;
}

// Implementations for getIsPrime and getDeadline
bool DeliveryRequest::getIsPrime() const {
    return isPrime;
}

int DeliveryRequest::getDeadline() const {
    return deadline;
}