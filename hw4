#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
using namespace std;

class employees {
public:
    int id;
    string condition;
    string year;
    string date;
    string time;

    bool operator < (const employees& e) {
        if (id != e.id) {
            return id < e.id;
        }
        if (year != e.year) {
            return year < e.year;
        }
        if (date != e.date) {
            return date < e.date;
        }
        if (time != e.time) {
            return time < e.time;
        }
        return condition == "sign-in";
    }
};

class lian { // 作為輸出
public:
    int id;
    int attend1;
    string datefirst;
    string dateend;

    bool operator < (const lian& l) {
        if (attend1 != l.attend1) {
            return l.attend1 < attend1;
        }
        return id < l.id;
    }
};

vector<class employees> employee;
vector<class lian> LiAn;
vector<int> id_diff; // 存不同種類id

void split_data(string data);
bool leap_year(int y);

int main(int argc,char **argv) {
    int n = 0; //有n組數據
    string data; //作為輸入值
    
    // 平常用輸入
    while (getline(cin, data)) {
        if (data == "") {
            break;
        }
        split_data(data);
        n++;
    }
    
    // vim專門輸入
    /*
    ifstream myfile = ifstream(argv[1]);

    if (myfile.is_open()) {
        while (getline(myfile, data)) {
            split_data(data);
            n++;
        };
        myfile.close();
    }
    else {
        cerr << "Failed to open " << argv[1] << endl;
    }
    
    //要int main(int argc,char **argv)
    */
    

    sort(employee.begin(), employee.end());
    sort(id_diff.begin(), id_diff.end());

    // test 數據
    /*
    for (int i = 0; i < employee.size(); i++) {
        cout <<  employee[i].id ;
        cout << "," << employee[i].condition ;
        cout << "," << employee[i].year << " " << employee[i].date << " " << employee[i].time << endl;
    }
    cout << endl;
    */
    int u = 0;
    for (int i = 0; i < id_diff.size(); i++) { // 把不同人跑完
        int att = 0; // 暫存 attend;
        int day = 0;
        int mode = 1; // 1.作為數入(開始) 2.繼續計算 3.結算
        class lian L;
        string x; // 開始日期
        string y; // 結束日期
        string df;   // 暫存 date_first
        string de;  // 暫存 date_end
        for (int j = u; j < employee.size(); j++) {
            if (id_diff[i] == employee[j].id) { 
                if (mode == 2) {
                    int uu = stoi(employee[j].date) / 100, v = stoi(employee[j - 1].date) / 100; // 月分
                    int w = stoi(employee[j].date) % 100, r = stoi(employee[j - 1].date) % 100; // 日期
                    if (employee[j].year == employee[j - 1].year && employee[j].date == employee[j - 1].date) { // 同天sign-in sign-out
                        if (j == employee.size() - 1) { // 最後兩筆資料剛好同一天
                            if (day >= att) {
                                att = day;
                                df = x;
                                de = y;
                            }
                            L.id = id_diff[i];
                            L.attend1 = att;
                            L.datefirst = df;
                            L.dateend = de;
                            LiAn.push_back(L);
                            break;
                        }
                        else {
                            continue;
                        }
                    }
                    if (employee[j].year == employee[j - 1].year && stoi(employee[j].date) - stoi(employee[j - 1].date) == 1) {  // 判斷要不要繼續計算
                        mode = 2;
                    }
                    else if ((uu == v + 1) && employee[j].year == employee[j - 1].year && w == 1) {  // 跨月份的情況
                        mode = 3;
                        switch (uu) {
                        case 2:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 3:
                            if (leap_year(stoi(employee[j].year))) {
                                if (r == 29) {
                                    mode = 2;
                                }
                            }
                            else {
                                if (r == 28) {
                                    mode = 2;
                                }
                            }
                            break;
                        case 4:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 5:
                            if (r == 30) {
                                mode = 2;
                            }
                            break;
                        case 6:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 7:
                            if (r == 30) {
                                mode = 2;
                            }
                            break;
                        case 8:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 9:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 10:
                            if (r == 30) {
                                mode = 2;
                            }
                            break;
                        case 11:
                            if (r == 31) {
                                mode = 2;
                            }
                            break;
                        case 12:
                            if (r == 30) {
                                mode = 2;
                            }
                            break;
                        default:
                            mode = 3;
                            break;
                        }
                    }
                    else if ((uu == 1 && v == 12) && stoi(employee[j].year) - stoi(employee[j - 1].year) == 1 && w == 1 && r == 31) { // 跨年
                        mode = 2;
                    }
                    else { // 停止計算
                        mode = 3;
                    }
                }
                switch (mode) {
                    case 1:
                        x = employee[j].year + employee[j].date; // 存開始日期
                        y = employee[j].year + employee[j].date; // 暫存結束日期
                        day++;
                        mode = 2;
                        break;
                    case 2:
                        day++;
                        y = employee[j].year + employee[j].date;
                        break;
                    case 3:
                        mode = 1;
                        if (day >= att) {
                            att = day;
                            df = x;
                            de = y;
                        }
                        day = 0;
                        if (j != employee.size() - 1) {
                            j--; // 要判斷結束的時候已經是下一筆資料了
                        }
                        else {
                            if (day >= att) {
                                att = day;
                                df = x;
                                de = y;
                            }
                            L.id = id_diff[i];
                            L.attend1 = att;
                            L.datefirst = df;
                            L.dateend = de;
                            LiAn.push_back(L);
                        }
                        break;
                }
            }
            else {
                u = j;
                if (day >= att) {
                    att = day;
                    df = x;
                    de = y;
                }
                L.id = id_diff[i];
                L.attend1 = att;
                L.datefirst = df;
                L.dateend = de;
                LiAn.push_back(L);
                break;
            }
        }
    }

    sort(LiAn.begin(), LiAn.end());

    // cout結果
    for (int i = 0; i < 3; i++) {
        cout << LiAn[i].id << ',' << LiAn[i].attend1 << ',' << LiAn[i].datefirst << ',' << LiAn[i].dateend << endl;
    }

    return 0;
}

void split_data(string data) {
    int h = 0;
    vector<string> mid; // 暫存資料
    class employees p;

    while (1) { // 切割
        mid.push_back(data.substr(0, data.find(",")));
        data = data.substr(data.find(",") + 1, data.length());

        if (data.find(",") == -1) {
            mid.push_back(data);
            break;
        }
    }
    p.id = stoi(mid[0]);
    p.condition = mid[1];
    p.year = mid[2].substr(0, 4);
    p.date = mid[2].substr(4, 4);
    p.time = mid[2].substr(8, 4);
    employee.push_back(p);
    // 找有幾個不同的員工
    for (int i = 0; i < id_diff.size(); i++) {
        if (p.id == id_diff[i]) {
            h = 1;
            break;
        }
    }
    if (h == 0) {
        id_diff.push_back(p.id);
    }
}

bool leap_year(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0 && y % 400 != 0) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}
