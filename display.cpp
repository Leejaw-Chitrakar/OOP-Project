#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>       // Required for toupper
#include <algorithm>    // Required for max
#include <limits>       // Required for numeric_limits
using namespace std;


// Map to store ASCII art for each letter
map<char, vector<string>> ascii_letters;

void initializeAsciiLetters() {
     // --- Letters for "STUDENT" ---
    // Define 'S'
    ascii_letters['S'] = {
        " ### ",
        "#    ",
        " ### ",
        "    #",
        " ### "
    };

    // Define 'T'
    ascii_letters['T'] = {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    };

    // Define 'U'
    ascii_letters['U'] = {
        "#   #",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    };

    // Define 'D'
    ascii_letters['D'] = {
        "#### ",
        "#   #",
        "#   #",
        "#   #",
        "#### "
    };

    // Define 'E'
    ascii_letters['E'] = {
        "#####",
        "#    ",
        "###  ",
        "#    ",
        "#####"
    };

    // Define 'N'
    ascii_letters['N'] = {
        "#   #",
        "##  #",
        "# # #",
        "#  ##",
        "#   #"
    };

    // --- Letters for "MANAGEMENT SYSTEM" ---
    // Define 'M'
    ascii_letters['M'] = {
        "#   #",
        "## ##",
        "# # #",
        "#   #",
        "#   #"
    };

    // Define 'A'
    ascii_letters['A'] = {
        "  #  ",
        " # # ",
        "#####",
        "#   #",
        "#   #"
    };

    // Define 'G'
    ascii_letters['G'] = {
        " ####",
        "#    ",
        "# ###",
        "#   #",
        " ### "
    };
    // Removed `ascii_letters['*']` as it's not part of the target words.


    // Define 'Y' (for SYSTEM)
    ascii_letters['Y'] = {
        "#   #",
        " # # ",
        "  #  ",
        "  #  ",
        "  #  "
    };

    // --- Special Characters ---
    // Define space (empty lines for spacing between words)
    ascii_letters[' '] = {
        "     ",
        "     ",
        "     ",
        "     ",
        "     "
    };

    // Define exclamation mark (if needed)
    ascii_letters['!'] = {
        "  !  ",
        "  !  ",
        "  !  ",
        "     ",
        "  !  "
    };
}

void printBigText(const string& text) {
    if (ascii_letters.empty()) {
        initializeAsciiLetters();
    }

    // Determine the height of the largest character (assuming consistent height)
    int char_height = 0;
    if (!ascii_letters.empty() && !ascii_letters.begin()->second.empty()) {
        char_height = ascii_letters.begin()->second.size();
    } else {
        cerr << "ASCII letters not initialized or empty.\n";
        return;
    }

    // Print line by line
    for (int i = 0; i < char_height; ++i) { // For each row of the big letters
        for (char c : text) { // For each character in the input text
            char upper_c = toupper(c); // Convert to uppercase for lookup

            if (ascii_letters.count(upper_c)) {
                // If the character is defined, print its corresponding line
                cout << ascii_letters[upper_c][i] << "  "; // Add some spacing between letters
            } else {
                // If not defined, print a placeholder or ignore
                cout << "???  ";
            }
        }
        cout << "\n"; // Newline after each row of big letters
    }
}

// Function to get the big text content as a vector of strings
// (This is a helper to allow calculating total width before printing)
vector<string> getBigTextLines(const string& text) {
    vector<string> lines;
    if (ascii_letters.empty()) {
        initializeAsciiLetters();
    }

    int char_height = 0;
    if (!ascii_letters.empty() && !ascii_letters.begin()->second.empty()) {
        char_height = ascii_letters.begin()->second.size();
    } else {
        cerr << "ASCII letters not initialized or empty.\n";
        return lines;
    }

    for (int i = 0; i < char_height; ++i) {
        string current_line = "";
        for (char c : text) {
            char upper_c = toupper(c);
            if (ascii_letters.count(upper_c)) {
                current_line += ascii_letters[upper_c][i];
                current_line += "  "; // Add spacing between letters
            } else {
                current_line += "???  "; // Placeholder for undefined characters
            }
        }
        lines.push_back(current_line);
    }
    return lines;
}

// Function to print text with a simple ASCII border
void printTextWithBorder(const vector<string>& text_lines, int horizontal_padding = 2) {
    if (text_lines.empty()) {
        cout << "Empty text provided for border.\n";
        return;
    }

    // Calculate maximum width of the text lines
    size_t max_text_width = 0;
    for (const string& line : text_lines) {
        max_text_width = max(max_text_width, line.length());
    }

    // Calculate total border width
    // +2 for the '+' characters, + (2 * horizontal_padding) for inner padding
    size_t border_width = max_text_width + (2 * horizontal_padding) + 2;

    // Top border
    cout << "+" ;
    for (size_t i = 0; i < border_width - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";

    // Content lines with side borders and padding
    for (const string& line : text_lines) {
        cout << "|";
        for (int i = 0; i < horizontal_padding; ++i) {
            cout << " "; // Left padding
        }
        cout << line;
        // Pad with spaces to match max width + horizontal padding
        for (size_t i = line.length(); i < max_text_width; ++i) {
            cout << " ";
        }
        for (int i = 0; i < horizontal_padding; ++i) {
            cout << " "; // Right padding
        }
        cout << "|\n";
    }

    // Bottom border
    cout << "+" ;
    for (size_t i = 0; i < border_width - 2; ++i) {
        cout << "-";
    }
    cout << "+\n";
}

// Function to show the ASCII art title
void showTitle() {
    initializeAsciiLetters();
    vector<string> title_part1 = getBigTextLines("   STUDENTS");
    vector<string> title_part2 = getBigTextLines("  MANAGEMENT");
    vector<string> title_part3 = getBigTextLines("   SYSTEM");
    vector<string> full_title_lines;
    full_title_lines.insert(full_title_lines.end(), title_part1.begin(), title_part1.end());
    full_title_lines.push_back("");
    full_title_lines.insert(full_title_lines.end(), title_part2.begin(), title_part2.end());
    full_title_lines.push_back("");
    full_title_lines.insert(full_title_lines.end(), title_part3.begin(), title_part3.end());
    cout << "\n\n";
    printTextWithBorder(full_title_lines, 3);
    cout << "\n\n";
}
