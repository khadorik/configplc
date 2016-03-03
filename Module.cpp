#include "Module.h"


namespace PLCConverter
{
	Module::Module()
	{
		name = "module";
	}

	bool Module::CreateNewModule(string info)
	{
		istringstream is(info);
		string tmp;
		getline(is, tmp, '	');
		article_no = tmp;
		getline(is, tmp, '	');
		subbus_name = tmp;
		getline(is, tmp, '	');
		module_name = tmp;

		if (article_no == "0750-0881")
			target_id = 11986;

		return true;
	}

	bool Module::nameIsEqual(string name)
	{
		return (article_no.compare(name) == 0);
	}

	void Module::pushChannel(Var_Type type)
	{
		int num = ch_list.size()+1;
		char buffer[100];

		Register * reg=0;

		if (type == Var_DI)
		{
			sprintf_s(buffer, "Ch_%d Digital input", num);
			reg = new Register();
		}
		else if (type == Var_DO)
		{
			sprintf_s(buffer, "Ch_%d Digital output", num);
			reg = new Register();
		}
		else if (type == Var_AI)
		{
			sprintf_s(buffer, "Ch_%d Input word", num);
			reg = new Register("0x0410","0x0010","0x0000");
		}
		else if (type == Var_AO)
		{
			sprintf_s(buffer, "Ch_%d Analog output", num);
			reg = new Register("0x0410", "0x1000", "0x0000");
		}
		else if (type == Var_BYTE_IN || type == Var_BYTE_OUT)
		{
			sprintf_s(buffer, "");
			reg = new Register("0x0180", "0x4040", "0x0000");
		}
		else if (type == Var_INT)
		{
			sprintf_s(buffer, "Ch_%d signed Input value", num);
			reg = new Register("0x0210", "0x0010", "0x0000");

		}

		Channel ch(num,buffer,(*reg));
		ch_list.push_back(ch);

		delete reg;
		reg = 0;
	}

	void Module::pushVar(string name, Var_Type type)
	{
		int num = var_list.size() + 1;
		char name_[100];
		char comment_[100];
		if (type == Var_DI)
		{
			sprintf_s(comment_, "Ch_%d Digital input", num);
			sprintf_s(name_, "_IN_Ch%d", num);
		}
		else if (type == Var_DO)
		{
			sprintf_s(comment_, "Ch_%d Digital output", num);
			sprintf_s(name_, "_OUT_Ch%d", num);
		}
		else if (type == Var_AI)
		{
			sprintf_s(comment_, "Ch_%d Input word", num);
			sprintf_s(name_, "_IW_Ch%d", num);
		}
		else if (type == Var_AO)
		{
			sprintf_s(comment_, "Ch_%d Analog output", num);
			sprintf_s(name_, "_QW_Ch%d", num);
		}
		else if (type == Var_BYTE_IN)
		{
			sprintf_s(comment_, "First Byte of 8");
			sprintf_s(name_, "_FIRST_BYTE_IN");
		}
		else if (type == Var_BYTE_OUT)
		{
			sprintf_s(comment_, "First Byte of 8");
			sprintf_s(name_, "_FIRST_BYTE_OUT");
		}
		else if (type == Var_INT)
		{
			sprintf_s(comment_, "Ch_%d signed Input value", num);
			sprintf_s(name_, "_IINT_Ch%d",num);
		}

		Var var(name_, name, comment_);

		var_list.push_back(var);
	}

	void Module::pushParams(string str1, string str2)
	{
		plc_prm1 = str1;
		plc_prm2 = str2;
	}

	void Module::setId(int id)
	{
		subbus_id = id;
	}

	void Module::Print(TiXmlNode* node)
	{
		if (node)
		{
			TiXmlElement module("module");
			module.SetAttribute("subbus-id", subbus_id);
			module.SetAttribute("subbus-name", subbus_name.c_str());
			module.SetAttribute("article-no", article_no.c_str());
			module.SetAttribute("module-name", module_name.c_str());
			if (target_id !=0)
				module.SetAttribute("target-id", target_id);

			TiXmlNode* node_ch = node->InsertEndChild(module);

			for (auto &ch : ch_list)
				ch.Print(node_ch);

			if (!plc_prm1.empty())
			{
				TiXmlElement plc_params1("plc_params");
				plc_params1.SetAttribute("id", plc_prm1.c_str());
				plc_params1.SetAttribute("value-text", "PLC");

				node_ch->InsertEndChild(plc_params1);
			}
			if (!plc_prm2.empty())
			{
				TiXmlElement plc_params2("plc_params");
				plc_params2.SetAttribute("id", plc_prm2.c_str());
				plc_params2.SetAttribute("value-text", "plugged");

				node_ch->InsertEndChild(plc_params2);
			}

			for (auto &var : var_list)
				var.Print(node_ch);
		
		}
	}
}