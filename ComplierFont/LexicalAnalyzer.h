#pragma once
#include "Define.h"

/// @brief 词法分析器类
class LexicalAnalyzer
{
public:
	/// @brief 构造函数
	LexicalAnalyzer();
	/// @brief 析构函数
	~LexicalAnalyzer();
	/// @brief 词法分析
	LexicalUnit Scan();
	/// @brief 读入一个字符
	void ReadCh();
	/// @brief 过滤从当前位置到下一个待识别的词素中间的注释和空白
	void FilterComSpace();
	/// @brief 回退i（正整数）个字符
	/// @param back_ch_num
	void BackCh(int back_ch_num);
	/// @brief 判断输入的字符串是否为关健符
	/// @param str 输入的待判断是否未关键字的字符串 
	/// @return 返回true时为关键字，否则不是
	bool ScanKeyWord(const std::string& str);
	/// @brief 将一些变量变成词法单元加入符号表
	/// @param name 输入的词法单元名，默认为从lexical_unit_morpheme_umap词素-单元名表用输入的字符串作词素读取出
	/// @param morpheme 词素，默认为输入的字符串peek_str_
	/// @param row 字符串末尾所在的行数，默认为row_
	/// @param column 字符串末尾所在的列数，默认为column_
	static void AddSymbol(const std::string& name = lexical_unit_morpheme_umap.at(peek_str_),
		const std::string& morpheme = peek_str_, const int row = row_,
	                      const int column = column_);

	/// @brief 读入待编译的程序文件的输入流
	std::ifstream if_stream_{ kInputProgramFileName };
	/// @brief 符号表
	static std::vector<LexicalUnit> symbol_table_;
	/// @brief 存储代码文件的每行有多少列
	static std::vector<int> col_num_of_line_;
protected:
	
	/// @brief 读入的字符
	char peek_ = ' ';
	/// @brief 读入的字符串
	static std::string peek_str_;
	/// @brief 当前扫描到的行号
	static int row_;
	/// @brief 当前扫描到的列号
	static int column_;
private:
};


