#include "config.h"
#include "Arboresance.h"
#include <stdlib.h>
#include <iostream>


#ifdef LINUX
	#include <sys/stat.h>
	#include <sys/types.h>
#else 
	#include <windows.h>
#endif


using namespace std;

	void Arboresance::createArboresance(char *cryptedFiles,char *keysDir){
		//TODO RM TMP FOLDER LINUX
		//TODO CREATE SRCPATH IF NOT EXITS WINDOWS 
#ifdef LINUX
		mkdir(cryptedFiles,S_IRWXU|S_IRWXG|S_IRWXO);
		mkdir(keysDir,S_IRWXU|S_IRWXG|S_IRWXO);
#else 
		CreateDirectory(cryptedFiles, NULL);
		CreateDirectory(keysDir, NULL);
#endif
	}	
