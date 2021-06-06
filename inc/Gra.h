#ifndef GRA_H
#define GRA_H
#include "Plansza.h"

//Klasa wyliczeniowa do definiowania typu gracza
enum class TYP_GRACZA {GRACZ, KOMPUTER};

//Klasa wyliczeniowa definiująca poziom trudności komputera
enum class POZIOM_TRUDNOSCI {LATWY, SREDNI, TRUDNY};

class Gra
{
    //Plansza do kółka i krzyżyk
    Plansza m_planszaDoGry;

    //Zmienna wskazująca, który gracz rozpoczyna grę
    TYP_GRACZA m_ktoRozpoczynaGre;

    //Typ znaku (kółko albo krzyżyk), który używa komputer
    ZNAK m_znakKomputera;

    //Typ znaku (kółko albo krzyżyk), który używa gracz
    ZNAK m_znakGracza;

    //Poziom trudności komputera
    POZIOM_TRUDNOSCI m_poziomTrudnosci;

    //Maksymalna głębokość wywołań minimax - ilość ruchów do przodu
    int m_maksymalnaGlebokosc;
public:
    //Konstruktory i destruktory klasy
    Gra();
    Gra(const Plansza& plansza, POZIOM_TRUDNOSCI poziomTrudnosci, TYP_GRACZA ktoRozpoczyna);
    ~Gra() = default;

    //Funkcja ocenia stan planszy: wygrywa kółko +1, wygrywa krzyżyk -1, remis 0
    int dokonajOcenyPlanszy() const;

    //Cofnięcie ruchu na planszy
    void cofnijRuch(ruchNaPlanszy ruch);

    //Wykonanie ruchu konkretnego znaku na planszy
    void wykonajRuch(ruchNaPlanszy ruch, ZNAK znak);

    //Funkcja ustawia poziom trudności
    void ustawPoziomTrudnosci(POZIOM_TRUDNOSCI poziom);

    //Funkcja zwracająca wartość najlepszego możliwego ruchu na planszy
    int minimax(int glebokosc, ZNAK czyjRuch);

    //Metoda minimax wzbogacona o algorytm minimax
    int minimax(int glebokosc, ZNAK czyjRuch, int alfa, int beta);

    //Metoda znajdująca najlepszy ruch na planszy dla konkretnego znaku
    ruchNaPlanszy znajdzNajlepszyRuch(ZNAK czyjRuch);

    //Metoda wykorzystująca minimax z cięciami alfa beta
    ruchNaPlanszy znajdzNajlepszyRuchAlfaBeta(ZNAK czyjRuch);

    //Metoda wyświetla planszę do gry
    void wyswietlPlanszeGry() const;

    //Resetowanie planszy do gry
    void resetujGre();

    //Metoda sprawdza, czy podane indeksy są poprawne
    bool czyMoznaWykonacRuch(int indeksWiersza, int indeksKolumny) const;

    //Metoda zamienia osobę rozpoczynającą grę
    void zmienGraczaRozpoczynajacego();

    //Metoda sprawdza, czy ktoś wygrał lub brakuje miejsca na planszy
    bool czyKoniecGry() const;

    //Metoda rozpoczynająca grę
    void rozpocznijGre();

    //Metoda sprawdzające, który gracz wygrywa - jest sekwencja wygrywająca jego znaków
    bool czyGraczWygrywa();
    bool czyKomputerWygrywa();
};

int dokonajOcenyPlanszy(const Plansza& plansza);

#endif
