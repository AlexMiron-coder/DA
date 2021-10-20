#ifndef LAB2_TITEM_HPP
#define LAB2_TITEM_HPP

const static short KEY_SIZE = 256;

struct TItem {
    char key[KEY_SIZE + 1] = {'\0'}; // ключ
    short keySize = 0; // размер ключа
    unsigned long long value = 0; // значение
    //TItem& operator = (TItem const &);
    friend bool operator > (const TItem& lhs, const TItem& rhs);
    friend bool operator < (const TItem& lhs, const TItem& rhs);
    friend bool operator == (const TItem& lhs, const TItem& rhs);
    void clear();
};

void TItem::clear() {
    keySize = 0;
    value = 0;
    for (short i = 0; i < KEY_SIZE; i++) {
        if (key[i] == '\0') {
            break;
        }
        key[i] = '\0';
    }
}

/*TItem& TItem::operator = (TItem const &rhs) {
    keySize = rhs.keySize;
    value = rhs.value;
    for (int i = 0; i < KEY_SIZE + 1; i ++) {
        key[i] = rhs.key[i];
    }
    return *this;
}*/

bool operator > (const TItem& lhs, const TItem& rhs) {
    int n = lhs.keySize < rhs.keySize ? lhs.keySize : rhs.keySize;
    for (int i = 0; i < n; i++) {
        if (lhs.key[i] != rhs.key[i]) {
            return lhs.key[i] > rhs.key[i];
        }
    }
    return lhs.keySize > rhs.keySize;
}

bool operator < (const TItem& lhs, const TItem& rhs) {
    int n = lhs.keySize < rhs.keySize ? lhs.keySize : rhs.keySize;
    for (int i = 0; i < n; i++) {
        if (lhs.key[i] != rhs.key[i]) {
            return lhs.key[i] < rhs.key[i];
        }
    }
    return lhs.keySize < rhs.keySize;
}

bool operator == (const TItem& lhs, const TItem& rhs) {
    if (lhs.keySize != rhs.keySize) {
        return false;
    }
    for (int i = 0; i < rhs.keySize; i++) {
        if (lhs.key[i] != rhs.key[i]) {
            return false;
        }
    }
    return true;
}


#endif //LAB2_TITEM_HPP