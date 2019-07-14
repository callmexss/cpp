/**
 * Regular Expression: a regular expression is a specific pattern 
 * that provides concise and flexible means to "match" strings of text,
 * such as particular characters, words, or patterns of characters. - wikipedia
 */
#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    string str("abc");
    while (true)
    {
        cin >> str;

        /**
         * .        Any character except newline.
         * ?        Zero or One proceding character.
         * *        Zero or More proceding character.
         * +        One or More proceding character.
         * [...]    Any character inside the square brackets.
         * ^[...]   Any character not inside the square brackets.
         * {s,e}    Show [s..e] times.
         * |        Or
         * \        Escape
         * ()       Group
         * [[:w:]]  Word Character: digit, number, or underscore
         * ^        Start char
         * $        End char
         */
        regex e("abc.", regex_constants::icase);
        // regex e("abc?");
        // regex e("abc*");
        // regex e("abc+");
        // regex e("ab[cd]*");
        // regex e("ab[^cd]*");
        // regex e("ab[cd]{3}");
        // regex e("ab[cd]{3, 5}");
        // regex e("ab[cd]{3,}");
        // regex e("ab|de[\]fg]"); // this is weird
        // regex e("(abc)de+\\1]"); // \1 first group
        // regex e("(ab)c(de+)\\2\\1");
        // regex e("[[:w:]]+@[[:w:]]+\.com");
        // bool match = regex_match(str, e);
        bool match = regex_search(str, e);
        cout << (match ? "Matched" : "Not matched") << endl;
    }
    return 0;
}
