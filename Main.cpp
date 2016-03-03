#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "tinyxml.h"
#include "plc.h"
#include <filesystem>

using namespace std;
using namespace PLCConverter;

int main()
{
		unique_ptr<PLC> plc = make_unique<PLC>();
		
		
		plc->ReadModuleFile("codePLC.txt");
		plc->ReadConf("plcConf.txt");
  		plc->Print();

		system("pause");

		return 0;
}
