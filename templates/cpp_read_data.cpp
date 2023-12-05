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
    Solution solution = Solution("year/day/input.txt");

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}