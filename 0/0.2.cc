#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const vector<string> split(const string& input) {
    string product;
    char del(' ');
    vector<string> output;

    for (char c : input) {
        if(c == del) {
            output.push_back(product);
            product = "";
        }

        product.push_back(c);
    }

    return output;
}

int main() {
    string target_file = "UPPloppet_resultat.txt";

    // string target_file{""};
    // cout << "Skriv namnet av en fil: ";
    // getline(cin, target_file);

    ifstream file(target_file);

    if (!file.is_open()) {
        cerr << "Failed to open file\n" << endl;
        return 1;
    }

    // String to store each line in
    struct Racer {
        string name;
        int hours;
        int minutes;
        int seconds;
    };

    string line;
    vector<Racer> data;

    while (getline(file, line)) {
        Racer racer;
        vector<string> tokens = split(line);
        racer.name = tokens[0];
        racer.hours = stoi(tokens[1]);
        racer.minutes = stoi(tokens[2]);
        racer.seconds = stoi(tokens[3]);
        data.push_back(racer);
    }

    sort(data.begin(), data.end(), 
         [](Racer a, Racer b){
            int a_total = a.hours * 60 * 60 + a.minutes * 60 + a.seconds;
            int b_total = b.hours * 60 * 60 + b.minutes * 60 + b.seconds;
            return a_total > b_total;
         });

    for (Racer racer : data) {
        int total = racer.hours * 60 * 60 + racer.minutes * 60 + racer.seconds;
        cout << total << endl;
    }

    file.close();
}
