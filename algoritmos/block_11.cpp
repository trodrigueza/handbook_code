#include <bits/stdc++.h>
using namespace std;

vector<string> board;
int counter = 0;

bool check1(vector<int> iter) {
	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 8; j++) {
			if(abs(i-j) == abs(iter[i]-iter[j])) return false;
		}
	}
	return true;
}

bool check2(vector<int> iter) {
	for (int i = 0; i < 8; i++) {
		int row = iter[i];
		int col = i;
		
		if(board[row][col] == '*') return false;
	}
	return true;
}
void gen(vector<int> &input, vector<int> &current, vector<bool> &used) {
	if (current.size() == input.size()) {
		if(check1(current) && check2(current)) {
			counter++;
		}
		return;
	}
	
	for (int i = 0; i < (int)input.size(); i++) {
		if(!used[i]) {
			used[i] = true;
			current.push_back(input[i]);
			gen(input, current, used);
			used[i] = false;
			current.pop_back();
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n = 8;
	vector<int> toGen(n);
	for (int i = 0; i < n; i++) {
		toGen[i] = i;
	}
	
	
	for (int i = 0; i < 8; i++) {
		string row = "";
		for (int j = 0; j < 8; j++) {
			char ch; cin >> ch;
			row += ch;
		}
		board.push_back(row);
	}
	
	vector<int> currentP;
	vector<bool> marked(n, false);
	gen(toGen, currentP, marked);
	cout << counter;
	return 0;
}
