#ifndef LAB6_TBIGINT_HPP
#define LAB6_TBIGINT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>



class TBigInt{
public:
    static const int base = 10;
    static const int digit = 1;

    TBigInt () = default;
    TBigInt (const int &);
    TBigInt (const std::string &);
    TBigInt (TBigInt &num, int j) {
        Data.resize(num.Data.size() - j);
        for (int i = 0; i < Data.size(); i++) {
            Data[i] = num.Data[i+j];
        }
    };

    void print() const;
    void setDigit(int, int);
    void DeleteZeros();

    static TBigInt Normalization(const TBigInt &, int);
    static void DivPow (TBigInt &, TBigInt &, TBigInt &, TBigInt &);
    static TBigInt Division(const TBigInt &, const TBigInt &);
    static TBigInt DivSmall(const TBigInt &, const int);

    friend std::ostream& operator << (std::ostream&, const TBigInt&);
    friend TBigInt operator + (const TBigInt &, const TBigInt &);
    friend TBigInt operator - (const TBigInt &, const TBigInt &);
    friend TBigInt operator * (const TBigInt &, const TBigInt &);
    friend TBigInt operator / (TBigInt &, TBigInt &);
    friend TBigInt operator ^ (TBigInt &, TBigInt &);
    TBigInt & operator = (const TBigInt &);
    friend bool operator == (const TBigInt &, const TBigInt &);
    friend bool operator > (const TBigInt &, const TBigInt &);
    friend bool operator < (const TBigInt &, const TBigInt &);

private:
    std::vector<int> Data;

};




TBigInt::TBigInt(const std::string &str) {
    int count = 0;
    while(count < str.size() - 1 and str[count] == '0'){
        count++;
    }
    if(count < str.size()){
        Data.resize(str.size()/digit + 1);
        int n = str.size();
        for(int i = 0; i < Data.size(); i++){
            int tmp_digit = 0;
            for(int j = 0; j < TBigInt::digit; j++){
                int index = n - (i + 1) * TBigInt::digit + j;
                if(index >= 0){
                    tmp_digit = tmp_digit * 10 + str[index] - '0';
                }
            }
            Data[i] = tmp_digit;
        }
        while(Data.size() > 1 and Data.back() == 0){ // удаляем лидирующие нули
            Data.pop_back();
        }
    }
}

std::ostream &operator << (std::ostream &stream, const TBigInt &num) {
    int n = num.Data.size();
    if (!n) {
        return stream;
    }
    stream << num.Data.back();
    for (int i = n - 2; i >= 0; i--) {
        stream << std::setfill('0') << std::setw(TBigInt::digit) << num.Data[i];
    }
    return stream;
}

void TBigInt::DeleteZeros(){
    while (Data.size() > 1 and Data.back() == 0) {
        Data.pop_back();
    }
}

void TBigInt::print() const {
    for(int i = Data.size() - 1; i >=0; i--){
        std::cout << Data[i] << "_";
    }
    std::cout << "\n";
}

TBigInt::TBigInt(const int &size) : Data(size, 0) {}


TBigInt operator + (const TBigInt &lhs, const TBigInt &rhs) {
    int size_of_res = std::max(lhs.Data.size(), rhs.Data.size());
    TBigInt res(size_of_res);
    int k = 0;
    for (int i = 0; i < size_of_res; i++) {
        int tmp = 0;
        if (i < lhs.Data.size()) {
            tmp += lhs.Data[i];
        }
        if (i < rhs.Data.size()) {
            tmp += rhs.Data[i];
        }
        res.Data[i] = (tmp + k)%TBigInt::base;
        k = (tmp + k) / TBigInt::base;
        if (k > 0) {
            res.setDigit(i, k);
        }
    }
    return res;
}

void TBigInt::setDigit (int pos, int val) {
    if (pos == Data.size() - 1) {
        Data.resize(Data.size() + 1);
        Data[pos+1] = val;
        return;
    }
}

TBigInt operator - (const TBigInt &lhs, const TBigInt &rhs) {
    TBigInt tmp_lhs = lhs;
    TBigInt tmp_rhs = rhs;
    int size_of_res = std::max(tmp_lhs.Data.size(), tmp_rhs.Data.size());
    TBigInt result(size_of_res);
    for (int i = 0; i < size_of_res; i++) {
        if (i < tmp_rhs.Data.size()) {
            if (tmp_lhs.Data[i] >= tmp_rhs.Data[i]) {
                result.Data[i] = tmp_lhs.Data[i] - tmp_rhs.Data[i];
            } else {
                int j = i+1;
                while (tmp_lhs.Data[j] == 0) {
                    j++;
                }
                tmp_lhs.Data[j]--;
                for (int k = j-1; k > i; k--) {
                    tmp_lhs.Data[k] = TBigInt::base - 1;
                }
                result.Data[i] = tmp_lhs.Data[i] + TBigInt::base - tmp_rhs.Data[i];
            }
        } else {
            result.Data[i] = tmp_lhs.Data[i];
        }
    }
    result.DeleteZeros();
    return result;
}

