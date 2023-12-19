#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
using std::string, std::vector, std::ifstream, std::pair, std::unordered_map, std::cout, std::endl;

class Solution {
    public:
        unordered_map<string, vector<vector<string> > > workflow;
        vector<unordered_map<char, int> > parts;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            string workflowLabel = "in";
            for (auto &part : parts) {
                while (workflowLabel.length() > 1) {
                    for (auto condition : workflow[workflowLabel]) {
                        if (condition.size() == 1) {
                            workflowLabel = condition[0];
                        }
                        else {
                            char &partLabel = condition[0][0];
                            char &comparator = condition[0][1];
                            int value = stoi(condition[1]);
                            string destination = condition[2];
                            if (comparator == '>') {
                                if (part[partLabel] > value) {
                                    workflowLabel = destination;
                                    break;
                                }
                            }
                            else {
                                if (part[partLabel] < value) {
                                    workflowLabel = destination;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (workflowLabel[0] == 'A') {
                    for (auto &pair : part) {
                        ans += pair.second;
                    }
                }
                workflowLabel = "in";
            }
            return ans;
        }

        long long partTwo() {
            unordered_map<char, pair<int, int> > ranges;
            ranges['x'] = {1, 4000};
            ranges['m'] = {1, 4000};
            ranges['a'] = {1, 4000};
            ranges['s'] = {1, 4000};
            return count(ranges, "in");
        }

    
    private:
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            bool conditions = true;
            vector<vector<string> > conditionList;
            string label;
            unordered_map<char, int> part;
            while (getline(inputFile, line)) {
                if (conditions) {
                    if (line.empty()) {
                        conditions = false;
                        continue;
                    }
                    else {
                        size_t condStart = line.find('{') + 1;
                        label = line.substr(0, condStart - 1);
                        line = line.substr(condStart);
                        while (line.length() > 1) {
                            size_t condEnd = line.find(',', 1);
                            condEnd = (condEnd == string::npos) ? line.length() - 1 : condEnd;
                            conditionList.push_back(splitCondition(line.substr(0, condEnd)));
                            line = line.substr(condEnd + 1);
                        }
                        workflow[label] = conditionList;
                        label.clear();
                        conditionList.clear();
                    }
                }
                else {
                    line = line.substr(1);
                    while (line.length() > 1) {
                        char label = line[0];
                        size_t end = line.find(',');
                        end = (end == string::npos) ? line.length() - 1 : end;
                        int value = stoi(line.substr(2, end));
                        line = line.substr(end + 1);
                        part[label] = value;
                    }
                    parts.push_back(part);
                    part.clear();
                }
            }
        }

        vector<string> splitCondition(string condition) {
            size_t colonIndex = condition.find(':');
            if (colonIndex == string::npos) {
                return {condition};
            }
            return {condition.substr(0, 2), condition.substr(2, colonIndex - 2), condition.substr(colonIndex + 1)};
        }

        long long count(unordered_map<char, pair<int, int> > ranges, string label) {
            if (label[0] == 'R') {
                return 0;
            }
            if (label[0] == 'A') {
                long long prod = 1;
                for (auto &pair : ranges) {
                    prod *= pair.second.second - pair.second.first + 1;
                }
                return prod;
            }

            vector<vector<string> > &conditions = workflow[label];
            long long total = 0;
            bool breaked = false;
            for (vector<string> &condition : conditions) {
                if (condition.size() > 1) {
                    char &partLabel = condition[0][0];
                    char &comparator = condition[0][1];
                    int value = stoi(condition[1]);
                    string destination = condition[2];
                    int &low = ranges[partLabel].first;
                    int &high = ranges[partLabel].second;
                    int aStart, aEnd, rStart, rEnd;
                    if (comparator == '<') {
                        aStart = low;
                        aEnd = value - 1;
                        rStart = value;
                        rEnd = high;
                    }
                    else {
                        aStart = value + 1;
                        aEnd = high;
                        rStart = low;
                        rEnd = value;
                    }
                    if (aStart <= aEnd) {
                        unordered_map<char, pair<int, int> > rangesCopy = ranges;
                        rangesCopy[partLabel] = {aStart, aEnd};
                        total += count(rangesCopy, destination);
                    }
                    if (rStart <= rEnd) {
                        ranges[partLabel] = {rStart, rEnd};
                    }
                }
                else {
                    total += count(ranges, condition[0]);
                }
            }
            return total;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2023/19/input.txt");
    int partOne = solution.partOne();
    long long partTwo = solution.partTwo();
    cout << "Part one: " << partOne << endl;
    cout << "Part two: " << partTwo << endl;

    cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}