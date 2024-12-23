#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            set<set<string> > connections = getThreewayInterconnections();
            for (auto& connection : connections) {
                for (auto& node : connection) {
                    if (node[0] == 't') {
                        ans++;
                        break;
                    }
                }
            }
            return ans;
        }

        string partTwo() {
            set<string> largest;
            for (auto& interconnection : interconnections) {
                if (interconnection.size() > largest.size()) {
                    largest = interconnection;
                }
            }
            string ans = "";
            for (auto& connection : largest) {
                ans += connection + ",";
            }
            return ans.substr(0, ans.size() - 1);
        }

    
    private:
        unordered_map<string, set<string> > data;
        set<set<string> > interconnections;
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            while (getline(inputFile, line)) {
                string a = line.substr(0, 2);
                string b = line.substr(3);
                data[a].insert(b);
                data[b].insert(a);
            }
            for (auto& [node, connections] : data) {
                set<string> requirements = {node};
                getAllInterconnections(node, interconnections, requirements);
            }
        }

        set<set<string> > getThreewayInterconnections() {
            set<set<string> > connections;
            for (auto& [a, b] : data) {
                for (int i = 0; i < b.size(); i++) {
                    for (int j = i + 1; j < b.size(); j++) {
                        auto i_it = next(b.begin(), i);
                        auto j_it = next(b.begin(), j);
                        if (data[*i_it].find(*j_it) != data[*i_it].end() && data[*j_it].find(*i_it) != data[*j_it].end()) {
                            connections.insert({a, *i_it, *j_it});
                        }
                    }
                }
            }
            return connections;
        }

        void getAllInterconnections(string node, set<set<string> >& interconnections, set<string> requirements) {
            if (interconnections.find(requirements) != interconnections.end()) return;
            interconnections.insert(requirements);
            for (auto connection : data[node]) {
                if (requirements.find(connection) != requirements.end()) continue;
                bool allConnected = true;
                for (auto& neighbor : requirements) {
                    if (data[connection].find(neighbor) == data[connection].end()) {
                        allConnected = false;
                        break;
                    }
                }
                if (!allConnected) continue;
                requirements.insert(connection);
                getAllInterconnections(connection, interconnections, requirements);
            }
        }
};

int main() {
    auto start = chrono::high_resolution_clock::now();
    Solution testSolution = Solution("2024/23/testinput.txt");
    Solution solution = Solution("2024/23/input.txt");

    cout << "Test One: " << testSolution.partOne() << endl;
    cout << "Test Two: " << testSolution.partTwo() << "\n\n";

    cout << "Part One: " << solution.partOne() << endl;
    cout << "Part Two: " << solution.partTwo() << endl;

    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << " ms" << endl;
}