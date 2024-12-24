#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    public:
    
        Solution(const char* filename) {
            getData(filename);
        }

        long long partOne() {
            long long ans = 0;
            doInstructions();
            for (int i = 0; i < wires.size(); i++) {
                string name = "z" + to_string(i);
                if (name.size() == 2) {
                    name = "z0" + to_string(i);
                }
                if (wires.find(name) == wires.end()) {
                    break;
                }
                ans |= (long long)wires[name] << i;
            }
            return ans;
        }

        int partTwo() {
            // Part two solved manually :(
            return 0;
        }

    
    private:
        map<string, int> wires;
        vector<tuple<string, string, string, string> > instructions;

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            bool wire = true;
            while (getline(inputFile, line)) {
                if (line == "") {
                    wire = false;
                    continue;
                }
                if (wire) {
                    wires[line.substr(0, line.find(":"))] = line[line.size() - 1] - '0';
                }
                else {
                    string op1, op2, op3, op4;
                    op1 = line.substr(0, line.find(" "));
                    line = line.substr(line.find(" ") + 1);
                    op2 = line.substr(0, line.find(" "));
                    line = line.substr(line.find(" ") + 1);
                    op3 = line.substr(0, line.find(" "));
                    line = line.substr(line.find(" ") + 1);
                    op4 = line.substr(3);
                    instructions.push_back({op1, op2, op3, op4});
                    if (wires.find(op4) == wires.end())
                    wires[op4] = -1;
                }
            }
        }

        void doInstructions() {
            while (!isCompleted()) {
                for (auto& [a, ins, b, c] : instructions) {
                    if (wires[a] == -1 || wires[b] == -1) {
                        continue;
                    }
                    if (wires[c] != -1) {
                        continue;
                    }
                    if (ins == "AND") {
                        wires[c] = wires[a] & wires[b];
                    }
                    else if (ins == "OR") {
                        wires[c] = wires[a] | wires[b];
                    }
                    else if (ins == "XOR") {
                        wires[c] = wires[a] ^ wires[b];
                    }
                }
            }
        }

        bool isCompleted() {
            for (auto& [key, value] : wires) {
                if (value == -1) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("2024/24/testinput.txt");
    Solution solution = Solution("2024/24/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;

    cout << "Part One: " << solution.partOne() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}