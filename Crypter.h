#include "config.h"
#include <cryptopp/rsa.h>
using namespace std;
class Crypter{
public:
	Crypter();
	void encryptFile(char* filename,char *srcPath, char*  key);
	void decryptFile(char * filename,char *srcPath,char* key);
	char * generateKey();
	string encryptAesKeyWithPublicKey(string aesKey);
	string decryptAesKeyWithPrivateKey(string cryptedAes, char * privateKey);
	void createKeyFile(char *key,char *path);
private:
	char fileDelim;
	char * getFileName(char *);

	
};