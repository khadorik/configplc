#include "Channel.h"

namespace PLCConverter
{
	Channel::Channel(int no, string name, Register reg)
	{
		no_.first = "channel-no";
		no_.second = no;

		name_.first = "channel-name";
		name_.second = name;

		reg_ = reg;
	}

	void Channel::Print(TiXmlNode* node)
	{
		if (node)
		{
			TiXmlElement ch("channel");
			ch.SetAttribute(no_.first.c_str(), no_.second);
			if (!name_.second.empty())
				ch.SetAttribute(name_.first.c_str(), name_.second.c_str());

			TiXmlNode* node_reg = node->InsertEndChild(ch);
			if (!reg_.isEmpty())
				reg_.Print(node_reg);
		}
	}

	Register::Register() :empty(true)
	{
		R11_.clear();
		R12_.clear();
		R13_.clear();
	}

	Register::Register(string r11, string r12, string r13) :empty(false)
	{
		R11_ = r11;
		R12_ = r12;
		R13_ = r13;
	}

	void Register::Print(TiXmlNode* node)
	{
		if (node)
		{
			TiXmlElement reg("register");
			reg.SetAttribute("R11", R11_.c_str());
			reg.SetAttribute("R12", R12_.c_str());
			reg.SetAttribute("R13", R13_.c_str());

			node->InsertEndChild(reg);
		}
	}


	Var::Var(string name, string visname, string comment)
	{
		name_.first = "name";
		name_.second = name;

		visname_.first = "visible-name";
		visname_.second = visname;

		comment_.first = "comment";
		comment_.second = comment;
	}

	void Var::Print(TiXmlNode* node)
	{
		if (node)
		{
			TiXmlElement var("var");
			var.SetAttribute(name_.first.c_str(), name_.second.c_str());
			var.SetAttribute(visname_.first.c_str(), visname_.second.c_str());
			var.SetAttribute(comment_.first.c_str(), comment_.second.c_str());

			node->InsertEndChild(var);
		}
	}
}