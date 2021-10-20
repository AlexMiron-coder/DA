#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>


struct TWord {
    unsigned long int word;
    unsigned int strNum;
    unsigned int wordNum;
    bool sent;
    friend bool operator == (const TWord &, const TWord &);
    friend bool operator != (const TWord &, const TWord &);
};

bool operator == (const TWord& lhs, const TWord& rhs) {
    if (!lhs.sent and !rhs.sent) {
        return lhs.word == rhs.word;
    }
    return false;
}


bool operator != (const TWord &lhs, const TWord &rhs) {
    if (!lhs.sent and !rhs.sent) {
        return !(lhs == rhs);
    }
    return true;
}

void Z_function(std::vector<TWord> text, int patternSize, std::vector<int> &ans) {
    std::vector<int> z(text.size(), 0);
    //std::vector<int> ans;
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
    //return ans;
}

void NaiveAlgorithm(std::vector<TWord> text, std::vector<TWord> pattern, std::vector<int> &result) {
    //std::vector<int> result;
    for (int i = pattern.size() + 1; i < text.size() - pattern.size() + 1; i++) {
        bool check = true;
        for (int j = 0; j < pattern.size(); j++) {
            //check = true;
            if (text[i + j] != pattern[j]) {
                check = false;
                break;
            }
        }
        if (check) result.push_back(i);
    }
}

void Naive(std::string text, std::string pattern, std::vector<int> &result) {
    //std::vector<int> result;
    bool check = true;
    while (check) {
        int pos = text.find(pattern);
        if (pos != std::string::npos) {
            text[pos] = ' ';
            text[pos - 1] = ' ';
            result.push_back(pos);
        } else {
            check = false;
        }
    }
    //return result;
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

    std::string T = "";
    std::string P = "";

    // считали паттерн
    std::getline(std::cin, str);
    std::istringstream istr(str);
    while (istr >> num) {
        tmp.word = num;
        tmp.sent = false;
        pattern.push_back(tmp);

        P += std::to_string(num);
        P += " ";
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

            T += std::to_string(num);
            T += " ";
        }
    }

    auto beginning = std::chrono::steady_clock::now();
    Z_function(text, patternSize, indexes);
    auto end = std::chrono::steady_clock::now();
    auto ZTime = end - beginning;


    beginning = std::chrono::steady_clock::now();
    std::vector<int> naive;
    Naive(T, P, naive);
    end = std::chrono::steady_clock::now();
    auto NaiveTime = end - beginning;


    std::cerr << "ZTime = " << std::chrono::duration_cast<std::chrono::milliseconds>(ZTime).count() << " ms\n";
    std::cerr << "NaiveTime = " << std::chrono::duration_cast<std::chrono::milliseconds>(NaiveTime).count() << " ms\n";
    return 0;
}
