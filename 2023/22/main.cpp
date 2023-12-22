#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
    public:
        vector<vector<int> > bricks;
        unordered_map<int, vector<int> > isSupporting;
        unordered_map<int, unordered_set<int> > isBeingSupportedBy;
    
        Solution(const char* filename) {
            getData(filename);
            sort(bricks.begin(), bricks.end(), [](const vector<int> &a, const vector<int> &b) {
                return a[2] < b[2];
            });
        }

        int partOne() {
            simulateFalling();
            for (int i = 0; i<bricks.size(); i++) {
                vector<int> &brick = bricks[i];
                for (int j = 0; j<i; j++) {
                    vector<int> &brick2 = bricks[j];
                    if (xyIntersect(brick, brick2) && brick[2] == brick2[5] + 1) {
                        isSupporting[j].push_back(i);
                        isBeingSupportedBy[i].insert(j);
                    }
                }
            }

            int ans = 0;
            for (int i = 0; i<bricks.size(); i++) {
                if (canBeDisingrated(i, isSupporting, isBeingSupportedBy)) {
                    ans++;
                }
            }
            return ans;
        }


        int partTwo() {
            int ans = 0;
            for (int i = 0; i<bricks.size(); i++) {
                unordered_set<int> falling;
                queue<int> q;
                for (int j : isSupporting[i]) {
                    if (isBeingSupportedBy[j].size() == 1) {
                        q.push(j);
                        falling.insert(j);
                    }
                }
                falling.insert(i);
                while (!q.empty()) {
                    int j = q.front();
                    q.pop();
                    for (int m : isSupporting[j]) {
                        if (falling.find(m) == falling.end() && supportsFalling(falling, isBeingSupportedBy[m])) {
                            q.push(m);
                            falling.insert(m);
                        }
                    }
                }
                ans += falling.size() - 1;
            }
            return ans;
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<int> brick;
            while (getline(inputFile, line)) {
                line.replace(line.find('~'), 1, ",");
                size_t splitPos = line.find(',');
                while (splitPos != string::npos) {
                    brick.push_back(stoi(line.substr(0, splitPos)));
                    line = line.substr(splitPos + 1);
                    splitPos = line.find(',');
                }
                brick.push_back(stoi(line));
                bricks.push_back(brick);
                brick.clear();
            }
        }

        bool xyIntersect(vector<int> &a, vector<int> &b) {
            return max(a[0], b[0]) <= min(a[3], b[3]) && max(a[1], b[1]) <= min(a[4], b[4]);
        }

        void simulateFalling() {
            for (int i = 0; i<bricks.size(); i++) {
                vector<int> &brick = bricks[i];
                int max_z = 1;
                for (int j = 0; j<i; j++) {
                    vector<int> &brick2 = bricks[j];
                    if (xyIntersect(brick, brick2)) {
                        max_z = max(max_z, brick2[5] + 1);
                    }
                }
                brick[5] = max_z + brick[5] - brick[2];
                brick[2] = max_z; 
            }
            sort(bricks.begin(), bricks.end(), [](const vector<int> &a, const vector<int> &b) {
                return a[2] < b[2];
            });
        }

        bool canBeDisingrated(int i, unordered_map<int, vector<int> > &isSupporting, unordered_map<int, unordered_set<int> > &isBeingSupportedBy) {
            if (isSupporting.find(i) != isSupporting.end()) {
                for (int j : isSupporting[i]) {
                    if (isBeingSupportedBy[j].size() < 2) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool supportsFalling(unordered_set<int> &falling, unordered_set<int> isBeingSupportedBy) {
            for (int i : isBeingSupportedBy) {
                if (falling.find(i) == falling.end()) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/22/input.txt");
    int partOne = solution.partOne();
    cout << "Part one: " << partOne << endl;
    int partTwo = solution.partTwo(); 
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}