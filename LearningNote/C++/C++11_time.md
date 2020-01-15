# 获取时间
---
```C++
auto pNow = std::chrono::system_clock::now();
std::time_t cNow = std::chrono::system_clock::to_time_t(pNow);
std::stringstream ss;
ss << std::put_time(std::localtime(&cNow), "%Y-%m-%d-%H-%M-%S");

std::string strNowTime;
ss >> strNowTime;
```