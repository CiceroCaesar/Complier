#include "LexicalAnalyzer.h"
std::string LexicalAnalyzer::peek_str_ = "";
int LexicalAnalyzer::row_ = 1;
int LexicalAnalyzer::column_ = 0;
std::vector<LexicalUnit> LexicalAnalyzer::symbol_table_ = {};
std::vector<int> LexicalAnalyzer::col_num_of_line_ = {};

LexicalAnalyzer::LexicalAnalyzer()
{
	if (!if_stream_.is_open())
	{
		std::cerr << kOpenFileFailed << kInputProgramFileName << '\n';
		exit(-1);
	}
	col_num_of_line_.emplace_back(column_);
}

LexicalAnalyzer::~LexicalAnalyzer()
{
	if_stream_.clear();
	if_stream_.close();
}

LexicalUnit LexicalAnalyzer::Scan()
{
	FilterComSpace();
	ReadCh();//(主判断部分加在循环内是一遍扫描完整个程序，现在是一次只扫描一个词法单元)
	/// @brief 关键字或标识符
	if (isalpha(peek_))
	{
		peek_str_ = "";
		while (isalnum(peek_))
		{
			peek_str_ += peek_;
			ReadCh();
		}
		if (ScanKeyWord(peek_str_))
		{
			/// @brief 关键字
			AddSymbol();
		}
		else
		{
			/// @brief 标识符
			AddSymbol(lexical_unit_morpheme_umap.at("Identifier") + ": " + peek_str_);
		}

	}
	/// @brief 数值
	else if (isdigit(peek_))
	{
		peek_str_ = "";
		while (isdigit(peek_))
		{
			peek_str_ += peek_;
			ReadCh();
			if (!isdigit(peek_))
			{
				/// @brief 数值
				AddSymbol(lexical_unit_morpheme_umap.at("NumericValue") + ": " + peek_str_);
			}
		}
	}
	/// @brief 赋值号
	else if ('=' == peek_)
	{
		peek_str_ = peek_;
		AddSymbol();
	}
	/// @brief 只有1个字符的词素及其词法单元
	else if (('+' == peek_) || ('-' == peek_) || ('*' == peek_) ||
		('/' == peek_) || ('=' == peek_) || ('>' == peek_) ||
		('<' == peek_) || (';' == peek_) || (',' == peek_) ||
		('(' == peek_) || (')' == peek_) || ('{' == peek_) ||
		('}' == peek_) || ('#' == peek_))
	{
		peek_str_ = peek_;
		AddSymbol();
	}
	/// @brief 算符 ==
	else if (('=' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = "==";
		AddSymbol();
	}
	/// @brief 算符 >=
	else if (('>' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = ">=";
		AddSymbol();
	}
	/// @brief 算符 <=
	else if (('<' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = "<=";
		AddSymbol();
	}
	/// @brief 算符 !=
	else if (('!' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = "!=";
		AddSymbol();
	}
	return symbol_table_.back();
}

void LexicalAnalyzer::ReadCh()
{
	/// @brief 读字符，存于peek_
	peek_ = if_stream_.get();
	/// @brief 读换行符
	if ('\n' == peek_)
	{
		//行数加一
		++row_;
		/// @brief 行数归零
		column_ = 0;
		/// @brief 在col_num_of_line向量中初始化1个该行的列数
		col_num_of_line_.emplace_back(column_);
	}
	/// @brief 若读到换行符
	else if ('\t' == peek_)
	{
		/// @brief 列数默认加4
		column_ += kTabDefaultCol;
		/// @brief 更新col_num_of_line中当前行数的总列数
		col_num_of_line_[static_cast<long long>(row_) - 1] = column_;
	}
	/// @brief 若除以上情况且未读到文件尾，正常加1列
	else if(EOF != peek_)
	{
		++column_;
		col_num_of_line_[static_cast<long long>(row_) - 1] = column_;
	}
	//否则，若读到文件尾，无处理，自动结束（可加输出提示）
	
}

void LexicalAnalyzer::FilterComSpace()
{
	/// @brief 注释字符串的长度，用于错误处理
	int com_ch_num = 0;
	/// @brief 此版本未将注释存入任何一个符号表中，即直接过滤
	do
	{
		/// @brief 读1个字符
		ReadCh();
		/// @brief 若是空白符，直接跳过，继续读
		if ((' ' == peek_) || ('\t' == peek_) || ('\n' == peek_))
		{
		}
		/// @brief 若是单斜线
		else if('/' == peek_)
		{
			/// @brief 继续读一个字符
			ReadCh();
			/// @brief 不满足两种注释的部分要求// 和 /*
			if (('/' != peek_) && ('*' != peek_))
			{
				/// @brief 回退1个字符
				BackCh(1);
				/// @brief 直接退出，结束此次过滤
				return;
			}
			/// @brief 如果第二个字符为/，即满足同行注释
			if ('/' == peek_)
			{
				/// @brief 一直读到本行结束，包括换行符也读入
				do
				{
					ReadCh();
				} while ('\n' == peek_);
				AddSymbol(lexical_unit_morpheme_umap.at("//"), "//");

			}
			/// @brief 如果第二个字符是星，即满足跨行注释的/*部分条件（此种情况画个状态机便利于理解）
			else if ('*' == peek_)
			{
				++com_ch_num;
				do
				{
					ReadCh();
					++com_ch_num;
					/// @brief 在之后的循环每次判断是否满足跨行注释的结束型号
					if ('*' == peek_)
					{
						ReadCh();
						++com_ch_num;
						/// @brief 继续判断是否全部满足跨行注释/**/（因为除了错误外，理论上一定有满足的时候，所以此处无return）
						/// 若满足，直接跳过
						if ('/' == peek_)
						{
							AddSymbol(lexical_unit_morpheme_umap.at("/**/"), "/**/");
						}
					}
				} while (true);
			}
		}
		/// @brief 既不是空白符也不是单斜线，则回退1字符，直接结束此次过滤
		else
		{
			BackCh(1);
			return;
		}
	} while (true);
}

void LexicalAnalyzer::BackCh(const int back_ch_num)
{
	
	for (int i = 1; back_ch_num >= i; ++i)
	{
		if_stream_.seekg(-1, std::ios::cur);
		--column_;
		peek_ = if_stream_.peek();
		/// @brief 回退时遇到换行符要处理当前指针位于的行数和列数
		if('\n' == peek_)
		{
			row_ = (row_ == 1) ? row_ : --row_;
			column_ = col_num_of_line_[static_cast<long long>(row_) - 1];
		}
		/// @brief 回退时遇到tab要处理当前指针位于的列数，默认4字符
		else if('\t' == peek_)
		{
			column_ -= kTabDefaultCol;
		}
	}
}

bool LexicalAnalyzer::ScanKeyWord(const std::string& str)
{
	for (const auto& key_word : kKeyWord)
	{
		if( str == key_word)
		{
			return true;
		}
	}
	return false;
}

auto LexicalAnalyzer::AddSymbol(const std::string& name, const std::string& morpheme, const int row, const int column) -> void
{
	symbol_table_.emplace_back(name, morpheme, row, column);
}
