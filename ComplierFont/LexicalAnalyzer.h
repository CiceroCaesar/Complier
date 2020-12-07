#pragma once
#include "Define.h"

/// @brief �ʷ���������
class LexicalAnalyzer
{
public:
	/// @brief ���캯��
	LexicalAnalyzer();
	/// @brief ��������
	~LexicalAnalyzer();
	/// @brief �ʷ�����
	LexicalUnit Scan();
	/// @brief ����һ���ַ�
	void ReadCh();
	/// @brief ���˴ӵ�ǰλ�õ���һ����ʶ��Ĵ����м��ע�ͺͿհ�
	void FilterComSpace();
	/// @brief ����i�������������ַ�
	/// @param back_ch_num
	void BackCh(int back_ch_num);
	/// @brief �ж�������ַ����Ƿ�Ϊ�ؽ���
	/// @param str ����Ĵ��ж��Ƿ�δ�ؼ��ֵ��ַ��� 
	/// @return ����trueʱΪ�ؼ��֣�������
	bool ScanKeyWord(const std::string& str);
	/// @brief ��һЩ������ɴʷ���Ԫ������ű�
	/// @param name ����Ĵʷ���Ԫ����Ĭ��Ϊ��lexical_unit_morpheme_umap����-��Ԫ������������ַ��������ض�ȡ��
	/// @param morpheme ���أ�Ĭ��Ϊ������ַ���peek_str_
	/// @param row �ַ���ĩβ���ڵ�������Ĭ��Ϊrow_
	/// @param column �ַ���ĩβ���ڵ�������Ĭ��Ϊcolumn_
	static void AddSymbol(const std::string& name = lexical_unit_morpheme_umap.at(peek_str_),
		const std::string& morpheme = peek_str_, const int row = row_,
	                      const int column = column_);

	/// @brief ���������ĳ����ļ���������
	std::ifstream if_stream_{ kInputProgramFileName };
	/// @brief ���ű�
	static std::vector<LexicalUnit> symbol_table_;
	/// @brief �洢�����ļ���ÿ���ж�����
	static std::vector<int> col_num_of_line_;
protected:
	
	/// @brief ������ַ�
	char peek_ = ' ';
	/// @brief ������ַ���
	static std::string peek_str_;
	/// @brief ��ǰɨ�赽���к�
	static int row_;
	/// @brief ��ǰɨ�赽���к�
	static int column_;
private:
};


