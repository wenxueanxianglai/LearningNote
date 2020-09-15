/*
Exercise 2.26: Which of the following are legal? For those that are illegal, explain why.
*/

int main()
{
    //const int buf;   must init
    int cnt = 0;
    const int sz = cnt;
    ++cnt;
    //++sz;  can't change
}