#include "stdafx.h"
#include "Channel.h"

namespace PLCConverter
{
	class Module
	{
	public:
		Module();
		bool CreateNewModule(string info);
		bool nameIsEqual(string name);
		void pushChannel(Var_Type type);
		void pushVar(string name, Var_Type type);
		void pushParams(string str1, string str2);
		void setId(int id);
		void Print(TiXmlNode* node);
	private:
		string name;
		int subbus_id;
		string subbus_name;
		string article_no;
		string module_name;
		int target_id;

		vector<Channel> ch_list;
		vector<Var> var_list;

		string plc_prm1;
		string plc_prm2;

	};
}