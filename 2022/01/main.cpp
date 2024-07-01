#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;

struct Elf {
    vector<int> calories;
    int totalCalories;

    Elf(vector<int> calories) {
        this->calories = calories;
        totalCalories = 0;
        calculateTotalCalories();
    }

    void calculateTotalCalories() {
        for (int i = 0; i < calories.size(); i++) {
            totalCalories += calories[i];
        }
    }
};

class Solution {
    public:
        vector<string> data;
        vector<Elf> elves;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            vector<int> calories;
            int maxCalories = 0;
            for (string line : data) {
                if (line.length() > 0) {
                    calories.push_back(stoi(line));
                }
                else {
                    Elf elf = Elf(calories);
                    elves.push_back(elf);
                    maxCalories = max(maxCalories, elf.totalCalories);
                    calories.clear();
                }
            }
            return maxCalories;
        }

        int partTwo() {
            sort(elves.begin(), elves.end(), [](Elf a, Elf b) {
                return a.totalCalories > b.totalCalories;
            });
            return elves[0].totalCalories + elves[1].totalCalories + elves[2].totalCalories;
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(line);
            }
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2022/01/input.txt");
    int partOne = solution.partOne();
    cout << "Part One: " << partOne << endl;
    int partTwo = solution.partTwo();
    cout << "Part Two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}