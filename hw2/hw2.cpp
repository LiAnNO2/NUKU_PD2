#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class employee { //員工資料
public:
	string number;  //員工編號
	string age;
	string sex;
	string salary;
};

vector<class employee> q[10000];

employee employees[10000];

void split_data(string data, int n, vector<string>& money);
void bubble_sort(vector<string>& v);

int main() {
	int n = 0;
	string data; //作為輸入值
	vector<string> money;
	/*
	ifstream myfile = ifstream(argv[1]);

	if (myfile.is_open()) {
		while (getline(myfile, data)) {
			split_data(data, n,money);
			n++;
		};
		myfile.close();
	}
	else {
		cerr << "Failed to open " << argv[1] << endl;
	}
	*/


	while (getline(cin, data)) { //開始切割資料
		if (data == "") { //讀不到東西就離開
			break;
		}
		split_data(data, n, money);
		n++;
	}

	bubble_sort(money);


	//for迴圈開始分類 並同時排序
	for (int i = 0; i < n; i++) {  //有n組數據
		for (int j = 0; j < money.size(); j++) { //有money.size()組不同的薪水
			if (stoi(money[j]) - stoi(employees[i].salary) == 0) {  //找到同樣薪水的分類
				if (q[j].size() == 0) {	//沒有東西直接push
					q[j].push_back(employees[i]);
				}
				else {
					for (int m = 0; m < q[j].size(); m++) {	//開始分類(一個一個看)
						if (stoi(employees[i].age) - stoi(q[j][m].age) < 0) { //如果data的年紀比較小
							q[j].insert(q[j].begin() + m, employees[i]);
							break;
						}
						else if (stoi(employees[i].age) - stoi(q[j][m].age) == 0) { //如果與data年紀一樣
							if (employees[i].sex.compare(q[j][m].sex) < 0) { //是女生就排前面
								q[j].insert(q[j].begin() + m, employees[i]);
								break;
							}
							else if (employees[i].sex.compare(q[j][m].sex) == 0) { //性別也相同
								if (stoi(employees[i].number) - stoi(q[j][m].number) < 0) { //編號小的排前面
									q[j].insert(q[j].begin() + m, employees[i]);
								}
								else {
									if (m == q[j].size() - 1) { //jugde 484 q vector 最後一項
										q[j].push_back(employees[i]);
										break;
									}
								}
							}
							else {
								if (m == q[j].size() - 1) { //jugde 484 q vector 最後一項
									q[j].push_back(employees[i]);
									break;
								}
							}
						}
						else if (m == q[j].size() - 1) { //data年紀最大
							q[j].push_back(employees[i]);
							break;
						}
					}

				}
			}
		}
	}
	//for迴圈cout結果
	for (int i = 0; i < money.size(); i++) {
		cout << "money.size = " << money.size() << endl;
		cout << stoi(money[i]);
		for (int j = 0; j < q[i].size(); j++) {
			cout << ',' + q[i][j].number;
		}
		cout << endl;
	}
	return 0;
}

void split_data(string data, int n, vector<string>& money) {
	vector<string> mid; //暫存資料
	int h = 0;
	while (1) { //切割
		mid.push_back(data.substr(0, data.find(",")));
		data = data.substr(data.find(",") + 1, data.length());

		if (data.find(",") == -1) {
			mid.push_back(data);
			break;
		}
	}
	employees[n].number = mid[0];
	employees[n].age = mid[1];
	employees[n].sex = mid[2];
	employees[n].salary = mid[3];
	for (int i = 0; i < money.size(); i++) { //取出不同種類的薪水
		if (stoi(mid[3]) == stoi(money[i])) {
			h = 1;
			break;
		}
	}
	if (h == 0) {
		money.push_back(mid[3]);
	}
}

void bubble_sort(vector<string>& v) {
	int num = v.size();
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (v[j].compare(v[j + 1]) > 0) {
				string l = v[j];
				v[j] = v[j + 1];
				v[j + 1] = l;
			}
		}
	}
}
