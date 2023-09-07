#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

int main() {
	while(true){
		Calculator calculator;
		cin>>calculator;
		calculator.calculate();
	}

    return 0;
}
