#include "../inc/Plansza.h"


Plansza::Plansza(int rozmiarPlanszy, int iloscElemSekwencji)
{
    m_iloscElemSekwencji = iloscElemSekwencji;
    if (m_iloscElemSekwencji > rozmiarPlanszy)
    {
        std::cerr << "Blad! Nieodpowiednia sekwencja elementow!" << std::endl;
        do
        {
            std::cin >> m_iloscElemSekwencji;
        }
        while (m_iloscElemSekwencji > rozmiarPlanszy);
    }

    m_rozmiarPlanszy = rozmiarPlanszy;
    m_plansza = new char* [rozmiarPlanszy];
    for (int i = 0; i < rozmiarPlanszy; ++i)
    {
        m_plansza[i] = new char [rozmiarPlanszy];
        for (int j = 0; j < rozmiarPlanszy; ++j)
        {
            m_plansza[i][j] = '-';
        }
    }
}

Plansza::Plansza(const Plansza &plansza)
{
    m_rozmiarPlanszy = plansza.m_rozmiarPlanszy;
    m_plansza = new char* [m_rozmiarPlanszy];
    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        m_plansza[i] = new char [m_rozmiarPlanszy];
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            m_plansza[i][j] = plansza.m_plansza[i][j];
        }
    }
    m_iloscElemSekwencji = plansza.m_iloscElemSekwencji;
}

Plansza::~Plansza()
{
    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        delete [] m_plansza[i];
    }
    delete [] m_plansza;
}

void Plansza::wyswietlPlansze() const
{
    for (int i = 1; i <= m_rozmiarPlanszy; ++i)
    {
        std::cout << "\t" << i;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        std::cout << i+1;
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            std::cout << "\t" << m_plansza[i][j];
        }
        std::cout << std::endl << std::endl;
    }
}

