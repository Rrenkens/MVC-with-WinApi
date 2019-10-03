#include "Model.h"

Stack<Model::Type_> Model::stack_;
Crowd<Model::Type_> Model::crowd_;

Stack<Model::Type_ >* Model::GetStack() {
	return &stack_;
}
Crowd<Model::Type_>* Model::GetCrowd() {
	return &crowd_;
}

size_t Model::GetStackSize() {
	return stack_.Size();
}
size_t Model::GetCrowdSize() {
	return crowd_.size();
}
