#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

struct Path {
    vector<pair<int, int> > points;
    Path(string& str) {
        size_t pos = 0;
        while (pos < str.length()) {
            size_t arrowPos = str.find(" -> ", pos);
            string pointStr;
            if (arrowPos == string::npos) {
                pointStr = str.substr(pos);
                pos = str.length();
            } else {
                pointStr = str.substr(pos, arrowPos - pos);
                pos = arrowPos + 4;
            }
            size_t commaPos = pointStr.find(',');
            int x = stoi(pointStr.substr(0, commaPos));
            int y = stoi(pointStr.substr(commaPos + 1));
            points.emplace_back(x, y);
        }
    }
};

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            while (true) {
                int x = 500, y = 0;
                int height = map.size();
                while (y < height - 1) {
                    if (map[y + 1][x] == '.') {
                        y++;
                    }
                    else if (map[y + 1][x - 1] == '.') {
                        y++;
                        x--;
                    }
                    else if (map[y + 1][x + 1] == '.') {
                        y++;
                        x++;
                    }
                    else {
                        map[y][x] = 'o';
                        sandCount++;
                        break;
                    }
                }
                if (y >= height - 1) break;
            }
            return sandCount;
        }

        int partTwo() {
            for (int x = 0; x < 1000; x++) {
                map[maxY + 2][x] = '#';
            }
            while (true) {
                int x = 500, y = 0;
                while (true) {
                    if (map[y + 1][x] == '.') {
                        y++;
                    }
                    else if (x > 0 && map[y + 1][x - 1] == '.') {
                        y++;
                        x--;
                    }
                    else if (x < 1000 - 1 && map[y + 1][x + 1] == '.') {
                        y++;
                        x++;
                    }
                    else {
                        if (y == 0 && x == 500) {
                            return sandCount + 1;
                        }
                        map[y][x] = 'o';
                        sandCount++;
                        break;
                    }
                }
            }
            return sandCount;
        }

    
    private:
    int maxY = 0;
        vector<Path> data;
        int sandCount = 0;
        vector<string> map;
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.emplace_back(line);
                for (const auto& point : data.back().points) {
                    maxY = max(maxY, point.second);
                }
            }
            map = createMap();
        }

        vector<string> createMap() {
            int height = maxY + 3;
            int width = 1000;
            vector<string> map;
            map.resize(height, string(width, '.'));
            for (const auto& path : data) {
                for (size_t i = 0; i < path.points.size() - 1; i++) {
                    int x1 = path.points[i].first;
                    int y1 = path.points[i].second;
                    int x2 = path.points[i + 1].first;
                    int y2 = path.points[i + 1].second;
                    if (x1 == x2) {
                        int startY = min(y1, y2);
                        int endY = max(y1, y2);
                        for (int y = startY; y <= endY; y++) {
                            map[y][x1] = '#';
                        }   
                    }
                    else if (y1 == y2) {
                        int startX = min(x1, x2);
                        int endX = max(x1, x2);
                        for (int x = startX; x <= endX; x++) {
                            map[y1][x] = '#';
                        }
                    }
                }
            }
            return map;
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