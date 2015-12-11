#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iterator>
#include <cmath>
#include <algorithm>

const int minCap = 8;

template<class Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::difference_type difference_type;
	typedef difference_type distance_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
};
template<class Type>
struct iterator_traits<Type*> {
	typedef std::random_access_iterator_tag iterator_category;
	typedef Type value_type;
	typedef ptrdiff_t difference_type;
	typedef difference_type distance_type;
	typedef Type *pointer;
	typedef Type& reference;
};
template<class Type>
struct iterator_traits<const Type*> {
	typedef std::random_access_iterator_tag iterator_category;
	typedef Type value_type;
	typedef ptrdiff_t difference_type;
	typedef difference_type distance_type;
	typedef const Type *pointer;
	typedef const Type& reference;
};

template<class T> class MyDeque {
private:
	int capacity_;
	int begin_, end_;
	std::vector <T> value_;

	int normilize_(int n) const
	{
		return (n + capacity_) % capacity_;
	}


public:
	MyDeque() : capacity_(minCap), value_(minCap),
		end_(0), begin_(0) {
	}
	MyDeque(int cap) : end_(0), capacity_(std::max(cap, minCap)),
					value_(std::max(cap, minCap)), begin_(0)
	{}
	MyDeque(const MyDeque &some) : capacity_(some.capacity_), value_(some.value_),
		end_(some.end_), begin_(some.begin_) {
	}
	MyDeque(MyDeque &&some) : capacity_(0), value_(nullptr),
		end_(0), begin_(0) {
		capacity_ = some.capacity_;
		end_ = some.end_;
		begin_ = some.begin_;
		value_ = some.value_;

		some.capacity_ = 0;
		some.end_ = 0;
		some.begin_ = 0;
		some.value_ = nullptr;
	}
	MyDeque& operator=(MyDeque&& some)
	{
		if (this != &some)
		{
			capacity_ = some.capacity_;
			end_ = some.end_;
			begin_ = some.begin_;
			value_ = some.value_;

			some.capacity_ = 0;
			some.end_ = 0;
			some.begin_ = 0;
			some.value_ = nullptr;
		}
		return *this;
	}
	~MyDeque() {}
	size_t size() const
	{
		return (end_ + capacity_ - begin_) % capacity_;
	}
	bool empty() const
	{
		return !(size());
	}
	void checkToMakeLarger()
	{
		if (normilize_(begin_ - 1) == end_)
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
		for (int i = begin_, j = 0; i != end_; i = normilize_(++i), ++j)
			tmp[j] = value_[i];
		value_ = tmp;
		end_ = size();
		capacity_ *= 2;
		begin_ = 0;
	}
	void makeSmaller()
	{
		std::vector<T> tmp(capacity_ / 2);
		for (int i = begin_, j = 0; i != end_; i = normilize_(i + 1), ++j)
			tmp[j] = value_[i];
		value_ = tmp;
		end_ = size();
		capacity_ /= 2;
		begin_ = 0;
	}
	void push_back(const T &tmp)
	{
		value_[end_] = tmp;
		end_ = normilize_(1 + end_);
		checkToMakeLarger();
	}
	void push_front(const T &tmp)
	{

		value_[begin_ = normilize_(begin_ - 1)] = tmp;
		checkToMakeLarger();
	}
	void pop_back() 
	{
		end_ = normilize_(end_ - 1);
		checkToMakeSmaller();
	}
	void pop_front()
	{
		begin_ = normilize_(begin_ + 1);
		checkToMakeSmaller();
	}
	T front() {
		return value_[begin_];
	}
	T front() const {
		return value_[begin_];
	}
	T back() {
		return value_[normilize_(end_ - 1)];
	}
	T back() const {
		return value_[normilize_(end - 1)];
	}
	int head() {
		return begin_;
	}
	int tail()
	{
		return end_;
	}
	T& operator [](int id)
	{
		return (value_[normilize_(begin_ + id)]);
	}
	const T& operator [](int id) const
	{
		return (value_[normilize_(begin_ + id)]);
	}
	template <class R>
	class base_iterator : public std::iterator<std::random_access_iterator_tag, MyDeque<T> >
	{
	private:
		T *ptr;
		int num;
		int capacity_;
		int begin_;
		base_iterator& normilize_(const base_iterator& a, difference_type delta) const
		{
			int new_pos = (a.num + delta + a.capacity_) % a.capacity_;
			return base_iterator(a.ptr - a.num + new_pos, new_pos, a.capacity_, a.begin_);
		}
		int toGoodVision(const base_iterator& a) const
		{
			return (-a.begin_ + a.num + a.capacity_) % a.capacity_;
		}
	public:
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef difference_type distance_type;
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

			return *this = normilize_(*this, 1);
		}
		base_iterator& operator ++(T)
		{

			return *this = normilize_(*this, 1);;
		}
		base_iterator& operator --()
		{
			return *this = normilize_(*this, -1);
		}
		base_iterator& operator --(T)
		{
			return *this = normilize_(*this, -1);
		}
		base_iterator& operator +=(const difference_type& idx)
		{
			return *this = normilize_(*this, idx);
		}
		base_iterator& operator -=(const difference_type& idx)
		{
			return *this = normilize_(*this, -idx);
		}
		base_iterator operator +(const difference_type& idx) const
		{
			return normilize_(*this, idx);
		}
		base_iterator operator -(const difference_type& idx) const
		{
			base_iterator Tmp(*this);
			return Tmp -= idx;
		}
		reference operator [](const size_type& idx) const 
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
			return toGoodVision(Other) == toGoodVision(*this);
		}
		bool operator !=(const base_iterator& Other) const
		{
			return !(*this == Other);
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
		return iterator(&value_[head()], head(), capacity_, begin_);
	}
	iterator end()
	{
		return iterator(&value_[tail()], tail(), capacity_, begin_);
	}
	iterator begin() const
	{
		return iterator(&value_[head()], head(), capacity_, begin_);
	}
	iterator end() const
	{
		return iterator(&value_[tail()], tail(), capacity_, begin_);
	}
	const_iterator cend()
	{
		return const_iterator(&value_[tail()], tail(), capacity_, begin_);
	}
	const_iterator cbegin()
	{
		return const_iterator(&value_[head()], head(), capacity_, begin_);
	}
	const_iterator cend() const
	{
		return const_iterator(&value_[tail()], tail(), capacity_, begin_);
	}
	const_iterator cbegin() const
	{
		return const_iterator(&value_[head()], head(), capacity_, begin_);
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
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cbegin());
	}
	const_reverse_iterator crbegin() 
	{
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cend());
	}
	const_reverse_iterator crend() const
	{
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cbegin());
	}
	const_reverse_iterator crbegin() const
	{
		return std::reverse_iterator<MyDeque<T>::base_iterator<const T> >(cend());
	}
};
