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
