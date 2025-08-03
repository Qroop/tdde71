#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  int i;
  float f;
  string s;

  cout << "Skriv in ett heltal: " << flush;
  cin >> i;
  while (cin.get() != '\n')
    ;
  cout << "Du skrev in talet: " << i << "\n" << endl;

  cout << "Skriv in fem decimaltal: " << flush;
  getline(cin, s);
  cout << "Du skrev in talen: ";
  istringstream iss(s);
  for (i = 0; i < 5 && iss >> f; ++i) {
    cout << f << " ";
  }
  cout << "\n\n" << flush;

  cout << "Skriv in ett heltal och ett flyttal: " << flush;
  cin >> i >> f;
  while (cin.get() != '\n')
    ;
  cout << "\n" << flush;

  cout << setprecision(4);
  cout << setw(15) << setfill('-') << left
       << "Du skrev in heltalet:" << setw(11) << right << i << "\n";
  cout << setw(15) << left << "Du skrev in flyttalet:" << setw(10) << right << f
       << "\n\n";

  cout << "Skriv in ett flyttal och ett heltal: " << flush;
  cin >> f >> i;
  while (cin.get() != '\n')
    ;
  cout << "Du skrev in heltalet: " << i << "\n";
  cout << "Du skrev in flyttalet: " << f << "\n";

  cout << "Skriv in ett tecken:  " << flush;
  // cin >> c;
  while (cin.get() != '\n')
    ;
  // cout << "Du skrev in tecknet: " << c << "\n";

  cout << "Skriv in ett ord: " << flush;
  cin >> s;
  while (cin.get() != '\n')
    ;
  cout << "Du skrev in ordet: " << s << "\n";

  cout << "Skriv in ett heltal och ett ord: " << flush;
  cin >> i >> s;
  while (cin.get() != '\n')
    ;
  cout << "Du skrev in talet " << i << " och ordet " << s << "\n";

  cout << "Skriv in ett tecken och ett ord:  " << flush;
  // cin >> c >> s;
  while (cin.get() != '\n')
    ;
  // cout << "Du skrev in " << c << " och " << s << "\n";

  cout << "Skrev in en rad text:  " << flush;
  getline(cin, s);
  cout << "Du skrev in: " << s << "\n";

  cout << "Skrev in en till rad text:  " << flush;
  getline(cin, s);
  cout << "Du skrev in: " << s << "\n";

  cout << "Skriv in tre ord:  " << flush;
  cin >> s;
  cout << s << " ";
  cin >> s;
  cout << s << " ";
  cin >> s;
  cout << s << "\n";
  while (cin.get() != '\n')
    ;

  return 0;
}
