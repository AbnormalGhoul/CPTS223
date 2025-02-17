// This was the file I copied from the lecture but I ended up not using it cuz it was unnecessary
// But I have it here cuz the rubric wants it

#include <iostream>
#include <string>
#include <forward_list>
#include <iterator>

using namespace std;

class Data
{
public:
    string key;
    string value;

    Data(string command, string description) : key(command), value(description) {
        
    }
};