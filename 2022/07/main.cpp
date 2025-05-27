#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

struct file {
    string name;
    int size;
};

struct directory {
    string name;
    directory* outerDir;
    int totalSize = 0;
    map<string, directory> subdirs;
    vector<file> files;
};


class Solution {
    public:
        vector<string> terminalLines;
        directory root;
        int targetSpace = 30000000;
        int currentSpace;
    
        Solution(const char* filename) {
            getData(filename);
            root.name = "/";
        }

        int partOne() {
            return getAllSizesOverHundredThousand(root);
        }

        int partTwo() {
            return getSmallestCompatibleDir(root, root.totalSize);
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            directory* currentDir = &root;
            while (getline(inputFile, line)) {
                if (line[0] == '$') {
                    // Command
                    if (line.substr(2, 2) == "cd") {
                        string dirName = line.substr(5);
                        if (dirName == "..") {
                            currentDir = currentDir->outerDir;
                        }
                        else if (dirName == "/") {
                            currentDir = &root;
                        }
                        else {
                            currentDir->subdirs[dirName].outerDir = currentDir;
                            currentDir = &currentDir->subdirs[dirName];
                            currentDir->name = dirName;
                        }
                    }
                    else if (line.substr(2, 2) == "ls") {
                        // Stay in the same dir, files and subdirs will be seen and added in the next lines
                        continue;
                    }
                }
                else {
                    if (line.substr(0, 3) == "dir") {
                        // Skip, exploration will be done when entering the dir
                    }
                    else {
                        file currentFile;
                        currentFile.name = line.substr(line.find(" ") + 1);
                        currentFile.size = stoi(line.substr(0, line.find(" ")));
                        currentDir->files.push_back(currentFile);
                    }
                }
            }
            getDirectorySize(root);
            currentSpace = 70000000 - root.totalSize;
        }

        int getDirectorySize(directory &dir) {
            for (file &f : dir.files) {
                dir.totalSize += f.size;
            }
            if (dir.subdirs.size() != 0) {
                for (auto &pair : dir.subdirs) {
                    dir.totalSize += getDirectorySize(pair.second);
                }
            }
            return dir.totalSize;
        }

        int getAllSizesOverHundredThousand(directory &dir) {
            int total = 0;
            if (dir.totalSize <= 100000) {
                total += dir.totalSize;
            }
            for (auto &pair : dir.subdirs) {
                total += getAllSizesOverHundredThousand(pair.second);
            }
            return total;
        }

        int getSmallestCompatibleDir(directory& dir, int currentBest) {
            if (dir.totalSize + currentSpace < targetSpace) {
                return currentBest;
            }
            if (dir.totalSize < currentBest) {
                currentBest = dir.totalSize;
            }
            for (auto &pair : dir.subdirs) {
                currentBest = getSmallestCompatibleDir(pair.second, currentBest);
            }
            return currentBest;
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