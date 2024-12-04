#include<iostream>
#include<queue>

struct Point {
    int x, y;
    int fishNum;
    bool isChecked;
    Point *left, *right, *up, *down;
    Point(int f, int x_, int y_)
        :fishNum(f), x(x_), y(y_), isChecked(false), left(nullptr), right(nullptr), up(nullptr), down(nullptr) {}
};

void searchOneArea(int sx, int sy, Point*** pointArray, int& maxTotalFish) {
    Point* start = pointArray[sx][sy];
    if (start == nullptr || start->isChecked) return;

    int tempTotal = 0;
    std::queue<Point*> que;
    que.push(start);
    start->isChecked = true;
    while (!que.empty()) {
        Point* currPoint = que.front();
        que.pop();
        tempTotal += currPoint->fishNum;
        if (currPoint->up != nullptr && !currPoint->up->isChecked) {
            que.push(currPoint->up);
            currPoint->up->isChecked = true;
        }
        if (currPoint->down != nullptr && !currPoint->down->isChecked) {
            que.push(currPoint->down);
            currPoint->down->isChecked = true;
        }
        if (currPoint->left != nullptr && !currPoint->left->isChecked) {
            que.push(currPoint->left);
            currPoint->left->isChecked = true;
        }
        if (currPoint->right != nullptr && !currPoint->right->isChecked) {
            que.push(currPoint->right);
            currPoint->right->isChecked = true;
        }
    }

    if (tempTotal > maxTotalFish) {
        maxTotalFish = tempTotal;
    }
}

int main () {
    int height, width;
    std::cin >> height >> width;

    Point*** pointArray = new Point**[height];
    for (int i = 0; i < height; i++) {
        pointArray[i] = new Point*[width];
        for (int j = 0; j < width; j++) {
            pointArray[i][j] = nullptr;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int fishNum;
            std::cin >> fishNum;
            // 只初始化水面部分，而不初始化陆地。
            if (fishNum != 0) {
                pointArray[i][j] = new Point(fishNum, i, j);
            }
        }
    }
    // 将最左下角视为(0, 0)，按照一般坐标系的划分进行。
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (pointArray[i][j] == nullptr) continue;

            if (i - 1 >= 0 && pointArray[i-1][j] != nullptr) {
                pointArray[i][j]->down = pointArray[i-1][j];
            }
            if (i + 1 <= height - 1 && pointArray[i+1][j] != nullptr) {
                pointArray[i][j]->up = pointArray[i+1][j];
            }
            if (j - 1 >= 0 && pointArray[i][j-1] != nullptr) {
                pointArray[i][j]->left = pointArray[i][j-1];
            }
            if (j + 1 <= width - 1 && pointArray[i][j+1] != nullptr) {
                pointArray[i][j]->right = pointArray[i][j+1];
            }
        }
    }

    int maxTotalFish = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            searchOneArea(i, j, pointArray, maxTotalFish);
        }
    }
    std::cout << maxTotalFish;

    // Free dynamically allocated memory
    // 第一次提交的时候内存泄漏了，别忘记删除指针呀！
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete pointArray[i][j];
        }
        delete[] pointArray[i];
    }
    delete[] pointArray;

    return 0;
}