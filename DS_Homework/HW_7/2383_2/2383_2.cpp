// 最小化堆，完美通过！

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<char, int> order; //存储各个字符与其顺序的映射

bool compare(string word_1, string word_2, unordered_map<char, int> order);

struct CompareString {
    bool operator()(const string& a, const string& b) {
        return compare(a, b, order); // "a" > "b" 
    }
};

bool compare(string word_1, string word_2, unordered_map<char, int> order)
// 不考虑等于的情况；word_1排在前面，返回false；word_2排在前面，返回true
{
    // word_1空，word_2非空，word_1排在前面
    if (!word_1.length() && word_2.length())
        return false;
    // word_2空，word_1非空，word_2排在前面
    else if (!word_2.length() && word_1.length())
        return true;
    // word_1非空，word_2非空，逐位比较
    else if (word_2.length() && word_1.length())
    {
        // word_1第一位排在前面，则word_1排在前面
        if (order[word_1[0]] < order[word_2[0]])
            return false;
        // word_2第一位排在前面，则word_2排在前面
        else if (order[word_1[0]] > order[word_2[0]])
            return true;
        else
            return compare(word_1.substr(1), word_2.substr(1), order);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        char character;
        cin >> character;

        order[character] = i;
    }

    priority_queue<string, vector<string>, CompareString> minHeap;
    for (int i = 0; i < m; i++)
    {
        string word;
        cin >> word;

        minHeap.push(word);
    }

    while (!minHeap.empty()) 
    {
        cout << minHeap.top() << endl; 
        minHeap.pop();
    }

    return 0;
}