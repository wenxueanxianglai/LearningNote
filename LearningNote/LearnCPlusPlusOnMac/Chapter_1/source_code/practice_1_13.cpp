/*
*   Rewrite the exercises from 1.4.1  using for loops.
*/


/***********  old **********
// 1_9
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

// 1_10
int main()
{
  int Iter = 10;

  while (Iter >= 0) {
    cout << Iter << " ";
  }

  cout << endl;

  return 0;
}

// 1_11
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

******************************/

#include <iostream>

using namespace std;

int main()
{
  // begin  1_9
  int sum1_9 = 0;
  for(int val = 50; val <= 100; ++val) {
    sum += val;
  }

  cout << "Sum of 50 to 100 inclusive is "
       << sum1_9 << endl;

  // begin 1_10
  for(int val = 10; val >= 0; --val) {
    cout << val << " ";
  }

  // begin 1_11
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
  for( ; nVal1 <= nVal2; ++nVal1) {
    cout << nVal1 << " ";
  }
}
