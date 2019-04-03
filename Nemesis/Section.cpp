#include "Section.hpp"

Section::Section()
{
	this->section_header = IMAGE_SECTION_HEADER();
	this->content = nullptr;
	this->data_size = 0;
	this->initial_size = 0;
}

Section::~Section() = default;
