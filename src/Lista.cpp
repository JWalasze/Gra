#include "../inc/Lista.h"

Lista::Lista()
{
    m_head = nullptr;
    m_tail = nullptr;
}

Lista::~Lista()
{
    ListNode* q;
    while (m_head != nullptr)
    {
        q = m_head->m_next;
        delete m_head;
        m_head = q;
    }
    m_tail = nullptr;
    delete q;
}

Lista::Lista(ruchNaPlanszy ruch)
{
    auto* new_item = new ListNode;
    new_item->m_next = nullptr;
    new_item->m_ruch = ruch;
    m_head = new_item;
    m_tail = new_item;
}

void Lista::push_front(ruchNaPlanszy ruch)
{
    auto* new_item = new ListNode;
    new_item->m_next = m_head;
    new_item->m_ruch = ruch;
    if (m_head == nullptr)
    {
        m_tail = new_item;
    }
    m_head = new_item;
}

void Lista::push_back(ruchNaPlanszy ruch)
{
    auto* new_item = new ListNode;
    new_item->m_next = nullptr;
    new_item->m_ruch = ruch;
    if (m_head == nullptr)
    {
        m_head = new_item;
        m_tail = new_item;
    }
    else
    {
        m_tail->m_next = new_item;
        m_tail = new_item;
    }
}

void Lista::pop_front()
{
    if (this->is_empty())
    {
        std::cout << "Lista jest pusta" << std::endl;
    }
    else
    {
        ListNode* old_head = m_head;
        m_head = old_head->m_next;
        delete old_head;
    }
}

bool Lista::is_empty()
{
    if (m_head == nullptr)
    {
        return true;
    }
    return false;
}

void Lista::show_items()
{
    if (m_head == nullptr)
    {
        std::cout << " Lista jest pusta!" << std::endl;
    }
    else
    {
        auto* current = new ListNode;
        current = m_head;
        std::cout << " head";
        while (current != nullptr)
        {
            std::cout << " -> " << current->m_ruch.indeksWiersza << "-" << current->m_ruch.indeksKolumny;
            current = current->m_next;
        }
        std::cout << std::endl;
        delete current;
    }
}

ListNode* Lista::get_head()
{
    return m_head;
}

ListNode* Lista::get_tail()
{
    return m_tail;
}

void Lista::set_head(ListNode* elem)
{
    m_head = elem;
}

void Lista::set_tail(ListNode* elem)
{
    m_tail = elem;
}
