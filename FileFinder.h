#include "config.h"
#include <vector>
using namespace std;
class FileFinder{
private:
	vector<string> files;
	void getFilesOnDir(string directory,vector<string> &v);
public:
	FileFinder(string path);
	vector<string> getFiles();
};