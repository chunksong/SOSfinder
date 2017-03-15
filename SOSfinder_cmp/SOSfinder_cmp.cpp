#include "SOSfinder.h"

int TargetTokenize(std::fstream& fsTarget, std::string szTargetString);
int GetTarget(std::fstream& fsTarget, std::string szTargetFileName, std::string szTargetString);
int CheckLength(std::string szSigStr, std::string szTargetStr, int iWinSize);
int CmpSigTarget(std::string szSigStr, std::string szTargetStr, int iWinSize);
int GetSignature(MYSQL_ROW row, std::string szSigStr);
int GetSimilarity(std::string szSigStr, std::string szTargetStr, int iWindowSize);


typedef struct stSignature {
	std::string szSigName;
	std::string szSigCVENum;
	std::string szSignature;
}stSig;


int main(int argc, char* argv[]) {
	// useage : SOSfinder <input file name/dir(optional)> 
	int iRtn;
	std::string szTargetString;
	int iWindowSize;
	std::fstream fsTargetFile;

	if (argc != 2) {
		std::cout << "Usage : SOSfinder <input file name>" << std::endl;
		return -1;
	}

	iRtn = GetTarget(fsTargetFile, argv[1], szTargetString);
	if (iRtn == D_FAIL) return -1;

	GetSimilarity(szTargetString, iWindowSize);
	if (iRtn == D_FAIL) return -1;

	return 0;

}

int TargetTokenize(std::fstream& fsTarget, std::string szTargetString) {
	std::set<std::string> address;
	std::set<std::string> mnemonic;
	std::set<std::string> regist;
	std::set<std::string> offset;
	std::string str;

	while (std::getline(fsTarget, szTargetString))
		str += szTargetString + ' ';
	szTargetString = "";

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str.at(i) == ':')
		{
			address.insert(szTargetString);
			szTargetString = "";
		}
		else if (str.at(i - 7) == ':' || str.at(i - 8) == ':')
		{
			mnemonic.insert(szTargetString);
			szTargetString = "";
		}
		else if (str.at(i + 1) == '#')
		{
			regist.insert(szTargetString);
			szTargetString = "";
		}
		else if (str.at(i) == '\n')
		{
			offset.insert(szTargetString);
			szTargetString = "";
		}
		else
			szTargetString.push_back(str.at(i));
	}
	return D_SUCC;
}

int GetTarget(std::fstream& fsTarget, std::string szTargetFileName, std::string szTargetString) {

	int iRtn;

	// open target file
	fsTarget.open(szTargetFileName.c_str(), std::ios::in);
	
	// check target file validation 
	if (!fsTarget) {
		std::cout << "Target File open error.." << std::endl;
		return D_FAIL;
	}

	// store target file to szTargetString
	iRtn = TargetTokenize(fsTarget, szTargetString);
	if (iRtn == D_FAIL) {
		std::cout << "Target File Tokenize error.." << std::endl;
	}

	// close target file;
	fsTarget.close();

	return D_SUCC;
}

int CheckLength(std::string szSigStr, std::string szTargetStr, int iWinSize) {

	if (szTargetStr.length() < 24) {
		std::cout << "Error : target file size is too small to compare.." << std::endl;
		return D_FAIL;
	}

	if (szTargetStr.length() < szSigStr.length()) {
		iWinSize = szTargetStr.length();
		szSigStr = szSigStr.substr(0, iWinSize);
	}
	else {
		iWinSize = szSigStr.length();
	}

	return D_SUCC;
}

int CmpSigTarget(stSignature stSign, std::string szTargetStr, int iWinSize) {

	int iNGram;
	double dJaccardIndex;
	std::set<std::string> setSigGram;
	std::set<std::string> setTargetGram;




	return D_SUCC;
}

int GetSignature(MYSQL_ROW row, stSignature stSign) {
	
	// row[0] => name_of_vuln 
	// row[1] => number_of_CVE  
	// row[2] => Tokenized_binary_code_of_vuln

	stSign.szSigName = row[0];
	stSign.szSigCVENum = row[1];
	stSign.szSignature = row[2];
	
	return D_SUCC;
}

int GetSimilarity(std::string szTargetStr, int iWindowSize) {

	int iRtn;
	int iMaxJI = -1;
	MYSQL_RES *res;	// the results
	MYSQL_ROW row;	// the results row (line by line)

	char* szDBQuery = "SELECT * FROM vuln_list";

	//DB connect
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection, "localhost", "root", "1234", "vuln", 0, NULL, 0)) {
		std::cout << "DB Conection error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	if (mysql_query(connection, szDBQuery))
	{
		std::cout << "MySQL query error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}

	res = mysql_use_result(connection);

	while ((row = mysql_fetch_row(res)) != NULL) {
		
		stSig stSigObject;

		iRtn = GetSignature(row,stSigObject);
		if (iRtn == D_FAIL) {
			std::cout << "Read SignatureFile from DB error.." << std::endl;
		}

		CheckLength(stSigObject.szSignature, szTargetStr, iWindowSize);

		CmpSigTarget(stSigObject, szTargetStr, iWindowSize);
	}

	return D_SUCC;

}
