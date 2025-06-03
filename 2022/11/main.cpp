#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <functional>

using namespace std;

struct Monkey {
    vector<long long> startingItems;
    function<long long(long long)> operand;
    int test;
    int ifTrue;
    int ifFalse;
    int inspections = 0;
};


class Solution {
    public:
        vector<Monkey> monkeys;
        vector<Monkey> monkeys2;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            for (int i = 0; i<20; i++) {
                for (Monkey &monkey : monkeys) {
                    doTurn(monkey);
                }
            }
            return calculateMostActiveMonkeys(monkeys);
        }

        long long partTwo() {
            for (int i = 0; i<10000; i++) {
                for (Monkey &monkey : monkeys2) {
                    doTurn(monkey, 2);
                }
            }
            return calculateMostActiveMonkeys(monkeys2);
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            int iteration = 0;
            Monkey monkey;
            while (getline(inputFile, line)) {
                switch (iteration % 7)
                {
                case 0:
                    break;

                case 1:
                    monkey.startingItems.clear();
                    line = line.substr(line.find(":") + 2); 
                    while (line.find(",") != string::npos) {
                        size_t pos = line.find(" ");
                        int num = stoi(line.substr(0, pos - 1));
                        monkey.startingItems.push_back(num);
                        line = line.substr(pos + 1);
                    }
                    monkey.startingItems.push_back(stoi(line));
                    break;

                case 2:
                    {
                        size_t pos = line.find_last_of(" ");
                        char op = line[pos - 1];
                        string last = line.substr(pos + 1);
                        if (last == "old") {
                            if (op == '+') {
                                monkey.operand = [](int old) { return old + old; };
                            } 
                            else if (op == '*') {
                                monkey.operand = [](int old) { return old * old; };
                            } 
                        } else {
                            int num = stoi(last);
                            if (op == '+') {
                                monkey.operand = [num](int old) { return old + num; };
                            } 
                            else if (op == '*') {
                                monkey.operand = [num](int old) { return old * num; };
                            } 
                        }
                    }
                    break;
                
                case 3:
                    monkey.test = stoi(line.substr(line.find_last_of(" ") + 1));
                    break;

                case 4:
                    monkey.ifTrue = stoi(line.substr(line.find_last_of(" ") + 1));
                    break;

                case 5:
                    monkey.ifFalse = stoi(line.substr(line.find_last_of(" ") + 1));
                    monkeys.push_back(monkey);
                    break;

                default:
                    break;
                }
                iteration++;
            }
            monkeys2 = monkeys;
        }

        void doTurn(Monkey &monkey, int part = 1) {
            int next;
            for (long long item : monkey.startingItems) {
                monkey.inspections++;
                item = monkey.operand(item);
                if (part == 1) {
                    item = item / 3;
                }
                if (item % monkey.test == 0) {
                    next = monkey.ifTrue;
                }
                else {
                    next = monkey.ifFalse;
                }
                if (part == 1) {
                    monkeys[next].startingItems.push_back(item);
                }
                else {
                    monkeys2[next].startingItems.push_back(item);
                }
            }
            monkey.startingItems.clear();
        }

        long long calculateMostActiveMonkeys(vector<Monkey> &monkeys) {
            int highest = 0;
            int secondHighest = 0;
            for (Monkey &monkey : monkeys) {
                if (monkey.inspections > highest) {
                    secondHighest = highest;
                    highest = monkey.inspections;

                }
                else if (monkey.inspections > secondHighest) {
                    secondHighest = monkey.inspections;
                }
            }
            return (long long)highest * secondHighest;
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

