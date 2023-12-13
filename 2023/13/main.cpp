#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
using namespace std;

class Solution {
    public:
        vector<vector<string>> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int ans = 0;
            for (vector<string> note : data) {
                ans += isMirrorHorizontal(note, 0);
                ans += isMirrorVertical(note, 0);
            }
            return ans;
        }

        int solvePartTwo() {
            int ans = 0;
            for (vector<string> current : data) {
                vector<string> curr = current;
                int original = isMirrorHorizontal(curr, 0);
                original += isMirrorVertical(curr, 0);
                for (int i = 0; i<curr.size(); i++) {
                    for (int j = 0; j<curr[i].size(); j++) {
                        curr[i][j] = (curr[i][j] == '.') ? '#' : '.';
                        int val = isMirrorHorizontal(curr, original);
                        if (val <= 0 || val == original) {
                            val = isMirrorVertical(curr, original);
                        }
                        if (val > 0 && val != original) {
                            ans += val;
                            i = curr.size();   
                            break;                         
                        }
                        else {
                            curr = current;
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
            vector<string> current;
            while (getline(inputFile, line)) {
                if (line.size() <= 1) {
                    data.push_back(current);
                    current.clear();
                    continue;
                }
                current.push_back(line);
            }
            data.push_back(current);
        }

        int isMirrorVertical(vector<string> note, int original) {
            int left = 0;
            int right = note[0].length() - 1;
            vector<pair<int, int> > possibilities;
            for (int i = 1; i<note[0].length(); i++) {
                int j = i - 1;
                if (isEqualVertical(note, j, i)) {
                    possibilities.push_back({j, i});
                }
            }
            for (auto &pair : possibilities) {
                bool symmetry = true;
                int midLeft = pair.first;
                int midRight = pair.second;
                left = midLeft;
                right = midRight;
                if (midRight == original) {
                    continue;
                }
                while (left >= 0 && right < note[0].length()) {
                    if (!isEqualVertical(note, left, right)) {
                        symmetry = false;
                        break;
                    }
                    left--;
                    right++;
                }
                if (symmetry) {
                    return midRight;
                }
            }
            return 0;
        }

        bool isEqualVertical(vector<string> note, int left, int right) {
            for (int i = 0; i<note.size(); i++) {
                if (note[i][left] != note[i][right]) {
                    return false;
                }
            }
            return true;
        }

        int isMirrorHorizontal(vector<string> note, int original) {
            int top = 0;
            int bottom = 1;
            vector<pair<int, int> > possibilities;
            for (int i = 1; i<note.size(); i++) {
                int j = i - 1;
                if (isEqualHorizontal(note, j, i)) {
                    possibilities.push_back({j, i});
                }
            }
            for (auto &pair : possibilities) {
                int midTop = pair.first;
                int midBottom = pair.second;
                if (midBottom * 100 == original) {
                    continue;
                }
                top = pair.first;
                bottom = pair.second;
                bool symmetry = true;
                while (top >= 0 && bottom < note.size()) {
                    if (!isEqualHorizontal(note, top, bottom)) {
                        symmetry = false;
                        break;
                    }
                    top--;
                    bottom++;
                }
                if (symmetry) {
                    return midBottom * 100;
                }
            }
            return 0;
        }

        bool isEqualHorizontal(vector<string> note, int top, int bottom) {
            for (int i = 0; i<note[0].length(); i++) {
                if (note[top][i] != note[bottom][i]) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/13/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}