# auto 与 decltype
---
```C++

using typeFun = void( * )(int);

void testfunct(int i) {
	std::cout << "testfunct" << std::endl;
	return;
}

void print(int i) {
	std::cout << "print: " << i << std::endl;
	return;
}

//
auto fudn(int i) -> decltype(&testfunct){
	return print;
}

decltype(&testfunct) ddffun(double i) {
	return print;
}

auto ffffdun(double i) ->  void ( * )(int){
	return print;
}

typeFun dfff(double i) {
	return print;
}

void( * fun(double i)) (int) {
	return testfunct;
}

auto ffun(double i) {
	return testfunct;
}


```

decltype 对 普通的内置类型推导可以
对于 函数的推导，普通的函数应使用 & ，这样看起来，对于普通函数来说，它就是对象，而不是指针。

对于auto ，因为针对的是对象，所以这里是可以的。
