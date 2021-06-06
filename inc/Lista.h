#ifndef LISTA_H
#define LISTA_H
#include <iostream>

//Struktura reprezentująca ruch kółka lub krzyżyka na planszy
struct ruchNaPlanszy
{
    int indeksWiersza;
    int indeksKolumny;
};

//Struktura reprezentująca element listy
struct ListNode
{
    ruchNaPlanszy m_ruch;
    ListNode* m_next;
};

class Lista
{
    //Wskaźnik na pierwszy element (głowę) listy
    ListNode* m_head;

    //Wskaźnik na ostatni element listy (ogon)
    ListNode* m_tail;
public:
    //Konstruktor bezparametrowy
    Lista();

    //Destruktor
    ~Lista();

    //Konstruktor
    Lista(ruchNaPlanszy ruch);

    //Dodawanie elementu na początek listy
    void push_front(ruchNaPlanszy ruch);

    //Dodawanie elementu na koniec listy
    void push_back(ruchNaPlanszy ruch);

    //Usunięcie pierwszego elementu
    void pop_front();

    //Sprawdza, czy lista jest pusta
    bool is_empty();

    //Wypisuje elementy pojedynczej listy
    void show_items();

    //Getter zwracający wskaźnik na głowę listy
    ListNode* get_head();

    //Getter zwracający wskaźnik na ogon listy
    ListNode* get_tail();

    //Setter ustawiający nową głowę listy
    void set_head(ListNode* elem);

    //Setter ustawiający nowy ogon listy
    void set_tail(ListNode* elem);
};

#endif
