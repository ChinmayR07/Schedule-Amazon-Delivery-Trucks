#include "Schedule.h"
#include "DeliveryRequest.h"
#include "Address.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    // Initialize random seed
    std::srand(std::time(nullptr));

    // Initialize the number of trucks and maximum deliveries per day
    const int numTrucks = 3;
    const int maxDeliveriesPerDay = 5;

    // Create a list of random addresses for delivery
   std::vector<Address> addresses;
    //    std::vector<Address> addresses = {
    //    Address(2, 3),
    //     Address(4, 6),
    //      Address(8, 9),
    //     Address(1, 7),
    //     Address(2, 3),
    //     Address(3,9),
    //      Address(3,0),    
    //      Address(4, 6),
    //      Address(8, 9),
    //     Address(1, 7),
    //     Address(2, 3),
    //     Address(3,9),
    //      Address(3,0)   
    // };
    const int numAddresses = 50; // Number of addresses
    for (int i = 0; i < numAddresses; ++i) {
        int x = std::rand() % 10+1; // Random x coordinate (0 to 9)
        int y = std::rand() % 10+1; // Random y coordinate (0 to 9)
        addresses.push_back(Address(x, y));
    }
int i=1;
    // Convert addresses to delivery requests with random prime status and deadline
    std::vector<DeliveryRequest> deliveryRequests;
    for (const auto& addr : addresses) {
       // bool isPrime = std::rand() % 2 == 0; // Randomly assign prime status
     bool isPrime;
       if(i<=5)
       isPrime=1;
       else
       isPrime=0;
       i++;

      // cout<<isPrime<<endl;
        int deadline = isPrime ? 1 : (std::rand() % 3 + 2); // Deadline: 1 for prime, 2-4 for non-prime
        deliveryRequests.push_back(DeliveryRequest(addr, isPrime, deadline));
    }

        // Print delivery requests
    // cout << "Delivery Requests:" << endl;
    // for (const auto& request : deliveryRequests) {
    //     cout << "Address: (" << request.getAddress().getX() << ", " << request.getAddress().getY() << "), ";
    //     cout << "Prime: " << (request.getIsPrime() ? "Yes" : "No") << ", ";
    //     cout << "Deadline: " << request.getDeadline() << endl;
    // }

    // Create and initialize the schedule
    Schedule schedule(numTrucks, maxDeliveriesPerDay);
    for (const auto& request : deliveryRequests) {
        schedule.addDeliveryRequest(request);
    }
Schedule::initializeCSV("route_data.csv");
    // Generate and display the schedule
    schedule.createSchedule();
    schedule.displaySchedule();
    schedule.writeToCSV("delivery_schedule.csv");
    
    return 0;
}
