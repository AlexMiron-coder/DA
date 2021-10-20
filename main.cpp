#include <iostream>

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
        mData = new TItem[size];
    }

    ~TVector () {
        delete[] mData;
    }

    unsigned int Size() {
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
            TItem* tmp = new TItem[maxSize];
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
        TItem* out = new TItem[size];
        for (int i = 0; i < NUMBER; i++) {
            for (int j = 0; j < KEY_BASE; j++) {
                count[j] = 0;
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
            for (int j = 0; j < KEY_BASE; j++) {
                count[j] = 0;
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
            for (int j = 0; j < KEY_BASE; j++) {
                count[j] = 0;
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

int main() {
    TVector vec;
    bool check = true;
    while (check) {
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
    }
    vec.RadixSort();
    vec.print();
    return 0;
}

/*
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-499-1234 hfghfdgfd
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+7-499-12345 fdghdfghfd
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
+8-103-1234 fdjhfdghdfghfd
+5-500-0000 dfghdfghdfgdfh
+213-049-1241 sfsdfsdfsdf
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naatt
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naat
+7-495-1123212	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3naa
+375-123-1234567	n399tann9nnt3ttnaaan9nann93na9t3a3t9999na3aan9antt3tn93aat3na
 */