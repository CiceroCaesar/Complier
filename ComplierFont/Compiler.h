#pragma once
#include "Define.h"
#include "LexicalAnalyzer.h"
#include "Parser.h"
class Compiler
{
public:
	void Test();
protected:
	LexicalAnalyzer lexical_analyzer_;
	Parser parser_;
private:
};

