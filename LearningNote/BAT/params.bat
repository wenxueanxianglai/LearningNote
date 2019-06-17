@echo off
echo %1
echo %~1
echo %0
echo %~f0
echo %~d0
echo %~p0
echo %~n0
echo %~x0
echo %~s0
echo %~a0
echo %~t0
echo %~z0

@rem 设置变量p
set p=abcdefghig	

@rem 打印变量p
echo %p%		

@rem 显示变量p中第6位之后的字符串 	
echo %p:~6%			