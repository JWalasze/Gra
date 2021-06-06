#include "../inc/Gra.h"


Gra::Gra() : m_planszaDoGry()
{
    this->ustawPoziomTrudnosci(POZIOM_TRUDNOSCI::SREDNI);
    m_ktoRozpoczynaGre = TYP_GRACZA::GRACZ;
    m_znakGracza = ZNAK::KOLKO;
    m_znakKomputera = ZNAK::KRZYZYK;
}

Gra::Gra(const Plansza &plansza, POZIOM_TRUDNOSCI poziomKomputera, TYP_GRACZA ktoRozpoczyna) : m_planszaDoGry(plansza)
{
    this->ustawPoziomTrudnosci(poziomKomputera);
    m_ktoRozpoczynaGre = ktoRozpoczyna;
    if (m_ktoRozpoczynaGre == TYP_GRACZA::GRACZ)
    {
        m_znakGracza = ZNAK::KOLKO;
        m_znakKomputera = ZNAK::KRZYZYK;
    }
    else
    {
        m_znakGracza = ZNAK::KRZYZYK;
        m_znakKomputera = ZNAK::KOLKO;
    }
}

void Gra::cofnijRuch(ruchNaPlanszy ruch)
{
    m_planszaDoGry.wyczyscPolePlanszy(ruch.indeksWiersza, ruch.indeksKolumny);
}

void Gra::wykonajRuch(ruchNaPlanszy ruch, ZNAK znak)
{
    if (znak == ZNAK::KOLKO)
    {
        m_planszaDoGry.dodajKolko(ruch.indeksWiersza, ruch.indeksKolumny);
    }
    else if (znak == ZNAK::KRZYZYK)
    {
        m_planszaDoGry.dodajKrzyzyk(ruch.indeksWiersza, ruch.indeksKolumny);
    }
}

int Gra::dokonajOcenyPlanszy() const
{
    if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO))
    {
        return 1;
    }
    else if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int dokonajOcenyPlanszy(const Plansza &plansza)
{
    if (plansza.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO))
    {
        return 1;
    }
    else if (plansza.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void Gra::ustawPoziomTrudnosci(POZIOM_TRUDNOSCI poziomTrudnosci)
{
    int tablicaPoziomow[] = {1,2,5};
    if (poziomTrudnosci == POZIOM_TRUDNOSCI::LATWY)
    {
        m_poziomTrudnosci = poziomTrudnosci;
        m_maksymalnaGlebokosc = tablicaPoziomow[0];
        return;
    }
    if (poziomTrudnosci == POZIOM_TRUDNOSCI::SREDNI)
    {
        m_poziomTrudnosci = poziomTrudnosci;
        m_maksymalnaGlebokosc = tablicaPoziomow[1];
        return;
    }
    if (poziomTrudnosci == POZIOM_TRUDNOSCI::TRUDNY)
    {
        m_poziomTrudnosci = poziomTrudnosci;
        m_maksymalnaGlebokosc = tablicaPoziomow[2];
        return;
    }
}

int Gra::minimax(int glebokosc, ZNAK czyjaKolej)
{
    if (glebokosc == 0 || this->czyKoniecGry())
    {
        if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO))
        {
            return this->dokonajOcenyPlanszy()+glebokosc;
        }
        if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK))
        {
            return this->dokonajOcenyPlanszy()-glebokosc;
        }
        return this->dokonajOcenyPlanszy();
    }

    if (czyjaKolej == ZNAK::KOLKO)
    {
        int maksymalnaOcena = -2147483647;

        Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
        auto* current = new ListNode;
        current = listaMozliwychRuchow.get_head();

        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KOLKO);
            int aktualnaOcena = minimax(glebokosc-1, ZNAK::KRZYZYK);
            maksymalnaOcena = std::max(maksymalnaOcena, aktualnaOcena);
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
        delete current;
        return maksymalnaOcena;
    }

    else
    {
        int minimalnaOcena = 2147483647;

        Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
        auto* current = new ListNode;
        current = listaMozliwychRuchow.get_head();

        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KRZYZYK);
            int aktualnaOcena = minimax(glebokosc-1, ZNAK::KOLKO);
            minimalnaOcena = std::min(minimalnaOcena, aktualnaOcena);
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
        delete current;
        return minimalnaOcena;
    }
}

void Gra::wyswietlPlanszeGry() const
{
    m_planszaDoGry.wyswietlPlansze();
    std::cout << std::endl;
}

