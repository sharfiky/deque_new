#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iterator>
#include <cmath>
#include <algorithm>

const int minCap = 8;

int norm(int a, int b)
{
	return (a + b) % b;
}


template<class T> class MyDeque {
private:
	int capacity_;
	int begin_, end_;
	std::vector <T> val;

	int norm(int n)
	{
		return (n + capacity_) % capacity_;
	}

	/*int norm(int n)
	{
	return n % capacity_;
	}*/


public:
	MyDeque() : capacity_(minCap), val(minCap),
		end_(0), begin_(minCap - 1) {
	}
	MyDeque(int cap) : end_(0), capacity_(std::max(cap, minCap)),
					val(std::max(cap, minCap)), begin_(std::max(cap, minCap) - 1)
	{}
	MyDeque(const MyDeque &some) : capacity_(some.capacity_), val(some.val),
		end_(some.end_), begin_(some.begin_) {
	}
	/*	MyDeque& operator = (const MyDeque & some)
	{
	val = some.val;
	capacity_ = some.capacity_;
	begin_ = some.begin_;
	end_ = some.end_;
	std::cout << "EQ\n";
	return *this;
	}

	*/
	/*
	MyDeque( MyDeque &&some):
	{
	val = some.val;
	capacity_ = some.capacity_;
	begin_ = some.begin_;
	end_ = some.end_;
	cout << "MOVE\n";
	}
	*/
	~MyDeque() {}
	int size() const
	{
		return (end_ + capacity_ - begin_ - 1) % capacity_;
	}
	bool empty() const
	{
		return !(size());
	}
	void checkToMakeLarger()
	{
		if (begin_ == end_)
			makeLarger();
	}
	void checkToMakeSmaller()
	{
		if (size() < capacity_ / 4 && size() / 2 > minCap)
			makeSmaller();
	}
	void makeLarger()
	{
		std::vector<T> tmp(capacity_ * 2);
		for (int i = norm(begin_ + 1), j = 0; i != end_; i = norm(++i), ++j)
			tmp[j] = val[i];
		val = tmp;
		end_ = size();
		capacity_ *= 2;
		begin_ = norm(capacity_ - 1);
	}
	void makeSmaller()
	{
		std::vector<T> tmp(capacity_ / 2);
		for (int i = norm(begin_ + 1), j = 0; i != end_; i = norm(i + 1), ++j)
			tmp[j] = val[i];
		val = tmp;
		end_ = size();
		capacity_ /= 2;
		begin_ = norm(capacity_ - 1);
	}
	void push_back(const T &tmp)
	{
		val[end_] = tmp;
		//++end_; //--begin_;
		end_ = norm(1 + end_);
		checkToMakeLarger();
	}
	void push_front(const T &tmp)
	{

		val[begin_] = tmp;
		begin_ = norm(begin_ - 1);
		checkToMakeLarger();
	}
	void pop_back() //front
	{
		//--end_; //++begin_;
		end_ = norm(end_ - 1);
		checkToMakeSmaller();
	}
	void pop_front()
	{
		begin_ = norm(begin_ + 1);
		checkToMakeSmaller();
	}
	T front() {
		return val[norm(begin_ + 1)];
	}
	T front() const {
		return val[norm(begin + 1, capacity_)];
	}
	T back() {
		return val[norm(end_ - 1)];
	}
	T back() const {
		return val[norm(end - 1, capacity_)];
	}
	int head() {
		return norm(begin_ + 1);
	}
	int tail()
	{
		return end_;
	}
	T& operator [](int id)
	{
		return (val[norm(begin_ + 1 + id)]);
	}
	T& operator [](int id) const
	{
		return (val[norm(begin + 1 + id), capacity_]);
	}
	template <class R>
	class base_iterator : public std::iterator<std::random_access_iterator_tag, MyDeque<T> >
	{
	private:
		T *ptr;
		int num;
		int capacity_;
		int begin_;
		base_iterator& norm(const base_iterator& a, difference_type delta) const
		{
			int new_pos = (a.num + delta + a.capacity_) % a.capacity_;
			return base_iterator(a.ptr - a.num + new_pos, new_pos, a.capacity_, a.begin_);
		}
		int toGoodVision(const base_iterator& a) const
		{
			return (-a.begin_ - 1 + a.num + a.capacity_) % a.capacity_;
		}
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef R& reference;
		typedef R* pointer;
		typedef size_t size_type;
		typedef std::random_access_iterator_tag iterator_category;

		base_iterator(T* Other, int num, int capacity_, int begin_) : num(num), capacity_(capacity_), begin_(begin_)
		{
			ptr = Other;
		}
		base_iterator(const base_iterator& other) : num(other.num), capacity_(other.capacity_), begin_(other.begin_)
		{
			ptr = other.ptr;
		}
		~base_iterator()
		{
		}
		base_iterator& operator =(const base_iterator& Other)
		{
			ptr = Other.ptr;
			num = Other.num;
			capacity_ = Other.capacity_;
			begin_ = Other.begin_;
			return *this;
		}
		base_iterator* operator ->() const
		{
			return &**this;
		}
		reference operator *() const
		{
			return *ptr;
		}
		base_iterator& operator ++()
		{

			return *this = norm(*this, 1);
		}
		base_iterator& operator ++(int)
		{

			return *this = norm(*this, 1);;
		}
		base_iterator& operator --()
		{
			return *this = norm(*this, -1);
		}
		base_iterator& operator --(int)
		{
			return *this = norm(*this, -1);
		}
		base_iterator& operator +=(const difference_type& idx)
		{
			return *this = norm(*this, idx);
		}
		base_iterator& operator -=(const difference_type& idx)
		{
			return *this = norm(*this, -idx);
		}
		base_iterator operator +(const difference_type& idx) const
		{
			return norm(*this, idx);
		}
		base_iterator operator -(const difference_type& idx) const
		{
			base_iterator Tmp(*this);
			return Tmp -= idx;
		}
		reference operator [](const size_type& idx) const // I don't know
		{
			return *(*this + idx);
		}
		bool operator <(const base_iterator& Other) const
		{
			return toGoodVision(*this) < toGoodVision(Other);
		}
		bool operator >(const base_iterator& Other) const
		{
			return toGoodVision(*this) > toGoodVision(Other);
		}
		bool operator ==(const base_iterator& Other) const
		{
			/*int a = toGoodVision(Other);
			//int b = toGoodVision(*this);
			int b = -a;*/
			return toGoodVision(Other) == toGoodVision(*this);
		}
		bool operator !=(const base_iterator& Other) const
		{
			return !(*this == Other);
			//return toGoodVision(*this) == toGoodVision(Other);
		}
		bool operator <=(const base_iterator& Other) const
		{
			return toGoodVision(*this) <= toGoodVision(Other);
		}
		bool operator >=(const base_iterator& Other) const
		{
			return toGoodVision(*this) >= toGoodVision(Other);
		}
		difference_type operator -(const base_iterator& Other) const
		{
			return (num + capacity_ - Other.num) % capacity_;
		}
	};
	typedef base_iterator<T>       iterator;
	typedef base_iterator<const T> const_iterator;
	typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
	typedef std::reverse_iterator<iterator>        reverse_iterator;
	iterator begin()
	{
		return iterator(&val[head()], head(), capacity_, begin_);
	}
	iterator end()
	{
		return iterator(&val[tail()], tail(), capacity_, begin_);
	}
	iterator begin() const
	{
		return iterator(&val[head()], head(), capacity_, begin_);
		//return begin();
	}
	iterator end() const
	{
		return iterator(&val[tail()], tail(), capacity_, begin_);
	}
	const_iterator cend()
	{
		return const_iterator(&val[tail()], tail(), capacity_, begin_);
	}
	const_iterator cbegin()
	{
		return const_iterator(&val[head()], head(), capacity_, begin_);
	}
	const_iterator cend() const
	{
		return const_iterator(&val[tail()], tail(), capacity_, begin_);
	}
	const_iterator cbegin() const
	{
		return const_iterator(&val[head()], head(), capacity_, begin_);
	}
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	reverse_iterator rend() const
	{
		return reverse_iterator(begin());
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	reverse_iterator rbegin() const
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator crend()
	{
		//return reverse_iterator(cbegin());
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cbegin());
	}
	const_reverse_iterator crbegin() 
	{
		//return reverse_iterator(cend());
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cend());
	}
	const_reverse_iterator crend() const
	{
		//return reverse_iterator(cbegin());
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cbegin());
	}
	const_reverse_iterator crbegin() const
	{
		//return reverse_iterator(cend());
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cend());
	}
};
