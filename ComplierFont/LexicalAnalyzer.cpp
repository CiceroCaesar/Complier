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
	ReadCh();//(���жϲ��ּ���ѭ������һ��ɨ������������������һ��ֻɨ��һ���ʷ���Ԫ)
	/// @brief �ؼ��ֻ��ʶ��
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
			/// @brief �ؼ���
			AddSymbol();
		}
		else
		{
			/// @brief ��ʶ��
			AddSymbol(lexical_unit_morpheme_umap.at("Identifier") + ": " + peek_str_);
		}

	}
	/// @brief ��ֵ
	else if (isdigit(peek_))
	{
		peek_str_ = "";
		while (isdigit(peek_))
		{
			peek_str_ += peek_;
			ReadCh();
			if (!isdigit(peek_))
			{
				/// @brief ��ֵ
				AddSymbol(lexical_unit_morpheme_umap.at("NumericValue") + ": " + peek_str_);
			}
		}
	}
	/// @brief ��ֵ��
	else if ('=' == peek_)
	{
		peek_str_ = peek_;
		AddSymbol();
	}
	/// @brief ֻ��1���ַ��Ĵ��ؼ���ʷ���Ԫ
	else if (('+' == peek_) || ('-' == peek_) || ('*' == peek_) ||
		('/' == peek_) || ('=' == peek_) || ('>' == peek_) ||
		('<' == peek_) || (';' == peek_) || (',' == peek_) ||
		('(' == peek_) || (')' == peek_) || ('{' == peek_) ||
		('}' == peek_) || ('#' == peek_))
	{
		peek_str_ = peek_;
		AddSymbol();
	}
	/// @brief ��� ==
	else if (('=' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = "==";
		AddSymbol();
	}
	/// @brief ��� >=
	else if (('>' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = ">=";
		AddSymbol();
	}
	/// @brief ��� <=
	else if (('<' == peek_) && ('=' == if_stream_.peek()))
	{
		ReadCh();
		peek_str_ = "<=";
		AddSymbol();
	}
	/// @brief ��� !=
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
	/// @brief ���ַ�������peek_
	peek_ = if_stream_.get();
	/// @brief �����з�
	if ('\n' == peek_)
	{
		//������һ
		++row_;
		/// @brief ��������
		column_ = 0;
		/// @brief ��col_num_of_line�����г�ʼ��1�����е�����
		col_num_of_line_.emplace_back(column_);
	}
	/// @brief ���������з�
	else if ('\t' == peek_)
	{
		/// @brief ����Ĭ�ϼ�4
		column_ += kTabDefaultCol;
		/// @brief ����col_num_of_line�е�ǰ������������
		col_num_of_line_[static_cast<long long>(row_) - 1] = column_;
	}
	/// @brief �������������δ�����ļ�β��������1��
	else if(EOF != peek_)
	{
		++column_;
		col_num_of_line_[static_cast<long long>(row_) - 1] = column_;
	}
	//�����������ļ�β���޴����Զ��������ɼ������ʾ��
	
}

void LexicalAnalyzer::FilterComSpace()
{
	/// @brief ע���ַ����ĳ��ȣ����ڴ�����
	int com_ch_num = 0;
	/// @brief �˰汾δ��ע�ʹ����κ�һ�����ű��У���ֱ�ӹ���
	do
	{
		/// @brief ��1���ַ�
		ReadCh();
		/// @brief ���ǿհ׷���ֱ��������������
		if ((' ' == peek_) || ('\t' == peek_) || ('\n' == peek_))
		{
		}
		/// @brief ���ǵ�б��
		else if('/' == peek_)
		{
			/// @brief ������һ���ַ�
			ReadCh();
			/// @brief ����������ע�͵Ĳ���Ҫ��// �� /*
			if (('/' != peek_) && ('*' != peek_))
			{
				/// @brief ����1���ַ�
				BackCh(1);
				/// @brief ֱ���˳��������˴ι���
				return;
			}
			/// @brief ����ڶ����ַ�Ϊ/��������ͬ��ע��
			if ('/' == peek_)
			{
				/// @brief һֱ�������н������������з�Ҳ����
				do
				{
					ReadCh();
				} while ('\n' == peek_);
				AddSymbol(lexical_unit_morpheme_umap.at("//"), "//");

			}
			/// @brief ����ڶ����ַ����ǣ����������ע�͵�/*���������������������״̬����������⣩
			else if ('*' == peek_)
			{
				++com_ch_num;
				do
				{
					ReadCh();
					++com_ch_num;
					/// @brief ��֮���ѭ��ÿ���ж��Ƿ��������ע�͵Ľ����ͺ�
					if ('*' == peek_)
					{
						ReadCh();
						++com_ch_num;
						/// @brief �����ж��Ƿ�ȫ���������ע��/**/����Ϊ���˴����⣬������һ���������ʱ�����Դ˴���return��
						/// �����㣬ֱ������
						if ('/' == peek_)
						{
							AddSymbol(lexical_unit_morpheme_umap.at("/**/"), "/**/");
						}
					}
				} while (true);
			}
		}
		/// @brief �Ȳ��ǿհ׷�Ҳ���ǵ�б�ߣ������1�ַ���ֱ�ӽ����˴ι���
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
		/// @brief ����ʱ�������з�Ҫ����ǰָ��λ�ڵ�����������
		if('\n' == peek_)
		{
			row_ = (row_ == 1) ? row_ : --row_;
			column_ = col_num_of_line_[static_cast<long long>(row_) - 1];
		}
		/// @brief ����ʱ����tabҪ����ǰָ��λ�ڵ�������Ĭ��4�ַ�
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
