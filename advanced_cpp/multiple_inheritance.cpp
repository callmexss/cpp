#include <iostream>
#include <string>
using namespace std;

/**
 * Multiple Inheritance
 */

class InputFile
{
public:
    void read() {}
    void open() {}
};

class OutputFile
{
public:
    void write() {}
    void open() {}
};

class IOFile : public InputFile, public OutputFile
{
};

int main()
{
    IOFile f;
    // f.open();
    f.OutputFile::open();

    return 0;
}

class File1
{                        //             File 
public:                  //              /\
    string name;         //     InputFile  OutputFile 
    void open() {}       //              \/
};                       //            IOFile 

class InputFile1 : virtual public File1
{
};

class OutputFile1 : virtual public File1
{
};

class IOFile1 : public InputFile1, public OutputFile1
{
}; // Diamond shape of hierarchy

int main1(int argc, const char** argv)
{
    IOFile1 f;
    f.open();
    return 0;
}

class File2
{
public:
    File2(string fname);
};

class InputFile2 : virtual public File2
{
public:
    InputFile2(string fname) : File2(fname) {}
};

class OutputFile2 : virtual public File2
{
public:
    OutputFile2(string fname) : File2(fname) {}
};

class IOFile2 : public InputFile2, public OutputFile2
{
public:
    IOFile2(string fname) : OutputFile2(fname), InputFile2(fname), File2(fname) {}
};


/*
 * Interface Segregation Principle
 * 
 * Split large interfaces into smaller and more specific ones so that clients
 * only need to know about the methods that are of interest to them.
 */

class Engineer
{
public:
    //...; // 40APIs
};

class Son
{
public:
    //...; //50APIs 
};

class Andy: public Engineer, Son
{
public:
    //...; //500 APIs
};

/**
 * Pure Abstract Classes
 * Abstract Class:A class has one or more pure virtural functions.
 * Pure Abstract Classes:
 * A class containing only pure virtual functions
 *     - no data
 *     - no concrete functions
 */

class OutputFile3
{
public:
    virtual void write() = 0;
    virtual void open() = 0;
};

/*
 * Summary:
 * 
 * 1. Multiple Inheritance is an important technicue,e.g.ISP
 * 2. Derive only from PACs when using Multiple Inheritance.
 */