/*
*   What does the following for loop do? what is the final value of sum?
*/

int main()
{
  int sum = 0;
  for(int i = -100; i <= 100; ++i)
    sum += i;
}

/***************
i     -100    -99           .....       99            100
sum   -100    -100 + -99                sum99         0

So, the final value of sum is zero.
****************/
