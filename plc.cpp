#include "plc.h"


namespace PLCConverter
{
	PLC::PLC()
	{
	}

	bool PLC::ReadModuleFile(string file)
	{
		ifstream ifs;
		ifs.open(file, ifstream::in);
		if (ifs.is_open()){
			string str;
			while (!(ifs.eof()))
			{
				getline(ifs, str);
				Module mod;
				mod.CreateNewModule(str);

				module_all_list.push_back(mod);
			}
			ifs.close();
			return true;
		}else{
			return false;
		}

	}

	bool PLC::ReadConf(string file)
	{
		ifstream ifs;
		ifs.open(file, ifstream::in);
		
		if (ifs.is_open()){
			string str;
			while (!ifs.eof())
			{
				getline(ifs, str);
				str.erase(remove_if(str.begin(), str.end(), &isspace));

				for (auto &i : module_all_list)
				{
					if (i.nameIsEqual(str))
					{
						Module module = i;
						module.setId(module_list.size());

						if (str == "0750-1405")
						{
							for (int i = 1; i <= 16; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_DI);
								module.pushVar(str, Var_DI);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0430")
						{
							for (int i = 1; i <= 8; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_DI);
								module.pushVar(str, Var_DI);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-1504")
						{
							for (int i = 1; i <= 16; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_DO);
								module.pushVar(str, Var_DO);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0530")
						{
							for (int i = 1; i <= 8; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_DO);
								module.pushVar(str, Var_DO);
							}
							module.pushParams("2010100000", "2010100001");

						}
						else if (str == "0750-0513")
						{
							for (int i = 1; i <= 2; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_DO);
								module.pushVar(str, Var_DO);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0468")
						{
							for (int i = 1; i <= 4; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_AI);
								module.pushVar(str, Var_AI);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0559")
						{
							for (int i = 1; i <= 4; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_AO);
								module.pushVar(str, Var_AO);
							}
							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0652#08" || str == "0750-0652")
						{
							module.pushChannel(Var_BYTE_IN);

							module.pushVar("", Var_BYTE_IN);
							module.pushVar("", Var_BYTE_OUT);

							module.pushParams("2010100000", "2010100001");
						}
						else if (str == "0750-0469/0003-0000" || str == "0750-0469")
						{
							for (int i = 1; i <= 2; i++)
							{
								getline(ifs, str);
								str.erase(remove_if(str.begin(), str.end(), &isspace));
								module.pushChannel(Var_INT);
								module.pushVar(str, Var_INT);
							}

							module.pushParams("2010100000", "2010100001");
						}
						module_list.push_back(module);
					}
				}

			}
			ifs.close();

			return true;
		}else{
			return false;
		}
	}

	bool PLC::Print()
	{
		TiXmlDocument plcconf("plcdoc.xml");
		TiXmlNode* node_module = 0;
		TiXmlNode* node_channel = 0;

		TiXmlElement app_el("application");
		app_el.SetAttribute("application-name", "CoDeSys 2.3");

		TiXmlElement project_el("project");
		project_el.SetAttribute("project-name", "EA-Configuration");

		TiXmlElement node_el("node");
		node_el.SetAttribute("node-name", "Knoten");
		node_el.SetAttribute("node-pos", 0);
		
		plcconf.Parse(header);
		node_module = plcconf.InsertEndChild(app_el);
		node_module = node_module->InsertEndChild(project_el);
		node_module = node_module->InsertEndChild(node_el);
		for (auto &module : module_list)
			module.Print(node_module);
		
		return plcconf.SaveFile();
	}
}