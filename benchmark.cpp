#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

const static short VALUE_SIZE = 65;
const static short KEY_BASE = 10;
const static short COUNTRY_SIZE = 3;
const static short REGION_SIZE = 3;
const static short NUMBER = 7;
const static short NUMBER_SIZE = 16;
const static short ZERO = 0;
const static char ZERO_ELEMENT = '\0';

struct TKey {
    char number[NUMBER_SIZE] = { ZERO_ELEMENT };
    short first_ind = ZERO;
    short second_ind = ZERO;
    short third_ind = ZERO;
    short size = ZERO;
};

struct TItem {
    TKey key;
    char value[VALUE_SIZE] = { ZERO_ELEMENT };
};

bool operator < (const TItem &lhs, const TItem &rhs) {
    if (lhs.key.second_ind - lhs.key.first_ind - 1 != rhs.key.second_ind - rhs.key.first_ind - 1) { // сравнение длин кодов стран
        return lhs.key.second_ind - lhs.key.first_ind - 1 < rhs.key.second_ind - rhs.key.first_ind - 1;
    }
    for (int i = 0; i < lhs.key.second_ind - lhs.key.first_ind - 1; i++) { // сравниваем коды стран
        if ((lhs.key.number[lhs.key.first_ind + 1 + i] - '0') != (rhs.key.number[rhs.key.first_ind + 1 + i] - '0')) {
            return lhs.key.number[lhs.key.first_ind + 1 + i] - '0' < rhs.key.number[rhs.key.first_ind + 1 + i] - '0';
        }
    }

    if (lhs.key.third_ind - lhs.key.second_ind - 1 != rhs.key.third_ind - rhs.key.second_ind - 1) { // сравнение длин кодов регионов
        return lhs.key.third_ind - lhs.key.second_ind - 1 < rhs.key.third_ind - rhs.key.second_ind - 1;
    }
    for (int i = 0; i < lhs.key.third_ind - lhs.key.second_ind - 1; i++) { // сравниваем коды регионов
        if (lhs.key.number[lhs.key.second_ind + 1 + i] - '0' != rhs.key.number[rhs.key.second_ind + 1 + i] - '0') {
            return lhs.key.number[lhs.key.second_ind + 1 + i] - '0' < rhs.key.number[rhs.key.second_ind + 1 + i] - '0';
        }
    }

    if (lhs.key.size - lhs.key.third_ind - 1 != rhs.key.size - rhs.key.third_ind - 1) { // сравнение длин самих номеров
        return lhs.key.size - lhs.key.third_ind - 1 < rhs.key.size - rhs.key.third_ind - 1;
    }
    for (int i = 0; i < lhs.key.size - lhs.key.third_ind - 1; i++) { // сравниваем сами номера
        if (lhs.key.number[lhs.key.third_ind + 1 + i] - '0' != rhs.key.number[rhs.key.third_ind + 1 + i] - '0') {
            return lhs.key.number[lhs.key.third_ind + 1 + i] - '0' < rhs.key.number[rhs.key.third_ind + 1 + i] - '0';
        }
    }

    return false;
}

class TVector {
private:
    unsigned int size;
    unsigned int maxSize;
    TItem* mData;

public:
    TVector () {
        size = 0;
        mData = 0;
        maxSize = 10;
    }

    TVector (unsigned int n) {
        size = n;
        maxSize = n;
        mData = new TItem[size];
    }

    ~TVector () {
        delete[] mData;
    }

    unsigned int Size() const {
        return size;
    }

    void push_back(TItem elem) {
        if (size == 0) {
            maxSize = 10;
            mData = new TItem[maxSize];
            mData[0] = elem;
            size = 1;
            return;
        }
        if (size == maxSize) {
            maxSize *= 2;
            auto* tmp = new TItem[maxSize];
            for (int i = 0; i < size; ++i) {
                tmp[i] = mData[i];
            }
            delete[] mData;
            mData = tmp;
        }
        mData[size] = elem;
        size++;
    }

    void print () {
        printf("\n");
        for (int i = 0; i < size; ++i) {
            printf("%s ", mData[i].key.number);
            printf("%s\n", mData[i].value);
        }
    }

