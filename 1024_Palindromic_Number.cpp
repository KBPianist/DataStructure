/*
** @Brief:No.1024 of PAT advanced level.
** @Author:DJH
** @Date:2019-11-5
*/ 
#include <iostream>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

bool isPalindromic(string number){
	int length = number.length();
	for(int index = 0; index < length; index++){
		if(number[index] != number[length - index - 1]) return false;
	}
	return true;
}

string addstr(string a, string b){
	string::iterator it1 = a.begin();
	string::iterator it2 = b.begin();
	string res;
	int temp = 0;
	int carry = 0;
	for(; it1 != a.end() && it2 != b.end(); it1++, it2++){
		temp = ((*it1 - '0') + (*it2 - '0') + carry);
		carry = temp > 9 ? 1 : 0;
		res.push_back((temp % 10) + '0');
	}
	
	while(it1 != a.end()){
		temp = ((*it1 - '0') + carry);
		carry = temp > 9 ? 1 : 0;
		res.push_back((temp % 10) + '0');
		it1++;
	}

	while(it2 != b.end()){
		temp = ((*it2 - '0') + carry);
		carry = temp > 9 ? 1 : 0;
		res.push_back((temp % 10) + '0');
		it2++;
	} 

	if(carry) res.push_back((carry + '0'));
	reverse(res.begin(), res.end()); //turnaround
	return res;
}

int main(){
	string number;
	int K;
	while(cin >> number >> K){
		int i = 0;
		for(; i < K && !isPalindromic(number); i++) {
			string res = number;
			reverse(res.begin(), res.end());
			number = addstr(number, res);
		}
		cout << number << endl;
		cout << (isPalindromic(number) ? i : K) << endl;
	} 
	return 0;
}