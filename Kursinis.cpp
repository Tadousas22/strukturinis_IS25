#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Statistika
{
    long long palyginimai = 0;
    long long sukeitimai = 0;
    double laikasMikrosekundemis = 0;
};


void selectionRikiavimas(vector<int>& masyvas, Statistika& statistika)
{
    int n = masyvas.size();

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            statistika.palyginimai++;

            if (masyvas[j] < masyvas[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            swap(masyvas[i], masyvas[minIndex]);
            statistika.sukeitimai++;
        }
    }
}



void suliejimas(vector<int>& masyvas,
                int kaire,
                int vidurys,
                int desine,
                Statistika& statistika)
{
    int kairiojoDydis = vidurys - kaire + 1;
    int desiniojoDydis = desine - vidurys;

    vector<int> kairePuse(kairiojoDydis);
    vector<int> desinePuse(desiniojoDydis);

    for (int i = 0; i < kairiojoDydis; i++)
        kairePuse[i] = masyvas[kaire + i];

    for (int i = 0; i < desiniojoDydis; i++)
        desinePuse[i] = masyvas[vidurys + 1 + i];

    int i = 0, j = 0, k = kaire;

    while (i < kairiojoDydis && j < desiniojoDydis)
    {
        statistika.palyginimai++;

        if (kairePuse[i] <= desinePuse[j])
            masyvas[k++] = kairePuse[i++];
        else
            masyvas[k++] = desinePuse[j++];

        statistika.sukeitimai++;
    }

    while (i < kairiojoDydis)
    {
        masyvas[k++] = kairePuse[i++];
        statistika.sukeitimai++;
    }

    while (j < desiniojoDydis)
    {
        masyvas[k++] = desinePuse[j++];
        statistika.sukeitimai++;
    }
}

void mergeRikiavimas(vector<int>& masyvas,
                     int kaire,
                     int desine,
                     Statistika& statistika)
{
    if (kaire < desine)
    {
        int vidurys = kaire + (desine - kaire) / 2;

        mergeRikiavimas(masyvas, kaire, vidurys, statistika);
        mergeRikiavimas(masyvas, vidurys + 1, desine, statistika);

        suliejimas(masyvas, kaire, vidurys, desine, statistika);
    }
}



vector<int> generuotiAtsitiktiniusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    for (int i = 0; i < dydis; i++)
        duomenys[i] = dist(gen);

    return duomenys;
}

vector<int> generuotiSurikiuotusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    for (int i = 0; i < dydis; i++)
        duomenys[i] = i + 1;

    return duomenys;
}

vector<int> generuotiAtvirkstiniusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    for (int i = 0; i < dydis; i++)
        duomenys[i] = dydis - i;

    return duomenys;
}



Statistika vykdytiSelection(vector<int> duomenys)
{
    Statistika s;

    auto start = high_resolution_clock::now();

    selectionRikiavimas(duomenys, s);

    auto end = high_resolution_clock::now();

    s.laikasMikrosekundemis =
        duration_cast<microseconds>(end - start).count();

    return s;
}

Statistika vykdytiMerge(vector<int> duomenys)
{
    Statistika s;

    auto start = high_resolution_clock::now();

    mergeRikiavimas(duomenys, 0, duomenys.size() - 1, s);

    auto end = high_resolution_clock::now();

    s.laikasMikrosekundemis =
        duration_cast<microseconds>(end - start).count();

    return s;
}

Statistika skaiciuotiVidurki(const vector<Statistika>& rez)
{
    Statistika v;

    for (auto r : rez)
    {
        v.palyginimai += r.palyginimai;
        v.sukeitimai += r.sukeitimai;
        v.laikasMikrosekundemis += r.laikasMikrosekundemis;
    }

    v.palyginimai /= rez.size();
    v.sukeitimai /= rez.size();
    v.laikasMikrosekundemis /= rez.size();

    return v;
}

void vykdytiTesta(const vector<int>& duomenys, const string& tipas)
{
    vector<Statistika> selRez;
    vector<Statistika> mergeRez;

    for (int i = 0; i < 5; i++)
    {
        selRez.push_back(vykdytiSelection(duomenys));
        mergeRez.push_back(vykdytiMerge(duomenys));
    }

    Statistika sel = skaiciuotiVidurki(selRez);
    Statistika mer = skaiciuotiVidurki(mergeRez);

    cout << "\n" << tipas << endl;

    cout << left
         << setw(20) << "Algoritmas"
         << setw(20) << "Laikas"
         << setw(20) << "Palyginimai"
         << setw(20) << "Sukeitimai"
         << endl;

    cout << left
         << setw(20) << "Selection"
         << setw(20) << sel.laikasMikrosekundemis
         << setw(20) << sel.palyginimai
         << setw(20) << sel.sukeitimai
         << endl;

    cout << left
         << setw(20) << "Merge"
         << setw(20) << mer.laikasMikrosekundemis
         << setw(20) << mer.palyginimai
         << setw(20) << mer.sukeitimai
         << endl;
}



int main()
{
    vector<int> dydziai = {5000, 10000, 50000};

    cout << fixed << setprecision(2);

    for (int dydis : dydziai)
    {
        cout << "\n============================\n";
        cout << "Dydis: " << dydis << endl;

        auto ats = generuotiAtsitiktiniusDuomenis(dydis);
        auto sur = generuotiSurikiuotusDuomenis(dydis);
        auto atm = generuotiAtvirkstiniusDuomenis(dydis);

        vykdytiTesta(ats, "Atsitiktiniai duomenys");
        vykdytiTesta(atm, "Atvirksciai surikiuoti");
        vykdytiTesta(sur, "Jau surikiuoti");
    }

    return 0;
}
