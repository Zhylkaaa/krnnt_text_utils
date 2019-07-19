%module flatten_test
%{
        #include "flatten.h"
%}

%include "std_vector.i"
%include "std_string.i"
namespace std {
        %template(StringVector) vector<string>;
        %template(StringVectorVector) vector< vector<string> >;
}
%include "flatten.h"
