#include <iostream>
#include <string>
#include "DictionaryList.h"

// Тестирование словаря
void dictionaryTest()
{
    // Создание списка
    DictionaryList<int> dictInt;
    // bool insert(const KeyT& key)
    dictInt.insert(2);
    dictInt.insert(9);
    dictInt.insert(5);
    dictInt.insert(7);
    // вставка нового элемента
    if (dictInt.insert(1))
    {
        std::cout << "inserted\n";
    }

    // оператор вывода
    std::cout << dictInt << '\n';

    // Поиск элемента
    // bool search(const KeyT& key)
    // существующие элементы
    if (dictInt.search(1))
    {
        std::cout << "found\n";
    }

    // Удаление элементов
    // bool remove(const KeyT& key)
    // существующие элементы
    if (dictInt.remove(5))
    {
        std::cout << "deleted\n";
    }

    // Объединение списков
    // void merge(DictionaryList& dict2)
    DictionaryList<int> dictInt2;
    dictInt2.insert(3);
    dictInt2.insert(5);
    dictInt2.insert(8);
    dictInt2.insert(11);

    dictInt.merge(dictInt2);

    std::cout << "After merge:\n";
    std::cout << dictInt << '\n';
    std::cout << dictInt2 << '\n';

    // Вычитание списков
    // void subtract(const DictionaryList& dict2)
    dictInt2.insert(3);
    dictInt2.insert(8);
    dictInt2.insert(11);

    dictInt.subtract(dictInt2);

    std::cout << "After subtraction:\n";
    std::cout << dictInt << '\n';
    std::cout << dictInt2 << '\n';

    // Пересечение списков
    // DictionaryList intersect(const DictionaryList& dict1, const DictionaryList& dict2)
    DictionaryList<int> dictInt3;
    dictInt3.insert(7);
    dictInt3.insert(2);
    // неповторяющиеся элементы
    dictInt3.insert(0);
    dictInt3.insert(18);

    DictionaryList<int> dictInt4 = intersect(dictInt, dictInt3);

    std::cout << "After intersection:\n";
    std::cout << dictInt << '\n';
    std::cout << dictInt3 << '\n';
    std::cout << dictInt4 << '\n';
}

int main()
{
    dictionaryTest();
    return 0;
}
