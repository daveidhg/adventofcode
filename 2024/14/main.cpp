#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <set>

struct Robot {
    int x;
    int y;
    int dx;
    int dy;

    Robot(int x, int y, int dx, int dy) : x(x), y(y), dx(dx), dy(dy) {}
};

class Solution {
    public:
        std::vector<Robot> robots;
    
        Solution(const char* filename) {
            getData(filename);
        }

        int partOne() {
            int width = 101;
            int height = 103;
            moveRobots(100, width, height);
            return multiplyQuadrants(width, height);
        }

        int partTwo() {
            int seconds = 0;
            int width = 101;
            int height = 103;
            while (!isChristmasTree(width, height)) {
                moveRobots(1, width, height);
                seconds++;
            }
            return seconds + 100; // 100 seconds were already added from part one
        }

    
    private:
        void getData(const char* filename) {
            std::ifstream inputFile;
            inputFile.open(filename);
            std::string line;
            while (getline(inputFile, line)) {
                line = line.substr(line.find("=") + 1);
                int x = std::stoi(line.substr(0, line.find(",")));
                line = line.substr(line.find(",") + 1);
                int y = std::stoi(line.substr(0, line.find(" ")));
                line = line.substr(line.find("=") + 1);
                int dx = std::stoi(line.substr(0, line.find(",")));
                int dy = std::stoi(line.substr(line.find(",") + 1));
                robots.emplace_back(x, y, dx, dy);
            }
        }

        void moveRobots(int seconds, int width, int height) {
            for (Robot& robot : robots) {
                robot.x += robot.dx * seconds;
                robot.y += robot.dy * seconds;
                robot.x = robot.x % width;
                robot.y = robot.y % height;
                if (robot.x < 0) {
                    robot.x += width;
                }
                if (robot.y < 0) {
                    robot.y += height;
                }
            }
        }

        int multiplyQuadrants(int width, int height) {
            int quadrants[4] = {0, 0, 0, 0};
            for (Robot& robot : robots) {
                if (robot.x < width / 2 && robot.y < height / 2) {
                    quadrants[0]++;
                } else if (robot.x > width / 2 && robot.y < height / 2) {
                    quadrants[1]++;
                } else if (robot.x < width / 2 && robot.y > height / 2) {
                    quadrants[2]++;
                } else if (robot.x > width / 2 && robot.y > height / 2) {
                    quadrants[3]++;
                }
            }
            return quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3];
        }

        bool isChristmasTree(int width, int height) {
                char grid[height][width];
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        grid[i][j] = '.';
                    }
                }
                for (Robot robot : robots) {
                    if (grid[robot.y][robot.x] == '#') {
                        return false;
                    }
                    grid[robot.y][robot.x] = '#';
                }
            return true;
        }
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Solution solution = Solution("2024/14/input.txt");
    std::cout << "Part One: " << solution.partOne() << std::endl;
    std::cout << "Part Two: " << solution.partTwo() << std::endl;

    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << " ms" << std::endl;
}