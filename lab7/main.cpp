#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> road(n);
    std::vector<std::vector<long long>> A(n, std::vector<long long>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> A[i][j];
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == 0) {
                A[i][j] += std::min(A[i - 1][j], A[i - 1][j + 1]);
            } else if (j == m - 1) {
                A[i][j] += std::min(A[i - 1][j - 1], A[i - 1][j]);
            } else {
                A[i][j] += std::min({A[i - 1][j - 1], A[i - 1][j], A[i - 1][j + 1]});
            }
        }
    }


    long long minA = A[n - 1][0];
    int k = 0;
    for (int j = 0; j < m; j++) {
        if (A[n - 1][j] < minA) {
            minA = A[n - 1][j];
            k = j;
        }
    }
    //road.push_back(std::make_pair(n - 1, k));
    road[n - 1] = std::make_pair(n - 1, k);
    std::cout << minA << std::endl;

    for (int i = n - 1; i >= 0; i--) {
        if (k == 0) {
            if (std::min(A[i][k], A[i][k + 1]) == A[i][k + 1]) {
                k++;
            }
        } else if (k == m - 1) {
            if (std::min(A[i][k - 1], A[i][k]) == A[i][k - 1]) {
                k--;
            }
        } else {
            long long check = std::min({A[i][k - 1], A[i][k], A[i][k + 1]});
            if (check == A[i][k - 1]) {
                k--;
            } else if (check == A[i][k + 1]) {
                k++;
            }
        }
        //road.push_back(std::make_pair(i, k));
        road[i] = std::make_pair(i, k);
    }

    for (int i = 0; i < n; i++) {
        if(i != 0) std::cout << " ";
        std::cout << "(" << road[i].first + 1 << "," << road[i].second + 1 << ")";
        if (i == n - 1) std::cout << "\n";
    }
    return 0;
}