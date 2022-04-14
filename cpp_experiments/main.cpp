#include <iostream>
#include <algorithm>
#include <stack>

bool valid_braces(const std::string& braces) {
    std::string openBraces = "([{";
    std::string closedBraces = ")]}";
    std::stack<char> st;

    for (const auto &elem: braces) {
        if (std::find(openBraces.begin(), openBraces.end(), elem) != openBraces.end()) {
            st.push(elem);
        }
        else{
            auto idx = std::find(closedBraces.begin(), closedBraces.end(), elem) - closedBraces.begin();

            if (not st.empty() and openBraces[idx] == st.top()) {
                st.pop();
            }
            else{
                return false;
            }
        }
    }
    return st.empty();
}

int main() {
    std:: cout << valid_braces("]]]");
    return 0;
}
