#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iterator>
#include<cmath>
using namespace std;

class keywords { // 紀錄
public:
    vector<string> keyword;
    double idf_sum[3] = {};
};

class ids {  // 儲存
public:
    int id2;
    double total;

    bool operator < (const ids& i) {
        if (total != i.total) {
            return i.total < total;
        }
        return id2 < i.id2;
    }
};

vector<class keywords> key;
vector<class ids> findmax;
vector<string> sentence; // 句子輸入
vector<int> repeated_word;
vector<int> id;
vector<vector<string>> word; 

string change(string s); // 轉小寫和去掉非字母和控空格符號
int count(vector<string>& mid, string kk); // 判斷有沒有符合

int main(int argc, char** argv) {
    int k;
    int num_sentence = 0;
    string data;

    for (int i = 1; i <= 2; i++) { // 第一個檔是句子 ，第二個檔是keyword
        ifstream myfile = ifstream(argv[i]);

        if (myfile.is_open()) {
            while (getline(myfile, data)) {
                if (i == 1) {
                    id.push_back(stoi(data.substr(0, data.find(","))));
                    data = data.substr(data.find(",") + 2, data.length());
                    sentence.push_back(change(data));
                    num_sentence++;
                }
                else if (i == 2) {
                    class keywords mid1;
                    vector<string> ww;
                    data = change(data);
                    while (1) { // 切空白
                        if (data.find(" ") != -1) { // 避免沒有空格卻pushback兩次
                            ww.push_back(data.substr(0, data.find(" ")));
                            data = data.substr(data.find(" ") + 1, data.length());
                        }

                        if (data.find(" ") == -1) {
                            ww.push_back(data);
                            break;
                        }
                    }
                    mid1.keyword = ww;
                    key.push_back(mid1);
                }
            }
            myfile.close();
        }
        else {
            cerr << "Failed to open " << argv[i] << endl;
        }
    }
    k = stoi(argv[3]);

    for (int i = 0; i < sentence.size(); i++) {
        vector<string> mid; // 存字串

        while (1) { // 切割
            if (sentence[i].find(" ") != -1) {
                mid.push_back(sentence[i].substr(0, sentence[i].find(" ")));
                sentence[i] = sentence[i].substr(sentence[i].find(" ") + 1, sentence[i].length());
            }

            if (sentence[i].find(" ") == -1) {
                mid.push_back(sentence[i]);
                break;
            }
        }
        word.push_back(mid);
    }
    // 計算IDF
    for (int p = 0; p < key.size(); p++) {
        for (int o = 0; o < key[p].keyword.size(); o++) {
            int num = 0;
            int sum = 0;
            for (int i = 0; i < word.size(); i++) {
                sum = count(word[i], key[p].keyword[o]);
                if (sum > 0) {
                    num += 1;
                }
            }
            repeated_word.push_back(sum);
            if (num != 0) {
                key[p].idf_sum[o] = (log10((double)num_sentence / num));
            }
            else {
                key[p].idf_sum[o] = 0;
            }
        }
    }

    // 判斷 
    int g = 0;
    for (int k = 0; k < key.size(); k++) {
        for (int i = 0; i < word.size(); i++) { //每個句子跑一遍
            class ids q;
            q.id2 = id[i];
            q.total = 0;
            for (int p = 0; p < key[k].keyword.size(); p++) {
                q.total += key[p].idf_sum[p] * (repeated_word[g++] / word[i].size());
            }
            findmax.push_back(q);
        }
        sort(findmax.begin(), findmax.end());
        for (int y = 0; y < 3; y++) {
            if (y != 0)
                cout << " ";
            if (findmax[y].total == 0)
                cout << "-1";
            else
                cout << findmax[y].id2;
        }
        findmax.clear();
    }
    return 0;
}


int count(vector<string>& mid, string kk) {
    int n = 0;
    for (int i = 0; i < mid.size(); i++) {
        if (kk.compare(mid[i]) == 0) {
            n++;
        }
    }
    return n;
}

string change(string s) {
    string h;
    for (int i = 0; i < s.size(); i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            h += s[i] + 'a' - 'A';
        }
        else if (('a' <= s[i] && s[i] <= 'z') || s[i] == ' ') {
            h += s[i];

        }
    }
    return h;
}
