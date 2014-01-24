#ifndef URGCPPWRAPPER_H
#define URGCPPWRAPPER_H

#include <urg_cpp/Urg_driver.h>
#include <urg_cpp/ticks.h>
#include <sstream>
#include <stdexcept>
#include <iostream>

class URGCPPWrapper
{
public:  
    URGCPPWrapper(const std::string& ip, const int ip_port);
    URGCPPWrapper(const int serial_baudrate, const std::string& serial_port);
    ~URGCPPWrapper();
    void start(bool use_intensity = true, bool use_multi_echo = false);
    void stop();

    void grabScan();
    void grabScanWithIntensity();
    void grabScanEcho();
    void grabScanEchoWithIntensity();

    void sync();

    // Getters
    std::string getAllInfo() const;
    bool isStarted() const;
    const std::vector<long>& getDistance() const;
    const std::vector<unsigned short>& getIntensity() const;
    long getTimeStamp() const;
    bool useIntensity() const;
    bool useMultiEcho() const;
    unsigned long int getNumberOfPoints() const;

    // Utility
    double index2rad(int index) const;

private:
    qrk::Urg_driver urg;
    std::vector<long> distance;
    std::vector<unsigned short> intensity;
    long time_stamp;

    // Connection info
    int ip_port;
    std::string ip;
    int serial_baudrate;
    std::string serial_port;

    // States
    bool started;
    bool use_intensity;
    bool use_multi_echo;
    qrk::Lidar::measurement_type_t measurement_type;

    void reserveDataContainer();
    void setMeasurementType(bool use_intensity, bool use_multi_echo);

};

#endif // URGCPPWRAPPER_H