ruchNaPlanszy Gra::znajdzNajlepszyRuch(ZNAK czyjRuch)
{
    int najlepszaOcena = -2147483647;
    int najgorszaOcena = 2147483647;
    Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
    auto* current = new ListNode;
    current = listaMozliwychRuchow.get_head();

    ruchNaPlanszy najlepszyAktualnyRuch = current->m_ruch;
    if (czyjRuch == ZNAK::KOLKO)
    {
        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KOLKO);
            int aktualnaOcena = minimax(m_maksymalnaGlebokosc, ZNAK::KRZYZYK);
            if (aktualnaOcena > najlepszaOcena)
            {
                najlepszaOcena = aktualnaOcena;
                najlepszyAktualnyRuch = current->m_ruch;
            }
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
    }
    else
    {
        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KRZYZYK);
            int aktualnaOcena = minimax(m_maksymalnaGlebokosc, ZNAK::KOLKO);
            if (aktualnaOcena < najgorszaOcena)
            {
                najgorszaOcena = aktualnaOcena;
                najlepszyAktualnyRuch = current->m_ruch;
            }
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
    }
    delete current;
    return najlepszyAktualnyRuch;
}

bool Gra::czyKoniecGry() const
{
    if ( m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK)
        || m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO)
        || m_planszaDoGry.czyPlanszaJestZapelniona())
    {
        return true;
    }
    return false;
}

void Gra::rozpocznijGre()
{
    this->wyswietlPlanszeGry();
    if (m_ktoRozpoczynaGre == TYP_GRACZA::GRACZ)
    {
        while (!this->czyKoniecGry())
        {
            int indeksWiersza, indeksKolumny;
            do
            {
                std::cout << "Indeks wiersza: ";
                std::cin >> indeksWiersza;
                std::cout  << std::endl << "Indeks kolumny: ";
                std::cin >> indeksKolumny;
                std::cout << std::endl;
            } while (!this->czyMoznaWykonacRuch(indeksWiersza,indeksKolumny));

            ruchNaPlanszy ruchGracza = {indeksWiersza, indeksKolumny};
            this->wykonajRuch(ruchGracza,ZNAK::KOLKO);

            this->wyswietlPlanszeGry();

            if (!this->czyKoniecGry())
            {
                ruchNaPlanszy ruchKomputera = this->znajdzNajlepszyRuchAlfaBeta(ZNAK::KRZYZYK);
                this->wykonajRuch(ruchKomputera,ZNAK::KRZYZYK);
                this->wyswietlPlanszeGry();
            }
        }
    }
    else
    {
        while (!this->czyKoniecGry())
        {
            ruchNaPlanszy ruchKomputera = this->znajdzNajlepszyRuchAlfaBeta(ZNAK::KOLKO);
            this->wykonajRuch(ruchKomputera,ZNAK::KOLKO);
            this->wyswietlPlanszeGry();

            if (!this->czyKoniecGry())
            {
                int indeksWiersza, indeksKolumny;
                do
                {
                    std::cout << "Indeks wiersza:";
                    std::cin >> indeksWiersza;
                    std::cout << std::endl << "Indeks kolumny:";
                    std::cin >> indeksKolumny;
                    std::cout << std::endl;
                } while (!this->czyMoznaWykonacRuch(indeksWiersza,indeksKolumny));

                ruchNaPlanszy ruchGracza = {indeksWiersza, indeksKolumny};
                this->wykonajRuch(ruchGracza,ZNAK::KRZYZYK);

                this->wyswietlPlanszeGry();
            }
        }
    }
    if (this->czyGraczWygrywa())
    {
        std::cout << "Gracz wygral z komputerem!" << std::endl;
    }
    else if (this->czyKomputerWygrywa())
    {
        std::cout << "Wygrala sztuczna inteligencja!" << std::endl;
    }
    else
    {
        std::cout << "Mamy remis :-|" << std::endl;
    }
}

