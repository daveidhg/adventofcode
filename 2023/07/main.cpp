#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
    public:
        vector<pair<string, int> > data;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int solvePartOne() {
            int ans = 0;
            sort(data.begin(), data.end(), best_hand_key(false, {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'}));
            for (int i = 0; i<data.size(); i++) {
                ans += data[i].second * (i + 1);
            }
            return ans;
        }

        int solvePartTwo() {
            int ans = 0;
            sort(data.begin(), data.end(), best_hand_key(true, {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'}));
            for (int i = 0; i<data.size(); i++) {
                ans += data[i].second * (i + 1);
            }
            return ans;
        }
    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                data.push_back({line.substr(0, line.find(' ')), stoi(line.substr(line.find(' ') + 1))});
            }
        }

        static int getHandScore(string hand, bool jokers) {
            // High card = 0, one pair = 1 etc. for sorting
            int jokerNum = 0;
            unordered_map<char, int> cardCount;
            for (char &card : hand) {
                cardCount[card]++;
            }
            if (jokers) {
                jokerNum = cardCount['J'];
                cardCount.erase(cardCount.find('J'));
                char highest;
                int highestVal = 0;
                for (const auto &pair : cardCount) {
                    if (pair.second > highestVal) {
                        highestVal = pair.second;
                        highest = pair.first;
                    }
                }
                cardCount[highest] += jokerNum;
            }
            if (cardCount.size() > 3) {
                return abs((int)cardCount.size() - 5);
            }
            if (cardCount.size() == 3) {
                int pairs = 0;
                bool three = false;
                for (const auto &pair : cardCount) {
                    if (pair.second == 2) {
                        pairs++;
                    }
                    else if (pair.second == 3) {
                        return 3;
                    }
                }
                return pairs;
            }
            if (cardCount.size() == 2) {
                for (const auto &pair : cardCount) {
                    if (pair.second == 4 || pair.second == 1) {
                        return 5;
                    }
                    else {
                        return 4;
                    }
                }
            }
            else {
                return 6;
            }
        }

        struct best_hand_key {
            bool jokers;
            vector<char> winningOrder;
            explicit best_hand_key(bool jokers_, vector<char> winningOrder_) : jokers(jokers_),  winningOrder(winningOrder_) {}
            inline bool operator() (const pair<string, int>& hand1, const pair<string, int>& hand2) {
                int val1 = getHandScore(hand1.first, jokers);
                int val2 = getHandScore(hand2.first, jokers);
                if (val1 != val2) {
                    return (val1 < val2);
                }
                else {
                    for (int i = 0; i<hand2.first.length(); i++) {
                        for (char &card : winningOrder) {
                            if (hand1.first[i] == card && hand2.first[i] != card) {
                                return false;
                            }
                            else if (hand1.first[i] != card && hand2.first[i] == card) {
                                return true;
                            }
                        }
                    }
                }
                return false;
            }
        };
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/07/input.txt");
    int partOne = solution.solvePartOne();
    int partTwo = solution.solvePartTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}