#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_set>
#include <array>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

class Solution {
public:
    vector<pair<char, int>> data;
    unordered_set<pair<int, int>, PairHash> visited;
    array<pair<int, int>, 4> dirs = {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

    Solution(const char* filename) {
        getData(filename);
    }

    int partOne() {
        visited.clear();
        simulateRope(2);
        return visited.size();
    }

    int partTwo() {
        visited.clear();
        simulateRope(10);
        return visited.size();
    }

private:
    inline int dirIndex(char dir) const {
        switch (dir) {
            case 'R': return 0;
            case 'L': return 1;
            case 'U': return 2;
            case 'D': return 3;
        }
        return 0;
    }

    void getData(const char* filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            data.emplace_back(line[0], stoi(line.data() + 2));
        }
    }

    void simulateRope(int len) {
        vector<pair<int, int>> rope(len, {0, 0});
        for (const auto& [dir, amount] : data) {
            auto [dx, dy] = dirs[dirIndex(dir)];
            for (int i = 0; i < amount; ++i) {
                rope[0].first += dx;
                rope[0].second += dy;
                for (int j = 1; j < len; ++j) {
                    if (abs(rope[j].first - rope[j-1].first) > 1 || abs(rope[j].second - rope[j-1].second) > 1) {
                        rope[j].first += (rope[j-1].first > rope[j].first) - (rope[j-1].first < rope[j].first);
                        rope[j].second += (rope[j-1].second > rope[j].second) - (rope[j-1].second < rope[j].second);
                    }
                }
                visited.emplace(rope[len - 1]);
            }
        }
    }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution("testinput.txt");
    Solution solution("input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}