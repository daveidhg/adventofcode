#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>
#include <map>
#include <cmath>
using namespace std;

class Solution {
    public:
        vector<string> data;
        set<pair<int, int> > plots;
        map<pair<int, int>, bool> cache;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            plots.clear();
            plots.insert(getStartPos());
            for (int i = 0; i<64; i++) {
                step();
            }
            return plots.size();
        }


        long long partTwo() {
            plots.clear();
            plots.insert(getStartPos());
            int steps = 26501365;
            int size = data.size();
            int mod = steps % size;
            vector<int> cycles = {mod, mod + size, mod + size * 2};
            vector<int> seenStates;
            for (int cycle : cycles) {
                for (int i = 0; i<cycle; i++) {
                    step2();
                }
                seenStates.push_back(plots.size());
                plots.clear();
                plots.insert(getStartPos());
            }
            int m = seenStates[1] - seenStates[0];
            int n = seenStates[2] - seenStates[1];
            int a = (n - m) / 2;
            int b = m - 3 * a;
            int c = seenStates[0] - b - a;
            int ceiling = ceil((double)steps / size);
            
            return (long long)a * pow(ceiling, 2) + (long long)b * ceiling + c;
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
        pair<int, int> getStartPos() {
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == 'S') {
                        return {j, i};
                    }
                }
            }
            return {};
        }
        void step() {
            set<pair<int, int> > newPlots;
            for (auto &pair : plots) {
                int x = pair.first;
                int y = pair.second;
                if (y < data.size() - 1 && data[y + 1][x] != '#') {
                    newPlots.insert({x, y + 1});
                }
                if (y > 0 && data[y - 1][x] != '#') {
                    newPlots.insert({x, y - 1});
                }
                if (x < data[y].length() && data[y][x + 1] != '#') {
                    newPlots.insert({x + 1, y});
                }
                if (x > 0 && data[y][x - 1] != '#') {
                    newPlots.insert({x - 1, y});
                }
            }
            plots = newPlots;
        }
        void step2() {
            set<pair<int, int> > newPlots;
            int size = data.size();
            for (auto &pair : plots) {
                int newX = pair.first;
                int newY = pair.second;
                int x = (newX < 0) ? ((newX % size) + size) % size : newX % size; 
                int y = (newY < 0) ? ((newY % size) + size) % size : newY % size; 
                if (isOpen(x, y + 1)) {
                    newPlots.insert({newX, newY + 1});
                }
                if (isOpen(x, y - 1)) {
                    newPlots.insert({newX, newY - 1});
                }
                if (isOpen(x + 1, y)) {
                    newPlots.insert({newX + 1, newY});
                }
                if (isOpen(x - 1, y)) {
                    newPlots.insert({newX - 1, newY});
                }
            }
            plots = newPlots;
        }
        bool isOpen(int newX, int newY) {
            if (cache.find({newX, newY}) != cache.end()) {
                return cache[{newX, newY}];
            }

            if (newX == -1) {
                newX = data.size() - 1;
            }
            else if (newX == data.size()) {
                newX = 0;
            }
            if (newY == -1) {
                newY = data.size() - 1;
            }
            else if (newY == data.size()) {
                newY = 0;
            }
            if (data[newY][newX] != '#') {
                cache[{newX, newY}] = true;
                return true;
            }
            cache[{newX, newY}] = false;
            return false;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/21/input.txt");
    int partOne = solution.partOne(); 
    long long partTwo = solution.partTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}