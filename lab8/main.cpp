#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

void CountingSort(std::vector<int> &data, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (data[i] > max) max = data[i];
    }
    std::vector<int> count(max + 1);
    for (int i = 0; i < n; i++) {
        count[data[i]]++;
    }
    for (int i = 1; i < max + 1; i++) {
        count[i] += count[i - 1];
    }
    std::vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
        res[--count[data[i]]] = data[i];
    }
    for (int i = 0; i < n; i++) {
        data[i] = res[i];
    }
}

double Area(int a, int b, int c) {
    double p = ((a + b + c) / 2.0);
    return sqrt(p * (p-a) * (p-b) * (p-c));
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> segments(n);
    for (int i = 0; i < n; i++) {
        std::cin >> segments[i];
    }
    CountingSort(segments, n);

    double maxArea = 0;
    double tmpArea;
    int seg1 = 0, seg2 = 0, seg3 = 0;
    for (int i = 1; i < n - 1; i++) {
        if (n < 3) break;
        if (segments[i - 1] + segments[i] > segments[i + 1]) {
            tmpArea = Area(segments[i - 1], segments[i], segments[i + 1]);
            if (tmpArea > maxArea) {
                maxArea = tmpArea;
                seg1 = segments[i - 1];
                seg2 = segments[i];
                seg3 = segments[i + 1];
            }
        }
    }
    if (maxArea != 0) {
        std::cout << std::fixed << std::setprecision(3) << maxArea << std::endl;
        std::cout << seg1 << " " << seg2 << " " << seg3 << std::endl;
    } else {
        std::cout << maxArea << std::endl;
    }
    return 0;
}
