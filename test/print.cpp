#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Encode a string as a JSON string literal.
string jsonString(const string& s) {
    const char* hex = "0123456789abcdef";
    string result = "\"";
    for (unsigned char c : s) {
        if (c == '"' || c == '\\') {
            result += '\\';
            result += c;
        } else if (c < 0x20) {
            result += "\\u00";
            result += hex[c >> 4];
            result += hex[c & 15];
        } else {
            result += c;
        }
    }
    return result + '"';
}

// Escape snippet syntax before applying JSON escaping.
string snippetLine(const string& s) {
    string result;
    for (char c : s) {
        if (c == '\\' || c == '$' || c == '}')
            result += '\\';
        result += c;
    }
    return jsonString(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string name, line;
    if (!getline(cin, name)) return 1;
    if (!name.empty() && name.back() == '\r') name.pop_back();
    if (name.empty()) {
        cerr << "Snippet name cannot be empty.\n";
        return 1;
    }

    vector<string> body;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line == "<<<END>>>") break;
        body.push_back(line);
    }

    cout << "{\n  " << jsonString(name) << ": {\n"
         << "    \"scope\": \"cpp\",\n"
         << "    \"prefix\": " << jsonString(name) << ",\n"
         << "    \"body\": [";
    for (size_t i = 0; i < body.size(); ++i)
        cout << (i ? ",\n" : "\n") << "      " << snippetLine(body[i]);
    cout << "\n    ],\n"
         << "    \"description\": " << jsonString(name) << "\n"
         << "  }\n}\n";
    return cout ? 0 : 1;
}