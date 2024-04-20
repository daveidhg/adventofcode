#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <chrono>

using namespace std;

class Solution {
    public:
        vector<string> data;
    
        Solution(const char* filename) {
            getData(filename);
        }
    
        int solvePartOne() {
            int sum = 0;
            for (string line : data) {
                int correctNums = 0;
                vector<int> yourNumbers = getYourNumbers(line);
                unordered_set<int> winningNumbers = getWinningNumbers(line);
                for (int num : yourNumbers) {
                    if (winningNumbers.find(num) != winningNumbers.end()) {
                        correctNums++;
                    }
                }
                sum += 1 * pow(2, correctNums - 1);
                correctNums = 0;
            }
            return sum;
        }

        int solvePartTwo() {
            unordered_map<int, int> extraCardsPerGame;
            for (string line : data) {
                int correctNums = 0;
                vector<int> yourNumbers = getYourNumbers(line);
                unordered_set<int> winningNumbers = getWinningNumbers(line);
                int cardNumber = getCardNumber(line);
                for (int num : yourNumbers) {
                    if (winningNumbers.find(num) != winningNumbers.end()) {
                        correctNums++;
                    }
                }
                int amountOfCards = (extraCardsPerGame.count(cardNumber) != 0) ? extraCardsPerGame[cardNumber] + 1 : 1;
                for (int i = cardNumber + 1; i<min(correctNums + cardNumber + 1, (int)data.size() + 1); i++) {
                    extraCardsPerGame[i] += amountOfCards;
                }
            }
            int sum = 0;
            for (int i = 1; i<= data.size(); i++) {
                sum += (extraCardsPerGame.count(i) != 0) ? extraCardsPerGame[i] + 1 : 1;
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

        unordered_set<int> getWinningNumbers(string line) {
            unordered_set<int> winningNumbers;
            string num;
            line = line.substr(line.find("|") + 2);
            for (int i = 0; i<line.length(); i++) {
                if (isdigit(line[i])) {
                    num += line[i];
                }
                else if (num.length() > 0) {
                    winningNumbers.insert(stoi(num));
                    num.clear();
                }
            }
            winningNumbers.insert(stoi(num));
            return winningNumbers;
        }

        vector<int> getYourNumbers(string line) {
            vector<int> numbers;
            string num;
            for (int i = line.find(":"); i<line.find("|"); i++) {
                if(isdigit(line[i])) {
                    num += line[i];
                }
                else if (num.length() > 0) {
                    numbers.push_back(stoi(num));
                    num.clear();
                }
            }
            return numbers;
        }

        int getCardNumber(string line) {
            size_t i = line.find(":") - 1;
            string num;
            while (isdigit(line[i])) {
                num.insert(num.begin(), line[i]);
                i--;
            }
            return stoi(num);
        }

};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/04/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}