#include "DeliveryRequest.h"
#include "Route.h"
#include "Address.h"
#include <iostream>
#include <vector>


int main() {
    // Example Addresses for Delivery Requests
    {
    std::cout<<"Test Case 1"<<std::endl;
    std::vector<Address> addresses = {
       Address(2, 3),
        Address(4, 6),
         Address(8, 9),
        Address(1, 7)
       
    };


    // Convert addresses to delivery requests
    std::vector<DeliveryRequest> deliveryRequests;
    for (const auto& addr : addresses) {
        deliveryRequests.push_back(DeliveryRequest(addr, false, 3)); // Non-prime, arbitrary deadline
    }

    // Create a Route object and use the Greedy Nearest Neighbor algorithm
    Route route;
    route.distance(addresses);
   // std::cout << "Total Distance without Greedy Algorithm: " << totalDistance << " units\n";
  
   // std::cout << "\nTotal Distance: " << route.calculateTotalDistance() << " units\n";
    route.createNearestNeighborRoute(deliveryRequests);
 

    // Print the constructed route
    std::cout << "Constructed Route after greedy: ";
    for (const auto& request : route.getDeliveryRequests()) {
        const Address& addr = request.getAddress();
        std::cout << "(" << addr.getX() << ", " << addr.getY() << ") ";
    }
    std::cout << "\nTotal Distance after greedy: " << route.calculateTotalDistance() << " units\n";
    }

    {
         std::cout<<"Test Case 2"<<std::endl;
    std::vector<Address> addresses = {
       Address(1, 2),
        Address(3, 4),
       Address(9, 0),
         Address(5, 6),
        Address(7, 8)
       
    };

    // Convert addresses to delivery requests
    std::vector<DeliveryRequest> deliveryRequests;
    for (const auto& addr : addresses) {
        deliveryRequests.push_back(DeliveryRequest(addr, false, 3)); // Non-prime, arbitrary deadline
    }

    // Create a Route object and use the Greedy Nearest Neighbor algorithm
    Route route;
    route.distance(addresses);
   // std::cout << "Total Distance without Greedy Algorithm: " << totalDistance << " units\n";
  
   // std::cout << "\nTotal Distance: " << route.calculateTotalDistance() << " units\n";
    route.createNearestNeighborRoute(deliveryRequests);
 

    // Print the constructed route
    std::cout << "Constructed Route after greedy: ";
    for (const auto& request : route.getDeliveryRequests()) {
        const Address& addr = request.getAddress();
        std::cout << "(" << addr.getX() << ", " << addr.getY() << ") ";
    }
    std::cout << "\nTotal Distance after greedy: " << route.calculateTotalDistance() << " units\n";
    
    }
    return 0;
}

