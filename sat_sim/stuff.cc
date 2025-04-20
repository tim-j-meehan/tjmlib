#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include "sgp4dc/SGP4.h"  // Include an SGP4 library header file


// Function to propagate orbit and send position data via ZeroMQ
void propagateOrbitAndSendData(const std::string& line1, const std::string& line2, const std::string& zmq_address) {
    // Initialize the ZeroMQ context and publisher socket
    zmq::context_t context(1);
    zmq::socket_t publisher(context, zmq::socket_type::pub);
    publisher.bind(zmq_address);

    // Parse the TLE
    elsetrec satellite;
    double tsince = 0.0;
    const char typerun = 'c';
    const char opsmode = 'a';
    char typeinput;
    double startmfe, stopmfe, deltamin, magdr;
    char long_str1[140];
    char long_str2[140];
    strcpy(long_str1,line1.c_str());
    strcpy(long_str2,line2.c_str());
    SGP4Funcs::twoline2rv(long_str1, long_str2, typerun, typeinput, opsmode, wgs72,
                          startmfe, stopmfe,deltamin, satellite);
//                  twoline2rv( longstr1, longstr2, typerun, typeinput, opsmode, whichconst,
//                              startmfe, stopmfe, deltamin, satrec );

nexts steps
find this point rotate the vector find the next point

pstart
pfinal = find_point(pstart)

pick any vector on the plane perpendicular to the normal vector
find the magic point where we have visibility
rotate this vector back down onto the plane and rotate it x deg
rinse and repeat
    // Propagation loop
    while (true) {
        // Propagate the satellite position
        double position[3], velocity[3];
        SGP4Funcs::sgp4(satellite, tsince, position, velocity);

        // Create a JSON message with the position data
        std::string message = "{\"x\": " + std::to_string(position[0]) +
                               ", \"y\": " + std::to_string(position[1]) +
                               ", \"z\": " + std::to_string(position[2]) + "}";

        // Send the message via ZeroMQ
        zmq::message_t zmq_message(message.begin(), message.end());
        publisher.send(zmq_message, zmq::send_flags::none);

        // Print the data to the console for debugging
        std::cout << "Sent: " << message << std::endl;

        // Wait for a short interval before propagating again (e.g., 1 second)
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Increment time since epoch
        tsince += 1.0;  // Advance by 1 minute
    }
}

int main() {
    // Example TLE lines for a satellite (replace with actual TLE data)
    std::string line1 = "1 25544U 98067A   23044.52137731  .00016717  00000+0  10270-3 0  9004";
    std::string line2 = "2 25544  51.6423 115.7655 0004941  82.1204  41.7932 15.49980417339278";

    // ZeroMQ publisher address
    std::string zmq_address = "tcp://*:5555";

    // Start propagation and data transmission
    propagateOrbitAndSendData(line1, line2, zmq_address);

    return 0;
}

