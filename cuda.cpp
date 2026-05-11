#include <iostream>
#include <vector>
#include <thread>
using namespace std;

// ---------- Sequential Vector Addition ----------
vector<int> sequential_add(const vector<int>& A, const vector<int>& B) {
    vector<int> C(A.size());
    for (int i = 0; i < A.size(); i++)
        C[i] = A[i] + B[i];
    return C;
}

// ---------- Parallel Vector Addition ----------
vector<int> parallel_add(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    vector<int> C(n);

    // Thread 1 work
    thread t1([&]() {
        for (int i = 0; i < n / 2; i++) {
            C[i] = A[i] + B[i];
        }
    });

    // Thread 2 work
    thread t2([&]() {
        for (int i = n / 2; i < n; i++) {
            C[i] = A[i] + B[i];
        }
    });

    // Wait for both threads
    t1.join();
    t2.join();

    return C;
}

// ---------- Main ----------
int main() {
    int N;
    cout << "Enter size of vectors: ";
    cin >> N;

    vector<int> A(N), B(N);

    cout << "Enter elements of vector A:\n";
    for(int i=0;i<N;i++){
        cin>>A[i];
    }
    //for (int &x : A) cin >> x;

    cout << "Enter elements of vector B:\n";
    for (int i=0;i<N;i++){
        cin>>B[i];
    }
    // for (int &x : B) cin >> x;

    // Sequential
    vector<int> C_seq = sequential_add(A, B);

    // Parallel
    vector<int> C_par = parallel_add(A, B);

    // Check results
    bool same = true;
    for (int i = 0; i < N; i++) {
        if (C_seq[i] != C_par[i]) {
            same = false;
            break;
        }
    }

    cout << "\nResults same: " << (same ? "Yes" : "No") << endl;

    cout << "Resultant Vector: ";
    for (int x : C_seq) cout << x << " ";

    return 0;
}