#include "iostream"
#include "vector"

long long L_Find(std::vector<long long> &damag, long long Element) {
    long long l = -1;
    long long r = damag.size();
    while (l + 1 < r) {
        long long m = l + (r - l) / 2;

        if (damag[m] < Element) {
            l = m;
        } else {
            r = m;
        }
    }

    if (r < damag.size()) {
        return r;
    }

    return r;
}

long long R_Find(std::vector<long long> &damag, long long Element) {
    long long l = -1;
    long long r = damag.size();
    while (l + 1 < r) {
        long long m = l + (r - l) / 2;

        if (damag[m] > Element) {
            r = m;
        } else {
            l = m;
        }
    }

    if (l > -1) {
        return l;
    }

    return l;
}

long long Count(std::vector<long long> &dmgs, long long start, long long end) {
    long long first;
    first = L_Find(dmgs, start);
    long long last;
    last = R_Find(dmgs, end);

    return last - first + 1;
}

long long Xor(std::vector<long long> &dmgs, std::vector<long long> &xores, long long start, long long end) {
    long long first;
    first = L_Find(dmgs, start);
    long long last;
    last = R_Find(dmgs, end);
    ++last;
    return (xores[last] ^ xores[first]);
}

long long Sum(std::vector<long long> &dmgs, std::vector<long long> &sums, long long start, long long end) {
    long long first;
    first = L_Find(dmgs, start);
    long long last;
    last = R_Find(dmgs, end);
    ++last;

    return sums[last] - sums[first];
}

void counting_sort_2_0_0(std::vector<long long> &A, int n, std::vector<std::string> &D) {
    int k = 0;
    for (int x = 0; x < n; ++x) {
        if (k < A[x]){
            k = A[x];
        }
    }
    ++k;

    long long C[k];


    for (int number = 0; number < k; ++number) {
        C[number] = 0;
    }

    for (int i = 0; i < n; ++i) {
        ++C[A[i]];
    }

    for (int number = 1; number < k; ++number) {
        C[number] = C[number] + C[number - 1];
    }

    std::vector<std::string> E(n);
    for (int i = 0; i < n; ++i) {
        E[i] = ' ';
    }
    long long B[n];
    for (int i = 0; i < n; ++i) {
        B[i] = 0;
    }

    for (int i = n - 1; i >= 0; --i) {
        B[C[A[i]] - 1] = A[i];
        E[C[A[i]] - 1] = D[i];
        --C[A[i]];
    }

    for (int num = 0; num < n; ++num) {
        A[num] = B[num];
        D[num] = E[num];
    }
}

void merge(std::vector<long long> &B, long long l, long long m, long long r, std::vector<std::string> &C) {
    long long tl1 = 0, tl2 = 0;
    long long res[r - l];
    std::string res_names[r - l];

    while ((l + tl1 < m) && (m + tl2 < r)) {
        if (B[l + tl1] <= B[m + tl2]) {
            res[tl1 + tl2] = B[l + tl1];
            res_names[tl1 + tl2] = C[l + tl1];
            ++tl1;
        } else {
            res[tl1 + tl2] = B[m + tl2];
            res_names[tl1 + tl2] = C[m + tl2];
            ++tl2;
        }
    }

    while ((l + tl1) < m) {
        res[tl1 + tl2] = B[l + tl1];
        res_names[tl1 + tl2] = C[l + tl1];
        ++tl1;
    }

    while ((m + tl2) < r) {
        res[tl1 + tl2] = B[m + tl2];
        res_names[tl1 + tl2] = C[m + tl2];
        ++tl2;
    }

    for (long long i = 0; i < (tl1 + tl2); ++i) {
        B[l + i] = res[i];
        C[l + i] = res_names[i];
    }
}

void merge_sort_recursive(std::vector<long long> &B, long long l, long long r, std::vector<std::string> &C) {
    if ((l + 1) >= r) {
        return;
    }
    long long m = (l + r) / 2;
    merge_sort_recursive(B, l, m, C);
    merge_sort_recursive(B, m, r, C);
    merge(B, l, m, r, C);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<long long> damage;
    std::vector<std::string> names;

    long long x;
    for (long long i = 0; i < n; ++i) {
        std::cin >> x;
        damage.push_back(x);
    }

    std::string y;
    for (long long i = 0; i < n; ++i) {
        std::cin >> y;
        names.push_back(y);
    }


    counting_sort_2_0_0(damage, n, names);


    std::vector<long long> pref_sum;
    std::vector<long long> pref_xor;
    std::vector<long long> indexes;

    for (long long i = 0; i < damage.size() + 1; ++i) {
        if (i == 0) {
            pref_sum.push_back(0);
        } else {
            pref_sum.push_back(pref_sum[i - 1] + damage[i - 1]);
        }
    }

    for (long long j = 0; j < damage.size() + 1; ++j) {
        if (j == 0) {
            pref_xor.push_back(0);
        } else {
            pref_xor.push_back(pref_xor[j - 1] ^ damage[j - 1]);
        }
    }

    indexes.reserve(damage.size());
    for (long long i = 0; i < damage.size(); ++i) {
        indexes.push_back(i);
    }

    long long q;
    std::cin >> q;

    std::string operation;
    long long left, right;
    long long OpRes[q];

    for (long long i = 0; i < q; ++i) {
        std::cin >> operation >> left >> right;
        if (operation == "Count") {
            OpRes[i] = Count(damage, left, right);
        } else if (operation == "Sum") {
            OpRes[i] = Sum(damage, pref_sum, left, right);
        } else if (operation == "Xor") {
            OpRes[i] = Xor(damage, pref_xor, left, right);
        }
    }

    for (long long i = 0; i < damage.size(); ++i) {
        std::cout << damage[i];
        if (i != damage.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
    for (long long i = 0; i < names.size(); ++i) {
        std::cout << names[i];
        if (i != names.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";

    for (long long i = 0; i < q; ++i) {
        std::cout << OpRes[i];
        if (i != q - 1) {
            std::cout << "\n";
        }
    }

    return 0;
}