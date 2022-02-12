// Fibonacci Series using Recursion
// #include <bits/stdc++>
#include <iostream>

using namespace std;
 
int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}
 
int main ()
{
    int n = 15;
    cout << "The " << n <<"th fibonacci number is: " << fib(n) << endl;

    return 0;
}
 
