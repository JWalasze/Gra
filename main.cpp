#include "inc/Gra.h"


int main()
{
    Plansza plansza1(5,4);

    Gra pierwszaGra(plansza1, POZIOM_TRUDNOSCI::TRUDNY, TYP_GRACZA::GRACZ);

    char wybor;
    std::cout << "Wybierz opcje:" << std::endl;
    std::cout << "1. Rozpocznij gre" << std::endl;
    std::cout << "2. Zakoncz gre" << std::endl;
    std::cout << "3. Zmien poziom trudnosci" << std::endl;
    std::cout << "4. Zamien gracza, ktory zaczyna" <<std::endl;
    std::cout << "Twoj wybor:  ";
    std::cin >> wybor;
    std::cout << std::endl;
    while (wybor != '2')
    {
        switch (wybor)
        {
            case '1':
                pierwszaGra.resetujGre();
                pierwszaGra.rozpocznijGre();
                break;
            case '2':
                std::cout << "Koniec dzialania programu." << std::endl;
                break;
            case '3':
                char wybor2;
                std::cout << "1. Latwy" << std::endl;
                std::cout << "2. Sredni" << std::endl;
                std::cout << "3. Trudny" << std::endl;
                std::cout << "Twoj wybor:";
                std::cin >> wybor2;
                if (wybor2 == '1')
                {
                    pierwszaGra.ustawPoziomTrudnosci(POZIOM_TRUDNOSCI::LATWY);
                }
                else if (wybor2 == '2')
                {
                    pierwszaGra.ustawPoziomTrudnosci(POZIOM_TRUDNOSCI::SREDNI);
                }
                else if (wybor2 == '3')
                {
                    pierwszaGra.ustawPoziomTrudnosci(POZIOM_TRUDNOSCI::TRUDNY);
                }
                break;
            case '4':
                pierwszaGra.zmienGraczaRozpoczynajacego();
                break;
            default:
                std::cout << "Podaj poprawny numer opcji!" << std::endl << std::endl;
        }
        std::cout << std::endl << "Wybierz opcje:" << std::endl;
        std::cout << "1. Rozpocznij gre" << std::endl;
        std::cout << "2. Zakoncz gre" << std::endl;
        std::cout << "3. Zmien poziom trudnosci" << std::endl;
        std::cout << "4. Zamien gracza, ktory zaczyna" <<std::endl;
        std::cout << "Twoj wybor: ";
        std::cin >> wybor;
        std::cout << std::endl;
    }

    return 0;
}
