#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int getMinIndex(const vector<float>& amount) {
    int minInd = 0;
    for (int i = 1; i < amount.size(); i++)
        if (amount[i] < amount[minInd])
            minInd = i;
    return minInd;
}

int getMaxIndex(const vector<float>& amount) {
    int maxInd = 0;
    for (int i = 1; i < amount.size(); i++)
        if (amount[i] > amount[maxInd])
            maxInd = i;
    return maxInd;
}

// Main Greedy Logic: 
void settleCashFlow(vector<float>& amount, const vector<string>& names) {
    int maxDebtor = getMinIndex(amount);
    int maxCreditor = getMaxIndex(amount);

    // Base Case: Agar sabka balance 0 ho gaya toh stop
    if (amount[maxDebtor] == 0 && amount[maxCreditor] == 0)
        return;

    // Minimum amount dhundna jo transfer ho sake
    float settleAmount = min(-amount[maxDebtor], amount[maxCreditor]);

    // Update balances
    amount[maxCreditor] -= settleAmount;
    amount[maxDebtor] += settleAmount;

    // Transaction output
    cout << names[maxDebtor] << " pays " << settleAmount << " to " << names[maxCreditor] << endl;

    // Agle settlement ke liye recursion
    settleCashFlow(amount, names);
}

int main() {
    int n, transactions;
    cout << "--- CASH FLOW MINIMISER ---" << endl;
    cout << "Enter number of friends: ";
    cin >> n;

    vector<string> names(n);
    map<string, int> nameToIndex;
    vector<float> netBalance(n, 0);

    cout << "Enter names of " << n << " friends:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> names[i];
        nameToIndex[names[i]] = i;
    }

    cout << "\nEnter total number of transactions: ";
    cin >> transactions;

    cout << "Enter transactions (Format: Giver_Name Taker_Name Amount):" << endl;
    for (int i = 0; i < transactions; i++) {
        string giver, taker;
        float amt;
        cin >> giver >> taker >> amt;

        // DAA Logic: Giver ka balance minus, Taker ka plus
        netBalance[nameToIndex[giver]] -= amt;
        netBalance[nameToIndex[taker]] += amt;
    }

    cout << "\n--- FINAL SETTLEMENT PLAN ---" << endl;
    settleCashFlow(netBalance, names);
    cout << "-----------------------------" << endl;

    return 0;
}
