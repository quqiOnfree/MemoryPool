﻿//test file
//测试文件

#include <iostream>
#include <ctime>
#include <memory>
#include "MemoryPool.h"

using namespace std;

int main()
{
	size_t times = 100000000;
	size_t* a;

	//允许单个类型获取内存的内存池，不允许生成数组
	//release 获取内存和释放内存平均耗时 1.22e-09s
	qmem::SingleDataTypeMemoryPool<size_t> sd;
	clock_t start = clock();
	for (size_t i = 0; i < times; ++i)
	{
		a = sd.allocate();
		sd.deallocate(a);
	}
	cout << static_cast<long double>(clock() - start) / CLOCKS_PER_SEC / times << '\n';

	//允许所有类型获取内存的内存池，允许生成数组
	//release 获取内存和释放内存平均耗时 6.72e-09s
	qmem::BaseMemoryPool bmp;
	start = clock();
	for (size_t i = 0; i < times; ++i)
	{
		a = bmp.allocate<size_t>();
		bmp.deallocate(a);
	}
	cout << static_cast<long double>(clock() - start) / CLOCKS_PER_SEC / times << '\n';

	//标准库内存池
	//release 获取内存和释放内存平均耗时 4.991e-08s
	allocator<size_t> stdAllocator;
	start = clock();
	for (size_t i = 0; i < times; ++i)
	{
		a = stdAllocator.allocate(1);
		stdAllocator.deallocate(a, 1);
	}
	cout << static_cast<long double>(clock() - start) / CLOCKS_PER_SEC / times << '\n';

	return 0;
}