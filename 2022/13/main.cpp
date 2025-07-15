#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

struct Packet {
    bool isInt;
    int value;
    vector<Packet> subPackets;

    Packet(int val) : isInt(true), value(val) {}
    Packet(const vector<Packet>& packets) : isInt(false), subPackets(packets) {}
};

class Solution {
    public:
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int ans = 0;
            for (size_t i = 0; i < pairs.size(); i++) {
                if (compare(pairs[i].first, pairs[i].second) < 0) {
                    ans += i + 1;
                }
            }
            return ans;
        }

        int partTwo() {
            vector<Packet> allPackets = getAllPackets();
            Packet twoPacket = parsePacket("[[2]]");
            Packet sixPacket = parsePacket("[[6]]");
            allPackets.emplace_back(twoPacket);
            allPackets.emplace_back(sixPacket);

            sort(allPackets.begin(), allPackets.end(), [this](const Packet& left, const Packet& right) {
                return compare(left, right) < 0;
            });

            int index2 = 0, index6 = 0;

            for (size_t i = 0; i < allPackets.size(); i++) {
                if (compare(allPackets[i], twoPacket) == 0) {
                    index2 = i + 1;
                }
                if (compare(allPackets[i], sixPacket) == 0) {
                    index6 = i + 1;
                }
            }
            return index2 * index6;
        }

    
    private:
        vector<pair<Packet, Packet> > pairs;
        void getData(const char* filename) {
            ifstream inputFile;
            inputFile.open(filename);
            string line;
            string first, second;
            bool expectFirst = true;
            while (getline(inputFile, line)) {
                if (line.empty()) continue;

                if (expectFirst) {
                    first = line;
                    expectFirst = false;
                }
                else {
                    second = line;
                    pairs.emplace_back(parsePacket(first), parsePacket(second));
                    expectFirst = true;
                }
            }   
        }

        Packet parsePacket(const string& str, size_t& i) {
            if (str[i] == '[') {
                ++i;
                std::vector<Packet> list;
                while (str[i] != ']') {
                    if (str[i] == ',') ++i;
                    list.push_back(parsePacket(str, i));
                }
                ++i; 
                return Packet(list);
            } 
            else {
                int num = 0;
                while (isdigit(str[i])) {
                    num = num * 10 + (str[i++] - '0');
                }
                return Packet(num);
            }
        }

        Packet parsePacket(const string& str) {
            size_t i = 0;
            return parsePacket(str, i);
        }

        int compare(const Packet& left, const Packet& right) {
            if (left.isInt && right.isInt) {
                return left.value - right.value;
            }
            if (!left.isInt && !right.isInt) {
                for (size_t i = 0; i < min(left.subPackets.size(), right.subPackets.size()); i++) {
                    int cmp = compare(left.subPackets[i], right.subPackets[i]);
                    if (cmp != 0) return cmp;
                }
                return left.subPackets.size() - right.subPackets.size();
            }
            if (left.isInt) {
                return compare(Packet(vector<Packet>{left}), right);
            }
            return compare(left, Packet(vector<Packet>{right}));
        }

        vector<Packet> getAllPackets() {
            vector<Packet> allPackets;
            allPackets.reserve(pairs.size() * 2);

            for (const auto& pair : pairs) {
                allPackets.push_back(pair.first);
                allPackets.push_back(pair.second);
            }
            return allPackets;
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