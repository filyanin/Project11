#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>

#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Source.h"
#include <unordered_map>



class S {

public:

    std::string m{ "Message string." };

    S() {

        //every element creation takes 2 seconds

        std::cout << "Construction started.\n";

        std::chrono::seconds sec(2);

        //std::this_thread::sleep_for(sec);

        std::cout << "Constructed.\n";

    };



    ~S() {

        std::cout << "Destroyed.\n";

    };

};
void print(S element) {
    std::cout << element.m << " ";
}
void print(int element) {
    std::cout << element << " ";
}

void heapSort(std::vector<int>& arr) {
    // Преобразовываем вектор в кучу
    std::make_heap(arr.begin(), arr.end());

    // Последовательно извлекаем максимальный элемент и убираем его из кучи
    for (int i = arr.size() - 1; i > 0; --i) {
        // Перемещаем максимальный элемент в конец массива (сортировка)
        std::pop_heap(arr.begin(), arr.begin() + i + 1);
    }
}
bool arePermutations(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        // Если размеры массивов не совпадают, они не могут быть перестановками друг друга.
        return false;
    }

    std::unordered_map<int, int> countMap;

    // Подсчитываем количество вхождений каждого элемента в первом массиве
    for (int num : arr1) {
        countMap[num]++;
    }

    // Уменьшаем счетчики для каждого элемента во втором массиве
    for (int num : arr2) {
        if (countMap.find(num) == countMap.end() || countMap[num] == 0) {
            // Если элемент не найден в карте или счетчик равен нулю, это не перестановка.
            return false;
        }
        countMap[num]--;
    }

    // Если все счетчики в карте стали нулями, то это перестановка.
    return true;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    //allocate memory for 5 messages

    constexpr int n{ 5 };

    alignas(alignof(S)) char arr[n * sizeof(S)];//создают массив arr, который имеет размер n элементов, где n умножается на размер типа S и выравнивается по требованию выравнивания типа S.

    //get pointers to the first and first-after-last elements

    auto first{ reinterpret_cast<S*>(arr) };

    auto last{ first + n };



    auto count{ 0 };

    std::cout << "\n No1";
    //initialize "on acquisition" idea)
    std::cout << "\nЗаполнение зарезервированной памяти сообщениями из конструктора S\n";
    for (auto it{ first }; it != last; ++it) {
        std::uninitialized_default_construct(it, it + 1);

        std::cout << count++ << ' ' << it->m << '\n';

    }
    std::cout << "Проход по всем элементам массива arr\n";
    for (char c : arr) {
        std::cout << c << " ";
    }
    std::cout << "\nВывод с использованием указателей на S (и освобождение памяти, т.к. последнее упоминание)\n";
    std::for_each(first, last, [](S s) {print(s);});


    std::cout << "\n No2";

    std::vector<int> vector_1;
    std::vector<int> sample;
    std::srand(time(0u));

    std::generate_n(std::back_inserter(vector_1), 10, []()->int {
        return int(rand()) % 10;
        });

    std::cout << "\nСгенерированные данные: ";
    std::for_each(vector_1.begin(), vector_1.end(), [](int s) {print(s); });
    if (std::is_heap(vector_1.begin(), vector_1.end())) {
        std::cout << "\nПеред нами куча";
    }
    else {
        std::cout << "\nСоставим из них кучу: ";
        std::make_heap(vector_1.begin(), vector_1.end());
        std::for_each(vector_1.begin(), vector_1.end(), [](int s) {print(s); });
    }
    std::copy(vector_1.begin(), vector_1.end(), std::back_inserter(sample));
    heapSort(vector_1);
    std::cout << "\nОтсортированная куча (по возрастанию): ";
    std::for_each(vector_1.begin(), vector_1.end(), [](int s) {print(s); });


    std::cout << "\n\n No3";
    std::cout << "\nСравним исходную кучу ( ";
    std::for_each(sample.begin(), sample.end(), [](int s) {print(s); });
    std::cout << ") с отсортированной ( ";
    std::for_each(vector_1.begin(), vector_1.end(), [](int s) {print(s); });
    std::cout << ")\n";
    if (arePermutations(vector_1, sample)) {
        std::cout << "Два набора элементов являются перестановками друг друга." << std::endl;
    }
    else {
        std::cout << "Два набора элементов не являются перестановками друг друга." << std::endl;
    }


    std::vector<int> vector_2;
    std::generate_n(std::back_inserter(vector_2), 10, []()->int {
        return int(rand()) % 10;
        });
    std::cout << "\nСравним исходную кучу ( ";
    std::for_each(sample.begin(), sample.end(), [](int s) {print(s); });
    std::cout << ") с случайным набором элементов ( ";
    std::for_each(vector_2.begin(), vector_2.end(), [](int s) {print(s); });
    std::cout << ")\n";
    if (arePermutations(vector_2, sample)) {
        std::cout << "Два набора элементов являются перестановками друг друга." << std::endl;
    }
    else {
        std::cout << "Два набора элементов не являются перестановками друг друга." << std::endl;
    }
    return 0;

}