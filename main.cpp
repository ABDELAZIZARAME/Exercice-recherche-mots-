#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>   // std::find
#include <chrono>      // mesure du temps
using namespace std;

bool contientDansLOrdre(const string& mot1, const string& mot2) {
    auto it = mot1.begin();
    for (char c : mot2) {
        it = find(it, mot1.end(), c);
        if (it == mot1.end()) {
            return false;
        }
        ++it;
    }
    return true;
}

int main() {
    // 1. Ouverture du fichier
    ifstream fichier("mots.txt");
    if (!fichier.is_open()) {
        cerr << "Erreur : impossible d'ouvrir mots.txt" << endl;
        return 1;
    }

    // 2. Lecture des mots dans un vector
    vector<string> mots;
    string mot;
    while (fichier >> mot) {
        mots.push_back(mot);
    }
    fichier.close();
    cout << mots.size() << " mots charges." << endl;

    // 3. Saisie de la recherche
    string recherche;
    cout << "Lettres a chercher (dans l'ordre) : ";
    cin >> recherche;

    // 4. Filtrage CHRONOMETRE
    vector<string> resultats;

    auto debut = chrono::steady_clock::now();            // heure de départ

    for (const string& m : mots) {
        if (contientDansLOrdre(m, recherche)) {
            resultats.push_back(m);
        }
    }

    auto fin = chrono::steady_clock::now();              // heure de fin

    // 5. Calcul de la durée
    chrono::duration<double, milli> duree_ms = fin - debut;
    auto duree_us = chrono::duration_cast<chrono::microseconds>(fin - debut);

    // 6. Affichage
    cout << resultats.size() << " mot(s) trouve(s)." << endl;

    size_t limite = min<size_t>(resultats.size(), 20);   // on affiche 20 mots maximum
    for (size_t i = 0; i < limite; i++) {
        cout << " - " << resultats[i] << endl;
    }
    if (resultats.size() > limite) {
        cout << " ... (" << resultats.size() - limite << " autres)" << endl;
    }

    cout << "Temps de recherche : " << duree_ms.count() << " ms ("
         << duree_us.count() << " microsecondes)" << endl;

    return 0;
}