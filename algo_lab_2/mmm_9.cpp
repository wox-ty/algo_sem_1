#include "iostream"

void ins_sort(int B[], int X){
    for (int j = 1; j < X; ++j){
        int key = B[j];
        int i = j - 1;
        while ((i >= 0) && (B[i] > key)){
            B[i + 1] = B[i];
            --i;
        }
        B[i + 1] = key;
    }
}

int mid(int A, int B, int C, int D, int E){
    int arr[5] = {A, B , C ,D, E};

    ins_sort(arr, 5);

    return arr[2];
}

void q_sort_clones(int B[], int l, int r) {
    int v = mid(B[l], B[(l+(l+r)/2)/2], B[(l + r) / 2], B[((l+r)/2+r)/2],B[r]);

    if (r <= l) {
        return;
    }

    int i = l;
    int j = r - 1;
    int p = l - 1;
    int q = r;
    while (i <= j) {
        while (B[i] < v) {
            ++i;
        }
        while (B[j] > v) {
            --j;
        }
        if (i >= j) {
            break;
        }

        std::swap(B[i], B[j]);

        if (B[i] == v) {
            ++p;
            std::swap(B[p], B[i]);
        }
        ++i;

        if (B[j] == v) {
            --q;
            std::swap(B[q], B[j]);
        }
        --j;
    }

    std::swap(B[i], B[r]);
    j = i - 1;
    ++i;

    for (int x = l; x <= p; ++x, --j) {
        std::swap(B[x], B[j]);
    }
    for (int y = r - 1; y >= q; --y, ++i) {
        std::swap(B[y], B[i]);
    }

    q_sort_clones(B, l, j);
    q_sort_clones(B, i, r);
}


int find(int arr[], int l, int r, int k) {
    int x = mid(arr[l], arr[(l+(l+r)/2)/2], arr[(l + r) / 2], arr[((l+r)/2+r)/2],arr[r]);

    int i = l;
    int j = r;

    while (i <= j) {
        while (arr[i] < x) {
            i++;
        }
        while (arr[j] > x) {
            j--;
        }

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    if (l <= k && k <= j)
        return find(arr, l, j, k);

    if (i <= k && k <= r)
        return find(arr, i, r, k);

    return arr[k];
}


int main() {
    int n, k;
    std::cin >> n >> k;
    int A, B, C, a1, a2;
    std::cin >> A >> B >> C >> a1 >> a2;

    int c[n];
    c[0] = a1;
    c[1] = a2;


    int clones = 0;
    int max_clones = 0;

    for (int i = 2; i < n; ++i) {
        c[i] = c[i - 2] * A + c[i - 1] * B + C;
        if (c[i] == c[i - 1]) {
            ++clones;
        } else {
            if (max_clones < clones) {
                max_clones = clones;
            }
            clones = 0;
        }
    }

    if (max_clones < clones) {
        max_clones = clones;
    }

//    for (int i = 0; i < n; ++i){
//        std::cout << c[i] << " ";
//    }
//    std::cout << "\n" << c[n-k] << "\n";

    if (max_clones >= k) {
        q_sort_clones(c, 0, n - 1);
    } else {
        find(c, 0, n - 1, n - k - 1);
    }


//    for (int i = n-k; i < n; ++i){
//        std::cout << c[i] << " ";
//    }

    int sum = c[n - 1];
    for (int u = n - 2; u > n - 1 - k; --u) {
        sum = sum ^ c[u];
    }
    std::cout << sum;

    return 0;
}