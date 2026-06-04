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


void iterpimoRikiavimas(vector<int>& masyvas,
                        Statistika& statistika)
{
    int dydis = masyvas.size();

    for (int i = 1; i < dydis; i++)
    {
        int raktas = masyvas[i];
        int j = i - 1;

        while (j >= 0)
        {
            statistika.palyginimai++;

            if (masyvas[j] > raktas)
            {
                masyvas[j + 1] = masyvas[j];
                statistika.sukeitimai++;
                j--;
            }
            else
            {
                break;
            }
        }

        masyvas[j + 1] = raktas;
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
    {
        kairePuse[i] = masyvas[kaire + i];
    }

    for (int i = 0; i < desiniojoDydis; i++)
    {
        desinePuse[i] = masyvas[vidurys + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = kaire;

    while (i < kairiojoDydis && j < desiniojoDydis)
    {
        statistika.palyginimai++;

        if (kairePuse[i] <= desinePuse[j])
        {
            masyvas[k] = kairePuse[i];
            i++;
        }
        else
        {
            masyvas[k] = desinePuse[j];
            j++;
        }

        statistika.sukeitimai++;
        k++;
    }

    while (i < kairiojoDydis)
    {
        masyvas[k] = kairePuse[i];
        i++;
        k++;

        statistika.sukeitimai++;
    }

    while (j < desiniojoDydis)
    {
        masyvas[k] = desinePuse[j];
        j++;
        k++;

        statistika.sukeitimai++;
    }
}



void suliejimoRikiavimas(vector<int>& masyvas,
                         int kaire,
                         int desine,
                         Statistika& statistika)
{
    if (kaire < desine)
    {
        int vidurys = kaire + (desine - kaire) / 2;

        suliejimoRikiavimas(masyvas,
                            kaire,
                            vidurys,
                            statistika);

        suliejimoRikiavimas(masyvas,
                            vidurys + 1,
                            desine,
                            statistika);

        suliejimas(masyvas,
                   kaire,
                   vidurys,
                   desine,
                   statistika);
    }
}



vector<int> generuotiAtsitiktiniusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    random_device atsitiktinisIrenginys;
    mt19937 generatorius(atsitiktinisIrenginys());

    uniform_int_distribution<> paskirstymas(1, 1000000);

    for (int i = 0; i < dydis; i++)
    {
        duomenys[i] = paskirstymas(generatorius);
    }

    return duomenys;
}

vector<int> generuotiSurikiuotusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    for (int i = 0; i < dydis; i++)
    {
        duomenys[i] = i + 1;
    }

    return duomenys;
}

vector<int> generuotiAtvirkstiniusDuomenis(int dydis)
{
    vector<int> duomenys(dydis);

    for (int i = 0; i < dydis; i++)
    {
        duomenys[i] = dydis - i;
    }

    return duomenys;
}



Statistika vykdytiIterpimoRikiavima(vector<int> duomenys)
{
    Statistika statistika;

    auto pradzia = high_resolution_clock::now();

    iterpimoRikiavimas(duomenys, statistika);

    auto pabaiga = high_resolution_clock::now();

    statistika.laikasMikrosekundemis =
        duration_cast<microseconds>
        (pabaiga - pradzia).count();

    return statistika;
}



Statistika vykdytiSuliejimoRikiavima(vector<int> duomenys)
{
    Statistika statistika;

    auto pradzia = high_resolution_clock::now();

    suliejimoRikiavimas(
        duomenys,
        0,
        duomenys.size() - 1,
        statistika);

    auto pabaiga = high_resolution_clock::now();

    statistika.laikasMikrosekundemis =
        duration_cast<microseconds>
        (pabaiga - pradzia).count();

    return statistika;
}



Statistika skaiciuotiVidurki(
    const vector<Statistika>& rezultatai)
{
    Statistika vidurkis;

    for (const auto& rezultatas : rezultatai)
    {
        vidurkis.palyginimai += rezultatas.palyginimai;
        vidurkis.sukeitimai += rezultatas.sukeitimai;
        vidurkis.laikasMikrosekundemis +=
            rezultatas.laikasMikrosekundemis;
    }

    vidurkis.palyginimai /= rezultatai.size();
    vidurkis.sukeitimai /= rezultatai.size();
    vidurkis.laikasMikrosekundemis /=
        rezultatai.size();

    return vidurkis;
}



void vykdytiTesta(const vector<int>& pradinisMasyvas,
                  const string& duomenuTipas)
{
    vector<Statistika> iterpimoRezultatai;
    vector<Statistika> suliejimoRezultatai;

    for (int i = 0; i < 5; i++)
    {
        iterpimoRezultatai.push_back(
            vykdytiIterpimoRikiavima(pradinisMasyvas));

        suliejimoRezultatai.push_back(
            vykdytiSuliejimoRikiavima(pradinisMasyvas));
    }

    Statistika iterpimoVidurkis =
        skaiciuotiVidurki(iterpimoRezultatai);

    Statistika suliejimoVidurkis =
        skaiciuotiVidurki(suliejimoRezultatai);

    cout << duomenuTipas << endl;
 

    cout << left
         << setw(20) << "Algoritmas"
         << setw(20) << "Laikas"
         << setw(20) << "Palyginimai"
         << setw(20) << "Sukeitimai"
         << endl;

    cout << left
         << setw(20) << "Iterpimo"
         << setw(20) << iterpimoVidurkis.laikasMikrosekundemis
         << setw(20) << iterpimoVidurkis.palyginimai
         << setw(20) << iterpimoVidurkis.sukeitimai
         << endl;

    cout << left
         << setw(20) << "Suliejimo"
         << setw(20) << suliejimoVidurkis.laikasMikrosekundemis
         << setw(20) << suliejimoVidurkis.palyginimai
         << setw(20) << suliejimoVidurkis.sukeitimai
         << endl;
}



int main()
{
    vector<int> dydziai =
    {
        5000,
        10000,
        50000
    };

    cout << fixed << setprecision(2);

    for (int dydis : dydziai)
    {
        cout << "\n\n";
        cout << "Duomenu kiekis: " << dydis << endl;
  

        vector<int> atsitiktiniaiDuomenys =
            generuotiAtsitiktiniusDuomenis(dydis);

        vector<int> surikiuotiDuomenys =
            generuotiSurikiuotusDuomenis(dydis);

        vector<int> atvirkstiniaiDuomenys =
            generuotiAtvirkstiniusDuomenis(dydis);

        vykdytiTesta(
            atsitiktiniaiDuomenys,
            "Atsitiktiniai duomenys");

        vykdytiTesta(
            atvirkstiniaiDuomenys,
            "Atvirksciai surikiuoti duomenys");

        vykdytiTesta(
            surikiuotiDuomenys,
            "Jau surikiuoti duomenys");
    }

    return 0;
}