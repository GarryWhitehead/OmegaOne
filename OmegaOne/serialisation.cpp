#include "serialisation.h"
#include <string>
#include <memory>
#include <regex>
#include "file_log.h"

template <typename T>
void SerialiseText(TextArchive *arch, T value, const var_info& info, std::string& line)
{
	// data stored in text file in the format e.g. <.x>val
	std::string begin_str = "<" + info.name + ">";
	std::string end_str = "";

	if (arch->mode == FileMode::FILE_OUT)
	{
		arch->file << begin_str << value << end_str << "\n";
	}
	else
	{
		getline(arch->file, line);
		size_t beg_loc = line.find(">");
		size_t end_loc = line.find("");
		line = line.substr(beg_loc + 1, end_loc - beg_loc);
		// to make sure that we have a digit only, regex the string
		line = std::regex_replace(line, std::regex("([^0-9])"), "");
	}
}

void TextArchive::Serialise(char& value, const var_info& info)
{
	std::string line;
	SerialiseText<int32_t>(this, value, info, line);
	if (!line.empty())
		value = line[0];
}

void TextArchive::Serialise(float& value, const var_info& info)
{
	std::string line;
	SerialiseText<float>(this, value, info, line);
	if (!line.empty())
		value = std::stof(line);
}

void TextArchive::Serialise(int32_t& value, const var_info& info)
{
	std::string line;
	SerialiseText<int32_t>(this, value, info, line);
	if (!line.empty())
		value = std::stoi(line);
}

void TextArchive::Serialise(uint32_t& value, const var_info& info)
{
	std::string line;
	SerialiseText<uint32_t>(this, value, info, line);
	if (!line.empty())
		value = std::stoi(line);
}

void TextArchive::Serialise(bool& value, const var_info& info)
{
	std::string line;
	SerialiseText<bool>(this, value, info, line);
	if (!line.empty())
		value = (std::stoi(line) == 0) ? false : true;
}

// global serialisation functions
void Serialise(Archive *arch, char& value, const var_info& info)
{
	arch->Serialise(value, info);
}

void Serialise(Archive *arch, float& value, const var_info& info)
{
	arch->Serialise(value, info);
}

void Serialise(Archive *arch, int32_t& value, const var_info& info)
{
	arch->Serialise(value, info);
}

void Serialise(Archive *arch, uint32_t& value, const var_info& info)
{
	arch->Serialise(value, info);
}

void Serialise(Archive *arch, bool& value, const var_info& info)
{
	arch->Serialise(value, info);
}