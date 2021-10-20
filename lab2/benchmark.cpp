#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <chrono>
#include <algorithm>
#include <cmath>
#include "TBTree.hpp"
#include "TItem.hpp"



int main() {
    TBTree bTree;
    TItem elem{};
    char k[KEY_SIZE + 1] = {'\0'};
    TNode* search;
    int index;

    std::map<std::string, unsigned long long> map;
    //long double bTreeTime = 0, mapTime = 0;
    std::chrono::steady_clock::time_point beginning, end, result;
    long bTreeTime = 0, mapTime = 0;
    long timeCheck;

    while ((scanf("%s", elem.key)) != EOF) {
        switch (elem.key[0]) {
            case '+':
                if (scanf("%s %llu", elem.key, &elem.value) == EOF) break;
                for (short i = 0; i < KEY_SIZE + 1; i++) {
                    if (elem.key[i] >= 'A' and elem.key[i] <= 'Z') {
                        elem.key[i] = elem.key[i] - 'A' + 'a';
                    }
                    if (elem.key[i] == '\0') {
                        elem.keySize = i;
                        break;
                    }
                }

                beginning = std::chrono::steady_clock::now();
                if (bTree.Search(elem)) {
                    break;
                } else {
                    bTree.Insert(elem);
                }
                end = std::chrono::steady_clock::now();
                bTreeTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();

                beginning = std::chrono::steady_clock::now();
                /*if (map.find(elem.key) == map.end()) {
                    map[elem.key] = elem.value;
                }*/
                map.insert(std::make_pair(elem.key, elem.value));
                //map.insert({elem.key, elem.value});
                end = std::chrono::steady_clock::now();
                mapTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();
                break;
            case '-':
                if (scanf("%s", elem.key) == EOF) break;
                for (short i = 0; i < KEY_SIZE + 1; i++) {
                    if (elem.key[i] >= 'A' and elem.key[i] <= 'Z') {
                        elem.key[i] = elem.key[i] - 'A' + 'a';
                    }
                    if (elem.key[i] == '\0') {
                        elem.keySize = i;
                        break;
                    }
                }

                beginning = std::chrono::steady_clock::now();
                if (bTree.Search(elem)) {
                    bTree.DeleteItem(elem);
                }
                end = std::chrono::steady_clock::now();
                bTreeTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();

                beginning = std::chrono::steady_clock::now();
                if (map.find(elem.key) != map.end()) {
                    map.erase(elem.key);
                }
                end = std::chrono::steady_clock::now();
                mapTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();
                break;
            case '!':
                if (scanf("%s", k) == EOF) break;
                if (k[0] == 'L') {
                    if (scanf("%s", k) == EOF) break;
                    FILE *input;
                    input = fopen(k, "r");
                    if (!input) {
                        printf("ERROR: can't open the file\n");
                        break;
                    }
                    bTree.Load(input);
                    fclose(input);
                } else if (k[0] == 'S') {
                    if (scanf("%s", k) == EOF) break;
                    FILE *output;
                    output = fopen(k, "w");
                    if (!output) {
                        printf("ERROR: can't open the file\n");
                        break;
                    }
                    bTree.Save(output);
                    printf("OK\n");
                    fclose(output);
                } else {
                    printf("ERROR: no such command\n");
                }
                break;
            default:
                for (short i = 0; i < KEY_SIZE + 1; i++) {
                    if (elem.key[i] >= 'A' and elem.key[i] <= 'Z') {
                        elem.key[i] = elem.key[i] - 'A' + 'a';
                    }
                    if (elem.key[i] == '\0') {
                        elem.keySize = i;
                        break;
                    }
                }
                beginning = std::chrono::steady_clock::now();
                search = bTree.SearchItem(elem, index);
                end = std::chrono::steady_clock::now();
                bTreeTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();

                beginning = std::chrono::steady_clock::now();
                map.find(elem.key);
                end = std::chrono::steady_clock::now();
                mapTime += std::chrono::duration_cast<std::chrono::microseconds>(end - beginning).count();
                break;
        }
        elem.clear();
    }
    //bTree.Print(0);
    printf("B-Tree time = %ld ms\n", bTreeTime);
    printf("std::map time = %ld ms\n", mapTime);
    return 0;
}