#include "LexicalUnit.h"

#include <utility>

LexicalUnit::LexicalUnit(std::string name, std::string morpheme,
	const int row, const int column):
 name_(std::move(name)), morpheme_(std::move(morpheme)),
row_(row), column_(column)
{
}

std::string LexicalUnit::GetMorpheme() const
{
	return morpheme_;
}

std::string LexicalUnit::GetName() const
{
	return name_;
}

int LexicalUnit::GetRow() const
{
	return row_;
}

int LexicalUnit::GetColumn() const
{
	return column_;
}
