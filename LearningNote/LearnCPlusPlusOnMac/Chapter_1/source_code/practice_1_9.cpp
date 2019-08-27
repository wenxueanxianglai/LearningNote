/*
*   Write a program that uses a while to sum the numbers from 50 to 100
*/

#include <iostream>

using namespace std;

int main()
{
  int Iter = 50;
  int sum = 0;
  while (Iter <= 100) {
    sum += Iter;
    ++Iter;
  }

  cout << "Sum of 50 to 100 inclusive is "
       << sum << endl;

  return 0;
}
