#include <gtest/gtest.h>

#include "../text_document.h"
#include "../editor.h"
#include "../command_creator.h"
#include "../editor_manager.h"

[[maybe_unused]] std::unique_ptr<EditorCommand> create_editor_command(Command name, std::string buff,
                                                                      std::size_t begin = 0, std::size_t end = 0){
    CommandDTO dto = CommandDTO(name, buff, begin, end);
    return CommandCreator::try_create_editor_command(dto);
}



TEST(TextDocumet, BasicTest){
    TextDocument doc;
    doc.insert("01234", 1);
    EXPECT_EQ(doc.data(), "01234");
    doc.erase(0, 2);
    EXPECT_EQ(doc.data(), "234");
    EXPECT_EQ(doc.substr(0, 2), "23");
    EXPECT_EQ(doc.size(), 3);
    std::ostringstream oss;
    doc.save(oss);
    EXPECT_EQ(oss.str(), "234");
}

TEST(CopyAndPaste, Empty) {
    std::istringstream input;
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    auto cmd = create_editor_command(Command::COPY, "", 0, 10);
    editor.execute(std::move(cmd));
    EXPECT_TRUE(doc.data().empty());
}

TEST(CopyAndPaste, NonEmpty) {
    std::istringstream input("aaa bb c");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);

    auto cmd1 = create_editor_command(Command::COPY, "", 5, 10);
    editor.execute(std::move(cmd1));
    EXPECT_EQ(doc.data(), "aaa bb c");
    auto cmd2 = create_editor_command(Command::PASTE, "", 6, 0);
    editor.execute(std::move(cmd2));
    EXPECT_EQ(doc.data(), "aaa bbb c c");

    auto cmd3 = create_editor_command(Command::COPY, "", 20, 1);
    editor.execute(std::move(cmd3));
    EXPECT_EQ(doc.data(), "aaa bbb c c");

//    editor.Paste(6);
    auto cmd4 = create_editor_command(Command::PASTE, "", 6, 0);
    editor.execute(std::move(cmd4));

    EXPECT_EQ(doc.data(), "aaa bbb c c");

//    editor.Copy(0, 1);
    auto cmd5 = create_editor_command(Command::COPY, "", 0, 1);
    editor.execute(std::move(cmd5));

    EXPECT_EQ(doc.data(), "aaa bbb c c");
//    editor.Paste(0);
    auto cmd6 = create_editor_command(Command::PASTE, "", 0, 0);
    editor.execute(std::move(cmd6));

    EXPECT_EQ(doc.data(), "aaaa bbb c c");

//    editor.Copy(8, 12);
    auto cmd7 = create_editor_command(Command::COPY, "", 8, 12);
    editor.execute(std::move(cmd7));

    EXPECT_EQ(doc.data(), "aaaa bbb c c");
//    editor.Paste(20);
    auto cmd8 = create_editor_command(Command::COPY, "", 20, 0);
    editor.execute(std::move(cmd8));
}

TEST(CopyAndPaste, Undo) {
    std::istringstream input("aaa bb c");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);

    auto cmd1 = create_editor_command(Command::COPY, "", 5, 10);
    editor.execute(std::move(cmd1));
    EXPECT_EQ(doc.data(), "aaa bb c");
    auto cmd2 = create_editor_command(Command::PASTE, "", 6, 0);
    editor.execute(std::move(cmd2));
    EXPECT_EQ(doc.data(), "aaa bbb c c");
    editor.Undo();
    EXPECT_EQ(doc.data(), "aaa bb c");
}
//
TEST(CopyAndPaste, Redo) {
    std::istringstream input("aaa bb c");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);

    auto cmd1 = create_editor_command(Command::COPY, "", 5, 10);
    editor.execute(std::move(cmd1));
    EXPECT_EQ(doc.data(), "aaa bb c");
    auto cmd2 = create_editor_command(Command::PASTE, "", 6, 0);
    editor.execute(std::move(cmd2));
    EXPECT_EQ(doc.data(), "aaa bbb c c");
    editor.Undo();
    EXPECT_EQ(doc.data(), "aaa bb c");
    editor.Redo();
    EXPECT_EQ(doc.data(), "aaa bbb c c");
    editor.Undo();
    EXPECT_EQ(doc.data(), "aaa bb c");
}

TEST(Insert, Empty) {
    std::istringstream input;
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    std::string buff = "";
    auto cmd1 = create_editor_command(Command::INSERT, buff, 0, 0);
    editor.execute(std::move(cmd1));
    EXPECT_TRUE(doc.data().empty());
    buff = "abc";
    auto cmd2 = create_editor_command(Command::INSERT, buff, 0, 0);
    editor.execute(std::move(cmd2));
    EXPECT_EQ(doc.data(), "abc");
}

TEST(Parser, CopyAndPaste) {
    std::istringstream input("abc def");
    std::istringstream commands("copy 1, 3\npaste 0");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    CommandParser parser(commands);
    EditorManager manager(editor, parser);
    manager.execute();
    EXPECT_EQ(doc.data(), "bcabc def");
}

TEST(Parser, Insert) {
    std::istringstream input("abc def");
    std::istringstream commands("insert \"gh\", 3");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    CommandParser parser(commands);
    EditorManager manager(editor, parser);
    manager.execute();
    EXPECT_EQ(doc.data(), "abcgh def");
}

TEST(Parser, Delete) {
    std::istringstream input("abc def");
    std::istringstream commands("delete 0, 4");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    CommandParser parser(commands);
    EditorManager manager(editor, parser);
    manager.execute();
    EXPECT_EQ(doc.data(), "def");
}

TEST(Parser, Undo) {
    std::istringstream input("abc def");
    std::istringstream del("delete 0, 4");
    auto doc = TextDocument(input);
    auto editor = Editor(doc);
    CommandParser parser1(del);
    EditorManager manager1(editor, parser1);
    manager1.execute();
    EXPECT_EQ(doc.data(), "def");

    std::istringstream un("undo");
    CommandParser parser2(un);
    EditorManager manager2(editor, parser2);
    manager2.execute();
    EXPECT_EQ(doc.data(), "abc def");

    std::istringstream commands("delete 0, 4\nundo");
    CommandParser parser3(commands);
    EditorManager manager3(editor, parser3);
    manager3.execute();
    EXPECT_EQ(doc.data(), "abc def");
}