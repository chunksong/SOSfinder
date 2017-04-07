#include "SOSfinder.h"

int TargetTokenize(std::fstream& fsTarget, std::string &szTargetString);
int GetTarget(std::fstream& fsTarget, std::string szTargetFileName, std::string &szTargetString);
int CheckLength(std::string szSigStr, std::string& szTargetStr, int& iSigSize);
double CmpSigTarget(std::string szSigStr, std::string szTargetStr, int iWinSize);
int GetSignature(MYSQL_ROW row, stSig &stSign);
int GetSimilarity(std::string &szTargetStr, int iWindowSize);
//--------------------------------------------------------------------------------
int GetSimilarity2(std::string &szTargetStr, int iWindowSize);
int GetSimilarity3(std::string &szTargetStr, int iWindowSize);
//--------------------------------------------------------------------------------
int InsertSignature(std::string szFileName);


int main(int argc, char* argv[]) {
	// useage : SOSfinder <input file name/dir(optional)> 
	int iRtn;
	std::string szTargetString;
	int iWindowSize = 8;
	std::fstream fsTargetFile;

	if (argc != 2) {
		std::cout << "Usage : SOSfinder <input file name>" << std::endl;
		return -1;
	}
	//InsertSignature(argv[1]);
	iRtn = GetTarget(fsTargetFile, argv[1], szTargetString);
	if (iRtn == D_FAIL) return -1;

	GetSimilarity(szTargetString, iWindowSize);
	if (iRtn == D_FAIL) return -1;

	return 0;

}

int TargetTokenize(std::fstream& fsTarget, std::string& szTargetString)
{
	std::string str;
	int cnt;

	while (getline(fsTarget, str))
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
		else if (str.find("blx") != -1)
			szTargetString += "blx";
		else if (str.find("bl") != -1)
			szTargetString += "bl";
		else if (str.find("b.") != -1)
			szTargetString += "b";
		else
		{
			szTargetString += "instruction\n";
			continue;
		}

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

	return D_SUCC;
}

