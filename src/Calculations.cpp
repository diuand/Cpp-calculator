/*
 * Calculations.cpp
 *
 *  Created on: Aug 9, 2023
 *      Author: andrei.nicoara
 */
#include<vector>
#include<string>
#include <sstream>
#include "Calculations.h"
#include<iostream>
#include <iomanip>
#include <algorithm>
using namespace std;





double Calculations::double_br_calc(string input_text){


	int ct{0};
	string currentSubstring;
	string result;

	for(size_t i{0};i<input_text.size();i++){
		if (input_text[i] == '('){
			ct++;
			if(ct>1){
				currentSubstring += input_text[i];
			}
		}else if(input_text[i] == ')'){
			ct--;
			if(ct == 0){
				if(result.size() > 0){
					if (result[result.size()-1] != '+' && result[result.size()-1] != '-' && result[result.size()-1] != '*' && result[result.size()-1] != '/') {
						result += "*" + to_string(complex_calc(currentSubstring));
					}else{
						result += to_string(complex_calc(currentSubstring));

					}
				}else{
					result += to_string(complex_calc(currentSubstring));
				}


				currentSubstring.clear();
			}else if(ct >0){
				currentSubstring += input_text[i];
			}

		}else{
			if(ct > 0){
				currentSubstring += input_text[i];
			}else{
				result+=input_text[i];
			}
		}



	}

	return complex_calc(result);
}

// A calculation that contains (,),*,*,+,-
double Calculations::complex_calc(string input_text){

	int openCount = 0;
	string result;
	string currentSubstring;

	// add a * befor and after brackets if the operators an not there
	for(size_t i{0};i<input_text.size();i++){
		if (input_text[i] == '(') {
			// insert the * while ( is not at the start of a string
			if(i == 0){
				continue;
			}else{
				char pc = input_text[i - 1];
				if (pc != '+' && pc != '-'&& pc != '(' && pc != '*' && pc != '/') {
					input_text.insert(i, "*");
				}
			}

		}
		else if (input_text[i] == ')') {
			// insert the * while ) is not at the end of a string
			if(i == input_text.size()-1){
				continue;
			}else{
				char nc = input_text[i + 1];
				if (nc != '+' && nc != '-' && nc != ')' && nc != '*' && nc != '/') {
					input_text.insert(i+1,  "*");
				}
			}

		}
	}
//	resolve the calculation of the mathematical expression
	for(size_t i{0};i<input_text.size();i++){
		if (input_text[i] == '(') {
			if (openCount > 0) {
				currentSubstring += input_text[i];
			}
			openCount++;
		}else if (input_text[i] == ')') {
			openCount--;
			if (openCount == 0) {
				result += to_string(priority_calc(currentSubstring));
				currentSubstring.clear();

			} else {
				currentSubstring += input_text[i];
			}
		} else {
			if (openCount > 0) {
				currentSubstring += input_text[i];
			}else{
				result+=input_text[i];
			}
		}
	}
	return priority_calc(result);
}

// A calculation that contains  *,*,+,-
double Calculations::priority_calc(string input_text){

	//	REQUIREMENTS
	char divide = '/'; char multiply = '*';

	stringstream ss(input_text);
	long double num;

	vector<long double> numbers;
	vector<char> oper;

	//	move the operators in vector oper and numbers in vector numbers
	while (ss >> num) {
		numbers.push_back(num);

		if (ss.peek() == '+' || ss.peek() == '-' ||ss.peek() == divide || ss.peek() == multiply) {
			oper.push_back(ss.get());
		}
	}

	//	make the multiplication and division
	for (size_t i = 0; i < oper.size(); ++i) {
		 if (oper[i] == divide) {

			auto result_div = numbers[i] / numbers[i + 1];
			numbers[i] = result_div;
			numbers.erase(numbers.begin() + i + 1);
			oper.erase(oper.begin() + i);
			--i;

		}
		 if (oper[i] == multiply) {
			auto result_mul = numbers[i] * numbers[i + 1];
			numbers[i] = result_mul;
			numbers.erase(numbers.begin() + i + 1);
			oper.erase(oper.begin() + i);
			--i;
		}

	}

	//	convert the result into a text to call simple_calc()
	string txt_pri_res;

	for (size_t i = 0; i < oper.size(); ++i) {
		txt_pri_res +=to_string(numbers[i]) + string(1,oper[i]);
	}
	txt_pri_res += to_string(numbers[numbers.size()-1]);
	return simple_calc(txt_pri_res);


}
// A calculation that  contains just + and -
double Calculations::simple_calc(string input_text){
	stringstream ss(input_text);
	long double num;

	vector<long double> numbers;
	vector<char> oper;

	while (ss >> num) {
		numbers.push_back(num);
		oper.push_back(ss.get());
	}

	long double result = numbers[0];
	for(size_t i{0};i<oper.size();i++){
		if(oper[i] == '-'){
			result -= numbers[i +1];
		}else if(oper[i] == '+'){
			result += numbers[i+1];
		}
	}


	return result;

}
