#include "Container.h"
#include "Stack.h"

#include <cassert>
#include <exception>
#include <iostream>

void test() {
	Stack<int> stack1;
	assert(stack1.IsEmpty());
	assert(stack1.begin() == stack1.end());
	stack1.Push(228);
	std::initializer_list<int> test = { 228 }, test2 = { 1, 2, 3 },
		test3 = { 1, 2, 3, 228 }, test4 = { 228, 1, 2, 3 };
	assert(stack1 == test);
	assert(stack1.Top() == 228);
	assert(stack1.Size() == 1);
	assert(*stack1.begin() == 228);
	assert(stack1.begin() != stack1.end());
	stack1.Push(42);
	assert(*(++stack1.begin()) == *(--stack1.end()));
	assert(*(++stack1.begin()) == 42);
	assert(stack1.Size() == 2);
	assert(stack1.Top() == 42);
	stack1.Pop();
	assert(stack1.Top() == 228);
	Stack<int> stack2 = { 1, 2, 3 };
	assert(stack2 != test);
	assert(stack2 == test2);
	stack1.Swap(stack2);
	assert(stack1 == test2 && stack2 == test);
	assert(stack1 + stack2 == test3);
	stack2 += stack1;
	assert(stack2 == test4);
	assert(stack2.Top() == 3);
	stack2.Clear();
	assert(stack2.IsEmpty());
	assert(stack2.begin() == stack2.end());
}
