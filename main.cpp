#include <set>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	string szTargetString;
	string str;
	fstream filename("inin.txt");

	int cnt;

	while (getline(filename, str))
	{
		if (str.find("mov") != -1)
			szTargetString += "mov";
		else if (str.find("add") != -1)
			szTargetString += "add";
		else if (str.find("mul") != -1)
			szTargetString += "mul";
		else if (str.find("div") != -1)
			szTargetString += "div";
		else if (str.find("cbw") != -1)
			szTargetString += "cbw";
		else if (str.find("cwd") != -1)
			szTargetString += "cwd";
		else if (str.find("inc") != -1)
			szTargetString += "inc";
		else if (str.find("dec") != -1)
			szTargetString += "dec";
		else if (str.find("adc") != -1)
			szTargetString += "adc";
		else if (str.find("sub") != -1)
			szTargetString += "sub";
		else if (str.find("sbb") != -1)
			szTargetString += "sbb";
		else if (str.find("imul") != -1)
			szTargetString += "imul";
		else if (str.find("idiv") != -1)
			szTargetString += "idiv";
		else if (str.find("push") != -1)
			szTargetString += "push";
		else if (str.find("pop") != -1)
			szTargetString += "pop";
		else if (str.find("and") != -1)
			szTargetString += "and";
		else if (str.find("or") != -1)
			szTargetString += "or";
		else if (str.find("xor") != -1)
			szTargetString += "xor";
		else if (str.find("not") != -1)
			szTargetString += "not";
		else if (str.find("neg") != -1)
			szTargetString += "neg";
		else if (str.find("shl") != -1)
			szTargetString += "shl";
		else if (str.find("ror") != -1)
			szTargetString += "ror";
		else if (str.find("cmp") != -1)
			szTargetString += "cmp";
		else if (str.find("jmp") != -1)
			szTargetString += "jmp";
		else if (str.find("call") != -1)
			szTargetString += "call";
		else if (str.find("ret") != -1)
			szTargetString += "ret";
		else if ((str.find("je") != -1) || (str.find("jz") != -1))
			szTargetString += "je";
		else if ((str.find("jl") != -1) || (str.find("jnge") != -1))
			szTargetString += "jl";
		else if ((str.find("jbe") != -1) || (str.find("jna") != -1))
			szTargetString += "jbe";
		else if ((str.find("jb") != -1) || (str.find("jnae") != -1))
			szTargetString += "jb";
		else if ((str.find("jp") != -1) || (str.find("jpe") != -1))
			szTargetString += "jp";
		else if (str.find("jo") != -1)
			szTargetString += "jo";
		else if (str.find("js") != -1)
			szTargetString += "js";
		else if (str.find("loop") != -1)
			szTargetString += "loop";
		else if (str.find("str") != -1)
			szTargetString += "str";
		else if (str.find("ldr") != -1)
			szTargetString += "ldr";

		if ((str.find(",") != -1) && (str.find("#") != -1))
		{
			cnt = 0;
			for (size_t i = 0; i < str.length(); i++)
			{
				if (str.at(i) == ',')
					cnt++;
			}
			if (cnt == 1)
				szTargetString += "\trc";
			else
				szTargetString += "\trrc";
		}
		else if ((str.find(",") != -1) && (str.find("#") == -1))
			szTargetString += "\trr";
		szTargetString += "\n";
	}
	cout << szTargetString;
	filename.close();
}