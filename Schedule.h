#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "DeliveryRequest.h"
#include "Route.h"
#include <fstream>
#include <string>

class Schedule {
public:
    Schedule(int numTrucks, int maxDeliveriesPerDay)
        : numTrucks(numTrucks), maxDeliveriesPerDay(maxDeliveriesPerDay), outputFilename("route_data.csv") {}

    void addDeliveryRequest(const DeliveryRequest& request);
    void createSchedule();
    const std::vector<Route>& getRoutes() const;
    void displaySchedule() const;
    DeliveryRequest consolidateRequests(const DeliveryRequest& existingRequest, const DeliveryRequest& newRequest);
    void writeToCSV(const std::string& filename) const;

    // Sets the filename for outputting route data
    void setOutputFilename(const std::string& filename) { outputFilename = filename; }


    static void initializeCSV(const std::string& filename);

private:
    int numTrucks;
    int currentDay = 1;
    int maxDeliveriesPerDay;
    int truckId = 1;  // Add this line
    std::vector<DeliveryRequest> deliveryRequests;
    std::vector<Route> routes;

    std::string outputFilename; // Filename for outputting route data

    void scheduleDeliveries(std::vector<DeliveryRequest>& deliveries);
    void finalizeRoute(std::vector<DeliveryRequest>& truckQueue, int truckId);
    
};

#endif // SCHEDULE_H
