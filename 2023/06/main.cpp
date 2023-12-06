#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Solution {
    public:
        vector<vector<int> > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int sum = 0;
            for (int i = 0; i<data[0].size(); i++) {
                int time = data[0][i];
                int distance = data[1][i];
                int j = 0;
                bool leftEdgeNotFound = true;
                while (leftEdgeNotFound) {
                    if ((j * (time - j)) > distance) {
                        leftEdgeNotFound = false;
                    }
                    else {
                        j++;
                    }
                }
                sum = (sum != 0) ? sum * (time - 2*j + 1) : time - 2*j + 1;
            }
            return sum;
        }

        int solvePartTwo() {
            string timeString;
            string distanceString;
            for (int i = 0; i<data[0].size(); i++) {
                timeString += to_string(data[0][i]);
                distanceString += to_string(data[1][i]);
            }
            int time = stoi(timeString);
            long long distance = stoll(distanceString);
            long long currentDistance;
            for (int i = 0; i<time; i++) {
                 currentDistance = (long long) i * (time - i);
                if (currentDistance > distance) {
                    return time - 2*i + 1;
                }
            }
            return 0;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                vector<int> nums;
                string num;
                for (char i : line) {
                    if (isdigit(i)) {
                        num += i;
                    }
                    else if (num.length() > 0) {
                        nums.push_back(stoi(num));
                        num.clear();
                    }
                }
                nums.push_back(stoi(num));
                num.clear();
                data.push_back(nums);
            }
        }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/06/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}