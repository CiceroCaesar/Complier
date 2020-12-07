#include "Compiler.h"
void Compiler::Test()
{
	while (EOF != lexical_analyzer_.if_stream_.peek())
	{
		lexical_analyzer_.Scan();
	}
	for (auto unit: lexical_analyzer_.symbol_table_)
	{
		std::cout << "Morpheme: " << unit.GetMorpheme()
			<< " Name: " << unit.GetName() << " Row: " << unit.GetRow()
			<< " Column: " << unit.GetColumn() << '\n';
	}
}
