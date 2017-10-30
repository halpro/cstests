/* 
 * File:   codinginterview.h
 * Author: alec
 *
 * Created on October 27, 2017, 12:26 PM
 */

#ifndef CODINGINTERVIEW_H
#define CODINGINTERVIEW_H


//! Calculate factorial with O(n) runtime

int factorial(int n) {
    if (n < 0)
        return -1;
    else if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

string stringPermutation(const string & str) {

}

void testCodingInterview() {
    cout << "Cracking coding interview tasks..." << endl;
    int intN = 10;
    cout << "1. factorial(" << intN << ") = ";
    cout << factorial(intN) << endl;
}
void interviewcake()
{
    
}

#endif /* CODINGINTERVIEW_H */

