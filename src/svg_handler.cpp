#include "svg_handler.h"

SvgHandler::SvgHandler()
{
    // Clear stored svg texts.
    clean();
}

SvgHandler::~SvgHandler()
{
    // Nothing to do.
}

bool SvgHandler::isValid(string path)
{
    transform(path.begin(), path.end(), path.begin(), ::toupper);
    return !(path.rfind(".SVG") == string::npos );
}

bool SvgHandler::load(string path)
{
    string lines = "";
    if (isValid(path)) {
        cout << "Open : " << path << endl;
        try {
            fstream filein;
            filein.open(path, ios::in);
            if (filein.is_open()) {
                string line;
                while (getline(filein, line)) {
                    lines.append(line + '\n');
                }
                filein.close();
            }
        } catch (...) {
            cout << "There was something wrong!" << endl;
        }
    }

    if (lines.empty()) {
        cout << "Empty file!" << endl;
        return false;
    }

    clean();
    update(lines);

    return true;
}

bool SvgHandler::save(string path, string text)
{
    if (isValid(path) && !text.empty()) {
        try {
            fstream fileout;
            fileout.open(path, ios::out);
            fileout << text;
            fileout.close();
            cout << "Save: " << path << endl;
            return true;
        } catch (...) {
            cout << "There was something wrong!" << endl;
        }
    }
    return false;
}

void SvgHandler::update(string text)
{
    if (!text.empty()) {
        this->svg_texts.push_back(text);
        cout << "New stored SVG text!" << endl;
        index = static_cast<int>(svg_texts.size() - 1);
    }
}

void SvgHandler::clean()
{
    svg_texts.clear();
    index = 0;
}

string SvgHandler::last()
{
    if (svg_texts.empty()) {
        cout << "Empty SVG Text Store!" << endl;
        return "";
    }

    cout << "Return last SVG text." << endl;
    return svg_texts.back();
}

string SvgHandler::undo()
{
    index = index - 1 < 0 ? index : index - 1;
    cout << "SVG text: " << index << "/" << (svg_texts.size() - 1) << endl;
    return svg_texts[index];
}

string SvgHandler::redo()
{
    index = index + 1 >= static_cast<int>(svg_texts.size()) ? index : index + 1;
    cout << "SVG text: " << index << "/" << (svg_texts.size() - 1) << endl;
    return svg_texts[index];
}
