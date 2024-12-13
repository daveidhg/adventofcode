#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

struct Machine {
    public: 
        std::pair<int, int> a;
        std::pair<int, int> b;
        std::pair<long long, long long> prizePos;

        Machine(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> prizePos) {
            this->a = a;
            this->b = b;
            this->prizePos = prizePos;
        }
};

class Solution {
    public:
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            return runAllMachines();
        }

        long long partTwo() {
            return runAllMachines(true);
        }

    
    private:
        std::vector<Machine> machines;

        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            std::pair<int, int> a;
            std::pair<int, int> b;
            std::pair<int, int> prizePos;
            while (getline(inputFile, line)) {
                if (line == "") {
                    continue;
                }
                if (line.find('P') != std::string::npos) {
                    line = line.substr(line.find('=') + 1);
                    int x = std::stoi(line.substr(0, line.find(',')));
                    int y = std::stoi(line.substr(line.find_last_of('=') + 1));
                    prizePos = std::make_pair(x, y);
                    machines.emplace_back(a, b, prizePos);
                }
                else {
                    bool isA = line.find('A') != std::string::npos;
                    line = line.substr(line.find('+') + 1);
                    int x = std::stoi(line.substr(0, line.find(',')));
                    int y = std::stoi(line.substr(line.find_last_of('+') + 1));
                    if (isA) {
                        a = std::make_pair(x, y);
                    }
                    else {
                        b = std::make_pair(x, y);
                    }
                }
            }
        }

        long long findWinCost(Machine& machine) {
            int* pAx = &machine.a.first;
            int* pAy = &machine.a.second;
            int* pBx = &machine.b.first;
            int* pBy = &machine.b.second;
            long long* pPx = &machine.prizePos.first;
            long long* pPy = &machine.prizePos.second;
            long long aCount = (*pPx * *pBy - *pPy * *pBx) / (*pAx * *pBy - *pAy * *pBx);
            long long bCount = (*pPx - *pAx * aCount) / *pBx;
            if (aCount * *pAx + bCount * *pBx == *pPx && aCount * *pAy + bCount * *pBy == *pPy) {
                return aCount * 3 + bCount;
            }
            return 0;
        }

        long long runAllMachines(bool partTwo = false) {
            long long tokens = 0;
            for (Machine machine : machines) {
                if (partTwo) {
                    machine.prizePos.first += 10000000000000;
                    machine.prizePos.second += 10000000000000;
                }
                long long win = findWinCost(machine);
                tokens += win;
            }
            return tokens;
        }

};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/13/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}