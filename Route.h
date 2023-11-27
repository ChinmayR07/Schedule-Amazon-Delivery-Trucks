#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <algorithm>
#include <cmath>
#include "DeliveryRequest.h"

class Route {
public:
    Route() {}


 double distance(const std::vector<Address>& addresses) const;
    // Creates a route using the nearest-neighbor heuristic
    void createNearestNeighborRoute(const std::vector<DeliveryRequest>& requests);

    // Calculates the total distance of a single route
    double calculateTotalDistance() const;

    const std::vector<DeliveryRequest>& getDeliveryRequests() const;
private:
    std::vector<DeliveryRequest> deliveryRequests; // Stores the delivery requests

    // Calculates the distance between two addresses
    double calculateDistance(const Address& a, const Address& b) const;
};

#endif // ROUTE_H