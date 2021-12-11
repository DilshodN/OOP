#include <iostream>
#include "parser.h"
#include "editor_manager.h"
#include "text_document.h"
#include "editor.h"

using namespace std;
int main() {
    std::istringstream input("abc def");
    std::istringstream commands("copy 1, 3\npaste 0");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    CommandParser parser(commands);
    EditorManager manager(editor, parser);
    manager.execute();
    return 0;
}