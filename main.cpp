#include <iostream>
#include <string>
#include "DictionaryList.h"

// Тестирование словаря
void dictionaryTest() {
    // Создание списка
    DictionaryList<int> dictInt;
    // bool insert(const KeyT& key)
    dictInt.insert(2);
    dictInt.insert(9);
    dictInt.insert(5);
    dictInt.insert(7);
    // вставка нового элемента
    if (dictInt.insert(1)) {
        std::cout << "inserted\n";
    }

    // оператор вывода
    std::cout << dictInt << '\n';

    // Поиск элемента
    // bool search(const KeyT& key)
    // существующие элементы
    if (dictInt.search(1)) {
        std::cout << "found\n";
    }

    // Удаление элементов
    // bool remove(const KeyT& key)
    // существующие элементы
    if (dictInt.remove(5)) {
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

void testCopyConstructor() {
    std::cout << "#################################\n";
    std::cout << "testCopyConstructor:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(20);
    dict1.insert(5);
    dict1.insert(0);
    dict1.insert(8);
    dict1.insert(7);

    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    std::cout << "Try dict2(dict1)\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>(dict1);

    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n\n";

    std::cout << "Try dict1.remove(5)\n";
    dict1.remove(5);
    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n\n";
    std::cout << "#################################\n";
}

void testCopyAssignment() {
    std::cout << "#################################\n";
    std::cout << "testCopyAssignment:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(20);
    dict1.insert(5);
    dict1.insert(0);
    dict1.insert(8);
    dict1.insert(7);

    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();

    dict2.insert(3);
    dict2.insert(2);
    dict2.insert(6);
    dict2.insert(11);
    dict2.insert(0);

    std::cout << "dict 2 created:\n" << dict2 << "\n\n";

    std::cout << "Try dict1 = dict2\n\n";

    dict1 = dict2;

    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n\n";

    std::cout << "Try dict2.insert(500):\n";
    dict2.insert(500);
    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n";
    std::cout << "#################################\n";
}

void testCopySelfAssignment() {
    std::cout << "#################################\n";
    std::cout << "testCopySelfAssignment:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(20);
    dict1.insert(5);
    dict1.insert(0);
    dict1.insert(8);
    dict1.insert(7);

    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    std::cout << "Try dict1 = dict1\n\n";

    dict1 = dict1;

    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "#################################\n";
}


void testMoveConstructor() {
    std::cout << "#################################\n";
    std::cout << "testMoveConstructor:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(10);
    dict1.insert(500);
    dict1.insert(9);
    dict1.insert(12);
    dict1.insert(18);


    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    std::cout << "Try dict2(dict(dict1))\n\n";

    DictionaryList<int> dict2 = std::move(DictionaryList<int>(dict1));

    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n\n";
    std::cout << "#################################\n";
}

void testMoveAssignment() {
    std::cout << "#################################\n";
    std::cout << "testMoveAssignment:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(10);
    dict1.insert(500);
    dict1.insert(9);
    dict1.insert(12);
    dict1.insert(18);


    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();

    dict2.insert(10);
    dict2.insert(20);
    dict2.insert(1);

    std::cout << "dict 2 created:\n" << dict2 << "\n\n";
    std::cout << "Try dict2 = std::move(DictionaryList(dict1));\n\n";

    dict2 = std::move(DictionaryList<int>(dict1));

    std::cout << "dict1:\n" << dict1 << "\n\n";
    std::cout << "dict2:\n" << dict2 << "\n\n";
    std::cout << "#################################\n";
}



void testInsert() {
    std::cout << "#################################\n";
    std::cout << "testInsert:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    dict1.insert(10);
    dict1.insert(500);


    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    std::cout << "Try dict1.insert(7)\n\n";
    bool b1 = dict1.insert(7);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b1 << "\n\n";

    std::cout << "Try dict1.insert(9)\n\n";
    bool b2 = dict1.insert(9);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b2 << "\n\n";

    std::cout << "Try dict1.insert(500)\n\n";
    bool b3 = dict1.insert(500);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b3 << "\n\n";


    std::cout << "#################################\n";
}

void testInsertToEmpty() {
    std::cout << "#################################\n";
    std::cout << "testInsertToEmpty:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.insert(9)\n\n";
    bool b2 = dict1.insert(9);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b2 << "\n\n";

    std::cout << "Try dict1.insert(7)\n\n";
    bool b1 = dict1.insert(7);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b1 << "\n\n";

    std::cout << "Try dict1.insert(500)\n\n";
    bool b3 = dict1.insert(500);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of insert: " << b3 << "\n\n";


    std::cout << "#################################\n";
}



void testRemove() {
    std::cout << "#################################\n";
    std::cout << "testRemove:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(20);
    dict1.insert(90);
    dict1.insert(10);
    dict1.insert(3);
    dict1.insert(8);
    dict1.insert(0);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.remove(100000)\n\n";
    bool b1 = dict1.remove(100000);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of remove: " << b1 << "\n\n";

    std::cout << "Try dict1.remove(8)\n\n";
    bool b2 = dict1.remove(8);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of remove: " << b2 << "\n\n";

    std::cout << "Try dict1.remove(90)\n\n";
    bool b3 = dict1.remove(90);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of remove: " << b3 << "\n\n";


    std::cout << "#################################\n";
}

void testRemoveEmpty() {
    std::cout << "#################################\n";
    std::cout << "testRemoveEmpty:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.remove(100000)\n\n";
    bool b1 = dict1.remove(100000);
    std::cout << "dict1:\n" << dict1 << "\n";
    std::cout << "Result of remove: " << b1 << "\n\n";


    std::cout << "#################################\n";
}



void testSearch() {
    std::cout << "#################################\n";
    std::cout << "testSearch:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(8);
    dict1.insert(10);
    dict1.insert(55);
    dict1.insert(3);
    dict1.insert(100);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.search(10)\n";
    bool b1 = dict1.search(10);
    std::cout << "Result of search: " << b1 << "\n\n";

    std::cout << "Try dict1.search(55)\n";
    bool b2 = dict1.search(55);
    std::cout << "Result of search: " << b2 << "\n\n";

    std::cout << "Try dict1.search(99999)\n";
    bool b3 = dict1.search(99999);
    std::cout << "Result of search: " << b3 << "\n\n";


    std::cout << "#################################\n";
}

void testSearchEmpty() {
    std::cout << "#################################\n";
    std::cout << "testSearchEmpty:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.search(30)\n";
    bool b1 = dict1.search(30);
    std::cout << "Result of search: " << b1 << "\n\n";

    std::cout << "Try dict1.search(0)\n";
    bool b2 = dict1.search(0);
    std::cout << "Result of search: " << b2 << "\n\n";



    std::cout << "#################################\n";
}


void testMerge() {
    std::cout << "#################################\n";
    std::cout << "testMerge:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(2);
    dict1.insert(1);
    dict1.insert(4);
    dict1.insert(5);
    dict1.insert(3);
    dict1.insert(70);
    dict1.insert(32);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    DictionaryList<int> dict2 = DictionaryList<int>();
    dict2.insert(2);
    dict2.insert(1);
    dict2.insert(4);
    dict2.insert(60);
    dict2.insert(10);
    std::cout << "dict 2 created:\n" << dict2 << "\n\n";


    std::cout << "Try dict1.merge(dict2)\n";
    dict1.merge(dict2);
    std::cout << "dict 1:\n" << dict1 << "\n";
    std::cout << "dict 2:\n" << dict2 << "\n";


    std::cout << "#################################\n";
}

void testMergeSelf() {
    std::cout << "#################################\n";
    std::cout << "testMergeSelf:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(2);
    dict1.insert(1);
    dict1.insert(4);
    dict1.insert(5);
    dict1.insert(3);
    dict1.insert(70);
    dict1.insert(32);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";


    std::cout << "Try dict1.merge(dict1)\n";
    dict1.merge(dict1);
    std::cout << "dict 1:\n" << dict1 << "\n";

    std::cout << "#################################\n";
}

void testMergeCopy() {
    std::cout << "#################################\n";
    std::cout << "testMergeCopy:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(2);
    dict1.insert(1);
    dict1.insert(4);
    dict1.insert(5);
    dict1.insert(3);
    dict1.insert(70);
    dict1.insert(32);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();
    dict2.insert(2);
    dict2.insert(1);
    dict2.insert(4);
    dict2.insert(5);
    dict2.insert(3);
    dict2.insert(70);
    dict2.insert(32);
    std::cout << "dict 2 created:\n" << dict2 << "\n\n";


    std::cout << "Try dict1.merge(dict2)\n";
    dict1.merge(dict2);
    std::cout << "dict 1:\n" << dict1 << "\n";
    std::cout << "dict 2:\n" << dict2 << "\n";

    std::cout << "#################################\n";
}

void testMergeEmptyToFull() {
    std::cout << "#################################\n";
    std::cout << "testMergeEmptyToFull:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();
    dict2.insert(2);
    dict2.insert(1);
    dict2.insert(4);
    dict2.insert(5);
    dict2.insert(3);
    dict2.insert(70);
    dict2.insert(32);
    std::cout << "dict 2 created:\n" << dict2 << "\n\n";


    std::cout << "Try dict1.merge(dict2)\n";
    dict1.merge(dict2);
    std::cout << "dict 1:\n" << dict1 << "\n";
    std::cout << "dict 2:\n" << dict2 << "\n";

    std::cout << "#################################\n";
}

void testMergeFullToEmpty() {
    std::cout << "#################################\n";
    std::cout << "testMergeFullToEmpty:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();
    dict1.insert(2);
    dict1.insert(1);
    dict1.insert(4);
    dict1.insert(5);
    dict1.insert(3);
    dict1.insert(70);
    dict1.insert(32);
    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();
    std::cout << "dict 2 created:\n" << dict2 << "\n\n";


    std::cout << "Try dict1.merge(dict2)\n";
    dict1.merge(dict2);
    std::cout << "dict 1:\n" << dict1 << "\n";
    std::cout << "dict 2:\n" << dict2 << "\n";

    std::cout << "#################################\n";
}

void testMergeEmpties() {
    std::cout << "#################################\n";
    std::cout << "testMergeEmpties:\n\n";
    DictionaryList<int> dict1 = DictionaryList<int>();

    std::cout << "dict 1 created:\n" << dict1 << "\n\n";

    DictionaryList<int> dict2 = DictionaryList<int>();

    std::cout << "dict 2 created:\n" << dict2 << "\n\n";


    std::cout << "Try dict1.merge(dict2)\n";
    dict1.merge(dict2);
    std::cout << "dict 1:\n" << dict1 << "\n";
    std::cout << "dict 2:\n" << dict2 << "\n";

    std::cout << "#################################\n";
}

void myTests() {
    testCopyConstructor();
    testCopyAssignment();
    testCopySelfAssignment();

    testMoveConstructor();
    testMoveAssignment();

    testInsert();
    testInsertToEmpty();

    testRemove();
    testRemoveEmpty();

    testSearch();
    testSearchEmpty();

    testMerge();
    testMergeSelf();
    testMergeCopy();
    testMergeEmptyToFull();
    testMergeFullToEmpty();
    testMergeEmpties();
}

int main() {
    myTests();
    return 0;
}