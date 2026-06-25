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
        cout << "\n1 - Prideti\n2 - Rodyti visus\n3 - Rodyti viena\n4 - Keisti pazymi\n5 - Pasalinti\n0 - Iseiti\n";
        cin >> pasirinkimas;

        if (pasirinkimas == 0) {
            break;
        }

        if (pasirinkimas == 1) {
            if (mokiniuKiekis >= MAX_MOKINIU) {
                cout << "Maksimalus mokiniu skaicius pasiektas!\n";
                continue;
            }

            cout << "Vardas: ";
            cin >> vardai[mokiniuKiekis];

            do {
                cout << "Kiek pazymiu (1-10): ";
                cin >> pazymiuKiekis[mokiniuKiekis];

                if (pazymiuKiekis[mokiniuKiekis] < 1 ||
                    pazymiuKiekis[mokiniuKiekis] > MAX_PAZYMIU) {
                    cout << "Klaida! Galima ivesti nuo 1 iki 10 pazymiu.\n";
                }
            } while (pazymiuKiekis[mokiniuKiekis] < 1 ||
                     pazymiuKiekis[mokiniuKiekis] > MAX_PAZYMIU);

            for (int i = 0; i < pazymiuKiekis[mokiniuKiekis]; i++) {
                do {
                    cout << "Iveskite " << i + 1 << "-aji pazymi (1-10): ";
                    cin >> pazymiai[mokiniuKiekis][i];

                    if (pazymiai[mokiniuKiekis][i] < 1 ||
                        pazymiai[mokiniuKiekis][i] > 10) {
                        cout << "Klaida! Pazymys turi buti nuo 1 iki 10.\n";
                    }
                } while (pazymiai[mokiniuKiekis][i] < 1 ||
                         pazymiai[mokiniuKiekis][i] > 10);
            }

            mokiniuKiekis++;
        }

        if (pasirinkimas == 2) {
            for (int i = 0; i < mokiniuKiekis; i++) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < pazymiuKiekis[i]; j++) {
                    cout << pazymiai[i][j] << " ";
                }
                cout << endl;
            }
        }

        if (pasirinkimas == 3) {
            string vardas;
            cout << "Ivesk varda: ";
            cin >> vardas;

            bool rastas = false;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    cout << vardai[i] << ": ";
                    for (int j = 0; j < pazymiuKiekis[i]; j++) {
                        cout << pazymiai[i][j] << " ";
                    }
                    cout << endl;
                    rastas = true;
                }
            }

            if (!rastas) {
                cout << "Mokinys nerastas.\n";
            }
        }

        if (pasirinkimas == 4) {
            string vardas;
            cout << "Ivesk varda: ";
            cin >> vardas;

            bool rastas = false;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    rastas = true;

                    int nr;
                    cout << "Kelintas pazymys: ";
                    cin >> nr;

                    if (nr < 1 || nr > pazymiuKiekis[i]) {
                        cout << "Neteisingas pazymio numeris!\n";
                        break;
                    }

                    do {
                        cout << "Naujas pazymys (1-10): ";
                        cin >> pazymiai[i][nr - 1];

                        if (pazymiai[i][nr - 1] < 1 ||
                            pazymiai[i][nr - 1] > 10) {
                            cout << "Klaida! Pazymys turi buti nuo 1 iki 10.\n";
                        }
                    } while (pazymiai[i][nr - 1] < 1 ||
                             pazymiai[i][nr - 1] > 10);
                }
            }

            if (!rastas) {
                cout << "Mokinys nerastas.\n";
            }
        }

        if (pasirinkimas == 5) {
            string vardas;
            cout << "Ivesk varda: ";
            cin >> vardas;

            bool rastas = false;

            for (int i = 0; i < mokiniuKiekis; i++) {
                if (vardai[i] == vardas) {
                    rastas = true;

                    for (int j = i; j < mokiniuKiekis - 1; j++) {
                        vardai[j] = vardai[j + 1];
                        pazymiuKiekis[j] = pazymiuKiekis[j + 1];

                        for (int k = 0; k < MAX_PAZYMIU; k++) {
                            pazymiai[j][k] = pazymiai[j + 1][k];
                        }
                    }

                    mokiniuKiekis--;
                    cout << "Mokinys pasalintas.\n";
                    break;
                }
            }

            if (!rastas) {
                cout << "Mokinys nerastas.\n";
            }
        }
    }

    return 0;
}
