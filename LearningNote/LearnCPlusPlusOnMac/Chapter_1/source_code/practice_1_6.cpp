/*
*   Explain whether the following program fragment is legal.
*/

#include < iostream >

int main()
{

  // 这段代码片段 不合法
  // 原因 ： C++的语句话 不以 换行为一句，而是以 分号为结束
  //  std::cout << "The sum of " << v1;
  //          << " and " << v2;
  //          << " is " << v1 + v2 << std::endl;


  /*
  *   If the program is legal, what does it do?
  *   If the program is not legal, why not?
  *   How would you fix it?
  */
  // 上述代码片段目的想输出 v1 + v2 的和， 把后面的分号去掉就行了
    std::cout << "The sum of " << v1;
            << " and " << v2;
            << " is " << v1 + v2 << std::endl;


  return 0;
}
