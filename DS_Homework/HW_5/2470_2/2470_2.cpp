#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<functional>
#include<stack>

struct post {
    int id;
    int heat;
    int day;
    post (int heat_input, int id_input, int day_input)
        : id(id_input), heat(heat_input), day(day_input) {}
};

struct compare {
    bool operator()(post a, post b) {
        return a.heat < b.heat || a.heat == b.heat && a.id < b.id;
    }
};

bool operator<(const post& a, const post& b) {
    if (a.heat != b.heat) {
        return a.heat < b.heat;
    }
    return a.id < b.id;
}

bool operator<=(const post& a, const post& b) {
    return !(b < a);
}

bool operator>(const post& a, const post& b) {
    return b < a;
}

bool operator>=(const post& a, const post& b) {
    return !(a < b);
}

int TDaysPopular(const int& nowDay, const int T, const std::vector<post>& most_popular_posts) {
    int start = std::max(0, nowDay - T);
    int stop = nowDay - 1;
    post bestPost = most_popular_posts[start];
    for (int i = start + 1; i <= stop; i++) {
        if (most_popular_posts[i] > bestPost) {
            bestPost = most_popular_posts[i];
        }
    }
    return bestPost.id;
}

int main () {
    int T, D, P;
    std::cin >> T >> D >> P;
    std::vector<post> most_popular_posts;
    
    for (int i = 0; i < D; i++) {
        std::priority_queue<post, std::vector<post>, compare> pq_max;
        for (int j = 0; j < P; j++) {
            // 输入每天各个帖子的浏览量
            int heat_ij;
            std::cin >> heat_ij;
            pq_max.push(post(heat_ij, j+1, i+1));
        }
        most_popular_posts.push_back(pq_max.top());
    }

    for (int nowDay = 1; nowDay <= D; nowDay++) {
        std::cout << TDaysPopular(nowDay, T, most_popular_posts) << " ";
    }
    return 0;
}