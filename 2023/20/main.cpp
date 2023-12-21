#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <set>
#include <numeric>
using std::string, std::vector, std::queue, std::unordered_map, std::pair, std::ifstream, std::cout, std::endl, std::set, std::lcm;

class Module {
    public:
        char type;
        string name;
        bool state;
        vector<string> destinations;
        unordered_map<string, bool> memory;

        Module() {
            state = false;
        }
        
        Module(char type_, string name_, vector<string> destinations_) {
            type = type_;
            name = name_;
            state = false;
            destinations = destinations_;
        }

        vector<string> signalInput(bool signal, string sender) {
            if (type == '&') {
                memory[sender] = signal;
                for (auto &pair : memory) {
                    if (!pair.second) {
                        state = true;
                        return destinations;
                    }
                }
                state = false;
                return destinations;
            }
            else if (type == '%') {
                if (signal) {
                    return {};
                }
                else {
                    state = !state;
                    return destinations;
                }
            }
            return destinations;
        }
};

class Solution {
    public:
        unordered_map<string, Module> modules;
    
        Solution(const char* filename) {
            getData(filename);
        }

        long long partOne() {
            long long lowSignals = 0;
            long long highSignals = 0;
            queue<pair<pair<string, string>, bool> > signalQueue;
            for (int i = 0; i<1000; i++) {
                signalQueue.push({{"button", "broadcaster"}, false});
                while (!signalQueue.empty()) {
                    string &sender = signalQueue.front().first.first;
                    string &reciever = signalQueue.front().first.second;
                    bool &signal = signalQueue.front().second;
                    if (signal) {
                        highSignals++;
                    }
                    else {
                        lowSignals++;
                    }
                    auto &currentModule = modules[reciever];
                    auto destinations = currentModule.signalInput(signal, sender);
                    for (string destination : destinations) {
                        signalQueue.push({{reciever, destination}, currentModule.state});
                    }
                    signalQueue.pop();
                }
            }
            return lowSignals * highSignals;
        }

        long long partTwo() {
            queue<pair<pair<string, string>, bool> > signalQueue;
            string outputModule;
            for (auto &pair : modules) {
                for (string destination : pair.second.destinations) {
                    if (destination == "rx") {
                        outputModule = pair.first;
                    }
                }
            }

            unordered_map<string, int> cycleLens;
            for (auto &pair : modules) {
                for (string destination : pair.second.destinations) {
                    if (destination == outputModule) {
                        cycleLens[pair.first] = 0;
                    }
                }
            }   
            int presses = 0;
            while (1) {
                presses++;
                signalQueue.push({{"button", "broadcaster"}, false});
                while (!signalQueue.empty()) {
                    string &sender = signalQueue.front().first.first;
                    string &reciever = signalQueue.front().first.second;
                    bool &signal = signalQueue.front().second;
                    if (reciever == outputModule && signal) {
                        cycleLens[sender] = presses;
                        if (all(cycleLens, 1)) {
                            vector<int> products;
                            for (auto &pair : cycleLens) {
                                products.push_back(pair.second);
                            }
                            return vector_lcm(products);
                        }
                    } 
                    auto &currentModule = modules[reciever];
                    auto destinations = currentModule.signalInput(signal, sender);
                    for (string destination : destinations) {
                        signalQueue.push({{reciever, destination}, currentModule.state});
                    }
                    signalQueue.pop();
                }
            }  
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                string moduleName = line.substr(0, line.find(' '));
                string destinations = line.substr(line.find('>') + 2);
                vector<string> destinationList;
                size_t splitPos = destinations.find(',');
                while (splitPos != string::npos) {
                    destinationList.push_back(destinations.substr(0, splitPos));
                    destinations = destinations.substr(splitPos + 2);
                    splitPos = destinations.find(',');
                }
                destinationList.push_back(destinations);
                char type;
                if (moduleName[0] != 'b') {
                    type = moduleName[0];
                    moduleName = moduleName.substr(1);
                }
                else {
                    type = '\0';
                }
                modules[moduleName] = Module(type, moduleName, destinationList);
            }
            for (auto &pair : modules) {
                Module module = pair.second;
                for (string destination : module.destinations) {
                    modules[destination].memory[pair.first] = false;
                }
            }
        }
        bool all(unordered_map<string, int> &map, int num) {
            for (auto &pair : map) {
                if (pair.second < num) {
                    return false;
                }
            }
            return true;
        }
        long long vector_lcm(vector<int> nums) {
            long long num = nums[0];
            for (int i = 1; i<nums.size(); i++) {
                num = lcm(num, nums[i]);
            }
            return num;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/20/input.txt");
    long long partOne = solution.partOne();
    cout << "Part one: " << partOne << endl;
    solution = Solution("2023/20/input.txt");
    long long partTwo = solution.partTwo();
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}