#pragma once
#include <string>
//#include "Define.h"

/// @brief 词法单元类
class LexicalUnit
{
public:
	LexicalUnit(std::string name, std::string morpheme,
	            const int row, const int column);
	std::string GetMorpheme() const;
	std::string GetName() const;
	int GetRow() const;
	int GetColumn() const;
protected:
	/// @brief 词素，例如：2
	std::string morpheme_;
	/// @brief 词法单元名，例如：num
	std::string name_;
	/// @brief 符号出现在代码的行号
	int row_ = 0;
	/// @brief 符号出现在代码的列号
	int column_ = 0;

private:
};

