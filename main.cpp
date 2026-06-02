#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ITEMS = 20;
const double TAX_RATE = 0.21;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int& menuCount) {
    ifstream file("menu.txt");

    if (!file) {
        cout << "Klaida: nepavyko atidaryti menu.txt failo." << endl;
        return;
    }

    menuCount = 0;

    while (menuCount < MAX_ITEMS) {
        string line;

        if (!getline(file, line))
            break;

        size_t pos = line.find_last_of(' ');

        if (pos == string::npos)
            continue;

        menuList[menuCount].menuItem = line.substr(0, pos);
        menuList[menuCount].menuPrice = stod(line.substr(pos + 1));

        menuCount++;
    }

    file.close();
}

void showMenu(menuItemType menuList[], int menuCount) {
    cout << fixed << setprecision(2);

    cout << "\nPUSRYCIU MENIU\n" << endl;

    for (int i = 0; i < menuCount; i++) {
        cout << setw(2) << i + 1 << ". "
             << left << setw(45) << menuList[i].menuItem
             << right << menuList[i].menuPrice << " EUR" << endl;
    }

    cout << "\nPasirinkite patiekalo numeri ir porciju kieki." << endl;
    cout << "Baigti uzsakyma - iveskite 0.\n" << endl;
}

void printCheck(menuItemType menuList[], int quantities[], int menuCount) {
    ofstream receipt("receipt.txt");

    double subtotal = 0;

    cout << fixed << setprecision(2);
    receipt << fixed << setprecision(2);

    cout << "\nSveiki atvyke i restorana \"Skanaus\"\n" << endl;
    receipt << "Sveiki atvyke i restorana \"Pavadinimas\"\n" << endl;

    for (int i = 0; i < menuCount; i++) {
        if (quantities[i] > 0) {
            double itemTotal = quantities[i] * menuList[i].menuPrice;
            subtotal += itemTotal;

            cout << quantities[i] << "  "
                 << left << setw(45) << menuList[i].menuItem
                 << right << itemTotal << " EUR" << endl;

            receipt << quantities[i] << "  "
                    << left << setw(45) << menuList[i].menuItem
                    << right << itemTotal << " EUR" << endl;
        }
    }

    double tax = subtotal * TAX_RATE;
    double total = subtotal + tax;

    cout << "\nMokesciai (21%)"
         << setw(39) << tax << " EUR" << endl;

    cout << "Galutine suma"
         << setw(41) << total << " EUR" << endl;

    receipt << "\nMokesciai (21%)"
            << setw(39) << tax << " EUR" << endl;

    receipt << "Galutine suma"
            << setw(41) << total << " EUR" << endl;

    receipt.close();
}

int main() {
    menuItemType menuList[MAX_ITEMS];
    int quantities[MAX_ITEMS] = {0};
    int menuCount = 0;

    getData(menuList, menuCount);

    if (menuCount == 0) {
        cout << "Meniu tuscias arba nepavyko jo nuskaityti." << endl;
        return 1;
    }

    showMenu(menuList, menuCount);

    int choice, quantity;

    while (true) {
        cout << "Iveskite patiekalo numeri: ";
        cin >> choice;

        if (choice == 0)
            break;

        if (choice < 1 || choice > menuCount) {
            cout << "Tokio patiekalo nera. Bandykite dar karta." << endl;
            continue;
        }

        cout << "Iveskite porciju kieki: ";
        cin >> quantity;

        if (quantity <= 0) {
            cout << "Porciju kiekis turi buti teigiamas." << endl;
            continue;
        }

        quantities[choice - 1] += quantity;
    }

    printCheck(menuList, quantities, menuCount);

    cout << "\nSaskaita issaugota faile receipt.txt" << endl;

    return 0;
}