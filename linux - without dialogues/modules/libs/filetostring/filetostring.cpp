#include "filetostring.hpp"

using namespace std;

FileToString::FileToString(const string & fn)
{
    setFileName(fn);
    lines = counterLines();
}

unsigned FileToString::counterLines() const
{
    try{
        return linesToEOF();
    }
    catch (runtime_error & e)
    {
       cerr<<e.what();
       exit(EXIT_FAILURE);
    }
}

unsigned FileToString::linesToEOF() const
{
    ifstream file(fileName);

    if (!file.is_open())
        throw runtime_error("Can't open the file: "+fileName+"\n");

    unsigned lines = 0;
    string temp;
    for (; getline(file, temp); ++lines) ;

    file.clear();
    file.close();
    return lines;
}

FileToString::FileToString(const FileToString & obj)
{
	fileName = obj.fileName;
	buffor = obj.buffor;
	lines = obj.lines;
}

FileToString & FileToString::operator=(const FileToString & obj)
{
	if (this == &obj) return *this;

	fileName = obj.fileName;
	buffor = obj.buffor;
	lines = obj.lines;

	return *this;
}

string FileToString::operator()(const string & fn)
{
    setFileName(fn);
    lines = counterLines();
    return getFileName();
}

string FileToString::operator()(const unsigned & numerLine)
{
    loadLine(numerLine);

    return val();
}

void FileToString::loadLine(const unsigned & numerLine)
{
	try{
		loadLineFromFile(numerLine);
	}
	catch (runtime_error & e){
        cerr<<e.what();
        exit(EXIT_FAILURE);
    }
}

void FileToString::loadLineFromFile(const unsigned & numerLine)
{
    unsigned numLine = checkNumber(numerLine);

	ifstream file(fileName);
	if (!file.is_open())
		throw runtime_error("Can't open the file: "+fileName+"\n");

	buffor = shared_ptr<string>(new string);

	string line;
	for (unsigned i = 1; getline(file, line); ++i)
	{
		if (i == numLine)
		{
			*buffor = line;
			break;
		}
	}
	file.clear();
	file.close();
}

unsigned FileToString::checkNumber(unsigned number) const
{
    if (number == 0) number = 1;
    else if (number < 0) number = -number;
    return number;
}
