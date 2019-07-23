%module krnnt_utils

%include "std_vector.i"
%include "std_string.i"
namespace std {
        %template(StringVector) vector<string>;
        %template(StringVectorVector) vector< vector<string> >;
}

%include "shape.i"
%include "flatten.i"
%include "uniq.i"
%include "create_tags4_without_guesser.i"
%include "create_tags5_without_guesser.i"
