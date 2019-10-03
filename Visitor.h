#pragma once
#include "Constants.h"

#include <sstream>

template<typename T>
class Stack;

template<typename T>
class Crowd;

template<typename T>
class Visitor {
public:
	virtual void Visit(Stack<T>&) = 0;
	virtual void Visit(Crowd<T>&) = 0;
};

template<typename T>
class PushVisitor : public Visitor<T> {
public:
	explicit PushVisitor(T& element);

	void Visit(Stack<T>&) override;
	void Visit(Crowd<T>&) override;
private:
	T element_;
};

template<typename T>
class PopVisitor : public Visitor<T> {
public:
	PopVisitor() = default;
	void Visit(Stack<T>&) override;
	void Visit(Crowd<T>&) override;
};

template<typename T>
class PrintVisitor : public Visitor<T> {
public:
	void Visit(Stack<T>&) override;
	void Visit(Crowd<T>&) override;

	std::string GetData() const;
	size_t GetDataSize() const;
	size_t GetSize() const;
private:
	size_t size_;
	std::string data_;
};

template<typename T>
PushVisitor<T>::PushVisitor(T& element) : element_(element) {}

template<typename T>
void PushVisitor<T>::Visit(Stack<T>& stack) {
	stack.Push(element_);
}
template<typename T>
void PushVisitor<T>::Visit(Crowd<T>& crowd) {
	crowd.push_back(element_);
}

template<typename T>
void PopVisitor<T>::Visit(Stack<T>& stack) {
	if (stack.IsEmpty()) {
		return;
	}
	stack.Pop();
}
template<typename T>
void PopVisitor<T>::Visit(Crowd<T>& crowd) {
	if (crowd.empty()) {
		return;
	}
	crowd.erase(crowd.begin() + Constants::rnd() % crowd.size());
}

template<typename T>
void PrintVisitor<T>::Visit(Stack<T>& stack) {
	std::ostringstream stream;
	stream << stack;
	data_ = stream.str();
	size_ = stack.Size();
}

template<typename T>
void PrintVisitor<T>::Visit(Crowd<T>& crowd) {
	std::ostringstream stream;
	stream << crowd;
	data_ = stream.str();
	size_ = crowd.size();
}

template<typename T>
std::string PrintVisitor<T>::GetData() const {
	return data_;
}

template<typename T>
size_t PrintVisitor<T>::GetDataSize() const {
	return data_.size();
}

template<typename T>
size_t PrintVisitor<T>::GetSize() const {
	return size_;
}