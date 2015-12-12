#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iterator>
#include <deque>
#include <ctime>
#include "transforms.h"
#include "gtest/gtest.h"
#include "mydeque.h"

using std::cout;

typedef int timeType;

void fillIntDeque(size_t &n, MyDeque<int> &a) {
	for (size_t i = 0; i < n; ++i)
	{
		a.push_back(i);
		a.push_front(n - i);
	}
}

timeType getTime() {
	return clock();
}


TEST(DequeLikeDeque, PushTakeBack)
{
	MyDeque<int> a;
	for (size_t i = 1; i < 10; ++i)
	{
		a.push_back(i);
		ASSERT_EQ(i, a.back());
	}
}
TEST(DequeLikeDeque, PushTakeFront)
{
	MyDeque<int> a;
	for (size_t i = 1; i < 10; ++i)
	{
		a.push_front(i);
		ASSERT_EQ(i, a.front());
	}
}

TEST(DequeLikeDeque, PopFront)
{
	MyDeque<int> a;
	for (size_t i = 1; i < 10; ++i)
	{
		a.push_front(i);
	}
	for (size_t i = 1; i < 10; ++i)
	{
		ASSERT_EQ(10 - i, a.front());
		a.pop_front();
	}
}
TEST(DequeLikeDeque, PopBack)
{
	MyDeque<int> a;
	for (size_t i = 1; i < 10; ++i)
	{
		a.push_back(i);
	}
	for (size_t i = 1; i < 10; ++i)
	{
		ASSERT_EQ(10 - i, a.back());
		a.pop_back();
	}
}

TEST(DequeLikeDeque, CheckSize)
{
	MyDeque<int> a;
	size_t n = 10;
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(i, a.size());
		a.push_back(i);
		ASSERT_EQ(i + 1, a.size());
	}
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(n - i, a.size());
		a.pop_back();
	}
}

TEST(DequeLikeDeque, CheckEmpty)
{
	MyDeque<int> a;
	size_t n = 10;
	ASSERT_TRUE(a.empty());
	for (size_t i = 0; i < n; ++i)
		a.push_back(i);
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_FALSE(a.empty());
		a.pop_front();
	}
	ASSERT_TRUE(a.empty());
}
TEST(DequeLikeVector, SquareScobe)
{
	size_t n = 10;
	MyDeque<int> a;
	for (size_t i = 0; i < 10; ++i)
	{
		a.push_back(i);
		if (i)
			a.push_front(-static_cast<int>(i));
	}
	for (size_t i = 0; i < 19; ++i)
	{
		ASSERT_EQ(i - 9, a[i]);
	}
}

template <class iter> void constIteratorTest(iter &it)
{
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
}

template <class iter> void unconstIteratorTest(iter &it)
{
	constIteratorTest(it);
	ASSERT_EQ(8, it[4] = 8) << "error [] = ";
	it[4] = 5;
}

TEST(IteratorTest, simpleIterator)
{
	MyDeque<int> a(10);
	size_t n = 10;
	fillIntDeque(n, a);

	unconstIteratorTest(a.begin());

	ASSERT_TRUE (a.begin() < a.end()) << "error <";
	ASSERT_TRUE ( a.begin() <= a.end()) << "error <=";
	ASSERT_TRUE (a.end() >= a.begin()) << "error >=";
	ASSERT_TRUE (a.end() > a.begin()) << "error >";
	ASSERT_EQ (n * 2, a.end() - a.begin()) << "iter1 - iter2";

	std::vector <int> c;
	MyDeque<int> b;
	for (size_t i = 0; i < n; ++i)
	{
		b.push_back(n - i);
		c.push_back(n - i);
	}
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "fucking push_back";
	}
	std::sort(c.begin(), c.end());
	std::sort(b.begin(), b.end());
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "after sort";
	}
	std::reverse(c.begin(), c.end());
	std::reverse(b.begin(), b.end());
	for (size_t i = 0; i < n; ++i)
	{
		ASSERT_EQ(b[i], c[i]) << "after reverse";
	}
}

