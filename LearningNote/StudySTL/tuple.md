# tuple
---
## 是什么：
* 是元组
* pair 的扩展

## 操作
### 1. 组装
#### make_tuple
```C++
std::string names[3] = { "alice", "bob", "carl" };
char ranks[3] = { 'A', 'B', 'C' };
int score[3] = { 5, 6, 7 };

// 组装  
auto mStudent = std::make_tuple(names[0], ranks[0], score[0]);
cout << std::get<0>(mStudent) << endl
  << std::get<1>(mStudent) << endl
  << std::get<2>(mStudent) << endl;
  // 但凡容器，都是拷贝的值, 所以，绕过这个，就用引用和指针。。。不过还是拷贝的值，只是这时候拷贝的是引用
	auto mStudent2 = std::make_tuple(names[0], ranks[0], std::ref(score[0]));
	score[0] += 10;
	cout << make_pair(score[0], get<2>(mStudent)) << endl;		// 所以 这里的值 为 (15, 5)
	cout << make_pair(score[0], get<2>(mStudent2)) << endl;		// 所以 这里的值 为 (15, 15)

	get<2>(mStudent) += 100;
	cout << make_pair(score[0], get<2>(mStudent)) << endl;    // 这里值为 (15, 105)
```
### 2. 拆包
#### std::tie()
```C++
std::string hoge;
char piyo;
int fuga;
std::tie(hoge, piyo, fuga) = mStudent;
cout << hoge << endl
  << piyo << endl
  << fuga << endl;
```
### 3. 利用tuple进行输出
```C++
template<std::size_t I = 0, typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type printtp(Tuple t) {

}

template<std::size_t I=0, typename Tuple>
typename std::enable_if<
	I < std::tuple_size<Tuple>::value
	>::type printtp(Tuple t) {
	std::cout << std::get<I>(t) << std::endl;
	printtp<I + 1>(t);
}

template<typename... Args>
void print(Args... args)
{
	printtp(std::make_tuple(args...));
}
```