int Gra::minimax(int glebokosc, ZNAK czyjaKolej, int alfa, int beta)
{
    if (glebokosc == 0 || this->czyKoniecGry())
    {
        if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO))
        {
            return this->dokonajOcenyPlanszy()+glebokosc;
        }
        if (m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK))
        {
            return this->dokonajOcenyPlanszy()-glebokosc;
        }
        return this->dokonajOcenyPlanszy();
    }

    if (czyjaKolej == ZNAK::KOLKO)
    {
        int maksymalnaOcena = -2147483647;

        Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
        auto* current = new ListNode;
        current = listaMozliwychRuchow.get_head();

        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KOLKO);
            int aktualnaOcena = minimax(glebokosc-1, ZNAK::KRZYZYK, alfa, beta);
            maksymalnaOcena = std::max(maksymalnaOcena, aktualnaOcena);
            alfa = std::max(alfa, maksymalnaOcena);
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
            if (beta <= alfa)
            {
                current = nullptr;
            }
        }
        delete current;
        return maksymalnaOcena;
    }

    else
    {
        int minimalnaOcena = 2147483647;

        Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
        auto* current = new ListNode;
        current = listaMozliwychRuchow.get_head();

        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KRZYZYK);
            int aktualnaOcena = minimax(glebokosc-1, ZNAK::KOLKO, alfa, beta);
            minimalnaOcena = std::min(minimalnaOcena, aktualnaOcena);
            beta = std::min(beta, minimalnaOcena);
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
            if (beta <= alfa)
            {
                current = nullptr;
            }
        }
        delete current;
        return minimalnaOcena;
    }
}

ruchNaPlanszy Gra::znajdzNajlepszyRuchAlfaBeta(ZNAK czyjRuch)
{
    int najlepszaOcena = -2147483647;
    int najgorszaOcena = 2147483647;
    Lista listaMozliwychRuchow = m_planszaDoGry.generujListeRuchow();
    auto* current = new ListNode;
    current = listaMozliwychRuchow.get_head();

    ruchNaPlanszy najlepszyAktualnyRuch = current->m_ruch;
    if (czyjRuch == ZNAK::KOLKO)
    {
        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KOLKO);
            int aktualnaOcena = minimax(m_maksymalnaGlebokosc, ZNAK::KRZYZYK,-2147483647,2147483647);
            if (aktualnaOcena > najlepszaOcena)
            {
                najlepszaOcena = aktualnaOcena;
                najlepszyAktualnyRuch = current->m_ruch;
            }
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
    }
    else
    {
        while (current != nullptr)
        {
            this->wykonajRuch(current->m_ruch,ZNAK::KRZYZYK);
            int aktualnaOcena = minimax(m_maksymalnaGlebokosc, ZNAK::KOLKO,-2147483647,2147483647);
            if (aktualnaOcena < najgorszaOcena)
            {
                najgorszaOcena = aktualnaOcena;
                najlepszyAktualnyRuch = current->m_ruch;
            }
            this->cofnijRuch(current->m_ruch);
            current = current->m_next;
        }
    }
    delete current;
    return najlepszyAktualnyRuch;
}

bool Gra::czyGraczWygrywa()
{
    if ((m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO) && m_znakGracza == ZNAK::KOLKO) ||
         m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK) && m_znakGracza == ZNAK::KRZYZYK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Gra::czyKomputerWygrywa()
{
    if ((m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KOLKO) && m_znakKomputera == ZNAK::KOLKO) ||
        m_planszaDoGry.czyJestSekwencjaWygrywajaca(ZNAK::KRZYZYK) && m_znakKomputera == ZNAK::KRZYZYK)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Gra::resetujGre()
{
    m_planszaDoGry.wyszyscPlansze();
}

void Gra::zmienGraczaRozpoczynajacego()
{
    if (m_ktoRozpoczynaGre == TYP_GRACZA::GRACZ)
    {
        m_ktoRozpoczynaGre = TYP_GRACZA::KOMPUTER;
        m_znakKomputera = ZNAK::KOLKO;
        m_znakGracza = ZNAK::KRZYZYK;
    }
    else
    {
        m_ktoRozpoczynaGre = TYP_GRACZA::GRACZ;
        m_znakKomputera = ZNAK::KRZYZYK;
        m_znakGracza = ZNAK::KOLKO;
    }
}

bool Gra::czyMoznaWykonacRuch(int indeksWiersza, int indeksKolumny) const
{
    if (!m_planszaDoGry.czyMiejsceJestZajete(indeksWiersza, indeksKolumny) &&
        m_planszaDoGry.czyMiejsceJestNaPlanszy(indeksWiersza, indeksKolumny))
    {
        return true;
    }
    std::cout << "Wybrane miejsce jest niepoprawne!" << std::endl;
    return false;
}
