#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>
#include <deque>
#include "gtest/gtest.h"
#include "mydeque.h"

using std::cout;

void fillIntDeque(int &n, MyDeque<int> &a) {
	for (int i = 0; i < n; ++i)
	{
		a.push_back(i);
		a.push_front(n - i);
	}
}



TEST(DequeLikeDeque, PushTakeBack)
{
	MyDeque<int> a;
	for (int i = 1; i < 10; ++i)
	{
		a.push_back(i);
		ASSERT_EQ(i, a.back());
	}
}
TEST(DequeLikeDeque, PushTakeFront)
{
	MyDeque<int> a;
	for (int i = 1; i < 10; ++i)
	{
		a.push_front(i);
		ASSERT_EQ(i, a.front());
	}
}

TEST(DequeLikeDeque, PopFront)
{
	MyDeque<int> a;
	for (int i = 1; i < 10; ++i)
	{
		a.push_front(i);
	}
	for (int i = 1; i < 10; ++i)
	{
		ASSERT_EQ(10 - i, a.front());
		a.pop_front();
	}
}
TEST(DequeLikeDeque, PopBack)
{
	MyDeque<int> a;
	for (int i = 1; i < 10; ++i)
	{
		a.push_back(i);
	}
	for (int i = 1; i < 10; ++i)
	{
		ASSERT_EQ(10 - i, a.back());
		a.pop_back();
	}
}

TEST(DequeLikeDeque, CheckSize)
{
	MyDeque<int> a;
	int n = 10;
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(i, a.size());
		a.push_back(i);
		ASSERT_EQ(i + 1, a.size());
	}
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(n - i, a.size());
		a.pop_back();
	}
}

TEST(DequeLikeDeque, CheckEmpty)
{
	MyDeque<int> a;
	int n = 10;
	ASSERT_TRUE(a.empty());
	for (int i = 0; i < n; ++i)
		a.push_back(i);
	for (int i = 0; i < n; ++i)
	{
		ASSERT_FALSE(a.empty());
		a.pop_front();
	}
	ASSERT_TRUE(a.empty());
}
TEST(DequeLikeVector, SquareScobe)
{
	int n = 10;
	MyDeque<int> a;
	for (int i = 0; i < 10; ++i)
	{
		a.push_back(i);
		if (i)
			a.push_front(-i);
	}
	for (int i = 0; i < 19; ++i)
	{
		ASSERT_EQ(i - 9, a[i]);
	}
}

long long intToLong(int &a)
{
	return a * (1 << 32) + a;
}
int intToInt(int &a)
{
	return a;
}

std::string intToString(int &a)
{
	std::string s;
	int n = a;
	while (n > 0)
	{
		s += ('A' + n % 26);
		n /= 26;
	}
	return s;
}



TEST(IteratorTest, simpleIterator)
{
	MyDeque<int> a(10);
	int n = 10;
	fillIntDeque(n, a);
	auto it = a.begin(), finish = a.end();
	ASSERT_EQ(1, *it);
	++it;
	ASSERT_EQ(2, *it) << "++error";
	--it;
	ASSERT_EQ(1, *it) << "--error";
	it++;
	ASSERT_EQ(2, *it) << "error++";
	it--;
	ASSERT_EQ(1, *it) << "error--";
	ASSERT_EQ(6, *(it += 5)) << "error+=";
	ASSERT_EQ(4, *(it - 2)) << "error - idx";
	ASSERT_EQ(1, *(it -= 5)) << "error-=";
	ASSERT_EQ(4, *(it + 3)) << "error + idx";
	ASSERT_EQ(5, it[4]) << "error []";
	ASSERT_EQ(8, it[4] = 8) << "error [] = ";
	it[4] = 5;

	ASSERT_TRUE (a.begin() < a.end()) << "error <";
	ASSERT_TRUE ( a.begin() <= a.end()) << "error <=";
	ASSERT_TRUE (a.end() >= a.begin()) << "error >=";
	ASSERT_TRUE (a.end() > a.begin()) << "error >";
	ASSERT_EQ (n * 2, a.end() - a.begin()) << "iter1 - iter2";

	std::vector <int> c;
	MyDeque<int> b;
	for (int i = 0; i < n; ++i)
	{
		b.push_back(n - i);
		c.push_back(n - i);
	}
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "fucking push_back";
	}
	std::sort(c.begin(), c.end());
	std::sort(b.begin(), b.end());
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "after sort";
	}
	std::reverse(c.begin(), c.end());
	std::reverse(b.begin(), b.end());
	for (int i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "after reverse";
	}
}