TBigInt operator * (const TBigInt &lhs, const TBigInt &rhs) {
    int n = lhs.Data.size(); // u
    int m = rhs.Data.size(); // v
    int size_of_res = n * m + 1;
    TBigInt result(size_of_res);
    for (int j = 0; j < m; j++) {
        if (rhs.Data[j] == 0) {
            continue;
        }
        int k = 0;
        for (int i = 0; i < n; i++) {
            int tmp = lhs.Data[i]*rhs.Data[j] + k + result.Data[i+j];
            result.Data[i+j] = tmp % TBigInt::base;
            k = tmp / TBigInt::base;
        }
        result.Data[j+n] = k;
    }
    result.DeleteZeros();
    return result;
}

TBigInt &TBigInt::operator = (const TBigInt &num) {
    Data = num.Data;
    return *this;
}

TBigInt TBigInt::Normalization (const TBigInt &num, int d) {
    std::string str;
    str = std::to_string(d);
    TBigInt tmp_d(str);

    int n = num.Data.size(); // u
    int m = 1; // v
    int size_of_res = n * m + 1;
    TBigInt result(size_of_res);

    int k = 0;
    for (int i = 0; i < n; i++) {
        int tmp = num.Data[i]*d + k + result.Data[i];
        result.Data[i] = tmp % TBigInt::base;
        k = tmp / TBigInt::base;
    }
    result.Data[n] = k;
    return result;
    //return num * tmp_d;
}


TBigInt operator / (TBigInt &lhs, TBigInt &rhs) {
    if (rhs.Data.size() > 1) {
        return TBigInt::Division(lhs, rhs);
    } else {
        return TBigInt::DivSmall(lhs, rhs.Data[rhs.Data.size() - 1]);
    }
}