    void RadixSort(){
        int count[KEY_BASE];
        auto* out = new TItem[size];
        for (int i = 0; i < NUMBER; i++) {
            for (int & j : count) {
                j = 0;
            }
            for (int j = 0; j < size; j++) {
                if (mData[j].key.size - 1 - i > mData[j].key.third_ind) {
                    count[mData[j].key.number[mData[j].key.size - 1 - i] - '0']++;
                } else {
                    count[ZERO]++;
                }
            }

            for (int j = 1; j < KEY_BASE; j++) {
                count[j] += count[j - 1];
            }

            for (int j = size - 1; j >= 0; j--) {
                if (mData[j].key.size - 1 - i > mData[j].key.third_ind) {
                    out[--count[mData[j].key.number[mData[j].key.size - 1 - i] - '0']] = mData[j];
                } else {
                    out[--count[ZERO]] = mData[j];
                }
            }
            for (int j = 0; j < size; j++) {
                mData[j] = out[j];
            }
        }

        for (int i = 0; i < REGION_SIZE; i++) {
            for (int & j : count) {
                j = 0;
            }
            for (int j = 0; j < size; j++) {
                if (mData[j].key.third_ind - 1 - i > mData[j].key.second_ind) {
                    count[mData[j].key.number[mData[j].key.third_ind - 1 - i] - '0']++;
                } else {
                    count[ZERO]++;
                }
            }
            for (int j = 1; j < KEY_BASE; j++) {
                count[j] += count[j - 1];
            }
            for (int j = size - 1; j >= 0; j--) {
                if (mData[j].key.third_ind - 1 - i > mData[j].key.second_ind) {
                    out[--count[mData[j].key.number[mData[j].key.third_ind - 1 - i] - '0']] = mData[j];
                } else {
                    out[--count[ZERO]] = mData[j];
                }
            }
            for (int j = 0; j < size; j++) {
                mData[j] = out[j];
            }
        }

        for (int i = 0; i < COUNTRY_SIZE; i++) {
            for (int & j : count) {
                j = 0;
            }
            for (int j = 0; j < size; j++) {
                if (mData[j].key.second_ind - 1 - i > mData[j].key.first_ind) {
                    count[mData[j].key.number[mData[j].key.second_ind - 1 - i] - '0']++;
                } else {
                    count[ZERO]++;
                }
            }
            for (int j = 1; j < KEY_BASE; j++) {
                count[j] += count[j - 1];
            }
            for (int j = size - 1; j >= 0; j--) {
                if (mData[j].key.second_ind - 1 - i > mData[j].key.first_ind) {
                    out[--count[mData[j].key.number[mData[j].key.second_ind - 1 - i] - '0']] = mData[j];
                } else {
                    out[--count[ZERO]] = mData[j];
                }
            }
            for (int j = 0; j < size; j++) {
                mData[j] = out[j];
            }
        }
        delete[] out;
    }
};

void Print(std::vector<TItem> v) {
    std::cout << "\n";
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i].key.number << " ";
        std::cout << v[i].value << "\n";
    }
}


int main() {
    std::ios::sync_with_stdio(true);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    std::vector<TItem> v;
    TVector vec;
    bool check = true;
    /*while (check) {
        TItem elem;
        if (scanf("%16s %64s", elem.key.number, elem.value) != EOF) {
            unsigned short i = 0;
            while (i < NUMBER_SIZE and elem.key.number[i] != '\0') {
                if (elem.key.number[i] == '-' and elem.key.second_ind != 0) {
                    elem.key.third_ind = i;
                }
                if (elem.key.number[i] == '-' and elem.key.second_ind == 0) {
                    elem.key.second_ind = i;
                }
                i++;
            }
            elem.key.size = i;
            vec.push_back(elem);
        } else {
            check = false;
        }
    }*/
    TItem elem;
    auto beginning = std::chrono::steady_clock::now();
    while (std::cin >> elem.key.number >> elem.value) {
        unsigned short i = 0;
        elem.key.second_ind = 0;
        elem.key.third_ind = 0;
        while (i < NUMBER_SIZE and elem.key.number[i] != '\0') {
            if (elem.key.number[i] == '-' and elem.key.second_ind != 0) {
                elem.key.third_ind = i;
            }
            if (elem.key.number[i] == '-' and elem.key.second_ind == 0) {
                elem.key.second_ind = i;
            }
            i++;
        }
        elem.key.size = i;
        vec.push_back(elem);
        v.push_back(elem);
    }
    auto end = std::chrono::steady_clock::now();
    auto result = end - beginning;
    std::cerr << "input numbers time = " << std::chrono::duration_cast<std::chrono::milliseconds>(result).count() << " ms\n";

    beginning = std::chrono::steady_clock::now();
    vec.RadixSort();
    end = std::chrono::steady_clock::now();
    result = end - beginning;
    std::cerr << "RadixSort time = " << std::chrono::duration_cast<std::chrono::milliseconds>(result).count() << " ms\n";

    beginning = std::chrono::steady_clock::now();
    stable_sort(v.begin(), v.end());
    end = std::chrono::steady_clock::now();
    result = end - beginning;
    std::cerr << "stable_sort time = " << std::chrono::duration_cast<std::chrono::milliseconds>(result).count() << " ms\n";

    //vec.print();
    //std::cout << "\n";
    //Print(v);
    return 0;
}