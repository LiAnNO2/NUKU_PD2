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
    int year;
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

vector<class employees> employee;
vector<int> id_diff; // 存不同種類id

void split_data(string data);
int count_time(int j);  // 回傳分鐘

int main() {
    int n = 0; //有n組數據
    string data; //作為輸入值

    //平常用輸入

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
    vector<int> overload;
    vector<int> notsign;

    // 算出overload天數 及 notsign天數
    int u = 0;
    for (int i = 0; i < id_diff.size(); i++) {
        int p = 0;
        int day_overload = 0;
        int day_notsign = 0;
        for (int j = u; j < employee.size(); j++) {  // 兩個兩個判斷   /// 1. 有可能某員工只有一次紀錄而且在最後一項數據
            //cout << "when id = " << id_diff[i] << " j = " << j << endl;
            if (p == 100) {
                p = 0;
                if (j == employee.size() - 1) {
                    overload.push_back(day_overload);
                    notsign.push_back(day_notsign);
                }
                continue;
            }
            if (id_diff[i] == employee[j].id) {
                if (j == employee.size() - 1) { // 某員工在最後一項數據
                    day_notsign++;
                    overload.push_back(day_overload);
                    notsign.push_back(day_notsign);
                    break;
                }
                if (employee[j].id == employee[j + 1].id) {    // id相同
                    if (employee[j].year == employee[j + 1].year
                        && employee[j].date.compare(employee[j + 1].date) == 0) { // 看日期有沒有一樣
                        if (count_time(j) > 480) {
                            day_overload++;
                        }
                        p = 100;
                    }
                    else {
                        day_notsign++;
                    }
                }
                else {
                    day_notsign++;
                }
            }
            else {  // 代表某id員工數據跑完
                u = j;
                overload.push_back(day_overload);
                notsign.push_back(day_notsign);
                break;
            }

        }
    }

    // cout結果
    for (int i = 0; i < id_diff.size(); i++) {
        cout << id_diff[i] << "," << overload[i] << "," << notsign[i] << endl;
    }

    // test 各項數值size
    /*
    cout << employee.size() << endl;
    cout << id_diff.size() << endl;
    cout << overload.size() << endl;
    cout << notsign.size() << endl;
    */

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
    p.year = stoi(mid[2].substr(0, 4));
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

int count_time(int j) { // 算工作時數
    string a_left(employee[j].time.begin(), employee[j].time.begin() + 2);
    string a_right(employee[j].time.begin() + 2, employee[j].time.begin() + 4);
    string b_left(employee[j + 1].time.begin(), employee[j + 1].time.begin() + 2);
    string b_right(employee[j + 1].time.begin() + 2, employee[j + 1].time.begin() + 4);
    int time1 = stoi(a_left) * 60 + stoi(a_right);
    int time2 = stoi(b_left) * 60 + stoi(b_right);

    // test 時間格式及數值
    /*
    cout << "worktime : " << time2 - time1 << endl;
    cout << a_left << endl;
    cout << a_right << endl;
    cout << b_left << endl;
    cout << b_right << endl;
    */

    return time2 - time1;
}
