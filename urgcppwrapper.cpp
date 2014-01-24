#include "urgcppwrapper.h"

URGCPPWrapper::URGCPPWrapper(const std::string &ip, const int ip_port)
    : ip(ip), ip_port(ip_port), serial_port(""), serial_baudrate(0),
      started(false), use_intensity(true), use_multi_echo(false),
      distance(0), intensity(0)
{
    if (!urg.open(ip.c_str(), ip_port, qrk::Urg_driver::Ethernet))
    {
        // Error
        std::stringstream ss;
        ss << "Urg_driver::open(): ";
        ss << ip << ":" << ip_port << std::endl;
        ss << urg.what();
        throw std::runtime_error(ss.str());
    }

    reserveDataContainer();
}

URGCPPWrapper::URGCPPWrapper(const int serial_baudrate, const std::string& serial_port)
    : serial_baudrate(serial_baudrate), serial_port(serial_port), ip(""), ip_port(0),
      started(false), use_intensity(true), use_multi_echo(false),
      distance(0), intensity(0)
{
    if (!urg.open(ip.c_str(), ip_port, qrk::Urg_driver::Ethernet))
    {
        // Error
        std::stringstream ss;
        ss << "Urg_driver::open(): ";
        ss << serial_port << ":" << serial_baudrate << std::endl;
        ss << urg.what();
        throw std::runtime_error(ss.str());
    }

    reserveDataContainer();
}


URGCPPWrapper::~URGCPPWrapper()
{
    stop();
    urg.close();
}

void URGCPPWrapper::start(bool use_intensity, bool use_multi_echo)
{
    if(!started){
        setMeasurementType(use_intensity, use_multi_echo);

        if(!urg.start_measurement(measurement_type))
        {
            std::stringstream ss;
            ss << "Urg_driver::start_measurement(): ";
            ss << urg.what();
            throw std::runtime_error(ss.str());
        }

        started = true;
    }
}

void URGCPPWrapper::stop()
{
    if(started){
        urg.stop_measurement();
        started = false;
    }
}

void URGCPPWrapper::grabScan()
{
    if (!urg.get_distance(distance, &time_stamp)) {
        std::stringstream ss;
        ss << "Urg_driver::get_distance(): " << urg.what() << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void URGCPPWrapper::grabScanWithIntensity()
{
    if (!urg.get_distance_intensity(distance, intensity, &time_stamp)) {
        std::stringstream ss;
        ss << "Urg_driver::get_distance_intensity(): " << urg.what() << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void URGCPPWrapper::grabScanEcho()
{
    if (!urg.get_multiecho(distance, &time_stamp)) {
        std::stringstream ss;
        ss << "Urg_driver::get_distance(): " << urg.what() << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void URGCPPWrapper::grabScanEchoWithIntensity()
{
    if (!urg.get_multiecho_intensity(distance, intensity, &time_stamp)) {
        std::stringstream ss;
        ss << "Urg_driver::get_multiecho_intensity(): " << urg.what() << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void URGCPPWrapper::sync()
{
    urg.set_sensor_time_stamp(qrk::ticks());
}

void URGCPPWrapper::setMeasurementType(bool use_intensity, bool use_multi_echo)
{
    if(!started)
    {
        this->use_intensity = use_intensity;
        this->use_multi_echo = use_multi_echo;

        if(use_intensity && use_multi_echo){
            measurement_type = qrk::Lidar::Multiecho_intensity;
        }else if(use_intensity){
            measurement_type = qrk::Lidar::Distance_intensity;
        }else if(use_multi_echo){
            measurement_type = qrk::Lidar::Multiecho;
        }else{
            measurement_type = qrk::Lidar::Distance;
        }

    }else{
        std::cerr << "Measurement already running. You must stop measurement before to change measurement type." << std::endl;
    }
}

void URGCPPWrapper::reserveDataContainer()
{
    const int data_size = urg.max_data_size();
    const int echo_size = urg.max_echo_size();

    distance.reserve(data_size * echo_size);
    intensity.reserve(data_size * echo_size);
}

/***************
 *
 * Getters
 *
 ***************/

std::string URGCPPWrapper::getAllInfo() const
{
    std::stringstream ss;
    ss << "Sensor product type: " << urg.product_type() << std::endl;
    ss << "Sensor firmware version: " << urg.firmware_version() << " (last version is 1.1.8 ?)" << std::endl;
    ss << "Sensor serial ID: " << urg.serial_id() << std::endl;
    ss << "Sensor status: " << urg.status() << std::endl;
    ss << "Sensor state: " << urg.state() << std::endl;

    ss << "step: ["
       << urg.min_step() << ", "
       << urg.max_step() << "]" << std::endl;
    ss << "distance: ["
       << urg.min_distance()
       << ", " << urg.max_distance() << "]" << std::endl;

    ss << "scan interval: " << urg.scan_usec() << " [usec]" << std::endl;
    ss << "sensor data size: " << urg.max_data_size() << std::endl;

    return ss.str();
}

bool URGCPPWrapper::isStarted() const
{
    return started;
}

const std::vector<long>& URGCPPWrapper::getDistance() const
{
    return distance;
}

const std::vector<unsigned short>& URGCPPWrapper::getIntensity() const
{
    return intensity;
}

long URGCPPWrapper::getTimeStamp() const
{
    return time_stamp;
}

bool URGCPPWrapper::useIntensity() const
{
    return use_intensity;
}

bool URGCPPWrapper::useMultiEcho() const
{
    return use_multi_echo;
}

unsigned long int URGCPPWrapper::getNumberOfPoints() const
{
    return urg.max_data_size();
}

double URGCPPWrapper::index2rad(int index) const
{
    return urg.index2rad(index);
}
