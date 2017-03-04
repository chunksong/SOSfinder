#include "SOSfinder.h"

int TargetTokenize(std::fstream& fsTarget,char* szTargetString) {
	

	return D_SUCC;
}

int GetTarget(std::fstream& fsTarget, char* szTargetFileName, char* szTargetString) {
	
	int iRtn;
	
	// open target file
	fsTarget.open(szTargetFileName, std::ios::in);
	
	// check target file validation 
	if (!fsTarget) {
		std::cout << "TargetFile open error.." << std::endl;
		return D_FAIL;
	}

	// store target file to szTargetString
	iRtn = TargetTokenize(fsTarget, szTargetString);
	if (iRtn == D_FAIL) {
		std::cout << "TargetFile Tokenize error.." << std::endl;
	}
	
	// close target file;
	fsTarget.close();
	
	return D_SUCC;
}

int ChekcLength(char* szSigStr, char* szTargetStr, int iWinSize) {
	return D_SUCC;
}

int CmpSigTarget(char* szSigStr, char* szTargetStr, int iWinSize) {
	return D_SUCC;
}

int GetSimilarity(char* szSigStr, char* szTargetStr, int iWindowSize) {
	
	int iRtn;
	int iMaxJI = -1;

	//DB connect


	//Get sig from Db by query
	iRtn = GetSignature(szSigStr);
	if (iRtn == D_FAIL) {
		std::cout << "Read SignatureFile from DB error.." << std::endl;
	}

	ChekcLength(szSigStr,szTargetStr, iWindowSize);

	CmpSigTarget(szSigStr, szTargetStr, iWindowSize);

}
int GetSignature(char* szSigStr) {

	
	szSigStr = 0; // need to modi
	
	return D_SUCC;
}


int main(int argc, char* argv[]) {
	// useage : SOSfinder <input file name/dir(optional)> 
	char* szTargetString;
	char* szSignatureString;
	int iWindowSize;
	std::fstream fsTargetFile;

	if (argc >= 3) {
		std::cout << "Usage : SOSfinder <input file name>" << std::endl;
	}

	GetTarget(fsTargetFile, argv[1],szTargetString);
	
	GetSimilarity(szSignatureString, szTargetString,iWindowSize);
	
	
	
	return 0;

}
