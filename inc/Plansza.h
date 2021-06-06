#ifndef PLANSZA_H
#define PLANSZA_H
#include <iostream>
#include "Lista.h"

//Klasa wyliczeniowa zawierający typy znaków, jakie mogą się pojawić na planszy
enum class ZNAK {KOLKO, KRZYZYK};

class Plansza
{
    //Dwuwymiarowa tablica typu 'char'
    char** m_plansza;

    //Długość krawędzi tablicy
    int m_rozmiarPlanszy;

    //Ilość elementów potrzebne do wygrania (w pionie, poziomie lub na ukos)
    int m_iloscElemSekwencji;
public:
    //Konstruktory i destruktor klasy
    Plansza() : Plansza(3,3){};
    Plansza(int rozmiarPlanszy, int iloscElemSekwencji);
    Plansza(const Plansza& plansza);
    ~Plansza();

    //Funkcja wyświetlająca aktualny stan planszy
    void wyswietlPlansze() const;

    //Dodaje znak kółko na plansze
    bool dodajKolko(int indeksWiersza, int indeksKolumny);

    //Dodaje znak krzyżyk na plansze
    bool dodajKrzyzyk(int indeksWiersza, int indeksKolumny);

    //Funckja sprawdza czy miejsce na planszy jest zajęte
    bool czyMiejsceJestZajete(int indeksWiersza, int indeksKolumny) const;

    //Funkcja sprawdza, czy nie ma już wolnych miejsc na planszy
    bool czyPlanszaJestZapelniona() const;

    //Funckja czyści plansze (wszystkie pola są puste)
    void wyszyscPlansze();

    //Funkcja czyści jedno, konkretne pole na planszy
    void wyczyscPolePlanszy(int indeksWiersza, int indeksKolumny) const;

    //Funkcja generuje i zwraca listę ruchów dostępnych na planszy
    Lista generujListeRuchow() const;

    //Funkcja sprawdza, czy jest sekwencja wygrywająca konkretnego znaku
    bool czyJestSekwencjaWygrywajaca(ZNAK znak) const;

    //Funkcje sprawdzające, czy są sekwencje - w pionie, w poziomie lub na ukos dla konkretnego znaku
    bool czyJestSekwencjaWPionie(ZNAK znak) const;
    bool czyJestSekwencjaWPoziomie(ZNAK znak) const;
    bool czyJestSekwencjaNaUkos(ZNAK znak) const;

    //Funkcja sprawdzająca czy wybrane miejsce leży na planszy
    bool czyMiejsceJestNaPlanszy(int indeksWiersza, int indeksKolumny) const;
};


#endif

