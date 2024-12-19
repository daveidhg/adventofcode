#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return 0;
        }

        int partTwo() {
            return 0;
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
    Solution testSolution = Solution("year/day/testinput.txt");
    Solution solution = Solution("year/day/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}