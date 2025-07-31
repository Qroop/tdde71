#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Racer {
	string name;
	int hours;
	int minutes;
	int seconds;

	Racer() : name(""), hours(0), minutes(0), seconds(0) {}
};

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

void printCentered(const std::string& text, int width) {
    int total_pad = width - text.size();
    int left_pad = total_pad / 2;
    int right_pad = total_pad - left_pad;

    if (total_pad > 0)
        std::cout << std::string(left_pad, ' ') << text << std::string(right_pad, ' ');
    else
        std::cout << text;
}

int main() {
	// Default file and rows
	string target_file = "UPPloppet_resultat.txt";
	size_t rows = 5;

	// cout << "Antal rader: " << target_file << endl;
	// getline(cin, target_file);
	// cout << "Antal rader: ";
	// cin >> rows;

	ifstream file(target_file);

	if (!file.is_open()) {
		cerr << "Failed to open file\n" << endl;
		return 1;
	}

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
	file.close();

	sort(data.begin(), data.end(), 
		[](Racer a, Racer b){
			int a_total = a.hours * 60 * 60 + a.minutes * 60 + a.seconds;
			int b_total = b.hours * 60 * 60 + b.minutes * 60 + b.seconds;
			return a_total < b_total;
		});

	printCentered("Namn", 10);
	cout << "|";
	printCentered("Tid", 10);
	cout << "\n" << setfill('=') << setw(20) << "" << "\n";
	for (size_t i = 0; i < rows && i < data.size(); ++i) {
		Racer& racer = data[i];
		cout << setfill(' ') << setw(9) << right << racer.name << " ";
		cout << "|";
		cout << setw(2) << racer.hours << ":"
			 << setfill('0') << setw(2) << racer.minutes << ":"
			 << setfill('0') << setw(2) << racer.seconds;
		cout << "\n";
	}
}
