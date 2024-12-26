#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <stack>

using namespace std;

class Solution {
    public:
    
        Solution(const char* filename) {
            getData(filename);
        }

        string partOne() {
            string ans;
            for (auto& stack : stacks) {
                ans += stack.top();
            }
            return ans;
        }

        string partTwo() {
            moveCrates2();
            string ans;
            for (auto& stack : stacksCopy) {
                ans += stack.top();
            }
            return ans;
        }

    
    private:
        vector<stack<char> > stacks;
        vector<stack<char> > stacksCopy;
        vector<tuple<int, int, int> > moves;

        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            vector<string> tempStack;
            bool foundStack = false;
            while (getline(inputFile, line)) {
                if (line == "") {
                    for (int i = 1; i < tempStack[0].size(); i += 4) {
                        stack<char> currentStack;
                        for (int j = tempStack.size() - 2; j >= 0; j--) {
                            if (tempStack[j][i] == ' ') break;
                            currentStack.push(tempStack[j][i]);
                        }
                        stacks.emplace_back(currentStack);
                    }
                    foundStack = true;
                    stacksCopy = stacks;
                    continue;
                }
                if (!foundStack) {
                    tempStack.emplace_back(line);
                }

                else {
                    line = line.substr(line.find(' ') + 1);
                    int num1 = stoi(line.substr(0, line.find(' ')));
                    line = line.substr(line.find("m "));
                    int num2 = stoi(line.substr(line.find(' ')));
                    int num3 = stoi(line.substr(line.find_last_of(' ')));
                    moves.emplace_back(num1, num2, num3);
                }

            }
        }

        void moveCrate(int amount, int fromStack, int toStack) {
            for (int i = 0; i < amount; i++) {
                stacks[toStack - 1].push(stacks[fromStack - 1].top());
                stacks[fromStack - 1].pop();
            }
        }

        void moveCrates() {
            for (auto& [amount, fromStack, toStack] : moves) {
                moveCrate(amount, fromStack, toStack);
            }
        }

        void moveCrates2() {
            for (auto& [amount, fromStack, toStack] : moves) {
                moveCrate2(amount, fromStack, toStack);
            }
        }

        void moveCrate2(int amount, int fromStack, int toStack) {
            stack<char> tempStack;
            for (int i = 0; i < amount; i++) {
                tempStack.push(stacksCopy[fromStack - 1].top());
                stacksCopy[fromStack - 1].pop();
            }
            while (!tempStack.empty()) {
                stacksCopy[toStack - 1].push(tempStack.top());
                tempStack.pop();
            }
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