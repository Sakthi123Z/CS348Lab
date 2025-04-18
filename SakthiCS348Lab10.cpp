/* Okay , so this is CS 348 Lab 10 and this is the Code on Visual Studio that will 
... oversee the numbers in the .txt and will print if the nums are right and the + 
and the program will take the file .txt and the produce the output which in on canvas
And The file name is SakthiLab10
 ... And Finally ... 
Name ... Sakthi Sivasubramanian 
First Created ... April 16 
Final Edits ... April 17
*/ 
#include <iostream> // this is including input-output stream
#include <fstream> // this is including file stream
#include <string> // this is including string class
#include <vector> // this is including vector container
#include <cctype> // this is including character check functions
#include <algorithm> // this is including algorithm utilities like remove

using namespace std; // this is using the standard namespace

// this is checking whether a string represents a valid double-formatted number
bool TheRightDouble(const string &s) {
    int a = s.length(); // this is getting the length of the string
    if (a == 0) return false; // this is rejecting empty strings
    int i = 0; // this is initializing index
    if (s[i] == '+' || s[i] == '-') i++; // this is skipping optional sign
    bool Numbers = false; // this is tracking if digits exist
    while (i < a && isdigit(s[i])) {
        i++; // this is moving through digit characters
        Numbers = true; // this is marking that digits were found
    }
    if (i < a && s[i] == '.') {
        i++; // this is skipping the dot
        bool Numbers1 = false; // this is tracking if digits exist after the dot
        while (i < a && isdigit(s[i])) {
            i++; // this is moving through decimal digits
            Numbers1 = true; // this is marking that decimal digits exist
        }
        if (!Numbers1) return false; // this is invalidating if nothing after dot
        return i == a && Numbers; // this is validating only if all parts are proper
    }
    return i == a && Numbers; // this is checking if input is a whole number
}

// this is standardizing the format by adding sign and flattening the decimal point
void normalize(string &s , int &decimals) {
    if (s[0] != '+' && s[0] != '-') s = "+" + s; // this is adding '+' if no sign
    if (s.find('.') == string::npos) s += ".0"; // this is appending ".0" if missing
    int pos = s.find('.'); // this is locating the dot position
    decimals = s.size() - pos - 1; // this is computing decimal places
    s.erase(pos , 1); // this is removing the dot
}

// this is adding two positive numeric strings
string add_positive_strings(const string &a , const string &b) {
    string result = ""; // this is the result string
    int carry = 0; // this is initializing carry
    for (int i = a.size() - 1 ; i >= 0 ; i--) {
        int d1 = a[i] - '0'; // this is converting character to digit
        int d2 = b[i] - '0'; // this is converting character to digit
        int sum = d1 + d2 + carry; // this is calculating the sum
        result = char('0' + (sum % 10)) + result; // this is inserting digit
        carry = sum / 10; // this is updating carry
    }
    if (carry) result = '1' + result; // this is appending leftover carry
    return result; // this is returning result
}

// this is subtracting one positive string from another (assuming a > b)
string subtract_positive_strings(const string &a , const string &b) {
    string result = ""; // this is the result string
    int borrow = 0; // this is initializing borrow
    for (int i = a.size() - 1; i >= 0; i--) {
        int d1 = a[i] - '0'; // this is extracting digit
        int d2 = b[i] - '0' + borrow; // this is extracting digit with borrow
        if (d1 < d2) {
            d1 += 10; // this is borrowing from the next digit
            borrow = 1; // this is setting borrow flag
        } else {
            borrow = 0; // this is clearing borrow
        }
        result = char('0' + (d1 - d2)) + result; // this is appending result digit
    }
    while (result.length() > 1 && result[0] == '0') result.erase(0 , 1); // this is removing leading zeros
    return result; // this is returning result
}

