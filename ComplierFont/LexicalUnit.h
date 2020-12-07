#pragma once
#include <string>
//#include "Define.h"

/// @brief �ʷ���Ԫ��
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
	/// @brief ���أ����磺2
	std::string morpheme_;
	/// @brief �ʷ���Ԫ�������磺num
	std::string name_;
	/// @brief ���ų����ڴ�����к�
	int row_ = 0;
	/// @brief ���ų����ڴ�����к�
	int column_ = 0;

private:
};

