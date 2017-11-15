#define _CRT_SECURE_NO_WARNINGS
#ifndef _TEXT_LOG_H
#define _TEXT_LOG_H
#include <string>
#include <fstream>

class FileLog;

extern FileLog *g_filelog;

class FileLog
{
public:
	FileLog();
	~FileLog() {}

	bool Init(std::string filename);
	void WriteLog(std::string text);
	void Delete();

private:
	std::ofstream m_file;
	std::string m_filename;
};

#endif _TEXT_LOG_H
