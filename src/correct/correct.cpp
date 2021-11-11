#include <iostream>
#include <cstring>
///                 0        1        2        3        4        5        6        7        8        9
int coordinate[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 0
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 1
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 2
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /// 3
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 4
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 5
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 6
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 7
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /// 8
};

struct Point {
    int x = 0;
    int y = 0;
    int z = 0;
};

int diff(const int *arr, int len) {
    int cnt = 0;
    int sum = 0;
    bool flag = false;
    for (int i = 0; i < len;) {
        if (flag) {
            break;
        }
        if (arr[i] == 0) {
            continue;
        }
        for (int j = i + 1; j <= len; j++) {
            if (j == len) {
                flag = true;
                break;
            }
            if (arr[j] == 0) {
                continue;
            }
            sum += abs(arr[i] - arr[j]);
            cnt++;
            i = j;
        }
    }
    std::cout << "sum: " << sum << ", cnt: " << cnt << ", ";
    return cnt == 0 ? 0 : int(sum / cnt);
}
void findVertical(int x, int y, int width) {
    /// top
    int top[3];
    Point topPoint[3];
    Point downPoint[3];
    for (int i = 1; i <= 3; i++) {
        int index = 3 * ((y - i) * width + x);
        top[i - 1] = coordinate[index];
        topPoint[i - 1].x = coordinate[index];
        topPoint[i - 1].y = coordinate[index + 1];
        topPoint[i - 1].z = coordinate[index + 2];
    }
    /// down
    int down[3];
    for (int i = 1; i <= 3; i++) {
        down[i - 1] = coordinate[3 * ((y + i) * width + x)];
        downPoint[i - 1].x = coordinate[3 * ((y + i) * width + x)];
        downPoint[i - 1].y = coordinate[3 * ((y + i) * width + x) + 1];
        downPoint[i - 1].z = coordinate[3 * ((y + i) * width + x) + 2];
    }
    std::string topStr{}, downStr{};
    int pickDown = 0;
    int pick = -1;
    for (int i = 0; i < 3; i++) {
        if (down[i] != 0 && top[i] != 0) {
            if (down[i] < top[i]) {
                pickDown++;
                if (pick < 0) {
                    pick = i;
                }
            }
        }
        topStr.append(std::to_string(top[i])).append(",");
        downStr.append(std::to_string(down[i])).append(",");
    }
    std::cout << "pick down rate: " << pickDown / 3 << ", pick: " << pick << std::endl;
    std::cout << "diff: " << diff(top, 3) << std::endl;
    std::cout << "top: " << topStr << std::endl;
    std::cout << "diff: " << diff(down, 3) << std::endl;
    std::cout << "down: " << downStr << std::endl;
}


void findHorizon(int x, int y, int width) {
    /// right
    int right[3];
    Point rightPoint[3];
    Point leftPoint[3];
    for (int i = 1; i <= 3; i++) {
        right[i - 1] = coordinate[3 * (y * width + (x + i))];
        rightPoint[i - 1].x = coordinate[3 * (y * width + (x + i))];
        rightPoint[i - 1].y = coordinate[3 * (y * width + (x + i)) + 1];
        rightPoint[i - 1].z = coordinate[3 * (y * width + (x + i)) + 2];
    }
    /// left
    int left[3];
    for (int i = 1; i <= 3; i++) {
        left[i - 1] = coordinate[3 * (y * width + (x - i))];
        leftPoint[i - 1].x = coordinate[3 * (y * width + (x - i))];
        leftPoint[i - 1].y = coordinate[3 * (y * width + (x - i)) + 1];
        leftPoint[i - 1].z = coordinate[3 * (y * width + (x - i)) + 2];
    }
    std::string rightStr{}, leftStr{};
    int pickLeft = 0;
    int pick = -1;
    for (int i = 0; i < 3; i++) {
        if (left[i] != 0 && right[i] != 0) {
            if (left[i] < right[i]) {
                pickLeft++;
                if (pick < 0) {
                    pick = i;
                }
            }
        }
        rightStr.append(std::to_string(right[i])).append(",");
        leftStr.append(std::to_string(left[i])).append(",");
    }
    std::cout << "pick left rate: " << pickLeft / 3 << ", pick: " << pick << std::endl;
    std::cout << "diff: " << diff(right, 3) << std::endl;
    std::cout << "right: " << rightStr << std::endl;
    std::cout << "diff: " << diff(left, 3) << std::endl;
    std::cout << "left: " << leftStr << std::endl;
}

int find(int x, int y, int width) {
    return coordinate[3 * (y * width + x)];
}

int main() {
    using namespace std;
    int width = 10;

    int x = 4;
    int y = 3;
    int res = find(x, y, width);
    std::cout << res << std::endl;
    findHorizon(x, y, width);
    findVertical(x, y, width);
}
