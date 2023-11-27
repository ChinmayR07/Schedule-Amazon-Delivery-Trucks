#include "Address.h"
#include "DeliveryRequest.h"
#include "Route.h" 
#include <cmath>
#include <limits>
#include <iostream>

// Calculate the Manhattan distance between two addresses
double Route::calculateDistance(const Address& a, const Address& b) const {
    int dx = std::abs(a.getX() - b.getX());
    int dy = std::abs(a.getY() - b.getY());
    return static_cast<double>(dx + dy);
}


// Calculate the total distance of the route using Manhattan Distance
double Route::calculateTotalDistance() const {
    if (deliveryRequests.size() < 2) return 0.0;

    double totalDistance = 0.0;
    for (size_t i = 0; i < deliveryRequests.size() - 1; ++i) {
        totalDistance += calculateDistance(deliveryRequests[i].getAddress(), deliveryRequests[i + 1].getAddress());
    }
    return totalDistance;
}

double Route::distance(const std::vector<Address>& addresses) const {
    if (addresses.empty()) return 0.0;

    double totalDistance = 0.0;
    Address depot(0, 0); // Depot address

    std::cout << "Constructed Route before greedy: ";

    // Start from depot
    Address previousLocation = depot;
    std::cout << "(" << depot.getX() << ", " << depot.getY() << ") "; // Print depot as starting point

    // Calculate the distance for each address from the previous location
    for (const auto& address : addresses) {
        totalDistance += calculateDistance(previousLocation, address);
        std::cout << "(" << address.getX() << ", " << address.getY() << ") "; // Print each address in the route
        previousLocation = address;
    }

    // Add distance back to depot
    totalDistance += calculateDistance(previousLocation, depot);
    std::cout << "(" << depot.getX() << ", " << depot.getY() << ") "; // Print depot as ending point

    std::cout << "\nTotal Distance before greedy: " << totalDistance << " units\n";

    return totalDistance;
}

// Create a route using the nearest-neighbor heuristic
void Route::createNearestNeighborRoute(const std::vector<DeliveryRequest>& requests) {
    if (requests.empty()) return;

    // Start with the depot and clear any existing requests
    deliveryRequests.clear();
    Address depot(0, 0); // Setting depot to (0, 0)
    deliveryRequests.push_back(DeliveryRequest(depot, true, 0)); // Start with the depot

    // Track visited requests
    std::vector<bool> visited(requests.size(), false);

    Address currentLocation = depot;
    while (deliveryRequests.size() < requests.size() + 1) { // +1 for depot
        double nearestDist = std::numeric_limits<double>::max();
        size_t nearestIndex = std::numeric_limits<size_t>::max();

        for (size_t i = 0; i < requests.size(); ++i) {
            if (!visited[i]) {
                double dist = calculateDistance(currentLocation, requests[i].getAddress());
                if (dist < nearestDist) {
                    nearestDist = dist;
                    nearestIndex = i;
                }
            }
        }

        if (nearestIndex != std::numeric_limits<size_t>::max()) {
            visited[nearestIndex] = true;
            currentLocation = requests[nearestIndex].getAddress();
            deliveryRequests.push_back(requests[nearestIndex]);
        }
    }

    if (currentLocation != depot) {
        deliveryRequests.push_back(DeliveryRequest(depot, true, 0));
    }
}




const std::vector<DeliveryRequest>& Route::getDeliveryRequests() const {
    return deliveryRequests;
}