TBigInt TBigInt::DivSmall(const TBigInt &lhs, const int rhs) {
    TBigInt result(lhs.Data.size());
    int carry = 0;
    for (int i= lhs.Data.size() - 1; i >= 0; i--) {
        int cur = lhs.Data[i] + carry * 1ll * base;
        result.Data[i] = cur / rhs;
        carry = cur % rhs;
    }
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::Division(const TBigInt &lhs, const TBigInt &rhs) {
    // u / v -> u >= v (rhs >= lhs)
    // u - lhs / u.size = m
    // v - rhs / v.size = n
    int d = TBigInt::base / (rhs.Data[rhs.Data.size()-1] + 1);
    //std::cout << "d = " << d << std::endl;

    TBigInt tmp_lhs(0); // u *= d
    tmp_lhs = lhs;
    tmp_lhs = Normalization(tmp_lhs, d);

    TBigInt tmp_rhs(0); // v *= d
    tmp_rhs = rhs;
    tmp_rhs = Normalization(tmp_rhs, d);
    tmp_rhs.DeleteZeros();

    //std::cout << "tmp_lhs and tmp_rhs: \n";
    //tmp_lhs.print();
    //tmp_rhs.print();

    TBigInt Q_(0);
    int m = tmp_lhs.Data.size();
    int n = tmp_rhs.Data.size();
    //std::cout << "m = " << m << " n = " << n << " and m-n = " << m-n << "\n";
    for (int j = m - n - 1; j >= 0; j--) {
        //std::cout << "j = " << j << std::endl;
        //n = tmp_rhs.Data.size();
        int q = (tmp_lhs.Data[j+n]*TBigInt::base + tmp_lhs.Data[j+n-1]) / tmp_rhs.Data[n-1];
        int r = (tmp_lhs.Data[j+n]*TBigInt::base + tmp_lhs.Data[j+n-1]) % tmp_rhs.Data[n-1];
        //std::cout << "q and r: " << q << " " << r << "\n";
        while ((r < TBigInt::base) and ((q == TBigInt::base) or (q*tmp_rhs.Data[n - 2] > (TBigInt::base * r + tmp_lhs.Data[j + n - 2])))) {
            //std::cout << q << " * " << tmp_rhs.Data[n - 2] << " > " << TBigInt::base << " * " << r << " + " << tmp_lhs.Data[j + n - 2] << std::endl;
            q--;
            r += tmp_rhs.Data[n-2];
        }
        //std::cout << "q and r after while: " << q << " " << r << "\n";
        //std::cout << "---------rare situation------\n";
        //std::cout << "tmp_rhs * q and tmp lhs:" <<  std::endl;
        //Normalization(tmp_rhs, q).print();
        //tmp_lhs.print();

        // проверка редкого случая
        TBigInt check = Normalization(tmp_rhs, q);
        check.DeleteZeros();
        if (check > TBigInt(tmp_lhs, j)) {
            q--;
            r += tmp_rhs.Data[n-2];
        }
        // ----
        //std::cout << "q and r after rare situation: " << q << " " << r << "\n";

        TBigInt tmp_qrhs(0);
        tmp_qrhs = tmp_rhs;
        tmp_qrhs = Normalization(tmp_qrhs, q);
        tmp_qrhs.DeleteZeros();
        //std::cout << q << " * tmp_rhs: \n";
        //tmp_qrhs.print();

        for (int i = 0; i < tmp_qrhs.Data.size(); i++) { // вычитание
            if (tmp_lhs.Data[i+j] >= tmp_qrhs.Data[i]) {
                tmp_lhs.Data[i+j] = tmp_lhs.Data[i+j] - tmp_qrhs.Data[i];
            } else {
                int index = i + j + 1;
                while (tmp_lhs.Data[index] == 0) {
                    index++;
                }
                tmp_lhs.Data[index]--;
                for (int k = index - 1; k > i + j; k--) {
                    tmp_lhs.Data[k] = TBigInt::base - 1;
                }
                tmp_lhs.Data[i+j] = tmp_lhs.Data[i+j] + TBigInt::base - tmp_qrhs.Data[i];
                //std::cout << "i = " << i << ": tmp_lhs[i+j] = " << tmp_lhs.Data[i + j] << std::endl;
            }
        }
        tmp_lhs.DeleteZeros();
        //std::cout << "tmp_lhs - tmp_qrhs = ";
        //tmp_lhs.print();
        if (q >= TBigInt::base) {
            int tmp_q = q / TBigInt::base;
            int tmp_r = q % TBigInt::base;
            Q_.Data.push_back(tmp_q);
            Q_.Data.push_back(tmp_r);
        } else {
            Q_.Data.push_back(q);
        }
        //std::cout << "Q_ = " << Q_ << std::endl;
    }
    std::reverse(Q_.Data.begin(), Q_.Data.end());
    Q_.DeleteZeros();
    return Q_;
}



TBigInt operator ^ (TBigInt &number, TBigInt &power) {
    TBigInt base = number;
    TBigInt two("2");
    TBigInt one("1");
    number = TBigInt("1");
    while (!(power.Data.size() == 1 && power.Data[0] == 0)) {
        if (power.Data[0] % 2 == 0) {
            base = base * base;
            power = power / two;
        } else {
            number = number * base;
            power = power - one;
        }
    }
    number.DeleteZeros();
    return number;
}

bool operator == (const TBigInt &lhs, const TBigInt &rhs) {
    if (lhs.Data.size() != rhs.Data.size()) {
        return false;
    }
    for (int i = 0; i < lhs.Data.size(); i++) {
        if (lhs.Data[i] != rhs.Data[i]) {
            return false;
        }
    }
    return true;
}

bool operator > (const TBigInt &lhs, const TBigInt &rhs) {
    if (lhs.Data.size() != rhs.Data.size()) {
        return lhs.Data.size() > rhs.Data.size();
    }
    for (int i = rhs.Data.size() - 1; i >= 0; i--) {
        if (lhs.Data[i] != rhs.Data[i]) {
            return lhs.Data[i] > rhs.Data[i];
        }
    }
    return false;
}

bool operator < (const TBigInt &lhs, const TBigInt &rhs) {
    if (lhs.Data.size() != rhs.Data.size()) {
        return lhs.Data.size() < rhs.Data.size();
    }
    for (int i = rhs.Data.size() - 1; i >= 0; i--) {
        if (lhs.Data[i] != rhs.Data[i]) {
            return lhs.Data[i] < rhs.Data[i];
        }
    }
    return false;
}


// 46585547708640867646250864433647610664692576
// 41

// 1945656156565165
// 156615
// /

// Кнут страница 302
#endif //LAB6_TBIGINT_HPP
