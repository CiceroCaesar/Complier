#pragma once
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "LexicalUnit.h"

class LexicalUnit;

/// @brief ���������ļ������պ�Ӧ��Ϊȫ�ֱ�����
const std::string kInputProgramFileName = "input_program.txt";
/// @brief δ�ܳɹ����ļ�ʱ�Ĵ�����ʾ
const std::string kOpenFileFailed = "Error : the program failed to open file ";
/// @brief tab����Ĭ��ռ4���п�
const int kTabDefaultCol = 4;
/// @brief �ؼ����ַ�������
const std::string kKeyWord[] = { "int","void","if","else","while","return" };
/// @brief Ϊ���еĴ��������Ӧ�Ĵʷ���Ԫ��������ϣ��Ķ�Ӧ��ϵ
const std::unordered_map<std::string, std::string> lexical_unit_morpheme_umap
{
	{"int","Keyword: int"}, {"void", "Keyword: void"}, {"if", "Keyword: if"},
	{"else", "Keyword: else"}, {"while", "Keyword: while"}, {"return", "Keyword: return"},
	{"Identifier","Identifier"}, {"NumericValue", "NumericValue"},
	{"=", "AssignmentSymbol"}, {"+", "Operator: +"}, {"-", "Operator: -"},
	{"*", "Operator: *"}, {"/", "Operator: /"}, {"=", "Operator: ="},
	{"==", "Operator: =="}, {">", "Operator: >"}, {">=", "Operator: >="},
	{"<", "Operator: <"}, {"<=", "Operator: <="}, {"!=", "Operator: !="},
	{";", "SentenceEnd: ;"}, {",", "SeparateSign: ,"}, {"/**/", "Comment: /**/"},
	{"//", "Comment: //"}, {"(", "LeftParentheses: ("}, {")", "RightParentheses: )"},
	{"{", "BigLeftParentheses: {"}, {"}", "BigRightParentheses: }"}, {"Letter", "Letter"},
	{"Digit", "Digit"}, {"#", "EndSymbol: #"}
};

const enum ExitCode
{
	kOpenFileFailedCode = 1, kLexBeginErrCode, kLexCrossComNotEndCode
};

const std::string kReadEOF = "The end of file is read, the reading process ends.\n";
/// @brief �ʷ�����ʱ���ص�����ĸ���Ϸ�
const std::string kLexBeginErr = "The first letter of the word is not a character that should appear. ";
/// @brief �ʷ�����ʱ/**/ע��δ����
const std::string kLexCrossComNotEnd = "The comment '/**/' has no terminator '*/'. ";