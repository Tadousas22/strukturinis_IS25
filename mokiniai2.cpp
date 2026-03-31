#include <iostream>
using namespace std;

int main() {
    const int MAX_MOKINIU = 100;
    const int MAX_PAZYMIU = 10;

    string vardai[MAX_MOKINIU];
    int pazymiai[MAX_MOKINIU][MAX_PAZYMIU];
    int pazymiuKiekis[MAX_MOKINIU];

    int mokiniuKiekis = 0;
    int pasirinkimas;

    while (true) {
        cout << "\n1 - Pridėti\n2 - Rodyti visus\n3 - Rodyti vieną\n4 - Keisti pažymį\n5 - Pašalinti\n0 - Išeiti\n";
        cin >> pasirinkimas;

        if (pasirinkimas == 0) {
            break;
        }

        // PRIDETI
        if (pasirinkimas == 1) {
            cout << "Vardas: ";
            cin >> vardai[mokiniuKiekis];

            cout << "Kiek pažymių: ";
            cin >> pazymiuKiekis[mokiniuKiekis];

            for (int i = 0; i < pazymiuKiekis[mokiniuKiekis]; i++) {
                cout << "Pažymys: ";
                cin >> pazymiai[mokiniuKiekis][i];
            }

            mokiniuKiekis++;
        }

        // RODYTI VISUS
        if (pasirinkimas == 2) {
            for (int i = 0; i < mokiniuKiekis; i++) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < pazymiuKiekis[i]; j++) {
                    cout << pazymiai[i][j] << " ";
                }
                cout << endl;
            }
        }

        // RODYTI VIENA
        if (pasirinkimas == 3) {
            string vardas;
            cout << "Įvesk vardą: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    cout << vardai[i] << ": ";
                    for (int j = 0; j < pazymiuKiekis[i]; j++) {
                        cout << pazymiai[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }

        // KEISTI PAZYMI
        if (pasirinkimas == 4) {
            string vardas;
            cout << "Įvesk vardą: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    int nr;
                    cout << "Kelintas pažymys: ";
                    cin >> nr;

                    cout << "Naujas pažymys: ";
                    cin >> pazymiai[i][nr - 1];
                }
            }
        }

        // PASALINTI
        if (pasirinkimas == 5) {
            string vardas;
            cout << "Įvesk vardą: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    for (int j = i; j < mokiniuKiekis - 1; j++) {
                        vardai[j] = vardai[j + 1];
                        pazymiuKiekis[j] = pazymiuKiekis[j + 1];

                        for (int k = 0; k < MAX_PAZYMIU; k++) {
                            pazymiai[j][k] = pazymiai[j + 1][k];
                        }
                    }
                    mokiniuKiekis--;
                }
            }
        }
    }

    return 0;
}
