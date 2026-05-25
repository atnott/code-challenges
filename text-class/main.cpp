#include"formatRowFile.hpp"
#include"textFile.hpp"
#include<iostream>
#include<string>

int main() {
    using std::cout;
    using std::endl;
    using std::string;

    string path = "STARLINK/chirp_20210126_084300_003_out.dat";

    TextFile<formatRowFile> file(path, false);

    cout << file.data.size() << endl;
    for (auto& i : file.data) {
        for (auto& j : i.columns) {
            cout << j << ' ';
        }
        cout << endl;
    }
    return 0;
}
