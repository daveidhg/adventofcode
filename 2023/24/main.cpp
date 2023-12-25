#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

struct Hailstone {
    long long px, py, pz;
    long long vx, vy, vz;
    __int128_t a, b, c; // long long is too small for the big numbers in the input. Overflows occur frequently

    Hailstone(vector<long long> xyz) {
        px = xyz[0];
        py = xyz[1];
        pz = xyz[2];
        vx = xyz[3];
        vy = xyz[4];
        vz = xyz[5];
        a = vy;
        b = -vx;
        c = vy * px - vx * py;
    }
};

class Solution {
    public:
        vector<Hailstone> hailstones;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne(long long min, long long max) {
            int ans = 0;
            for (int i = 0; i<hailstones.size(); i++) {
                Hailstone &hailstone1 = hailstones[i];
                for (int j = 0; j<i; j++) {
                    Hailstone &hailstone2 = hailstones[j];
                    if (parallel(hailstone1, hailstone2)) {
                        continue;
                    }
                    auto [x, y] = intersect(hailstone1, hailstone2);
                    if (min <= x && x <= max && min <= y && y <= max) {
                        if (futureCollision(hailstone1, x, y) && futureCollision(hailstone2, x, y)) {
                            ans++;
                        }
                    }
                }
            }
            return ans;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                line.replace(line.find('@') - 1, 2, ",");
                size_t splitPos = line.find(',');
                vector<long long> hailstone;
                while (splitPos != string::npos) {
                    hailstone.push_back(stoll(line.substr(0, splitPos)));
                    line = line.substr(splitPos + 2);
                    splitPos = line.find(',');
                }
                hailstone.push_back(stoll(line));
                hailstones.push_back(hailstone);
            }
        }

        bool parallel(Hailstone &a, Hailstone &b) {
            return a.a * b.b == a.b * b.a;
        }

        pair<long double, long double> intersect(Hailstone &first, Hailstone &second) {
            long double x = (first.c * second.b - second.c * first.b) / (first.a * second.b - second.a * first.b);
            long double y = (second.c * first.a - first.c * second.a) / (first.a * second.b - second.a * first.b);
            return {x, y};
        }

        bool futureCollision(Hailstone &hailstone, long double x, long double y) {
            if ((x - hailstone.px) * hailstone.vx >= 0 && (y - hailstone.py) * hailstone.vy >= 0) {
                return true;
            }
            return false;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/24/input.txt");
    int partOne = solution.partOne(200000000000000, 400000000000000); 
    cout << "Part one: " << partOne << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}