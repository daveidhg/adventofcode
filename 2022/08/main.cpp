#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>

using namespace std;

class Solution {
    public:
        vector<vector<int> > trees;
        set<pair<int, int> > seen;
        int size;
        vector<pair<int, int> > dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            addSeenTrees();
            return seen.size();
        }

        int partTwo() {
            int ans = 0;
            for (int i = 0; i<size; i++) {
                for (int j = 0; j<size; j++) {
                    ans = max(ans, getScenicScore(i, j));
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
                vector<int> temp;
                for (char &c : line) {
                    temp.emplace_back(c - '0');
                }
                trees.emplace_back(temp);
                temp.clear();
            }
            size = trees.size(); 
        }

        void addSeenTrees() {
            for (int i = 0; i<size; i++) {
                int leftMax = -1;
                int rightMax = -1;
                int topMax = -1;
                int bottomMax = -1;
                for (int j = 0; j<size; j++) {
                    if (trees[i][j] > leftMax) {
                        seen.emplace(i, j);
                        leftMax = trees[i][j];
                    }
                    if (trees[i][size - 1 - j] > rightMax) {
                        seen.emplace(i, size - 1 - j);
                        rightMax = trees[i][size - 1 - j];
                    }
                    if (trees[j][i] > topMax) {
                        seen.emplace(j, i);
                        topMax = trees[j][i];
                    }
                    if (trees[size - 1 - j][i] > bottomMax) {
                        seen.emplace(size - 1 - j, i);
                        bottomMax = trees[size - 1 - j][i];
                    }
                    if (leftMax == 9 && rightMax == 9 && topMax == 9 && bottomMax == 9) {
                        break;
                    }
                }
            }
        }

        int getScenicScore(int y, int x) {
            int height = trees[y][x];
            int score = 1;
            for (auto[dx, dy] : dirs) {
                int dirScore = 0;
                for (int i = 1; i<size; i++) {
                    if (y+i*dy >= size || y+i*dy < 0 || x+i*dx >= size || x+i*dx < 0) {
                        break;
                    }
                    if (trees[y+i*dy][x+i*dx] >= height) {
                        dirScore++;
                        break;
                    }
                    dirScore++;
                }
                score *= dirScore;
            }
            return score;
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