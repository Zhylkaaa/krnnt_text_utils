%module krnnt_utils

%include "std_vector.i"
%include "std_string.i"
%include "std_map.i"

namespace std {
        %template(StringVector) vector<string>;
        %template(StringVectorVector) vector< vector<string> >;
        %template(StringVectorVectorVector) vector< vector< vector< string > > >;
        %template(IntVectorVector) vector< vector< int > >;
        %template(IntVectorVectorVector) vector< vector< vector< int > > >;
        %template(StringIntMap) map<string, int>;
}

%include "shape.i"
%include "flatten.i"
%include "uniq.i"
%include "create_tags4_without_guesser.i"
%include "create_tags5_without_guesser.i"
%include "pad.i"