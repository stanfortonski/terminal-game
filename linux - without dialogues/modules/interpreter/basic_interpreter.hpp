/***
* Author: Stasiek Fortoński
* Date: 21.05.2017
* Basic Interpreter With Saver And Loader
* Version: 1.0.2
***/

#ifndef BASICINTEPRETER_HPP
#define BASICINTEPRETER_HPP 1
#include <iostream>
#include <string>
#include <exception>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using std::string;
using std::ostream;
using std::ifstream;
using std::fstream;
using std::exception;

class BasicInterpreter
{
    std::string fileName;

    inline void keyEdit(string & key) const{key+="=";}

public:
	BasicInterpreter(){}
    explicit BasicInterpreter(const string & fn): fileName(fn){}
    virtual ~BasicInterpreter() {}

    void load(string key, string & val) const
    {
        try
        {
            keyEdit(key);
            ifstream file(fileName);
            if (!file.is_open()) throw exception();

            string temp;
            while (std::getline(file, temp))
            {
                size_t found = temp.find(key);

                if (string::npos != found)
                    val = temp.substr(key.size()+found, temp.size()-found);
            }
            file.clear();
            file.close();
        }
        catch(exception & e)
        {
            std::cerr<<"Loader Error: file "<<fileName<<" is not found!\n";
            exit(EXIT_FAILURE);
        }
    }

    template <typename T>
    void load(string key, T & val) const
    {
        try
        {
            keyEdit(key);
            ifstream file(fileName);
            if (!file.is_open()) throw exception();

            string temp;
            while (std::getline(file, temp))
            {
                size_t found = temp.find(key);

                if (string::npos != found)
                    val = atof(temp.substr(key.size()+found, temp.size()-found).c_str());
            }
            file.clear();
            file.close();
        }
        catch(exception & e)
        {
            std::cerr<<"Loader Error: file "<<fileName<<" is not found!\n";
            exit(EXIT_FAILURE);
        }
    }

    template <typename T>
    void save(string key, const T & val) const
    {
        keyEdit(key);
        fstream file(fileName, fstream::out | fstream::app);

        file<<key<<val<<std::endl;
        file.clear();
        file.close();
    }

	string getFileName() const{return fileName;}
	string & getFileName(){return fileName;}
};
#endif
