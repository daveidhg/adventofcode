#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Solution {
    public:
        vector<pair<pair<int, int>, pair<int, int> > > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int count = 0;
            for (int i = 0; i<data.size(); i++) {
                if (isOverlapping(data[i].first, data[i].second)) {
                    count++;
                }
            }
            return count;
        }

        int partTwo() {
            int count = 0; 
            for (int i = 0; i<data.size(); i++) {
                if (hasSomeOverlap(data[i].first, data[i].second)) {
                    count++;
                }
            }
            return count;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                size_t firstPos = line.find_first_of('-');
                size_t secondPos = line.find_first_of(',', firstPos);
                size_t thirdPos = line.find_first_of('-', secondPos);
                data.push_back({{stoi(line.substr(0, firstPos)), stoi(line.substr(firstPos + 1, secondPos - firstPos - 1))}, {
                    stoi(line.substr(secondPos + 1, thirdPos - secondPos - 1)), stoi(line.substr(thirdPos + 1))}});
            }
        }

        bool isOverlapping(pair<int, int> a, pair<int, int> b) {
            return (a.first <= b.first && b.second <= a.second) || (a.first >= b.first && b.second >= a.second);
        }

        bool hasSomeOverlap(pair<int, int> a, pair<int, int> b) {
            return a.first <= b.second && b.first <= a.second;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2022/04/input.txt");
    int partOne = solution.partOne();
    cout << "Part One: " << partOne << endl;
    int partTwo = solution.partTwo();
    cout << "Part Two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}