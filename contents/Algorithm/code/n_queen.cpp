#include <iostream>
#include <cmath>
using namespace std;

const int MAX_N = 10;  // set max value (can change by needed) 
int n;
int col[MAX_N];  // array for save queen's position

bool promising(int i) {
    int k = 1;
    bool isPromising = true;

    while (k < i && isPromising) { 
        if (col[i] == col[k] || abs(col[i] - col[k]) == abs(i - k)) {
            isPromising = false;
        }
        k++;
    }
    return isPromising;
}

void queens(int i) {
    if (promising(i)) {  // promising case
        if (i == n) {  // if all queens are placed
            for (int k = 1; k <= n; k++) {
                cout << col[k] << " ";
            }
            cout << endl;
        } else {
            for (int j = 1; j <= n; j++) {
                col[i + 1] = j;
                queens(i + 1);  // recursive call
            }
        }
    }
}

int main() {
    cout << "Enter the number of queens: ";
    cin >> n;
    queens(0);
    return 0;
}
