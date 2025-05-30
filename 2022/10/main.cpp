#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

class Solution {
    public:
        vector<pair<string, int> > commands;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return simulateCycles(cycles);
        }

        int partTwo() {
            return 0;
        }

    
    private:
        vector<int> cycles = {20, 60, 100, 140, 180, 220};    

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            int value;
            while (getline(inputFile, line)) {
                string command = line.substr(0, 4);
                if (command == "addx") 
                value = stoi(line.substr(4));
                commands.emplace_back(command, value);
            }
        }

        int simulateCycles(vector<int> &cycles) {
            int commandPointer = -1;
            int cycleCalculationPointer = 0;
            int cyclesLeft = 0;
            int valueToBeAdded = 0;
            int x = 1;
            int sum = 0;
            int vertical;
            int horizontal;
            char screen[6][40];
            char pixel;
            for (int i = 0; i<240; i++) {
                vertical = i / 40;
                horizontal = i % 40;
                if (abs(x - horizontal) < 2) {
                    pixel = '#';
                }
                else {
                    pixel = '.';
                }
                screen[vertical][horizontal] = pixel;
                if (cycleCalculationPointer < cycles.size() && cycles[cycleCalculationPointer] == i + 1) {
                    int strength = x * cycles[cycleCalculationPointer];
                    sum += strength;
                    cycleCalculationPointer++;
                }
                if (cyclesLeft == 0) {
                    commandPointer++;
                    auto const &[command, value] = commands[commandPointer];
                    if (command == "noop") {
                        continue;
                    } else  {
                        valueToBeAdded = value;
                        cyclesLeft = 1;
                    } 
                }
                else {
                    cyclesLeft--;
                    x += valueToBeAdded;
                }

            }
            for (auto &line : screen) {
                cout << endl;
                for (char &c : line) {
                    cout << c;
                }
            }

            return sum;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("testinput.txt");
    Solution solution = Solution("input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}