/*
*   In addition to the ++ operator that adds 1 to its operand,
*   there is a decrement operator (--) that subtracts 1.
* Use the decrement operator to write a while that prints the numbers from ten down to zero.
*/

#include <iostream>

using namespace std;

int main()
{
  int Iter = 10;

  while (Iter >= 0) {
    cout << Iter << " ";
  }

  cout << endl;

  return 0;
}
