#include <iostream>
using namespace std;

int main() {
    cout << "Skriv in ett heltal: ";
    int input;
    cin >> input;
    cout << "Du skrev in talet: " << input << "\n" << endl;

    // TODO: Add flush
    
    cout << "Skriv en fem decimaltal: ";
    float inputs[5];
    for(int i = 0; i < 5; i++) {
        cin >> inputs[i];
    }

    // TODO: Add flush

    cout << "Du skrev in talen: ";
    for(int i = 0; i < 5; i++) {
        cout << inputs[i] << " ";
    }
    cout << "\n";

    cout << "Skriv in ett heltal och ett flyttal: ";
    cout << "Du skrev in heltalet: ";
    cout << "Du skrev in flyttalet: ";

    cout << "Skriv in ett flyttal och ett heltal:  ";
    cout << "Du skrev in heltalet: ";
    cout << "Du skrev in flyttalet: ";

    cout << "Skriv in ett tecken:  ";
    cout << "Du skrev in tecknet: ";

    cout << "Skriv in ett ord: ";
    cout << "Du skrev in ordet: ";

    cout << "Skriv in ett heltal och ett ord: ";
    cout << "Du skrev in talet  och ordet ";

    cout << "Skriv in ett tecken och ett ord:  ";
    cout << "Du skrev in  och ";

    cout << "Skrev in en rad text:  ";
    cout << "Du skrev in:  ";

    cout << "Skrev in en till rad text:  ";
    cout << "Du skrev in: ";

    cout << "Skriv in tre ord:  ";
    cout << "Du skrev in: ";
}

