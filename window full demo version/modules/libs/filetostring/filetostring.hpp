/***
	File: filetostring.hpp
	Author: Stasiek Fortonski
	Date: 2016 - 12.08.17
***/

#ifndef FILETOSTRING_HPP
#define FILETOSTRING_HPP 1
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

class FileToString
{
	std::string fileName;
    std::shared_ptr<std::string> buffor;
    unsigned lines;

	void loadLineFromFile(const unsigned & numerLine);
    unsigned linesToEOF() const;
	unsigned checkNumber(unsigned number) const;

public:
	inline void setFileName(const std::string & fn)
	{
		fileName = fn;
	}

	inline std::string getFileName()
	{
		return fileName;
	}

	inline std::string val() const
	{
		return *buffor;
	}

	operator std::string()
	{
		return *buffor;
	}

    inline unsigned amountOfLines() const
	{
		return lines;
	}

	FileToString(){;}
	FileToString(const std::string & fn);
    FileToString(const FileToString & obj);
	FileToString & operator=(const FileToString & obj);

    void loadLine(const unsigned & numerLine);
    std::string operator()(const unsigned & numerLine);
    std::string operator()(const std::string & fn);
    unsigned counterLines() const;
};
#endif