bool Plansza::dodajKolko(int wspolrzedna_1, int wspolrzedna_2)
{
    if (wspolrzedna_1 > m_rozmiarPlanszy || wspolrzedna_2 > m_rozmiarPlanszy)
    {
        return false;
    }
    else
    {
        if (!this->czyMiejsceJestZajete(wspolrzedna_1,wspolrzedna_2))
        {
            m_plansza[wspolrzedna_1-1][wspolrzedna_2-1] = 'O';
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Plansza::dodajKrzyzyk(int wspolrzedna_1, int wspolrzedna_2)
{
    if (wspolrzedna_1 > m_rozmiarPlanszy || wspolrzedna_2 > m_rozmiarPlanszy)
    {
        return false;
    }
    else
    {
        if (!this->czyMiejsceJestZajete(wspolrzedna_1, wspolrzedna_2))
        {
            m_plansza[wspolrzedna_1 - 1][wspolrzedna_2 - 1] = 'X';
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool Plansza::czyMiejsceJestZajete(int wspolrzedna_1, int wspolrzedna_2) const
{
    if (m_plansza[wspolrzedna_1-1][wspolrzedna_2-1] == '-')
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Plansza::czyPlanszaJestZapelniona() const
{
    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            if (m_plansza[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

bool Plansza::czyJestSekwencjaWPionie(ZNAK znak) const
{
    char sprawdzanyZnak;
    if (znak == ZNAK::KOLKO)
    {
        sprawdzanyZnak = 'O';
    }
    if (znak == ZNAK::KRZYZYK)
    {
        sprawdzanyZnak = 'X';
    }

    //Od tego wiersza nie będzie już sprawdzane, czy wystepuje sekwencja znaków
    int indeksOstatniegoSprawdzanegoWiersza = m_rozmiarPlanszy - m_iloscElemSekwencji;

    //W przeszukiwaniu pionowym, indeks i przechodzi przez wiersze, j przez kolumny
    for (int i = 0; i <= indeksOstatniegoSprawdzanegoWiersza; ++i)
    {
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            int it = i;
            char elementPlanszy = m_plansza[i][j];
            if (elementPlanszy == sprawdzanyZnak)
            {
                char kolejnaPozycja = m_plansza[++it][j];
                int k = 1;
                while (k < m_iloscElemSekwencji && kolejnaPozycja == elementPlanszy)
                {
                    if (k == m_iloscElemSekwencji-1)
                    {
                        return true;
                    }
                    kolejnaPozycja = m_plansza[++it][j];
                    ++k;
                }
            }
        }
    }
    return false;
}

bool Plansza::czyJestSekwencjaWPoziomie(ZNAK znak) const
{
    char sprawdzanyZnak;
    if (znak == ZNAK::KOLKO)
    {
        sprawdzanyZnak = 'O';
    }
    if (znak == ZNAK::KRZYZYK)
    {
        sprawdzanyZnak = 'X';
    }

    //Od tej kolumny nie będzie już sprawdzane, czy wystepuje sekwencja znaków
    int indeksOstatniejSprawdzanejKolumny = m_rozmiarPlanszy - m_iloscElemSekwencji;

    //W przeszukiwaniu poziomym, indeks i przechodzi przez kolumny, j przez wiersze
    for (int i = 0; i <= indeksOstatniejSprawdzanejKolumny; ++i)
    {
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            int it = i;
            char elementPlanszy = m_plansza[j][i];
            if (elementPlanszy == sprawdzanyZnak)
            {
                char kolejnaPozycja = m_plansza[j][++it];
                int k = 1;
                while (k < m_iloscElemSekwencji && kolejnaPozycja == elementPlanszy)
                {
                    if (k == m_iloscElemSekwencji-1)
                    {
                        return true;
                    }
                    kolejnaPozycja = m_plansza[j][++it];
                    ++k;
                }
            }
        }
    }
    return false;
}

bool Plansza::czyJestSekwencjaNaUkos(ZNAK znak) const
{
    char sprawdzanyZnak;
    if (znak == ZNAK::KOLKO)
    {
        sprawdzanyZnak = 'O';
    }
    if (znak == ZNAK::KRZYZYK)
    {
        sprawdzanyZnak = 'X';
    }

    //Zmienna wyznacza zakres sprawdzania indeksu kolumny i wiersza
    int indeksSprawdzaniaIndeksow = m_rozmiarPlanszy - m_iloscElemSekwencji;

    //W przeszukiwaniu poziomym, indeks i przechodzi przez kolumny, j przez wiersze
    for (int i = 0; i <= indeksSprawdzaniaIndeksow; ++i)
    {
        for (int j = 0; j <= indeksSprawdzaniaIndeksow; ++j)
        {
            int it_wierszy = i;
            int it_kolumn = j;
            char elementPlanszy = m_plansza[i][j];
            if (elementPlanszy == sprawdzanyZnak)
            {
                char kolejnaPozycja = m_plansza[++it_wierszy][++it_kolumn];
                int k = 1;
                while (k < m_iloscElemSekwencji && kolejnaPozycja == elementPlanszy)
                {
                    if (k == m_iloscElemSekwencji-1)
                    {
                        return true;
                    }
                    kolejnaPozycja = m_plansza[++it_wierszy][++it_kolumn];
                    ++k;
                }
            }
        }
    }

    //W przeszukiwaniu poziomym, indeks i przechodzi przez kolumny, j przez wiersze
    for (int i = 0; i <= m_rozmiarPlanszy-m_iloscElemSekwencji; ++i)
    {
        for (int j = m_rozmiarPlanszy-1; j >= m_iloscElemSekwencji-1; --j)
        {
            int it_wierszy = i;
            int it_kolumn = j;
            char elementPlanszy = m_plansza[i][j];
            if (elementPlanszy == sprawdzanyZnak)
            {
                char kolejnaPozycja = m_plansza[++it_wierszy][--it_kolumn];
                int k = 1;
                while (k < m_iloscElemSekwencji && kolejnaPozycja == elementPlanszy)
                {
                    if (k == m_iloscElemSekwencji-1)
                    {
                        return true;
                    }
                    kolejnaPozycja = m_plansza[++it_wierszy][--it_kolumn];
                    ++k;
                }
            }
        }
    }
    return false;
}

void Plansza::wyszyscPlansze()
{
    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            m_plansza[i][j] = '-';
        }
    }
}

bool Plansza::czyJestSekwencjaWygrywajaca(ZNAK znak) const
{
    if (this->czyJestSekwencjaWPionie(znak) ||
        this->czyJestSekwencjaWPoziomie(znak) ||
        this->czyJestSekwencjaNaUkos(znak))
    {
       return true;
    }
    else
    {
        return false;
    }
}

void Plansza::wyczyscPolePlanszy(int indeksWiersza, int indeksKolumny) const
{
    if (this->czyMiejsceJestZajete(indeksWiersza, indeksKolumny))
    {
        m_plansza[indeksWiersza-1][indeksKolumny-1] = '-';
    }
}

Lista Plansza::generujListeRuchow() const
{
    Lista listaRuchow;
    for (int i = 0; i < m_rozmiarPlanszy; ++i)
    {
        for (int j = 0; j < m_rozmiarPlanszy; ++j)
        {
            if (!this->czyMiejsceJestZajete(i+1,j+1))
            {
                ruchNaPlanszy ruch = {i+1,j+1};
                listaRuchow.push_back(ruch);
            }
        }
    }
    return listaRuchow;
}

bool Plansza::czyMiejsceJestNaPlanszy(int indeksWiersza, int indeksKolumny) const
{
    if (indeksWiersza > m_rozmiarPlanszy || indeksKolumny > m_rozmiarPlanszy)
    {
        return false;
    }
    return true;
}