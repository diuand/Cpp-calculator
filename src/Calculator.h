/*
 * Calculator.h
 *
 *  Created on: Aug 7, 2023
 *      Author: andrei.nicoara
 */

#include <iostream>
#include <vector>
#include "Calculations.h"

#ifndef CALCULATOR_H_
#define CALCULATOR_H_



class Calculator : protected Calculations {
private:
	string input_text{""};
	string INVALID_CHAR{"qwertyuiopasdfghjklzxcvbnm"};
	string INVALID_SIGN{",<>?;'\\[]:}{|_!@#$%^&`~="};
	double result{0.0};

public:
	Calculator() = default;
	virtual ~Calculator() = default;
	friend istream& operator>>(istream& input, Calculator& rhs);

	//	verify-ing the input_text
	bool legal_chars();
	bool legal_statement();
	bool verify_text();

	// complete calc
	void calculate();




};

#endif /* CALCULATOR_H_ */
