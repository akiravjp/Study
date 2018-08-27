#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

// ����64λ����
typedef __int64 int64_t;

// ��ȡϵͳ�ĵ�ǰʱ�䣬��λ΢��(us)
int64_t GetSysTimeMicros()
{
	// ��1601��1��1��0:0:0:000��1970��1��1��0:0:0:000��ʱ��(��λ100ns)
#define EPOCHFILETIME   (116444736000000000UL)
	FILETIME ft;
	LARGE_INTEGER li;
	int64_t tt = 0;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	// ��1970��1��1��0:0:0:000�����ڵ�΢����(UTCʱ��)
	tt = (li.QuadPart - EPOCHFILETIME) / 10;
	return tt;
}

// ����1��n֮�����������ĺ�
int64_t CalculateSum(int n)
{
	if (n < 0)
	{
		return -1;
	}

	/*int64_t sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += i;
	}
	return sum;*/
	// �Ż�
	return (n * (1 + n)) >> 1;
}

// �ж�����n�Ƿ�Ϊ����
//bool IsPrime(int n)
//{
//	if (n < 2)
//	{
//		return false;
//	}
//
//	for (int i = 2; i < n; i++)
//	{
//		if (n %i == 0)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
// �ж�����n�Ƿ�Ϊ�������Ż���
bool IsPrime(int n)
{
	if (n < 2)
	{
		return false;
	}

	if (n == 2)
	{
		return true;
	}

	//��2�ı����޳���
	if (n % 2 == 0)
	{
		return false;
	}

	// ��ʵ���ܱ�С��n�ĸ����µ�������������һ������
	for (int i = 3; i*i <= n; i += 2)
	{
		if (n % i == 0)
		{
			return false;
		}
	}

	return true;
}


void PrintPrimeSum()
{
	int64_t startTime = GetSysTimeMicros();
	std::ofstream outfile;
	outfile.open("D:\\Test\\PrimeSum.dat", std::ios::out | std::ios::app);
	int count = 0;
	int64_t sum = 0;
	for (int i = 10000; i <= 100000; i++)
	{
		if (IsPrime(i))
		{
			sum = CalculateSum(i);
			//std::cout << sum << "\t";
			outfile << sum << "\t";
			count++;
			if (count % 10 == 0)
			{
				//std::cout << std::endl;
				outfile << std::endl;
			}
		}
	}
	outfile.close();
	int64_t usedTime = GetSysTimeMicros() - startTime;
	int second = usedTime / 1000000;
	int64_t temp = usedTime % 1000000;
	int millise = temp / 1000;
	int micros = temp % 1000;
	std::cout << "ִ��ʱ��:" << second << "s " << millise << "' " << micros << "''" << std::endl;
}