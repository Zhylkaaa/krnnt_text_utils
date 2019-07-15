#include "shape.h"

std::string shape(std::string text){
	if(text.empty())return "";

    static std::locale loc("pl_PL.UTF8");
    std::string res;
    UnicodeString text_unicode = UnicodeString::fromUTF8(text);
    int len = 0;

    if(std::islower((wchar_t)text_unicode[0], loc))res+='l';
    else if(std::isupper((wchar_t)text_unicode[0], loc))res+='u';
    else if(std::isdigit((wchar_t)text_unicode[0], loc))res+='d';
    else res+='x';

    for(int i = 1;i<text_unicode.length();i++){
        if(std::islower((wchar_t)text_unicode[i], loc)) {
            if(res[len]!='l'){res+='l';++len;}
        } else if(std::isupper((wchar_t)text_unicode[i], loc)) {
            if(res[len]!='u'){res+='u';++len;}
        } else if(std::isdigit((wchar_t)text_unicode[i], loc)) {
            if(res[len]!='d'){res+='d';++len;}
        } else {
            if(res[len]!='x'){res+='x';++len;}
        }
    }

    return res;
}
