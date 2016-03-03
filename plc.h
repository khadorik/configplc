#include "stdafx.h"
#include "Module.h"


namespace PLCConverter
{
	class PLC
	{
	public:
		bool Print();
		bool ReadConf(string file);
		bool ReadModuleFile(string file);
		PLC();
	private:
		const char* header = "<?xml version = \"1.0\" encoding = \"ISO-8859-1\" standalone = \"yes\" >\n";
		
		vector<Module> module_list;
		vector<Module> module_all_list;
	};
}
