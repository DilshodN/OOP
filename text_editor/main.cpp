#include <iostream>
#include <fstream>
#include "text_document.h"
#include "editor.h"

using namespace std;
int main() {
    std::ifstream in_file("input.txt");
    std::ifstream commands("commands.txt");
    auto doc = TextDocument(in_file);
    cout << "Init doc: " << doc.data() << endl;
    Editor editor(doc);
    editor.run(commands);
    cout << doc.data();
    return 0;
}