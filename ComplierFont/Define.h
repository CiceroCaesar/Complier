#pragma once
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "LexicalUnit.h"

class LexicalUnit;

/// @brief 输入程序的文件名（日后应该为全局变量）
const std::string kInputProgramFileName = "input_program.txt";
/// @brief 未能成功打开文件时的错误提示
const std::string kOpenFileFailed = "Error : the program failed to open file ";
/// @brief tab符号默认占4个列宽
const int kTabDefaultCol = 4;
/// @brief 关键字字符串数组
const std::string kKeyWord[] = { "int","void","if","else","while","return" };
/// @brief 为所有的词素与其对应的词法单元名建立哈希表的对应关系
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