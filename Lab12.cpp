//AI model used: ChatGPT
//Date consulted: 05/06/26


#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

double extractNumeric(const string& str) {
//PROMPT 1:
// Write me C++ code for a double extractNumeric(const string& str) that looks through 
// string left to right and checks for signed numbers. It checks for +/- before a number in a 
// string. If +/- is by itself, -999999.99 gets returned. Decimals are allowed. It should only 
// stop on a sign if it is directly followed by a digit or. 

    int i=0;
    int n=str.length();

    while (i < n) {

    if (isdigit(str[i]) || str[i] == '.') {
        break;
    }

    if ((str[i] == '+' || str[i] == '-') && i + 1 < n && (isdigit(str[i+1]) || str[i+1] == '.')) {
        break;
    }
    i++;
}
    if (i>=n) {
        return -999999.99;
    }

    int sign=1;
    bool digits=false;

    if (str[i]=='+' || str[i]=='-') {
        if (i + 1 < n && (isdigit(str[i+1])||str[i+1]=='.')) {
            if (str[i]=='-') sign=-1;
            i++;
        } else {
            return -999999.99;
        }
    }
//The above block of code was generated for prompt 1. I have read through each line, and fully 
//understand how the code works. I’ve also tested and confirmed the above code works.

//PROMPT 2:
//Adding to the above code, give me code that parses the whole number before a decimal 
// and the digits after the decimal point in the number. If no digits are found while parsing the string,
// return -999999.99. After parsing the whole number and decimal part, combine them into a final result

    double number = 0; 
    int digitCount = 0;
    while (i < n && isdigit(str[i])) {
         digits = true; 
         digitCount++;
         if (digitCount > 18) {
            return -999999.99;
    }
         number = number * 10 + (str[i] - '0'); 
         i++; 
    }


    double fraction = 0;
    double divisor = 10;

    if (i < n && str[i] == '.') {
        i++;

    while (i < n && isdigit(str[i])) {
        digits = true;
        fraction += (str[i] - '0') / divisor;
        divisor *= 10;
        i++;
    }
}
    if (!digits) {
    return -999999.99;
}

//The above code was generated for prompt 2. I modified it by adding checks for values outside of the 
// allowed range. After modification and testing the code, it works per requirements, and I understand 
// how each line of the code works.


//PROMPT 3:
//Adding to the above code, generate code that supports scientific notation (e/E), allows statements 
//like “-2.E+3”, and rejects statements like “1e, 1e+, or 1e-”. The code should apply exponents and
//return the parsed number as final result.
//Valid ranges include: 
//Double values from -1.7e308 to 1.7e308
//If the number is outside of the range, return -999999.99
//large exponents like 1e999 should be treated as out of range


    double result = (number + fraction) * sign;


    if (i < n && (str[i] == 'e' || str[i] == 'E')) {
        i++;

        int expSign = 1;

        if (i < n && (str[i] == '+' || str[i] == '-')) {
            if (str[i] == '-') {
                expSign = -1;
            }
            i++;
        }

        if (i >= n || !isdigit(str[i])) {
            return -999999.99;
        }

        int exponent = 0;

        while (i < n && isdigit(str[i])) {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }

        exponent *= expSign;

        if (exponent > 0) {
            for (int j = 0; j < exponent; j++) {
                result *= 10;
            }
        } else {
            for (int j = 0; j < -exponent; j++) {
                result /= 10;
            }
        }
    }

        if (i<n) {
            if (isdigit(str[i]) || str[i]=='.') {
            return -999999.99;
        }
    }
        
        if (result>1.7e308 || result<-1.7e308 || isinf(result)) {
            return -999999.99;
        }

    return result;
}

//The above code was generated for prompt 3. I modified it by adding checks for extra digits/decimals
//when parsing. I also added checks for numbers outside of the valid double range.After modification and 
// testing the code, it works per requirements, and I understand how each line of the code works.


//The below code was writting by me.
int main()  {
    string input;
    while (true) {
        cout << "Enter a string (or 'END' to quit):";
        getline(cin,input);
        if (input=="END") {
            cout << "Program terminated." << endl;
            break;
        }
        double result=extractNumeric(input);

        if (result==-999999.99) {
            cout << "Invalid input: no valid floating-point number found" << endl;
        } else {
            cout << fixed << setprecision(4);
            cout << "Extracted number: " << result << endl;
        }
    }
    return 0;
}