#pragma once
#include "Container.h"
#include "Stack.h"

#include <string>

class Model {
public:
	using Type_ = std::string;
	static Stack<Type_>* GetStack();
	static Crowd<Type_>* GetCrowd();
	static size_t GetStackSize();
	static size_t GetCrowdSize();
private:
	static Stack<Type_> stack_;
	static Crowd<Type_> crowd_;
};
