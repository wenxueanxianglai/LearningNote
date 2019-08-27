#include <iostream>
using namespace std;

int main()
{
  int sum = 0;
  int val = 0;

  // keep executing the while as long as val is less than or equal to 10
  while (val <= 10) {
    sum += val;       // assigns sum + val to sum
    ++val;            // add 1 to val
  }

  cout << "SUm of 1 to 10 inclusive is " << sum << endl;
  return 0;
}