TEST(IteratorTest, ReverseIterator)
{
	MyDeque <int> a, b;
	int n = 9;
	for (int i = 0; i < n; ++i)
	{
		a.push_back(i);
		b.push_back(i);
	}
	auto iter = a.begin();
	(*iter) = 0;

	std::reverse(a.begin(), a.end());
	std::vector <int> toA, toB;
	for (auto it = a.begin(); it != a.end(); ++it)
		toA.push_back(*it);
	for (auto it = b.rbegin(); it != b.rend(); ++it)
		toB.push_back(*it);
	for (int i = 0; i < n; ++i)
		ASSERT_EQ(toA[i], toB[i]) << "reverse";
	std::reverse(a.rbegin(), a.rend());
	for (int i = 0; i < n; ++i)
		ASSERT_EQ(b[i], a[i]) << "reverse to reverse";
	
}

void push_backToBoth(MyDeque<int> &a, std::deque<int> &b, int x)
{
	a.push_back(x);
	b.push_back(x);
	ASSERT_EQ(a.size(), b.size());
	ASSERT_EQ(a.back(), b.back());
}

void pop_backToBoth(MyDeque<int> &a, std::deque<int> &b, int x)
{
	ASSERT_EQ(a.empty(), b.empty());
	if (!a.empty())
	{
		a.pop_back();
		b.pop_back();
		ASSERT_EQ(a.size(), b.size());
		ASSERT_EQ(a.empty(), b.empty());
		if (!a.empty())
			ASSERT_EQ(a.back(), b.back());
	}
}

void pop_frontToBoth(MyDeque<int> &a, std::deque<int> &b, int x)
{
	ASSERT_EQ(a.empty(), b.empty());
	if (!a.empty())
	{
		a.pop_front();
		b.pop_front();
		ASSERT_EQ(a.size(), b.size());
		ASSERT_EQ(a.empty(), b.empty());
		if (!a.empty())
			ASSERT_EQ(a.front(), b.front());
	}
}

void push_frontToBoth(MyDeque<int> &a, std::deque<int> &b, int x)
{
	a.push_front(x);
	b.push_front(x);
	ASSERT_EQ(a.front(), b.front());
}

void extend(MyDeque<int> &my, std::deque<int> &your, int N)
{
	for (int i = 0; i < N; ++i)
	{
		push_backToBoth(my, your, rand());
		push_frontToBoth(my, your, rand());
	}
}

void makeShorter(MyDeque<int> &my, std::deque<int> &your, int N)
{
	for (int i = 0; i < N; ++i)
	{
		pop_backToBoth(my, your, rand());
		pop_frontToBoth(my, your, rand());
	}
}
void checkEqualDeques(const MyDeque<int> &my, const std::deque<int> &your, std::string mistake)
{
	bool ans = 1;
	ASSERT_EQ(my.size(), your.size());
	for (size_t i = 0; i < my.size(); ++i)
		ASSERT_EQ(my[i], your[i]) << "mistake in " << mistake;
}

void sortBothByNormalIterator(MyDeque<int> &my, std::deque<int> &your)
{
	std::sort(my.begin(), my.end());
	std::sort(your.begin(), your.end());
	checkEqualDeques(my, your, "normalIterator");
}

void sortBothByReverseIterator(MyDeque<int> &my, std::deque<int> &your)
{
	std::sort(my.rbegin(), my.rend());
	std::sort(your.rbegin(), your.rend());
	checkEqualDeques(my, your, "ReverseIterator");
}

void reverseBoth(MyDeque<int> &my, std::deque<int> &your)
{
	std::reverse(my.begin(), my.end());
	std::reverse(your.begin(), your.end());
}




TEST(StressTest, Little)
{
	int N = 1 << 5;
	MyDeque<int> my;
	std::deque <int> your;
	extend(my, your, N);
	makeShorter(my, your, N / 2);
	N /= 2; //N = n / 2
	sortBothByReverseIterator(my, your);
	extend(my, your, N / 2); // N / 2 = n / 4
	N += N / 2; // N = n * 0.75
	makeShorter(my, your, N / 3);
	N -= N / 3; //N = n / 2
	extend(my, your, N);
	N *= 2;
		
	makeShorter(my, your, N / 4 * 3);
	N /= 4; // N = n / 4
	reverseBoth(my, your);
	makeShorter(my, your, N);
	ASSERT_EQ(my.empty(), your.empty());
}



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}