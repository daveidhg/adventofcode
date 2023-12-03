#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int sum = 0;
            int numStartIndex;
            bool lastWasSymbol = false;
            bool numAlreadyAdded = false;
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (isdigit(data[i][j])) {
                        numAlreadyAdded = false;
                        numStartIndex = j;
                        while (isdigit(data[i][j])) {
                            if (j < data[i].length() - 1)
                                j++;
                            else
                                break;
                        }

                        if (lastWasSymbol) {
                            sum += stoi(data[i].substr(numStartIndex, j - numStartIndex + 1));
                            numAlreadyAdded = true;
                        }

                        else if (data[i][j] != '.' && !isdigit(data[i][j])) {
                            sum += stoi(data[i].substr(numStartIndex, j - numStartIndex + 1));
                            numAlreadyAdded = true;
                            lastWasSymbol = true;
                        }

                        else {
                            lastWasSymbol = false;
                        }

                        if (i != 0 && !numAlreadyAdded) {
                            for (int index = ((numStartIndex - 1) >= 0) ? numStartIndex - 1 : 0; index<=j; index++) {
                                if (data[i - 1][index] != '.' && !isdigit(data[i - 1][index])) {
                                    sum += stoi(data[i].substr(numStartIndex, j - numStartIndex + 1));
                                    numAlreadyAdded = true;
                                    break;
                                }
                            }
                        }
                        if (i < data.size() - 1 && !numAlreadyAdded) {
                            for (int index = ((numStartIndex - 1) >= 0) ? numStartIndex - 1 : 0; index<=j; index++) {
                                if (data[i + 1][index] != '.' && !isdigit(data[i + 1][index])) {
                                    sum += stoi(data[i].substr(numStartIndex, j - numStartIndex + 1));
                                    numAlreadyAdded = true;
                                    break;
                                }
                            }
                        }
                    }
                    else if (data[i][j] != '.' && !isdigit(data[i][j])) {
                        lastWasSymbol = true;
                    }
                    else {
                        lastWasSymbol = false;
                    }
                }
            }
            return sum;
        }

        int solvePartTwo() {
            int sum = 0;
            for (int i = 0; i<data.size(); i++) {
                for (int j = 0; j<data[i].length(); j++) {
                    if (data[i][j] == '*') {
                        int num1 = 0;
                        int num2 = 0;
                        int startIndex = j - 1;
                        int endIndex = j + 1;
                        if (i != 0) {
                            for (int index = startIndex; index <= endIndex; index++) {
                                if (isdigit(data[i - 1][index])) {
                                    int numStartIndex = index;
                                    int numEndIndex = index;
                                    while (isdigit(data[i - 1][numStartIndex])) {
                                        numStartIndex--;
                                        if (numStartIndex < 0) {
                                            break;
                                        }
                                    }
                                    numStartIndex++;
                                    while (isdigit(data[i - 1][numEndIndex])) {
                                        numEndIndex++;
                                    }
                                    if (num1 == 0) {
                                        num1 = stoi(data[i - 1].substr(numStartIndex, numEndIndex - numStartIndex));
                                    }
                                    else {
                                        num2 = stoi(data[i - 1].substr(numStartIndex, numEndIndex - numStartIndex));
                                    }
                                }
                            }
                        }
                        if (isdigit(data[i][startIndex])) {
                            int numStartIndex = startIndex;
                            int numEndIndex = startIndex + 1;
                            while (isdigit(data[i][numStartIndex])) {
                                numStartIndex--;
                                if (numStartIndex < 0) {
                                    break;
                                }
                            }
                            numStartIndex++;
                            if (num1 == 0) {
                            num1 = stoi(data[i].substr(numStartIndex, numEndIndex - numStartIndex));
                            }
                            else {
                                num2 = stoi(data[i].substr(numStartIndex, numEndIndex - numStartIndex));
                            }
                        }
                        if (isdigit(data[i][endIndex])) {
                            int numStartIndex = endIndex;
                            int numEndIndex = endIndex;
                            while (isdigit(data[i][numEndIndex])) {
                                numEndIndex++;
                            }
                            if (num1 == 0) {
                            num1 = stoi(data[i].substr(numStartIndex, numEndIndex - numStartIndex));
                            }
                            else {
                                num2 = stoi(data[i].substr(numStartIndex, numEndIndex - numStartIndex));
                            }
                        }
                        if (i != 0) {
                            for (int index = startIndex; index <= endIndex; index++) {
                                if (isdigit(data[i + 1][index])) {
                                    int numStartIndex = index;
                                    int numEndIndex = index;
                                    while (isdigit(data[i + 1][numStartIndex])) {
                                        numStartIndex--;
                                        if (numStartIndex < 0) {
                                            break;
                                        }
                                    }
                                    numStartIndex++;
                                    while (isdigit(data[i + 1][numEndIndex])) {
                                        numEndIndex++;
                                    }
                                    index = numEndIndex;
                                    if (num1 == 0) {
                                        num1 = stoi(data[i + 1].substr(numStartIndex, numEndIndex - numStartIndex));
                                    }
                                    else {
                                        num2 = stoi(data[i + 1].substr(numStartIndex, numEndIndex - numStartIndex));
                                    }
                                }
                            }
                        }
                        if (num1 != num2)
                            sum += num1 * num2;
                    }
                }
            }
            return sum;
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
};

int main() {
    Solution solution = Solution("2023/03/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
}