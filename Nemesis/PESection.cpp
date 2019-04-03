#include "Section.hpp"

Section::Section()
{
	this->content_ = nullptr;
	this->data_size_ = 0;
	this->initial_size_ = 0;
}

Section::~Section()
= default;
