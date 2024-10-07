#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

double calculateDistance(double *p1, double *p2)
{
    return std::sqrt(std::pow(p2[0] - p1[0], 2) +
                     std::pow(p2[1] - p1[1], 2) +
                     std::pow(p2[2] - p1[2], 2));
}

int main()
{
    int dist = 0;
    int global_waypoint_num_ = 0;
    double global_waypoints_[256][3];
    std::ifstream file("/home/hw/projects/ego-planner-ws/map/route.csv");
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Unable to open file!" << std::endl;
        return -1;
    }

    global_waypoints_[0][0] = 383.9244384765625;
    global_waypoints_[0][1] = -218.73434448242188;
    global_waypoints_[0][2] = 2;

    int i = 1;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string x_str, y_str;

        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ','))
        {
            global_waypoints_[i][0] = std::stod(x_str);
            global_waypoints_[i][1] = std::stod(y_str);
            global_waypoints_[i][2] = 2;
        }
        dist += calculateDistance(global_waypoints_[i], global_waypoints_[i - 1]);

        std::cout << i << "th waypoints: ("
                 << global_waypoints_[i][0] << ", "
                 << global_waypoints_[i][1] << ", "
                 << global_waypoints_[i][2] << ")"
                 << " distance is "
                 << dist
                 << std::endl;

        i++;
    }

    global_waypoint_num_ = i;

    file.close();

    return 0;
}