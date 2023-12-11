#include "DeliveryRequest.h"
#include "DeliveryRequest.h"

DeliveryRequest::DeliveryRequest() : address(0, 0), isPrime(false), deadline(0) {
    // Initialize with default values
}
bool DeliveryRequest::isValid() const {
    return deadline != 0; // A non-zero deadline implies a valid request
}
// Other constructors and methods...

// Constructor implementation (assuming you have already defined it)
DeliveryRequest::DeliveryRequest(const Address& address, bool isPrime, int deadline)
    : address(address), isPrime(isPrime), deadline(deadline) {}

// Get the address associated with the delivery request
const Address& DeliveryRequest::getAddress() const {
    return address;
}

bool DeliveryRequest::operator==(const DeliveryRequest& other) const {
    return this->address == other.address &&
           this->isPrime == other.isPrime &&
           this->deadline == other.deadline;
}
// Implementations for getIsPrime and getDeadline
bool DeliveryRequest::getIsPrime() const {
    return isPrime;
}

int DeliveryRequest::getDeadline() const {
    return deadline;
}