int GetTarget(std::fstream& fsTarget, std::string szTargetFileName, std::string &szTargetString) {

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

int CheckLength(std::string szSigStr, std::string& szTargetStr, int& iSigSize) {

	if (szTargetStr.length() < 24) { // 24 == gram(8) * 3 인스트로덕션이 3글자이기 때문에
		std::cout << "Error : target file size is too small to compare.." << std::endl;
		return D_FAIL;
	}

	if (szTargetStr.length() < szSigStr.length()) {
		iSigSize = szTargetStr.length();
		szSigStr = szSigStr.substr(0, iSigSize);
	} 
	else {
		iSigSize = szSigStr.length();
	}

	return D_SUCC;
}

double CmpSigTarget(stSignature stSign, std::string szTargetStr, int iWinSize) {

	int iNGram,iFlag;
	int iCounter = 0;
	std::string::size_type iCursor = 0;
	std::string::size_type iPrev = 0;
	std::string::size_type iStart = 0;
	double dJaccardIndex;
	//std::string szTemp;
	std::string szNGramElement;
	std::set<std::string> setSigGram;
	std::set<std::string> setTargetGram;
	std::vector<std::string> vIntersection;
	std::vector<std::string> vUnion;

	//construct gram set
	iNGram = iWinSize;
	iFlag = 0;
	iStart = iPrev;  //do not work
	while ((iCursor = stSign.szSignature.find("\n", iStart + 1) < stSign.szSignature.length())) {
		
		szNGramElement = "";		
		//std::cout << szNGramElement << std::endl;		
	
		iStart = stSign.szSignature.find("\n", iStart + 1);
		iPrev = iStart;
		
		iCounter = 1;
		
		while (iCounter <= iNGram) {
				 
			iCursor = stSign.szSignature.find("\n", iPrev + 1);
			if(iCursor > stSign.szSignature.length()){
				iFlag = 1;
				break;
			}
			
			szNGramElement += stSign.szSignature.substr(iPrev, iCursor - iPrev);
			iPrev = iCursor;
			iCounter ++;				
		}
		if(iFlag)	break;
		//std::cout << "--------------------" << std::endl <<"iCursor : " << iCursor << std::endl << "------------------" << szNGramElement << std::endl;

		setSigGram.insert(szNGramElement);
				
		
	}
	
	iStart = 0;
	iPrev = 0;
	iCursor = 0;
	iFlag = 0;

	while ((iCursor = szTargetStr.find("\n", iStart + 1) < szTargetStr.length())) {
		
		szNGramElement = "";		
		//std::cout << szNGramElement << std::endl;		
		//std::cout << "iCursor : " << iCursor << " iPrev : " << iPrev << std::endl;

		iStart = szTargetStr.find("\n", iStart + 1);
		iPrev = iStart;
		
		iCounter = 1;
		
		while (iCounter <= iNGram) {
				 
			iCursor = szTargetStr.find("\n", iPrev + 1);
			if(iCursor > szTargetStr.length()){
				iFlag = 1;
				break;
			}
			
			szNGramElement += szTargetStr.substr(iPrev, iCursor - iPrev);
			//std::cout << szTargetStr.substr(iPrev, iCursor - iPrev) << std::endl;
			iPrev = iCursor;
			iCounter ++;				
		}
		if(iFlag)	break;
		//std::cout << "iCursor : " << iCursor << " iPrev : " << iPrev << std::endl;

		setTargetGram.insert(szNGramElement);
	}
	
	std::set_intersection(setSigGram.begin(), setSigGram.end(), setTargetGram.begin(), setTargetGram.end(), std::back_inserter(vIntersection));
	std::set_union(setSigGram.begin(), setSigGram.end(), setTargetGram.begin(), setTargetGram.end(), std::back_inserter(vUnion));
	
	//std::cout << setSigGram.size() << " " << setTargetGram.size() << std::endl;
	//std::cout << (double)vIntersection.size() << " " << (double)vUnion.size()<< std::endl;
	dJaccardIndex = (double)vIntersection.size() / (double)vUnion.size();

	//need to modi : print out when upper threshold
	//std::cout << "Jaccard Index is " << dJaccardIndex << std::endl;
	
	return dJaccardIndex;
}

int GetSignature(MYSQL_ROW row, stSig &stSign) {
	
	// row[0] => name_of_vuln 
	// row[1] => number_of_CVE  
	// row[2] => Tokenized_binary_code_of_vuln
	stSign.szSigName = row[0];
	stSign.szSigCVENum = row[1];
	stSign.szSignature = row[2];
	
	return D_SUCC;
}

int GetSimilarity(std::string &szTargetStr, int iWindowSize) {

	int iRtn;
	int iMaxJI = -1;
	int iSigSize;
	double dResultJaccard = 0;
	double dTempJaccard = 0;
	std::string::size_type iStart = 0;
	
	MYSQL_RES *res;	// the results
	MYSQL_ROW row;	// the results row (line by line)

	std::string szDBQuery = "SELECT * FROM vuln";

	//DB connect
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection, "localhost", "root", "1234", "vuln", 0, NULL, 0)) {
		std::cout << "DB Conection error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	if (mysql_query(connection, szDBQuery.c_str()))
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
		std::cout << stSigObject.szSigName << " : " <<stSigObject.szSignature.length() << " " << "input : " << szTargetStr.length() << std::endl; 
		dResultJaccard = 0;
		iStart = 0;		
		CheckLength(stSigObject.szSignature, szTargetStr, iSigSize);		
		//need to compare same size window
		//CmpSigTarget(stSigObject, szTargetStr, iWindowSize);
		double start_time = clock();				
		while( iStart + iSigSize  <= szTargetStr.length()){
			dTempJaccard = CmpSigTarget(stSigObject, szTargetStr.substr(iStart, iSigSize), iWindowSize);
			iStart = szTargetStr.find("\n", iStart + 1);
			dResultJaccard = dResultJaccard > dTempJaccard ? dResultJaccard : dTempJaccard;
		}
		double end_time = clock();
		std::cout << "total time : " << ((end_time - start_time)/CLOCKS_PER_SEC) << std::endl;
		std::cout << "JaccardIndex is : " << dResultJaccard << std::endl << std::endl;	
	}

	return D_SUCC;

}
//----------------------------------------------------------------------------------------------------
int GetSimilarity2(std::string &szTargetStr, int iWindowSize) {

	int iRtn;
	int iMaxJI = -1;
	int iSigSize;
	double dResultJaccard = 0;
	double dTempJaccard = 0;
	std::string::size_type iStart = 0;
	
	MYSQL_RES *res;	// the results
	MYSQL_ROW row;	// the results row (line by line)

	std::string szDBQuery = "SELECT * FROM vuln";

	//DB connect
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection, "localhost", "root", "1234", "vuln", 0, NULL, 0)) {
		std::cout << "DB Conection error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	if (mysql_query(connection, szDBQuery.c_str()))
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
		std::cout << stSigObject.szSigName << " : " <<stSigObject.szSignature.length() << " " << "input : " << szTargetStr.length() << std::endl; 
		dResultJaccard = 0;
		iStart = 0;		
		CheckLength(stSigObject.szSignature, szTargetStr, iSigSize);
		double start_time = clock();		
		//need to compare same size window
		//CmpSigTarget(stSigObject, szTargetStr, iWindowSize);
		if(2 * iSigSize >= szTargetStr.length()){
			while( iStart + iSigSize  <= szTargetStr.length()){
				dTempJaccard = CmpSigTarget(stSigObject, szTargetStr.substr(iStart, iSigSize), iWindowSize);
				iStart = szTargetStr.find("\n", iStart + 1);
				dResultJaccard = dResultJaccard > dTempJaccard ? dResultJaccard : dTempJaccard;
			}
		}
		else{
			while( iStart + (2 * iSigSize)  <= szTargetStr.length()){
				dTempJaccard = CmpSigTarget(stSigObject, szTargetStr.substr(iStart, 2*iSigSize), iWindowSize);
				iStart += iSigSize;
				dResultJaccard = dResultJaccard > dTempJaccard ? dResultJaccard : dTempJaccard;
			}
			dTempJaccard = CmpSigTarget(stSigObject, szTargetStr.substr(iStart, szTargetStr.length() - (2*iSigSize) + 1), iWindowSize);
			dResultJaccard = dResultJaccard > dTempJaccard ? dResultJaccard : dTempJaccard;
		}
		double end_time = clock();
		std::cout << "total time : " << ((end_time - start_time)/CLOCKS_PER_SEC) << std::endl;
		std::cout << "JaccardIndex is : " << dResultJaccard << std::endl << std::endl;	
	}

	return D_SUCC;

}
int GetSimilarity3(std::string &szTargetStr, int iWindowSize) {

	int iRtn;
	int iMaxJI = -1;
	int iSigSize;
	double dResultJaccard = 0;
	double dTempJaccard = 0;
	std::string::size_type iStart = 0;
	
	MYSQL_RES *res;	// the results
	MYSQL_ROW row;	// the results row (line by line)

	std::string szDBQuery = "SELECT * FROM vuln";

	//DB connect
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection, "localhost", "root", "1234", "vuln", 0, NULL, 0)) {
		std::cout << "DB Conection error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	if (mysql_query(connection, szDBQuery.c_str()))
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
		std::cout << stSigObject.szSigName << " : " <<stSigObject.szSignature.length() << " " << "input : " << szTargetStr.length() << std::endl; 
		dResultJaccard = 0;
		iStart = 0;		
		CheckLength(stSigObject.szSignature, szTargetStr, iSigSize);		
		// need to compare same size window
		// CmpSigTarget(stSigObject, szTargetStr, iWindowSize);
		double start_time = clock();		
		while( iStart + iSigSize  <= szTargetStr.length()){
			// need to modify for third method
		}
		double end_time = clock();
		std::cout << "total time : " << ((end_time - start_time)/CLOCKS_PER_SEC) << std::endl;
		std::cout << "JaccardIndex is : " << dResultJaccard << std::endl << std::endl;	
	}

	return D_SUCC;

}
//---------------------------------------------------------------------------------------------------
int InsertSignature(std::string szFileName) {

	std::fstream fsSignatureFile;
		
	std::string FileName;
	std::string CVENum;
	std::string BinCode;
	std::string szLine;
	FileName = szFileName;
	CVENum = "test";
	BinCode = "";

	fsSignatureFile.open(szFileName.c_str(), std::ios::in);
	TargetTokenize(fsSignatureFile, BinCode);

	//-----------------------------------------------------------------------------------------------
	std::string szDBQuery = "INSERT INTO vuln (name,CVENum,BinCode) VALUES ('"+ FileName +"','"+ CVENum +"','"+ BinCode +"')";
	//-----------------------------------------------------------------------------------------------
	
	
	//DB connect
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection, "localhost", "root", "1234", "vuln", 0, NULL, 0)) {
		std::cout << "DB Conection error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	if (mysql_query(connection, szDBQuery.c_str()))
	{
		std::cout << "MySQL query error : " << mysql_error(connection) << "\n" << std::endl;
		exit(1);
	}
	return D_SUCC;
}
