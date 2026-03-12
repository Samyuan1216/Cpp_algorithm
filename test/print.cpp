#include <bits/stdc++.h>

std::string escapeJSON(const std::string& input) {
    std::string output;
    output.reserve(input.length());
    for (char c : input) {
        switch (c) {
            case '"':  output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\t': output += "\\t";  break;
            default:   output += c;      break;
        }
    }
    return output;
}

int main() {
    std::string prefix, description, line;
    
    if (!(std::cin >> prefix)) return 0;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, description);
    description.erase(std::remove(description.begin(), description.end(), '\r'), description.end());
    description = escapeJSON(description);

    std::vector<std::string> body_lines;
    while (std::getline(std::cin, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        body_lines.push_back(escapeJSON(line));
    }

    std::cout << "{\n";
    std::cout << "\t\"Print to console\": {\n";
    std::cout << "\t\t\"scope\": \"cpp\",\n";
    std::cout << "\t\t\"prefix\": \"" << prefix << "\",\n";
    std::cout << "\t\t\"body\": [\n";

    for (size_t i = 0; i < body_lines.size(); ++i) {
        std::cout << "\t\t\t\"" << body_lines[i] << "\"";
        if (i != body_lines.size() - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }

    std::cout << "\t\t],\n";
    std::cout << "\t\t\"description\": \"" << description << "\"\n";
    std::cout << "\t}\n";
    std::cout << "}\n";

    return 0;
}
