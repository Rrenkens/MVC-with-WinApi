#pragma once
#include "Container.h"

#include <exception>
#include <initializer_list>
#include <iostream>
#include <iterator>

template<typename T>
class Stack : public Container<T> {
public:
	class Iterator :
		public std::iterator<std::random_access_iterator_tag, T> {
	public:
		Iterator();
		Iterator(const Iterator&);
		~Iterator() = default;

		Iterator& operator=(const Iterator&);

		T& operator*() const;
		T* operator->() const;

		Iterator& operator++();
		const Iterator operator++(int);
		Iterator& operator--();
		const Iterator operator--(int);
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;

	private:
		explicit Iterator(Stack*, T*);
		friend Stack;
		Stack* stack_;
		T* element_;
	};

	class ConstIterator :
		public std::iterator<std::random_access_iterator_tag, T> {
	public:
		ConstIterator();
		ConstIterator(const ConstIterator&);
		~ConstIterator() = default;

		const T& operator*() const;
		const T* operator->() const;

		ConstIterator& operator++();
		const ConstIterator operator++(int);
		ConstIterator& operator--();
		const ConstIterator operator--(int);
		bool operator==(const ConstIterator& other) const;
		bool operator!=(const ConstIterator& other) const;

	private:
		explicit ConstIterator(const Stack*, T*);
		friend Stack;
		const Stack* stack_;
		T* element_;
	};

	// Default constructor. Initially, stack is empty,
	// but memory for one element has already been allocated.
	explicit Stack();
	Stack(const std::initializer_list<T>&);

	Stack(const Stack&);
	Stack& operator=(const Stack&);

	Stack(Stack&&) noexcept;
	Stack& operator=(Stack&&) noexcept;

	~Stack();

	bool IsEmpty() const;
	size_t Size() const;

	void Push(const T&);
	void Pop();
	T Top() const;

	void Swap(Stack<T>&);
	void Clear();

	bool operator==(const Stack&) const;
	bool operator!=(const Stack&) const;
	Stack operator+(const Stack&) const;
	Stack operator+=(const Stack&);

	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;

	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const Stack<U>& cur) {
		for (const auto& el : cur) {
			out << el << std::endl;
		}
		return out;
	}

	template<typename U>
	friend std::istream& operator>>(std::istream& in, Stack<U>& cur) {
		size_t cnt_of_element;
		in >> cnt_of_element;
		for (size_t i = 0; i < cnt_of_element; i++) {
			U temp;
			in >> temp;
			cur.Push(temp);
		}
		return in;
	}

	void Accept(Visitor<T>*) override;

private:
	// How much memory is allocated
	size_t allocated_size_;

	// How much memory is used
	size_t size_;

	// Pointer to stack
	T* data_;

	// Changes the size of stack stored in data_
	void Relocate(size_t new_size);
};

// Implement Iterator methods
template<typename T>
Stack<T>::Iterator::Iterator() : stack_(nullptr), element_(nullptr) {}

template<typename T>
Stack<T>::Iterator::Iterator(const Stack::Iterator& other) :
	stack_(other.stack_), element_(other.element_) {}

template<typename T>
Stack<T>::Iterator::Iterator(Stack* other_stack, T* other_element) :
	stack_(other_stack), element_(other_element) {}

template<typename T>
typename Stack<T>::Iterator&Stack<T>::Iterator::operator=(
	const Stack::Iterator& other) {
	stack_ = other.stack_;
	element_ = other.element_;
}

template<typename T>
T& Stack<T>::Iterator::operator*() const {
	return *element_;
}

template<typename T>
T* Stack<T>::Iterator::operator->() const {
	return element_;
}

template<typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator++() {
	if (*this == stack_->end()) {
		throw std::logic_error("You went over the stack");
	}
	element_ += 1;
	return *this;
}

template<typename T>
const typename Stack<T>::Iterator Stack<T>::Iterator::operator++(int) {
	auto temp = *this;
	++(*this);
	return temp;
}

template<typename T>
typename Stack<T>::Iterator& Stack<T>::Iterator::operator--() {
	if (*this == stack_->begin()) {
		throw std::logic_error("You went over the stack");
	}
	element_ -= 1;
	return *this;
}

template<typename T>
const typename Stack<T>::Iterator Stack<T>::Iterator::operator--(int) {
	auto temp = *this;
	--(*this);
	return temp;
}

template<typename T>
bool Stack<T>::Iterator::operator==(const Iterator& other) const {
	return element_ == other.element_;
}

template<typename T>
bool Stack<T>::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

// Implement ConstIterator methods
template<typename T>
Stack<T>::ConstIterator::ConstIterator() :
	stack_(nullptr), element_(nullptr) {}

template<typename T>
Stack<T>::ConstIterator::ConstIterator(const Stack::ConstIterator& other) :
	stack_(other.stack_), element_(other.element_) {}

template<typename T>
Stack<T>::ConstIterator::ConstIterator(
	const Stack* other_stack, T* other_element) :
	stack_(other_stack), element_(other_element) {}

template<typename T>
const T& Stack<T>::ConstIterator::operator*() const {
	return *element_;
}

template<typename T>
const T* Stack<T>::ConstIterator::operator->() const {
	return element_;
}

