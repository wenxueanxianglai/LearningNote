/*
*   Write your own version of a program that prints the sum of a set of integers read from cin
*/

#include <iostream>

using namespace std;

int main()
{
  int sum = 0;
  int val = 0;

  while(cin >> val) {
    sum += val;
  }

  cout << "Sum is " << sum << endl;

  return 0;
}
