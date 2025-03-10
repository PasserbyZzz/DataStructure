// 冒泡排序 超时！

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

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

void bubbleSort(vector<string> &words, int m, unordered_map<char, int> order) 
// 冒泡排序
{  
    int i, j;   
    bool change = true;
    string tmp;   

    for (j = m - 1; j > 0 && change; j--) 
    {    
        change = false;

        for (i = 0; i < j; i++)
            if (compare(words[i], words[i+1], order)) 
            {   
                tmp = words[i];  
                words[i] = words[i+1];
                words[i+1] = tmp;  
                change = true;
            } 
    }
} 

int main()
{
    int n, m;
    cin >> n >> m;

    unordered_map<char, int> order; //存储各个字符与其顺序的映射
    for (int i = 0; i < n; i++)
    {
        char character;
        cin >> character;

        order[character] = i;
    }

    vector<string> words;
    for (int i = 0; i < m; i++)
    {
        string word;
        cin >> word;

        words.push_back(word);
    }

    bubbleSort(words, m, order);
    for (int i = 0; i < m; i++)
    {
        cout << words[i] << endl;
    }

    return 0;

}