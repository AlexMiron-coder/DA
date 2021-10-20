#include <iostream>
#include <sstream>
#include <vector>
#include <string>


struct TWord {
    unsigned long int word;
    unsigned int strNum;
    unsigned int wordNum;
    bool sent;
    friend bool operator == (const TWord &, const TWord &);
};

bool operator == (const TWord& lhs, const TWord& rhs) {
    if (!lhs.sent and !rhs.sent) {
        return lhs.word == rhs.word;
    }
    return false;
}

std::vector<int> Z_function(std::vector<TWord> text, int patternSize) {
    std::vector<int> z(text.size(), 0);
    std::vector<int> ans;
    for (int i = 1, l = 0, r = 0; i < text.size(); i++) {
        if (i <= r) {
            z[i] = std::min(z[i - l], r - i + 1);
        }

        while (i + z[i] < text.size()) {
            if (text[i + z[i]] == text[z[i]]) {
                z[i]++;
            } else {
                break;
            }
        }

        if (z[i] > 0 && i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        if (z[i] == patternSize) ans.push_back(i);
    }
    return ans;
}


int main() {
    unsigned int stringNum = 0;
    unsigned int wordNum;
    unsigned long int num;
    int patternSize;
    std::string str;
    std::vector<TWord> pattern;
    std::vector<TWord> text;
    std::vector<int> indexes;
    TWord tmp = {0,0,0, true};
    TWord sentinella = {0,0,0,true};

    // считали паттерн
    std::getline(std::cin, str);
    std::istringstream istr(str);
    while (istr >> num) {
        tmp.word = num;
        tmp.sent = false;
        pattern.push_back(tmp);
    }
    //

    patternSize = pattern.size();
    text = pattern;
    text.push_back(sentinella);

    while (true) {
        if (!std::getline(std::cin, str)) {
            break;
        }
        stringNum++;
        wordNum = 0;
        std::istringstream istr(str);
        while (istr >> num) {
            wordNum++;
            tmp.word = num;
            tmp.strNum = stringNum;
            tmp.wordNum = wordNum;
            tmp.sent = false;
            text.push_back(tmp);
        }
    }

    indexes = Z_function(text, patternSize);
    std::cout << indexes.size() << std::endl;
    for (int i = 0; i < indexes.size(); i++) {
        std::cout << text[indexes[i]].strNum << ", " << text[indexes[i]].wordNum << "\n";
    }
    return 0;
}

/*
11 45 11 45 90
0011 45 011 0045 11 45 90 11 45 11 45 90
 */