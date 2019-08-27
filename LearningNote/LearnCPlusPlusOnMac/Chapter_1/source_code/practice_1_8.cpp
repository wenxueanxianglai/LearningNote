/*
*   Indicate which, if any, of the following output statement are legal:
*/

#include <iostream>

int main()
{
  std::cout << "/*";      //合法
  std::cout << "*/";      // 合法
//  std::cout << /* "*/" */;  // 不合法 
  std::cout << /*  "*/" /* "/*"  */;   //合法
  return 0;
}
/*
*  After you've predicted what will happen, test your answers by compiling a
*  program with each of these statements. Correct any errors you encounter
*/
