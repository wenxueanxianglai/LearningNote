/*
*   Write a program that prompts the user for two integers.
*   Print each number in the range specified by those two integers.
*/

#include <iostream>

using namespace std;

int main()
{
  cout << "Enter two numbers:" << endl;

  int nVal1 = 0;
  int nVal2 = 0;

  cin >> nVal1 >> nVal2;

  if (nVal1 > nVal2) {
    int temp = nVal1;
    nVal1 = nVal2;
    nVal2 = temp;
  }

  cout << "The range :" ;
  while (nVal1 <= nVal2 ) {
      cout << nVal1 << " ";
      ++nVal1;
  }

  return 0;
}
