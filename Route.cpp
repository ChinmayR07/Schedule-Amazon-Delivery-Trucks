#include "Address.h"
#include "DeliveryRequest.h"
#include "Route.h" 
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>  // Include for file operations
#include <cmath> // for std::fabs

using namespace std;
// Calculate the Manhattan distance between two addresses
double Route::calculateDistance(const Address& a, const Address& b) const {
    int dx = std::abs(a.getX() - b.getX());
    int dy = std::abs(a.getY() - b.getY());
    return static_cast<double>(dx + dy);
}

void Route::addDeliveryRequest(const DeliveryRequest& request) {
    deliveryRequests.push_back(request);
}

size_t Route::getNumberOfDeliveries() const {
    return deliveryRequests.size();
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

    // Calculate the distance for each address from the previous location
    for (const auto& address : addresses) {
        totalDistance += calculateDistance(previousLocation, address);
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
    if (requests.size() < 2) return; // Need at least depot and one delivery point

    // Start with the depot and clear any existing requests
    deliveryRequests.clear();
    // Track visited requests; start with the depot as visited
    std::vector<bool> visited(requests.size(), false);
    visited[0] = true;

    Address currentLocation = requests.front().getAddress();
    
    // Iterate to create the route
    while (deliveryRequests.size() < requests.size()) {
        double nearestDist = std::numeric_limits<double>::max();
        size_t nearestIndex = 1; // Start from second request (skip depot)

        for (size_t i = 1; i < requests.size(); ++i) {
            if (!visited[i]) {
                double dist = calculateDistance(currentLocation, requests[i].getAddress());
                if (dist < nearestDist) {
                    nearestDist = dist;
                    nearestIndex = i;
                }
            }
        }

        visited[nearestIndex] = true;
        currentLocation = requests[nearestIndex].getAddress();
        deliveryRequests.push_back(requests[nearestIndex]);
    }

    // Clear and update greedyRoute
    greedyRoute.clear();
    int size=0;
    for (const auto& request : deliveryRequests) {
        greedyRoute.push_back(request.getAddress());
        size++;
        if(size==deliveryRequests.size()-1)
        break;
    }
    Address origin = Address(0,0);
    greedyRoute.push_back(origin);
    greedyDistance = calculateTotalDistance(); // Set greedy distance
}


void Route::optimizeWithLinKernighan() {
    bool improved = true;
    const double improvementThreshold = 0.01; // Adjust this threshold as needed

    while (improved) {
        improved = false;
        double bestDistance = calculateTotalDistance();
        
        auto beginIt = deliveryRequests.begin();
        auto endIt = deliveryRequests.end() - 1;

        for (auto i = beginIt + 1; i < endIt; ++i) {
            for (auto k = i + 1; k < endIt; ++k) {
                std::reverse(i, k + 1);
                double newDistance = calculateTotalDistance();

                // Allow improvements up to improvementThreshold percentage
                if ((bestDistance - newDistance) / bestDistance > improvementThreshold) {
                    bestDistance = newDistance;
                    improved = true;
                } else {
                    // Reverse back
                    std::reverse(i, k + 1);
                }
            }
        }
    }

    // Clear and update lkRoute
    lkRoute.clear();
    int size=0;
    for (const auto& request : deliveryRequests) {
        lkRoute.push_back(request.getAddress());
        size++;
        if(size==deliveryRequests.size()-1)
        break;
    }

    Address origin = Address(0,0);
    lkRoute.push_back(origin);
    lkDistance = calculateTotalDistance(); // Set LK distance after optimization
}


void Route::outputRouteData(const std::string& filename, int day, int truckId) const {
    std::ofstream outFile(filename, std::ios::app); // Append mode

    // Output route data for the Greedy heuristic
    if (!greedyRoute.empty()) {
        for (const auto& addr : greedyRoute) {
            outFile << day << "," << truckId << ","
                    << addr.getX() << "," << addr.getY() << ",Greedy\n";
        }
    }


    // Output route data for the Lin-Kernighan heuristic
    if (!lkRoute.empty()) {
        for (const auto& addr : lkRoute) {
            outFile << day << "," << truckId << ","
                    << addr.getX() << "," << addr.getY() << ",Lin-Kernighan\n";
        }
     }
   
}

const std::vector<DeliveryRequest>& Route::getDeliveryRequests() const {
    return deliveryRequests;
}

void Route::printRoute() const {
    for (const auto& request : deliveryRequests) {
        const Address& addr = request.getAddress();
        std::cout << "(" << addr.getX() << ", " << addr.getY() << ") ";
    }
    std::cout << std::endl;
}