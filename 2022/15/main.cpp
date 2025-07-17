#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <regex>
#include <unordered_set>

using namespace std;

struct Sensor {
    int x, y, beaconX, beaconY;
    Sensor(int x, int y, int beaconX, int beaconY) : x(x), y(y), beaconX(beaconX), beaconY(beaconY) {}
};

class Solution {
    public:
        Solution(const char* filename, bool isTest = false) {
            if (isTest) targetRow = 10, maxCoordinate = 20;
            getData(filename);
        }

        int partOne() {
            calculateNoBeaconPositions();
            mergeIntervals();
            return countNoBeaconPositions();
        }

        long long partTwo() {
            for (int y = 0; y <= maxCoordinate + 1; y++) {
                targetRow = y;
                calculateNoBeaconPositions(true);
                mergeIntervals();
                if (noBeaconIntervals.size() > 1) {
                    return (long long)(noBeaconIntervals[1].first - 1) * 4000000 + y;
                }
            }
            return 0;
        }

    
    private:
        vector<Sensor> sensors;
        int targetRow = 2000000;
        int maxCoordinate = 4000000;
        vector<pair<int, int> > noBeaconIntervals;
        unordered_set<int> beaconsInTargetRow;
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            regex pattern(R"x(x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+))x");
            while (getline(inputFile, line)) {
                smatch matches;
                regex_search(line, matches, pattern);
                int x = stoi(matches[1]);
                int y = stoi(matches[2]);
                int beaconX = stoi(matches[3]);
                int beaconY = stoi(matches[4]);
                sensors.emplace_back(x, y, beaconX, beaconY);
            }
        }

        void calculateNoBeaconPositions(bool partTwo = false) {
            noBeaconIntervals.clear();
            beaconsInTargetRow.clear();
            for (const auto& sensor : sensors) {
                if (sensor.beaconY == targetRow) {
                    beaconsInTargetRow.insert(sensor.beaconX);
                }
            }
            for (const auto& sensor : sensors) {
                int distance = abs(sensor.x - sensor.beaconX) + abs(sensor.y - sensor.beaconY);
                int rowDistance = abs(sensor.y - targetRow);
                if (rowDistance <= distance) {
                    int horizontalDistance = distance - rowDistance;
                    int start = sensor.x - horizontalDistance;
                    int end = sensor.x + horizontalDistance;
                    if (partTwo) {
                        if (end < 0 || start > maxCoordinate) continue;
                        if (start < 0) start = 0;
                        if (end > maxCoordinate) end = maxCoordinate;
                    }
                    noBeaconIntervals.emplace_back(start, end);
                }
            }
        }

        void mergeIntervals() {
            sort(noBeaconIntervals.begin(), noBeaconIntervals.end());
            vector<pair<int, int>> merged;  
            for (const auto& interval : noBeaconIntervals) {
                if (merged.empty() || merged.back().second < interval.first) {
                    merged.push_back(interval);
                }
                else {
                    merged.back().second = max(merged.back().second, interval.second);
                }
            }
            noBeaconIntervals = merged;
        }

        int countNoBeaconPositions() {
            int count = 0;
            for (const auto& interval : noBeaconIntervals) {
                count += interval.second - interval.first + 1;
                for (const auto& beaconX : beaconsInTargetRow) {
                    if (beaconX >= interval.first && beaconX <= interval.second) {
                        count--;
                    }
                }
            }
            return count;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("testinput.txt", true);
    Solution solution = Solution("input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}