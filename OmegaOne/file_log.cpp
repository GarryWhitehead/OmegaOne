#include "file_log.h"
#include <chrono>
#include <ctime>
#include <iomanip>

FileLog *g_filelog = nullptr;

FileLog::FileLog()
{
	g_filelog = this;
}

bool FileLog::Init(std::string filename)
{
	if (filename != "")
	{
		m_filename = filename;
		m_file.open(m_filename, std::ios_base::app);
		if (m_file.is_open())
		{
			// init file by writing time/date
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);
			m_file << "Data log initialised at " << std::put_time(std::localtime(&in_time_t), "%d-%m-&y %X") << "\n\n";
			m_file.close();
			return true;
		}
	}
	return false;
}

void FileLog::WriteLog(std::string text)
{
	m_file.open(m_filename, std::ios_base::app);
	if (m_file.is_open())
	{
		// log text along with time and date
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);
		m_file << "Text logged at: " << std::put_time(std::localtime(&in_time_t), "%d-%m-&y %X") << "\n";
		m_file << text << "\n\n";
		m_file.close();
	}
}

void FileLog::Delete()
{
	remove(m_filename.c_str());
}