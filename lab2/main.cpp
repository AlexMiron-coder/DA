#include <iostream>
#include <cstdio>
#include "TBTree.hpp"
#include "TItem.hpp"



int main() {
    TBTree bTree;
    TItem elem{};
    [[maybe_unused]] short size;
    char k[KEY_SIZE + 1] = {'\0'};
    [[maybe_unused]] unsigned long long value;
    TNode* search;
    int index;
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
                if (bTree.Search(elem)) {
                    printf("Exist\n");
                } else {
                    bTree.Insert(elem);
                    printf("OK\n");
                }
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
                if (bTree.Search(elem)) {
                    bTree.DeleteItem(elem);
                    printf("OK\n");
                } else {
                    printf("NoSuchWord\n");
                }
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
                search = bTree.SearchItem(elem, index);
                if (search == nullptr) {
                    printf("NoSuchWord\n");
                } else {
                    printf("OK: %llu\n", search->thisNode[index].value);
                }
                break;
        }
        elem.clear();
    }
    bTree.Print(0);
    return 0;
}

/*
+ word 34
+ fdfgdfg 325
+ ffhdh 325
+ you 1
+ flag 335
+ root 123
! Save dict
! Load dict
 */