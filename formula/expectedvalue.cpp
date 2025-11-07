#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    // Example: Biased dice
    // Face 1: 10%, Face 2: 20%, Face 3: 30%, Face 4: 10%, Face 5: 10%, Face 6: 20%
    vector<double> values = {1, 2, 3, 4, 5, 6};
    vector<double> probs = {0.1, 0.2, 0.3, 0.1, 0.1, 0.2};

    double expected_value = 0;
    for (int i = 0; i < values.size(); ++i) {
        expected_value += values[i] * probs[i];
    }

    cout << fixed << setprecision(2) << "Gia tri ky vong: " << expected_value << endl;
    // Output: 3.50
    return 0;
}
