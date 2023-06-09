#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
#include <iterator>
using namespace std;

class keywords { // 紀錄並作為輸出
public:
    vector<string> keyword;
    vector<int> yes;
};


vector<class keywords> key;
vector<string> sentence; // 句子輸入
vector<string> id;

string change(string s); // 轉小寫和去掉非字母和留空格符號
bool yon(vector<string>& mid, int k); // 判斷有沒有符合

int main(int argc, char** argv) {
    string data;
    for (int i = 1; i <= 2; i++) { // 第一個檔是句子 ，第二個檔是keyword
        ifstream myfile = ifstream(argv[i]);

        if (myfile.is_open()) {
            int y = 0;
            while (getline(myfile, data)) {
                if (i == 1) {
                    id.push_back(data.substr(0, data.find(",")));
                    data = data.substr(data.find(",") + 1, data.length());
                    sentence.push_back(change(data));
                }
                else {
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

    // 判斷
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
        sort(mid.begin(), mid.end());
        auto result1 = unique(mid.begin(), mid.end());
        mid.resize(distance(mid.begin(), result1));

        for (int k = 0; k < key.size(); k++) {
            if (yon(mid, k)) {
                key[k].yes.push_back(stoi(id[i]));
            }
        }
    }

    // 輸出
    for (int i = 0; i < key.size(); i++) {
        if (key[i].yes.size() == 0) {
            cout << "-1" << endl;
        }
        else {
            sort(key[i].yes.begin(), key[i].yes.end());
            for (int j = 0; j < key[i].yes.size(); j++) {
                if (j == 0) {
                    cout << key[i].yes[j];
                }
                else {
                    cout << " " << key[i].yes[j];
                }
            }
            cout << endl;
        }
    }

    return 0;
}

bool yon(vector<string>& mid, int k) {
    sort(key[k].keyword.begin(), key[k].keyword.end());
    auto result = unique(key[k].keyword.begin(), key[k].keyword.end());
    key[k].keyword.resize(distance(key[k].keyword.begin(), result));

    int time = key[k].keyword.size();
    int x = 0;
    for (int j = 0; j < mid.size(); j++) {
        for (int l = 0; l < time; l++) {
            if (mid[j].compare(key[k].keyword[l]) == 0) {
                x++;
                break;
            }
        }
        if (x == time) {
            return true;
        }
    }
    return false;
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
