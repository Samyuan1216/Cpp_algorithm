#include <bits/stdc++.h>

int main()
{
    std::string prefix, description, line;
    std::cin >> prefix;
    std::cin.ignore();

    std::getline(std::cin, description);

    std::vector<std::string> body_lines;
    while (std::getline(std::cin, line))
    {
        body_lines.push_back(line);
    }

    std::cout << "{\n";
    std::cout << "\t\"Print to console\": {\n";
    std::cout << "\t\t\"scope\": \"cpp\",\n";
    std::cout << "\t\t\"prefix\": \"" << prefix << "\",\n";

    std::cout << "\t\t\"body\": [\n";
    for (size_t i = 0; i < body_lines.size(); ++i) {
        std::cout << "\t\t\t\"" << body_lines[i] << "\"";
        
        if (i != body_lines.size() - 1)
        {
            std::cout << ",";
        }

        std::cout << "\n";
    }

    std::cout << "\t\t],\n";
    std::cout << "\t\t\"description\": \"" << description << "\"\n";
    std::cout << "\t}\n";
    std::cout << "}\n";
}
