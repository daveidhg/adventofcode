#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (string step : data) {
                ans += hashWord(step);
            }
            return ans;
        }

        int partTwo() {
            unordered_map<int, vector<string> > boxes;
            for (string step : data) {
                size_t find = step.find('-');
                if (find != string::npos) {
                    string label = step.substr(0, find);
                    int box = hashWord(label);
                    for (int i = 0; i<boxes[box].size(); i++) {
                        if (boxes[box][i].substr(0, boxes[box][i].find(' ')) == label) {
                            boxes[box].erase(boxes[box].begin()+i);
                        }
                    }
                }
                else {
                    find = step.find('=');
                    string label = step.substr(0, find);
                    int box = hashWord(label);
                    bool found = false;
                    for (int i = 0; i<boxes[box].size(); i++) {
                        if (boxes[box][i].substr(0, boxes[box][i].find(' ')) == label) {
                            boxes[box][i] = step.substr(0, find) + ' ' + step.substr(find + 1);
                            found = true;
                        }
                    }
                    if (!found) {
                        boxes[box].push_back(step.substr(0, find) + ' ' + step.substr(find + 1));
                    }
                }
            }
            int ans = 0;
            for (auto &pair : boxes) {
                for (int i = 0; i<pair.second.size(); i++) {
                    ans += (pair.first + 1) * (i + 1) * (pair.second[i][pair.second[i].length() - 1] - '0');
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
                size_t idx = line.find(',');
                while (idx != string::npos) {
                    data.push_back(line.substr(0, idx));
                    line = line.substr(idx + 1);
                    idx = line.find(',');
                }
                data.push_back(line);
            }
        }

        int hashChar(char c, int sum) {
            sum += c;
            sum *= 17;
            sum %= 256;
            return sum;
        }

        int hashWord(string word) {
            int sum = 0;
            for (char c : word) {
                sum = hashChar(c, sum);
            }
            return sum;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/15/input.txt");
    int partOne = solution.partOne();
    int partTwo = solution.partTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}