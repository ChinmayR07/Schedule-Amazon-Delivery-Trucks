#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <algorithm>
#include <cmath>
#include "DeliveryRequest.h"
#include <string>  // Include for std::string

class Route {
public:
    Route() {}

    // Adds a delivery request to the route
    void addDeliveryRequest(const DeliveryRequest& request);
    double distance(const std::vector<Address>& addresses) const;

    // Creates a route using the nearest-neighbor heuristic
    void createNearestNeighborRoute(const std::vector<DeliveryRequest>& requests);

    // Optimizes the route using the Lin-Kernighan heuristic
    void optimizeWithLinKernighan();

    // Calculates the total distance of the route
    double calculateTotalDistance() const;

    // Gets the number of deliveries in the route
    size_t getNumberOfDeliveries() const;

    double getGreedyDistance() const { return greedyDistance; }
    double getLKDistance() const { return lkDistance; }

    void printRoute() const;
    const std::vector<DeliveryRequest>& getDeliveryRequests() const;

    // Outputs the route data for visualization
    void outputRouteData(const std::string& filename, int day, int truckId) const;

private:
    double greedyDistance = 0.0;
    double lkDistance = 0.0;

    std::vector<DeliveryRequest> deliveryRequests; // Stores the delivery requests
    std::vector<Address> greedyRoute;              // Stores the greedy heuristic route
    std::vector<Address> lkRoute;                  // Stores the Lin-Kernighan heuristic route

    // Calculates the distance between two addresses
    double calculateDistance(const Address& a, const Address& b) const;
};

#endif // ROUTE_H