TEST(IteratorTest, ReverseIterator)
{
	MyDeque <int> a, b, c;
	size_t n = 10;
	fillIntDeque(n, c);
	for (size_t i = 0; i < n; ++i)
	{
		a.push_back(i);
		b.push_back(i);
	}
	std::reverse(c.begin(), c.end());
	unconstIteratorTest(c.rbegin()); //simple testing reverse iterators
	auto iter = a.begin();
	(*iter) = 0;
	std::reverse(a.begin(), a.end());
	std::vector <int> toA, toB;
	for (auto it = a.begin(); it != a.end(); ++it)
		toA.push_back(*it);
	for (auto it = b.rbegin(); it != b.rend(); ++it)
		toB.push_back(*it);
	for (size_t i = 0; i < n; ++i)
		ASSERT_EQ(toA[i], toB[i]) << "reverse";
	std::reverse(a.rbegin(), a.rend());
	for (size_t i = 0; i < n; ++i)
		ASSERT_EQ(b[i], a[i]) << "reverse to reverse";
	
}

TEST(IteratorTest, ConstIteratorTest)
{
	MyDeque <int>  c;
	size_t n = 10;
	fillIntDeque(n, c);
	constIteratorTest(c.cbegin()); //simple testing const iterators
}

TEST(IteratorTest, ConstReverseIteratorTest)
{
	MyDeque <int>  c;
	size_t n = 10;
	fillIntDeque(n, c);
	std::reverse(c.begin(), c.end());
	constIteratorTest(c.crbegin()); //simple testing const iterators
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
	ASSERT_EQ(a.size(), b.size());
}

void extendBoth(MyDeque<int> &my, std::deque<int> &your, size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		push_backToBoth(my, your, rand());
		push_frontToBoth(my, your, rand());
	}
}

template<class UniversalHeap> void extendOne(UniversalHeap &H, size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		H.push_back(rand());
		H.push_front(rand());
	}
}

void makeShorter(MyDeque<int> &my, std::deque<int> &your, size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		pop_backToBoth(my, your, rand());
		pop_frontToBoth(my, your, rand());
	}
}

template<class UniversalHeap> void makeShorterOne(UniversalHeap &H, size_t N)
{
	for (size_t i = 0; i < N; ++i)
	{
		H.pop_back();
		H.pop_front();
	}
}

void checkEqualDeques(const MyDeque<int> &my, const std::deque<int> &your, std::string mistake)
{
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

template <class UniversalDeque> double stressAllTime(size_t n)
{
	timeType t = getTime();
	size_t N = n * 4;
	UniversalDeque my;
	extendOne(my, N);
	makeShorterOne(my, N / 2);
	extendOne(my, N / 4); 
	makeShorterOne(my, N / 4);
	extendOne(my, N / 2);
	makeShorterOne(my, N / 4 * 3);
	reverse(my.begin(), my.end());
	makeShorterOne(my, N / 4);
	return (getTime() - t) * 1.0 ;
}
template <class UniversalDeque> double stressTimePerOperation(size_t n)
{
	return stressAllTime<UniversalDeque> stressAllTime(n) / (17 * n * 8);
}
void isLineTime(size_t N)
{
	FILE *linealFile =  fopen("lineal.txt", "w");
	size_t step = N / 100;
	for (size_t i = step; i < N; i += step)
		fprintf(linealFile, "%.6f\n", stressAllTime<MyDeque<int> >(i));
}

void compTimeWithRealDeque(size_t N)
{
	FILE *compareFile = fopen("myVSreal.txt", "w");
	size_t step = N / 10;
	for (size_t i = step; i < N; i += step)
		fprintf(compareFile, "%.6f %.6f\n", stressAllTime<MyDeque<int> >(i), stressAllTime<std::deque<int> > (i));
}


TEST(StressTest, Little)
{
	size_t N = 1 << 5;
	MyDeque<int> my;
	std::deque <int> your;
	extendBoth(my, your, N);
	makeShorter(my, your, N / 2);
	sortBothByNormalIterator(my, your);
	extendBoth(my, your, N / 4);
	makeShorter(my, your, N / 4);
	sortBothByReverseIterator(my, your);
	extendBoth(my, your, N / 2);
	makeShorter(my, your, N / 4 * 3);
	reverseBoth(my, your);
	makeShorter(my, your, N / 4);
	ASSERT_EQ(my.empty(), your.empty());
}

void testPerformance(size_t N)
{
	isLineTime(N);
	compTimeWithRealDeque(N);
}

TEST(Performance, lineal)
{
	testPerformance(1000);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}