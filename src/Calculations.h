/*
 * Calculations.h
 *
 *  Created on: Aug 9, 2023
 *      Author: andrei.nicoara
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Calculations {

public:
	Calculations() = default;
	~Calculations() = default;
protected:

	vector<string> operators{"+","-","/","*"};
	vector<char> parenthesis{'(',')'};
	// calc options
	double double_br_calc(string input_text);
	double complex_calc(string input_text);
	double priority_calc(string input_text);
	double simple_calc(string input_text);

};

#endif /* CALCULATIONS_H_ */
