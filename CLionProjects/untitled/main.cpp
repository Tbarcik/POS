#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;


vector<vector<bool>> vytvorSvet(int riadky, int stlpce, bool nahodne) {
vector<vector<bool>> svet(riadky, vector<bool>(stlpce, false));

    if (nahodne) {

        for (int i = 0; i < riadky; ++i) {
            for (int j = 0; j < stlpce; ++j) {
                svet[i][j] = rand() % 2 == 0;
            }
        }

    } else {

        cout << "Manuálne nastavenie farieb:" << endl;
        for (int i = 0; i < riadky; ++i) {
            for (int j = 0; j < stlpce; ++j) {
                char volba;
                cout << "Bunka [" << i << "][" << j << "]: Chcete čiernu farbu? (y/n): ";
                cin >> volba;
                svet[i][j] = (volba == 'y' || volba == 'Y');
            }
        }
    }

    return svet;
}


void vypisSvet(const vector<vector<bool>>& svet) {
    for (const auto& riadok : svet) {
        for (bool bunka : riadok) {
            cout << (bunka ? 'X' : '.');
        }
        cout << endl;
    }
}


void aktualizujSvet(vector<vector<bool>>& svet) {
    int riadky = svet.size();
    int stlpce = svet[0].size();

    vector<vector<bool>> novySvet(riadky, vector<bool>(stlpce, false));

    for (int i = 0; i < riadky; ++i) {
        for (int j = 0; j < stlpce; ++j) {
            int ziviSusedia = 0;

            // Kontrola okolitých buniek
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    if (x == 0 && y == 0) continue;
                    int ni = i + x;
                    int nj = j + y;

                    // Overnie či susedné bunky nevypadajú
                    if (ni >= 0 && ni < riadky && nj >= 0 && nj < stlpce) {
                        ziviSusedia += svet[ni][nj] ? 1 : 0;
                    }
                }
            }

            // Aplikácia pravidiel Game of Life
            if (svet[i][j]) {
                // Živá bunka
                if (ziviSusedia == 2 || ziviSusedia == 3) {
                    novySvet[i][j] = true;  // Prežitie
                } else {
                    novySvet[i][j] = false;  // Smrť
                }
            } else {
                // Mŕtva bunka
                if (ziviSusedia == 3) {
                    novySvet[i][j] = true;  // Oživenie
                } else {
                    novySvet[i][j] = false;
                }
            }
        }
    }


    svet = novySvet;
}


bool vyberSposobInicializacie() {
    char volba;
    cout << "Chcete náhodné generovanie farieb alebo manuálne nastavenie? n - nahodné nastavenie m -manuálne nastavanie   (n/m): ";
    cin >> volba;

    return (volba == 'n' || volba == 'N');
}

int main() {
    srand(time(NULL));

    int riadky = 10;
    int stlpce = 10;


    bool nahodne = vyberSposobInicializacie();

    // Vytvorenie sveta s vybraným spôsobom inicializácie
    vector<vector<bool>> svet = vytvorSvet(riadky, stlpce, nahodne);


    for (int krok = 0; krok < 10; ++krok) {
        // Výpis stavu sveta
        cout << "Krok " << krok << ":" << endl;
        vypisSvet(svet);

        aktualizujSvet(svet);

        sleep(1);
    }

    return 0;
}