template<typename T>
typename Stack<T>::ConstIterator& Stack<T>::ConstIterator::operator++() {
	if (*this == stack_->end()) {
		throw std::logic_error("You went over the stack");
	}
	element_ += 1;
	return *this;
}

template<typename T>
const typename Stack<T>::ConstIterator Stack<T>::
ConstIterator::operator++(int) {
	auto temp = *this;
	++(*this);
	return temp;
}

template<typename T>
typename Stack<T>::ConstIterator& Stack<T>::ConstIterator::operator--() {
	if (*this == stack_->begin()) {
		throw std::logic_error("You went over the stack");
	}
	element_ -= 1;
	return *this;
}

template<typename T>
const typename Stack<T>::ConstIterator Stack<T>::
ConstIterator::operator--(int) {
	auto temp = *this;
	--(*this);
	return temp;
}

template<typename T>
bool Stack<T>::ConstIterator::operator==(const ConstIterator& other) const {
	return element_ == other.element_;
}
template<typename T>
bool Stack<T>::ConstIterator::operator!=(const ConstIterator& other) const {
	return !(*this == other);
}

template<typename T>
void Stack<T>::Accept(Visitor<T>* visitor) {
	visitor->Visit(*this);
}

//Implement stack methods
template<typename T>
Stack<T>::Stack() :size_(0), allocated_size_(1), data_(new T[1]) {}

template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& other)
	: size_(0), allocated_size_(other.size()), data_(new T[allocated_size_]) {
	for (const auto& el : other) {
		Push(el);
	}
}

template<typename T>
Stack<T>::Stack(const Stack& other) :
	size_(other.size_),
	allocated_size_(other.allocated_size_),
	data_(new T[allocated_size_]) {
	for (size_t i = 0; i < other.size_; i++) {
		data_[i] = other.data_[i];
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	if (allocated_size_ != other.allocated_size_) {
		allocated_size_ = other.allocated_size_;
		delete[] data_;
		data_ = new T[allocated_size_];
	}
	size_ = other.size_;
	for (size_t i = 0; i < other.size_; i++) {
		data_[i] = other.data_[i];
	}
	return *this;
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept : size_(other.size_),
allocated_size_(other.allocated_size_),
data_(other.data_) {
	other.size_ = 0;
	other.allocated_size_ = 1;
	other.data_ = new T[other.allocated_size_];
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
	delete[] data_;
	allocated_size_ = other.allocated_size_;
	size_ = other.size_;
	data_ = other.data_;
	other.size_ = 0;
	other.allocated_size_ = 1;
	other.data_ = new T[other.allocated_size_];
	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	delete[] data_;
}

template<typename T>
bool Stack<T>::IsEmpty() const {
	return size_ == 0;
}

template<typename T>
size_t Stack<T>::Size() const {
	return size_;
}

template<typename T>
void Stack<T>::Push(const T& value) {
	if (size_ == allocated_size_) {
		Relocate(allocated_size_ * 2);
	}
	data_[size_] = value;
	size_++;
}

template<typename T>
void Stack<T>::Pop() {
	if (size_ == 0) {
		throw std::logic_error("Remove from empty stack!");
	}
	Top().~T();
	size_--;
	if (size_ < allocated_size_ / 4) {
		Relocate(allocated_size_ / 2);
	}
}

template<typename T>
T Stack<T>::Top() const {
	if (size_ == 0) {
		throw std::logic_error("Getting value from empty stack");
	}
	return data_[size_ - 1];
}

template<typename T>
void Stack<T>::Swap(Stack<T>& other) {
	Stack<T> temp = std::move(other);
	other = std::move(*this);
	*this = std::move(temp);
}

template<typename T>
void Stack<T>::Clear() {
	delete[] data_;
	*this = Stack();
}

template<typename T>
bool Stack<T>::operator==(const Stack<T>& other) const {
	if (size_ != other.size_) {
		return false;
	}
	for (Stack<T>::ConstIterator lhs = begin(), rhs = other.begin();
		lhs != end(); lhs++, rhs++) {
		if (*lhs != *rhs) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack<T>& other) const {
	return !(*this == other);
}

template<typename T>
Stack<T> Stack<T>::operator+(const Stack<T>& other) const {
	Stack<T> ret = *this;
	for (const auto& el : other) {
		ret.Push(el);
	}
	return ret;
}

template<typename T>
Stack<T> Stack<T>::operator+=(const Stack<T>& other) {
	for (const auto& el : other) {
		Push(el);
	}
	return *this;
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::begin() {
	return Stack::Iterator(this, data_);
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() {
	return Stack::Iterator(this, data_ + size_);
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::begin() const {
	return Stack::ConstIterator(this, data_);
}

template<typename T>
typename Stack<T>::ConstIterator Stack<T>::end() const {
	return Stack::ConstIterator(this, data_ + size_);
}

template<typename T>
void Stack<T>::Relocate(size_t new_size) {
	allocated_size_ = new_size;
	T* temp = data_;
	data_ = new T[allocated_size_];
	for (size_t i = 0; i < size_; i++) {
		data_[i] = temp[i];
	}
	delete[] temp;
}