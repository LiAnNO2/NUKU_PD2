#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <algorithm>
#include <iterator>
using namespace std;

class keywords { // ¬ö¿ ý¨ Ã§ @¬° ¿ é ¥X
        public:
                string sentence; // ¥y¤ l¿ é ¤ J
                int id;

                bool operator < (const keywords& k) {
                        return id < k.id;
                }
};


vector<class keywords> key;

int main(int argc,char **argv) {

        string data;
                ifstream myfile = ifstream(argv[1]);

                if (myfile.is_open()) {
                        while (getline(myfile, data)) {
                                        class keywords a;
                                        a.id = stoi(data.substr(0, data.find(",")));
                                        data = data.substr(data.find(",") + 1, data.length());
                                        a.sentence = data;
                                        key.push_back(a);
                        }
                        myfile.close();
                }
                else {
                        cerr << "Failed to open " << argv[1] << endl;
                }

                sort(key.begin(), key.end());
                for (int i = 0; i < 100; i++) {
                        cout<< key[i].id << " " << key[i].sentence << endl;
                }

        return 0;
}
