/*
This program will take in a flight log, a list of flights that should have paths found for. The program will then output the paths into the output file.
This program creates an adjacency list since the flights can be visualized as a graph, undirected for this project since flights can be bidirectional.
The program utilizes a modified depth-first search in order to find all paths from the source city to the destination city.
The program sorts the top 3 paths based on either time or cost. The sorting criteria is given in the flight request file.
Test cases: 60/60
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <forward_list>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// Define a structure to represent a flight path
struct FlightPath {
    vector<string> cities;
    pair<float, float> total_cost_duration;

    FlightPath() {} // Default constructor

    FlightPath(const vector<string>& _cities, float cost, float duration)
        : cities(_cities), total_cost_duration(make_pair(cost, duration)) {}
};

class FlightPlanner {
private:
    using FlightList = forward_list<pair<string, pair<float, float>>>;
    vector<pair<string, FlightList>> adjacency_list;
    vector<FlightPath> paths_found;
    int num_flights;

public:
    void parseFlightData(const string& file_name) {
        ifstream file(file_name);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << file_name << endl;
            return;
        }

        int n;
        file >> n;
        num_flights = n;

        adjacency_list.resize(num_flights);

        file.ignore(); // Ignore the newline after reading num_cities

        for (int i = 0; i < num_flights; ++i) {
            string line;
            // Read a line from the file
            if (!getline(file, line)) {
                cerr << "Error: Unexpected end of file." << endl;
                return;
            }
    
            // Parse the line to extract origin, destination, cost, and duration
            stringstream ss(line);
            string origin, destination;
            float cost, duration;
    
            if (getline(ss, origin, '|') && getline(ss, destination, '|') &&
                (ss >> cost) && (ss.ignore() && (ss >> duration))) {
                // Add the flight from origin to destination
                auto it_origin = find(adjacency_list.begin(), adjacency_list.end(), make_pair(origin, FlightList()));
                if (it_origin != adjacency_list.end()) {
                    it_origin->second.push_front(make_pair(destination, make_pair(cost, duration)));
                } else {
                    adjacency_list.emplace_back(make_pair(origin, FlightList()));
                    adjacency_list.back().second.push_front(make_pair(destination, make_pair(cost, duration)));
                }
    
                // Add the flight from destination to origin (bidirectional)
                auto it_destination = find(adjacency_list.begin(), adjacency_list.end(), make_pair(destination, FlightList()));
                if (it_destination != adjacency_list.end()) {
                    it_destination->second.push_front(make_pair(origin, make_pair(cost, duration)));
                } else {
                    adjacency_list.emplace_back(make_pair(destination, FlightList()));
                    adjacency_list.back().second.push_front(make_pair(origin, make_pair(cost, duration)));
                }
            } else {
                cerr << "Error: Invalid data format in line: " << line << endl;
            }
        }

        file.close();
    }

    void findPathsDFS(const string& source, const string& destination) {
        // Stack to store the current node, path, cost, and time
        stack<pair<string, pair<vector<string>, pair<float, float>>>> s;
        
        // Push the source node onto the stack with initial values
        s.push(make_pair(source, make_pair(vector<string>{source}, make_pair(0.0f, 0.0f))));
        
        while (!s.empty()) {
            // Pop the top element from the stack
            auto u = s.top();
            s.pop();
            
            // Check if the current node is the destination
            if (u.first == destination) {
                // If so, add the current path to the paths_found vector
                paths_found.push_back(FlightPath(u.second.first, u.second.second.first, u.second.second.second));
            } else {
                // Iterate over the neighbors of the current node
                for (const auto& neighbor : adjacency_list) {
                    if (neighbor.first == u.first) { // Check if the neighbor has an edge with the current node
                        for (const auto& flight : neighbor.second) {
                            // Check if the neighbor city has not been visited yet
                            if (find(u.second.first.begin(), u.second.first.end(), flight.first) == u.second.first.end()) {
                                // If not, push the neighbor onto the stack with updated path, cost, and time
                                vector<string> curr_path = u.second.first;
                                curr_path.push_back(flight.first);
                                float current_cost = u.second.second.first + flight.second.first;
                                float current_time = u.second.second.second + flight.second.second;
                                s.push(make_pair(flight.first, make_pair(curr_path, make_pair(current_cost, current_time))));
                            }
                        }
                    }
                }
            }
        }
    }

    
    static bool compareCost(FlightPath flight1, FlightPath flight2)
    {
        return (flight1.total_cost_duration.first < flight2.total_cost_duration.first);
    }
    
    static bool compareTime(FlightPath flight1, FlightPath flight2)
    {
        return (flight1.total_cost_duration.second < flight2.total_cost_duration.second);
    }


    void findTopPathsAndWriteToFile(const string& output_file, const string& origin, const string& destination, const string& sorting_preference, int k, int flightNumber) {
        // Sort the paths based on efficiency
        if(sorting_preference == "C")
        {
            sort(paths_found.begin(), paths_found.end(), compareCost);
        }
        else
        {
            sort(paths_found.begin(), paths_found.end(), compareTime);
        }
        // If you want only the top k paths, keep the first k paths
        paths_found.resize(min(k, (int)paths_found.size()));

        // Open the output file
        ofstream outputFileStream(output_file, ios::app);
        if (!outputFileStream.is_open()) {
            cerr << "Error: Unable to open output file " << output_file << endl;
            return;
        }

        // Write flight details and paths to the output file
        outputFileStream << "Flight " << flightNumber << ": " << origin << ", " << destination << " (" << sorting_preference << ")" << endl;
        for (int i = 0; i < paths_found.size(); ++i) {
            outputPath(outputFileStream, origin, destination, sorting_preference, i + 1, paths_found[i]);
        }
        outputFileStream << endl;

        // Close the output file
        outputFileStream.close();
    }



    void parseRequestedFlights(const string& file_name, const string& outputFile) {
        ifstream file(file_name);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << file_name << endl;
            return;
        }

        int num_requests;
        file >> num_requests;

        file.ignore(); // Ignore the newline after reading num_requests
        
        ofstream outputFileStream(outputFile);
        outputFileStream.close();

        for (int i = 0; i < num_requests; ++i) {
            paths_found.clear();
            string line;
            getline(file, line);
            stringstream ss(line);
            string source, destination, preference;
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, preference, '|');

            // Call findPathsDFS if the preference is a valid choice
            if (preference == "T" || preference == "C") {
                findPathsDFS(source, destination);
            } else {
                cerr << "Error: Invalid sorting preference '" << preference << "' for flight from " << source << " to " << destination << endl;
            }
            findTopPathsAndWriteToFile(outputFile, source, destination, preference, 3, i + 1);
            paths_found.clear();
        }

        file.close();
    }

    // Helper method to output a flight path
    void outputPath(ostream& output, string origin, string destination, const string& sorting_preference, int index, const FlightPath& path) {
        output << "Path " << index << ": ";
        for (const string& city : path.cities) {
            output << city;
            if(city != destination)
            {
                output << " -> ";
            }
        }
        output << ". Time: " << fixed << setprecision(0) << path.total_cost_duration.second << " Cost: " << setprecision(2) << path.total_cost_duration.first << endl;
    }

};

int main(int argc, char* argv[]) {
    FlightPlanner planner;
    string flightData = argv[1];
    
    // Parse flight data
    planner.parseFlightData(flightData);
    string requestedFlights = argv[2];
    string outputFileName = argv[3];
    
    // Parse requested flights and find top k paths for each request
    planner.parseRequestedFlights(requestedFlights, outputFileName);

    return 0;
}
