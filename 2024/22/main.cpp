#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <map>

using namespace std;

class Solution {
    public:
        vector<int> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        long long partOne() {
            long long ans = 0;
            for (int i : data) {
                for (int j = 0; j < 1999; j++) {
                    i = calculateNextSecretNumber(i);
                }
                ans += calculateNextSecretNumber(i);
            }
            return ans;
        }

        int partTwo() {
            map<tuple<int, int, int, int>, long long> sequenceValues;
            for (int num : data)  {
                vector<long long> buyer = {num % 10};
                for (int i = 0; i < 1999; i++) {
                    num = calculateNextSecretNumber(num);
                    buyer.push_back(num % 10);
                }
                set<tuple<int, int, int, int> > seen;
                for (int i = 0; i < buyer.size(); i++) {
                    int a = buyer[i];
                    int b = buyer[i + 1];
                    int c = buyer[i + 2];
                    int d = buyer[i + 3];
                    int e = buyer[i + 4];
                    tuple<int, int, int, int> sequence = {b - a, c - b, d - c, e - d};
                    if (seen.find(sequence) != seen.end()) continue;
                    seen.insert(sequence);
                    sequenceValues[sequence] += e;
                }
            }
            int max = 0;
            for (auto& [sequence, value] : sequenceValues) {
                if (value > max) {
                    max = value;
                }
            }
            return max;
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back(stoi(line));
            }
        }

        long long calculateNextSecretNumber(long long number) {
            number = (number ^ (number * 64)) % 16777216;
            number = (number ^ (number / 32)) % 16777216;
            return (number ^ (number * 2048)) % 16777216;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("2024/22/testinput.txt");
    Solution solution = Solution("2024/22/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}