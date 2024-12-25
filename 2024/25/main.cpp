#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (auto& key : keys) {
                for (auto& lock : locks) {
                    if (match(lock, key)) ans++;
                }
            }
            return ans;
        }

    
    private:
        vector<vector<int> > keys;
        vector<vector<int> > locks;


        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<string> schematic;
            while (getline(inputFile, line)) {
                schematic.clear();
                schematic.emplace_back(line);
                for (int i = 0; i < 6; i++) {
                    getline(inputFile, line);
                    schematic.emplace_back(line);
                }
                translateSchematic(schematic);
                getline(inputFile, line); // empty line
            }
        }

        void translateSchematic(vector<string>& schematic) {
            bool key = false;
            if (schematic[0] == "#####") {
                key = true;
            }
            vector<int> translated;
            for (int i = 0; i < 5; i++) {
                for (int j = 1; j < 7; j++) {
                    if (key && schematic[j][i] == '.') {
                        translated.emplace_back(j - 1);
                        break;
                    } 
                    else if (!key && schematic[j][i] == '#') {
                        translated.emplace_back(6 - j);
                        break;
                    }
                }
            }
            if (key) {
                keys.emplace_back(translated);
            }
            else {
                locks.emplace_back(translated);
            }
        }

        bool match(vector<int>& lock, vector<int>& key) {
            for (int i = 0; i < 5; i++) {
                if (key[i] + lock[i] > 5) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("testinput.txt");
    Solution solution = Solution("input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;

    cout << "Part One: " << solution.partOne() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}