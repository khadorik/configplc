#include "stdafx.h"


namespace PLCConverter
{
	enum Var_Type
	{
		Var_DI,
		Var_DO,
		Var_AI,
		Var_AO,
		Var_BYTE_IN,
		Var_BYTE_OUT,
		Var_INT
	};

	class Var
	{
	public:
		Var(string name, string visname, string comment);
		void Print(TiXmlNode* node);
	private:
		pair <string, string> name_;
		pair <string, string> visname_;
		pair <string, string> comment_;
	};

	class Register
	{
	public:
		Register();
		Register(string r11, string r12, string r13);
		void Print(TiXmlNode* node);
		bool isEmpty(){ return empty; }
	private:
		bool empty;
		string R11_;
		string R12_;
		string R13_;
	};


	class Channel
	{
	public:
		Channel(int no, string name, Register reg);
		void Print(TiXmlNode* node);
	private:
		pair <string, int> no_;
		pair <string, string> name_;
		Register reg_;
	};

	
}