#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

class Solution {
    public:
        string data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return findMarkerPosition(data, 4);
        }

        int partTwo() {
            return findMarkerPosition(data, 14);
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            getline(inputFile, data);
        }

        bool isDistinct(string chars, int size) {
            for (int i = 0; i < size; i++) {
                for (int j = i + 1; j < size; j++) {
                    if (chars[i] == chars[j]) return false;
                }
            }
            return true;
        }

        int findMarkerPosition(string& buffer, int size) {
            for (int i = size; i < buffer.size(); i++) {
                if (isDistinct(buffer.substr(i - size, i), size)) return i;
            }
            return -1;
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