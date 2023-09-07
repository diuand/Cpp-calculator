#include "Calculator.h"
#include<iostream>
#include<vector>
#include<string>
#include <iomanip>
#include <sstream>
using namespace std;

//errors
class Invalid_sign : public std::exception {
private:
	string message;
public:
	Invalid_sign(string data):message("INVALID SIGN: " + data){};
    const char* what() const noexcept override {
    	return message.c_str();
    }
};
class Invalid_char : public std::exception {
private:
	string message;
public:
	Invalid_char(string data):message("INVALID CHAR: " + data){};
    const char* what() const noexcept override {
    	return message.c_str();
    }
};
class Devided_by_0 : public std::exception {
public:
	Devided_by_0() noexcept = default;
    const char* what() const noexcept override {
        return "DEVIDED BY 0";
    }
};
class Missing_brackets : public std::exception {
public:
	Missing_brackets() noexcept = default;
    const char* what() const noexcept override {
        return "MISSING A BRACKET";
    }
};
class Multiple_operators : public std::exception {
private:
	string message;
public:
	Multiple_operators(string data):message("MULTIPLE OPERATORS: " + data){};
    const char* what() const noexcept override {
    	return message.c_str();
    }
};
class Missing_sign_bb : public std::exception {
private:
	string message;
public:
	Missing_sign_bb():message("MISSING SIGN BEFORE BRACKET" ){};
    const char* what() const noexcept override {
    	return message.c_str();
    }
};
class Missing_sign_ab : public std::exception {
private:
	string message;
public:
	Missing_sign_ab():message("MISSING SIGN AFTER BRACKET " ){};
    const char* what() const noexcept override {
    	return message.c_str();
    }
};


// verify if input_text contains invalid data
bool Calculator::legal_chars(){
	for(auto chr : input_text){
		//invalid char
		for(auto inv_chr : this->INVALID_CHAR){
			if(tolower(chr) == inv_chr){
				throw Invalid_char{string(1, inv_chr)};
			}
		}
		//invalid sign
		for(auto inv_chr : this->INVALID_SIGN){
					if(tolower(chr) == inv_chr){
						throw Invalid_sign{string(1, inv_chr)};
					}
				}
	}
	return true;
}

// verify if input_text can be mathematically resolved
bool Calculator::legal_statement(){

	// devide by 0
	if(input_text.find("/0") != string::npos){
		throw Devided_by_0{};
	}

	// check if there are enough brackets
	int bracket_ct{0};
	for(auto data : input_text){
		for(auto bracket : parenthesis){
			if(data == bracket){
				bracket_ct++;
			}
		}

	}
	if(bracket_ct %2 == 1){
		throw Missing_brackets{};
	}

	// multiple operators
	for(auto op_1 :operators){
		for(auto op_2:operators){
			string combination = op_1+op_2;
			if(input_text.find(combination) != string::npos){
				throw Multiple_operators{combination};
			}
		}
	}

	return true;
}

// move to a specific calculation method ( simple_calc /  priority_calc / complex_calc)
void Calculator::calculate(){
	if(verify_text()){
		cout<<"RESULT: "<<fixed<<setprecision(2)<<double_br_calc(input_text)<<endl;
	}

}

// all the verifications
bool Calculator::verify_text(){

	if(input_text.empty()) return false;

	//remove white spaces in input_text
	stringstream updated_text;
	for(auto chr:input_text){
		if(!isspace(chr)){
			updated_text<<chr;
		}
	}
	input_text = updated_text.str();

    // verify the text
	try{
		return legal_chars() && legal_statement();
	}
	catch(const Devided_by_0& e){
		cerr<<"ERROR: "<<e.what()<<endl;
		return false;
	}
	catch(const Missing_brackets& e){
		cerr<<"ERROR: "<<e.what()<<endl;
		return false;
	}
	catch(const Multiple_operators& e){
		cerr<<"ERROR: "<<e.what()<<endl;
		return false;
	}
	catch(const Invalid_sign& e){
		cerr<<"ERROR: "<<e.what()<<endl;
		return false;
	}
	catch(const Invalid_char& e){
		cerr<<"ERROR: "<<e.what()<<endl;
		return false;
	}
	return true;
}


// inserting the text in calculator
istream& operator>>(istream& is, Calculator& rhs){
	getline(is, rhs.input_text);
	return is;
}
