#pragma once
#include "Visitor.h"

#include <chrono>
#include <iostream>
#include <random>
#include <vector>

template<typename T>
class Container {
public:
	virtual void Accept(Visitor<T>*) = 0;
};

template<typename T>
class Crowd : public Container<T>, public std::vector<T> {
public:
	void Accept(Visitor<T>*) override;
};

template<typename T>
void Crowd<T>::Accept(Visitor<T>* visitor) {
	visitor->Visit(*this);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Crowd<T>& crowd) {
	for (const auto& el : crowd) {
		stream << el << std::endl;
	}
	return stream;
}

