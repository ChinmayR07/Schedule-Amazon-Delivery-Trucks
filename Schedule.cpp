#include "Schedule.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
using namespace std;
void Schedule::addDeliveryRequest(const DeliveryRequest& request) {
    deliveryRequests.push_back(request);
}
void Schedule::initializeCSV(const std::string& filename) {
    std::ofstream outFile(filename, std::ios::trunc); // Open in truncate mode to clear the file
    // Write headers here if needed
   
    outFile.close();
}

void Schedule::createSchedule() {
    // Group deliveries by address
    std::map<Address, std::vector<DeliveryRequest>> addressGroups;

    // Populate addressGroups
    for (const auto& request : deliveryRequests) {
        addressGroups[request.getAddress()].push_back(request);
    }

    // Custom sorting function to sort by minimum deadline within each group
    auto customSort = [](const std::vector<DeliveryRequest>& groupA, const std::vector<DeliveryRequest>& groupB) {
        // Find the minimum deadline in each group
        auto minDeadlineA = std::min_element(groupA.begin(), groupA.end(), [](const DeliveryRequest& a, const DeliveryRequest& b) {
            return a.getDeadline() < b.getDeadline();
        });

        auto minDeadlineB = std::min_element(groupB.begin(), groupB.end(), [](const DeliveryRequest& a, const DeliveryRequest& b) {
            return a.getDeadline() < b.getDeadline();
        });

        // Compare the minimum deadlines to sort the groups
        return minDeadlineA->getDeadline() < minDeadlineB->getDeadline();
    };

    // Sort address groups based on the minimum deadline within each group
    std::vector<std::vector<DeliveryRequest>> sortedGroups;
    for (auto& entry : addressGroups) {
        sortedGroups.push_back(entry.second);
    }
    std::sort(sortedGroups.begin(), sortedGroups.end(), customSort);

    // Concatenate sorted address groups into the final vector
    std::vector<DeliveryRequest> Deliveries;
    for (const auto& group : sortedGroups) {
        Deliveries.insert(Deliveries.end(), group.begin(), group.end());
    }

    // Schedule Non-Prime deliveries for subsequent days
    scheduleDeliveries(Deliveries);
}

void Schedule::scheduleDeliveries(std::vector<DeliveryRequest>& deliveries) {
    DeliveryRequest depotRequest(Address(0, 0), true, 0);
    std::vector<std::vector<DeliveryRequest>> truckQueues(numTrucks, {depotRequest});

    size_t truckIndex = 0;

    for (const auto& delivery : deliveries) {
        // Check if delivery deadline is met
 //cout<<delivery.getAddress().getX()<<" "<<delivery.getAddress().getY()<<" "<<delivery.getDeadline()<<endl;
        if (delivery.getDeadline() < currentDay) {
            std::cerr << "Warning: Unable to meet deadline for delivery to Address("
                      << delivery.getAddress().getX() << ", " << delivery.getAddress().getY()
                      << ") with deadline " << delivery.getDeadline() << "\n";
            continue;  // Skip this delivery
        }
        
        truckQueues[truckIndex].push_back(delivery);
        //   std::cout << "Added to Truck " << truckIndex + 1 << " Queue: Address("
        //           << delivery.getAddress().getX() << ", " << delivery.getAddress().getY()
        //           << "), Deadline: " << delivery.getDeadline() <<" Current Day"<<currentDay<< "\n";
        //  cout<<"Truck Queue Size "<<truckQueues[truckIndex].size()<<endl;
        if (truckQueues[truckIndex].size() == maxDeliveriesPerDay+1) {
             truckQueues[truckIndex].push_back(depotRequest);
     //    cout<<"Truck Queue Size"<<truckQueues[truckIndex].size();
           finalizeRoute(truckQueues[truckIndex], truckIndex + 1);
           
            truckIndex = (truckIndex + 1) % numTrucks;
             truckQueues[truckIndex] = {depotRequest};
              if (truckIndex == 0) { 
            currentDay++;
        }
        }
    }

    // Finalize remaining deliveries
        if (truckQueues.size() > 1) {
            truckQueues[truckIndex].push_back(depotRequest);
            finalizeRoute(truckQueues[truckIndex], truckIndex + 1);
        }
    
}
  

void Schedule::finalizeRoute(std::vector<DeliveryRequest>& truckQueue, int truckId) {
    if (!truckQueue.empty() && truckQueue.size() > 2) {
        Route route;
        route.createNearestNeighborRoute(truckQueue);
        route.optimizeWithLinKernighan();
        routes.push_back(route);

        route.outputRouteData(outputFilename, currentDay, truckId);
    }

    // After finalizing the last truck for the day, increment the day counter
    if (&truckQueue == &routes.back().getDeliveryRequests() && truckQueue != routes.front().getDeliveryRequests()) {
        currentDay++;
    }
}

void Schedule::displaySchedule() const {
    int day = 1;
    int truckId = 1;

    for (const auto& route : routes) {
        std::cout << "Day " << day << ", Truck " << truckId << ":\n";

        // Print the starting point
        std::cout << "    Starting Point: Address(0, 0)\n";

        // Print each delivery request except for the starting and ending depot
        auto requests = route.getDeliveryRequests();
        for (size_t i = 1; i < requests.size() - 1; ++i) {
            const Address& addr = requests[i].getAddress();
            std::cout << "    Address: (" << addr.getX() << ", " << addr.getY() << ")";
            std::cout << ", Prime: " << (requests[i].getIsPrime() ? "Yes" : "No");
            std::cout << ", Deadline: " << requests[i].getDeadline() << "\n";
        }

        // Print the ending point
        std::cout << "    Ending Point: Address(0, 0)\n";

        // Print the total distance
        std::cout << "    Total Distance: " << route.calculateTotalDistance() << " units\n";

        // Update the truck and day counters
        if (truckId == numTrucks) {
            truckId = 1;
            ++day;
        } else {
            ++truckId;
        }
    }

    // // Output CSV format for Python processing
    // std::cout << "Route, Greedy Distance, LK Distance\n";
    // for (size_t i = 0; i < routes.size(); ++i) {
    //     std::cout << "Route " << i + 1 << ", "
    //               << routes[i].getGreedyDistance() << ", "
    //               << routes[i].getLKDistance() << "\n";
    // }
}



void Schedule::writeToCSV(const std::string& filename) const {
    std::ofstream csvFile(filename);

    // Write CSV headers
    csvFile << "Day,Truck,Total Greedy Distance,Total LK Distance\n";

    int day = 1;
    int truckId = 1;
    double dailyTotalGreedy = 0.0, dailyTotalLK = 0.0;

    for (const auto& route : routes) {
        double greedyDistance = route.getGreedyDistance();
        double lkDistance = route.getLKDistance();

        csvFile << day << "," << truckId << "," << greedyDistance << "," << lkDistance << "\n";

        dailyTotalGreedy += greedyDistance;
        dailyTotalLK += lkDistance;

        // Update day and truckId for the next iteration
        if (truckId == numTrucks) {
            // Write daily totals
            csvFile << day << ",Total," << dailyTotalGreedy << "," << dailyTotalLK << "\n";

            truckId = 1;
            ++day;
            dailyTotalGreedy = 0.0; dailyTotalLK = 0.0;
        } else {
            ++truckId;
        }
    }

    csvFile.close();
}

const std::vector<Route>& Schedule::getRoutes() const {
    return routes;
}
