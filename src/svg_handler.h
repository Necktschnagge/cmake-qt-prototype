#ifndef SVG_HANDLER_H
#define SVG_HANDLER_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class SvgHandler
{
public:
    SvgHandler();
    ~SvgHandler();

    bool load(string path);
    bool save(string path, string text);

    void update(string text);
    void clean();

    string last();
    string undo();
    string redo();

private:
    vector<string> svg_texts;
    int index;

    bool isValid(string path);

};

#endif // SVG_HANDLER_H
