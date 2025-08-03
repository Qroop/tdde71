#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
	int i;
	float f;
	string s;
	stringstream iss;

	cout << "Skriv in ett heltal: " << flush;
	cin >> i;
	while (cin.get() != '\n')
	;
	cout << "Du skrev in talet: " << i << "\n" << endl;

	cout << "Skriv in fem decimaltal: " << flush;
	getline(cin, s);
	cout << "Du skrev in talen: ";
	iss.clear();
	iss.str(s);
	for (i = 0; i < 5 && iss >> f; ++i) {
	cout << f << " ";
	}
	cout << "\n\n" << flush;

	cout << "Skriv in ett heltal och ett flyttal: " << flush;
	cin >> i >> f;
	while (cin.get() != '\n');
	cout << flush;
	cout << setprecision(5);
	cout << fixed;
	cout << setw(15) << left
	   << "Du skrev in heltalet:" << setw(11) << right << i << "\n";
	cout << setw(15) << left << "Du skrev in flyttalet:" << setw(10) << right << f
	   << "\n\n";

	cout << "Skriv in ett flyttal och ett heltal: " << flush;
	cin >> f >> i;
	while (cin.get() != '\n');
	cout << flush;
	cout << setprecision(4);
	cout << setw(15) << setfill('-') << left
	   << "Du skrev in heltalet:" << setw(11) << right << i << "\n";
	cout << setw(15) << left << "Du skrev in flyttalet:" << setw(10) << right << f
	   << "\n\n";

	cout << "Skriv in ett tecken: " << flush;
	cin >> s;
	while (cin.get() != '\n');
	cout << "Du skrev in tecknet: " << s[0] << "\n\n";


	cout << "Skriv in ett ord: ";
	cin >> s;
	while (cin.get() != '\n');
	cout << "Du skrev in ordet: " << s << "\n\n" << flush;


	cout << "Skriv in ett heltal och ett ord: " << flush;
	cin >> i >> s;
	while (cin.get() != '\n');
	cout << "Du skrev in talet |" << i << "| och ordet |" << s << "|.\n\n";

	iss.clear();
	iss.str(s);
	cout << "Skriv in ett tecken och ett ord:  " << flush;
	iss >> s;
	cout << "Du skrev in \"" << s.substr(0) << "\" och '" << s[0] << "'\n\n";

	cout << "Skrev in en rad text: " << flush;
	getline(cin, s);
	cout << "Du skrev in: \"" << s << "\"\n\n";

	cout << "Skrev in en till rad text: " << flush;
	getline(cin, s);
	cout << "Du skrev in: \"" << s << "\"\n\n";

	cout << "Skriv in tre ord:  " << flush;
	iss.clear();
	iss.str(s);
	iss >> s;
	cout << "Du skrev in: \"" << s << "\", \"";
	iss >> s;
	cout << s << "\" och \"";
	iss >> s;
	cout << s << "\"\n\n";

	return 0;
}