// this is the main string-based double addition function that supports sign and decimals
string AddStrings(string a , string b) {
    int adec , bdec; // this is storing number of decimal places
    normalize(a , adec); // this is normalizing a
    normalize(b , bdec); // this is normalizing b
    int maxd = max(adec , bdec); // this is finding max decimal precision
    while (adec < maxd) {
        a += "0"; // this is padding a
        adec++;
    }
    while (bdec < maxd) {
        b += "0"; // this is padding b
        bdec++;
    }

    string sa = a.substr(1); // this is slicing off the sign
    string sb = b.substr(1); // this is slicing off the sign
    int dot_a = sa.length() - maxd; // this is position of the decimal point in a
    int dot_b = sb.length() - maxd; // this is position of the decimal point in b

    string int_a = sa.substr(0 , dot_a); // this is extracting integer part of a
    string dec_a = sa.substr(dot_a); // this is extracting decimal part of a
    string int_b = sb.substr(0 , dot_b); // this is extracting integer part of b
    string dec_b = sb.substr(dot_b); // this is extracting decimal part of b

    int max_int_len = max(int_a.length() , int_b.length()); // this is calculating max integer length
    while (int_a.length() < max_int_len) int_a = "0" + int_a; // this is padding integer part of a
    while (int_b.length() < max_int_len) int_b = "0" + int_b; // this is padding integer part of b

    string res_int , res_dec; // this is result parts
    string sign = "+"; // this is initializing result sign

    bool aneg = a[0] == '-'; // this is checking if a is negative
    bool bneg = b[0] == '-'; // this is checking if b is negative

    if (aneg == bneg) { // this is for both same sign
        string sum_int = add_positive_strings(int_a , int_b); // this is integer addition
        int carry = 0; // this is carry for decimal addition
        string sum_dec = ""; // this is decimal result
        for (int i = dec_a.length() - 1; i >= 0; --i) {
            int digit_a = dec_a[i] - '0'; // this is extracting digit
            int digit_b = dec_b[i] - '0'; // this is extracting digit
            int sum = digit_a + digit_b + carry; // this is adding decimal digits
            sum_dec = char('0' + (sum % 10)) + sum_dec; // this is storing digit
            carry = sum / 10; // this is updating carry
        }
        if (carry) {
            sum_int = add_positive_strings(sum_int , "1"); // this is carrying to integer part
        }
        res_int = sum_int; // this is storing result integer
        res_dec = sum_dec; // this is storing result decimal
        sign = aneg ? "-" : "+"; // this is keeping sign
    } else { // this is if signs are different
        string abs_a = int_a + dec_a; // this is full number of a without sign
        string abs_b = int_b + dec_b; // this is full number of b without sign

        if (abs_a == abs_b) return "0.0"; // this is handling exact cancel

        bool a_abs_greater = abs_a > abs_b; // this is comparing magnitude

        string larger_int = a_abs_greater ? int_a : int_b; // this is larger integer part
        string smaller_int = a_abs_greater ? int_b : int_a; // this is smaller integer part
        string larger_dec = a_abs_greater ? dec_a : dec_b; // this is larger decimal part
        string smaller_dec = a_abs_greater ? dec_b : dec_a; // this is smaller decimal part

        sign = a_abs_greater ? a[0] : b[0]; // this is applying sign of larger number

        int borrow = 0; // this is initializing borrow
        res_dec = ""; // this is clearing decimal result
        for (int i = maxd - 1; i >= 0; --i) {
            int d1 = larger_dec[i] - '0'; // this is digit from larger
            int d2 = smaller_dec[i] - '0' + borrow; // this is digit from smaller with borrow
            if (d1 < d2) {
                d1 += 10; // this is borrowing
                borrow = 1; // this is setting borrow
            } else {
                borrow = 0; // this is clearing borrow
            }
            res_dec = char('0' + (d1 - d2)) + res_dec; // this is storing result
        }
        res_int = subtract_positive_strings(larger_int , smaller_int); // this is integer subtraction
    }

    if (res_int == "") res_int = "0"; // this is fixing empty integer result
    while (res_dec.length() < maxd) res_dec += "0"; // this is padding decimal result
    string res = res_int + "." + res_dec; // this is combining parts

    while (res.length() > 1 && res[0] == '0' && res[1] != '.') res.erase(0 , 1); // this is trimming leading zeros
    if (res[0] == '.') res = "0" + res; // this is fixing leading decimal point
    if (sign == "-" && res != "0.0") res = "-" + res; // this is applying final sign
    return res; // this is returning final result
}

// this is the main function
int main() {
    string filename; // this is the name of the file to open
    cout << "Please Add the file ...  "; // this is asking user input
    cin >> filename; // this is reading filename
    ifstream infile(filename); // this is opening file stream
    if (!infile.is_open()) return 1; // this is checking if file failed
    string line; // this is each input line
    while (getline(infile , line)) {
        line.erase(remove(line.begin() , line.end(), '\r') , line.end()); // this is removing carriage returns
        line.erase(remove(line.begin() , line.end(), ' ') , line.end()); // this is removing spaces
        if (TheRightDouble(line)) {
            cout << "valid: " << line << endl; // this is printing valid number
            string result = AddStrings(line , "-123.456"); // this is adding with fixed number
            cout << "sum: " << result << endl; // this is printing result
        } else {
            cout << "invalid: " << line << endl; // this is printing invalid message
        }
    }
    infile.close(); // this is closing file
    return 0; // this is ending program
}
