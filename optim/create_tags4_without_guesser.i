%module create_tag4_test
%{
        #include "create_tags4_without_guesser.h"
%}

%include "std_vector.i"
%include "std_string.i"
namespace std {
        %template(StringVector) vector<string>;
}
%include "create_tags4_without_guesser.h"
