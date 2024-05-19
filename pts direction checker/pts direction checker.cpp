#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

struct Point {
    double x, y, z;
};

enum Direction { CLOCKWISE, COUNTERCLOCKWISE, UNKNOWN };

Direction findDirection(const std::vector<Point>& points) {
    double sum = 0;

    for (size_t i = 0; i < points.size() - 1; i++) {
        sum += (points[i].x * points[i + 1].y) - (points[i + 1].x * points[i].y);
    }

    sum += (points.back().x * points.front().y) - (points.front().x * points.back().y);

    if (sum > 0) {
        return COUNTERCLOCKWISE;
    }
    else if (sum < 0) {
        return CLOCKWISE;
    }
    else {
        return UNKNOWN;
    }
}

std::vector<Point> readPointsFromFile(const std::filesystem::path& filePath) {
    std::vector<Point> points;
    std::ifstream inFile(filePath);

    Point p;
    while (inFile >> p.x >> p.y >> p.z) {
        points.push_back(p);
    }

    return points;
}

int main() {
    for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        if (entry.path().extension() == ".pts" || entry.path().extension() == ".PTS") {
            std::vector<Point> points = readPointsFromFile(entry.path());

            if (points.size() > 1) {
                Direction dir = findDirection(points);

                std::cout << entry.path().filename().string() << "\t";

                if (dir == CLOCKWISE) {
                    std::cout << "cw" << std::endl;
                }
                else if (dir == COUNTERCLOCKWISE) {
                    std::cout << "ccw" << std::endl;
                }
                else {
                    std::cout << "unknown" << std::endl;
                }
            }
            else {
                std::cout << entry.path().filename().string() << "\t";
                std::cout << "not enough points" << std::endl;
            }
        }
    }

    system("pause");
    return 0;
}

