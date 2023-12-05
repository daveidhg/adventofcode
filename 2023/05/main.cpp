#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
using namespace std;

class Solution {
    public:
        vector<unsigned int> seeds;
        vector<vector<unsigned int> > seedToSoil;
        vector<vector<unsigned int> > soilToFertilizer;
        vector<vector<unsigned int> > fertilizerToWater;
        vector<vector<unsigned int> > waterToLight;
        vector<vector<unsigned int> > lightToTemperature;
        vector<vector<unsigned int> > temperatureToHumidity;
        vector<vector<unsigned int> > humidityToLocation;
    
        Solution(const char* filename) {
            getData(filename);
        }

        unsigned int solvePartOne() {
            set<unsigned int> locations;
            for (unsigned int seed : seeds) {
                locations.insert(getCorrespondingNumber(humidityToLocation, 
                                    getCorrespondingNumber(temperatureToHumidity, 
                                    getCorrespondingNumber(lightToTemperature, 
                                    getCorrespondingNumber(waterToLight, 
                                    getCorrespondingNumber(fertilizerToWater, 
                                    getCorrespondingNumber(soilToFertilizer, 
                                    getCorrespondingNumber(seedToSoil, seed))))))));
            }
            return *locations.begin();
        }

        unsigned int solvePartTwo(int startNum, int incrementNum) {
            set<unsigned int> locations;
            unsigned int i = startNum;
            unsigned int seedNum;
            unsigned int lowerBound;
            unsigned int upperBound;
            while (true) {
                seedNum = getCorrespondingNumberOpposite(seedToSoil,
                            getCorrespondingNumberOpposite(soilToFertilizer,
                            getCorrespondingNumberOpposite(fertilizerToWater, 
                            getCorrespondingNumberOpposite(waterToLight, 
                            getCorrespondingNumberOpposite(lightToTemperature, 
                            getCorrespondingNumberOpposite(temperatureToHumidity, 
                            getCorrespondingNumberOpposite(humidityToLocation, i)))))));
                for (int j = 0; j<seeds.size(); j += 2) {
                    lowerBound = seeds[j];
                    upperBound = lowerBound + seeds[j + 1] - 1;
                    if (seedNum < upperBound && seedNum > lowerBound) {
                        return i;
                    }
                }
                i += incrementNum; 
            }
        }

    
    private:
        unsigned int getCorrespondingNumber(vector<vector<unsigned int> > map, unsigned int num){
            for (auto range : map) {
                unsigned int lowerBound = range[1];
                unsigned int upperBound = lowerBound + range[2] - 1;
                if (num <= upperBound && num >= lowerBound) {
                    unsigned int targetLowerBound = range[0];
                    return range[0] + num - lowerBound;
                }
            }
            return num;
        }

        unsigned int getCorrespondingNumberOpposite(vector<vector<unsigned int> > map, unsigned int num) {
            for (auto range : map) {
                unsigned int lowerBound = range[0];
                unsigned int upperBound = lowerBound + range[2] - 1;
                if (num <= upperBound && num >= lowerBound) {
                    unsigned int targetLowerBound = range[1];
                    return range[1] + num - lowerBound;
                }
            }
            return num;            
        }

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            string currentMap = "seeds";
            while (getline(inputFile, line)) {
                if (currentMap == "seeds") {
                    string seed;
                    for (char i : line.substr(line.find(":") + 2)) {
                        if (isdigit(i)) {
                            seed += i;
                        }
                        else {
                            seeds.push_back(stoul(seed));
                            seed.clear();
                        }
                    }
                    seeds.push_back(stoul(seed));
                    currentMap.clear();
                }
                else {
                    if (line == "") {
                        continue;
                    }
                    else if (!isdigit(line[0])) {
                        currentMap = line.substr(0, line.find('-'));
                        continue;
                    }
                    string num;
                    vector<unsigned int> range;
                    for (char i : line) {
                        if (isdigit(i)) {
                            num += i;
                        }
                        else if (i == ' ') {
                            range.push_back(stoul(num));
                            num.clear();
                        }
                    }
                    range.push_back(stoul(num));
                    num.clear();
                    if (currentMap == "seed") {
                        seedToSoil.push_back(range);
                    }
                    else if (currentMap == "soil") {
                        soilToFertilizer.push_back(range);
                    }
                    else if (currentMap == "fertilizer") {
                        fertilizerToWater.push_back(range);
                    }
                    else if (currentMap == "water") {
                        waterToLight.push_back(range);
                    }
                    else if (currentMap == "light") {
                        lightToTemperature.push_back(range);
                    }
                    else if (currentMap == "temperature") {
                        temperatureToHumidity.push_back(range);
                    }      
                    else if (currentMap == "humidity") {
                        humidityToLocation.push_back(range);
                    }    
                    range.clear();                                                                                                              
                }
            }

        }
};

int main() {
    Solution solution = Solution("2023/05/input.txt");
    unsigned int partOne = solution.solvePartOne();

    // Starts from location 0 and increments 10K. Uses the hit location - 10K and increments 1K and so on...
    // Brute force from 0 and all the way up takes way too long. 
    unsigned int partTwo = solution.solvePartTwo(solution.solvePartTwo(solution.solvePartTwo(solution.solvePartTwo(0, 10000) - 10000, 1000) - 1000, 100) - 100, 1);
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
}