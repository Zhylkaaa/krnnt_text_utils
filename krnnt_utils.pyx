# distutils: language=c++
# cython: boundscheck=False, wraparound=False, initializedcheck=False, c_string_encoding='utf-8', c_string_type=str, optimiza.use_switch=True

from libcpp.string cimport string
from keras.preprocessing import sequence
import numpy as np
cimport numpy as np
from libcpp.string cimport string
from libcpp.vector cimport vector
from libcpp.unordered_set cimport unordered_set


def shape(word):
    cdef int index = 0
    cdef string s
    cdef Py_ssize_t ustring_len = len(word)
    cdef Py_UNICODE* ustring = word
    cdef int i

    if(ustring[0].islower()):
        s += <char> 'l'
    elif(ustring[0].isupper()):
        s += <char> 'u'
    elif(ustring[0].isdigit()):
        s += <char> 'd'
    else:
        s += <char> 'x'

    for i in range(1, ustring_len):
        if(ustring[i].islower()):
            if s[index] != <char> 'l':
                s += <char> 'l'
                index+=1
        elif(ustring[i].isupper()):
            if(s[index] != <char> 'u'):
                s += <char> 'u'
                index+=1
        elif(ustring[i].isdigit()):
            if(s[index] != <char> 'd'):
                s += <char> 'd'
            index += 1
        else:
            if(s[index] != <char> 'x'):
                s += <char> 'x'
                index += 1    
    return s

cdef inline k_hot(tags, unique_tags_dict):
    # print
    result = np.zeros(len(unique_tags_dict))

    for tag in tags:
        try:
            result[unique_tags_dict[tag]] = 1
        except KeyError:
            # print('KeyError:', tag, file=sys.stderr)
            pass
    return result

def pad(batch, unique_features_dict, feature_name):
    if not batch:
        return []

        # feature_name='tags4e3'
    result_batchX = []
        # print('batch len',len(batch))
    for sentence in batch:
        X_sentence = []
            # y_sentence = []
        for sample in sentence:
            # print(feature_name, sample.features[feature_name])
            X_sentence.append(k_hot(sample.features[feature_name], unique_features_dict[feature_name]))

        result_batchX.append(X_sentence)

        # max_sentence_length = max([len(x) for x in result_batchX])
        # self.log('KHOT')
    return sequence.pad_sequences(
        result_batchX)  # , sequence.pad_sequences(result_batchY, maxlen=max_sentence_length)

def create_tags4_without_guesser(tags):
    if('ign' in tags):
        return ['ign']
    cdef vector[string] res
    cdef unordered_set[string] used
    #used.reserve(5000)
    used.reserve(50)
    for tag in tags:
        create_tag4(tag, res, used)
    return res

cdef inline create_tag4(string s, vector[string]& res, unordered_set[string]& used):
    cdef string tags1 = string("1")
    cdef string tags2 = string("2")
    cdef int last_pos = -1
    cdef int i
    cdef string sub
    cdef string colon = string(":")

    for i in range(s.length()):
        if(s[i] == <char>':' or s[i] == <char>'.'):
            sub = s.substr(last_pos + 1, i - last_pos - 1)
            tags1 += sub
            tags2 += sub
            last_pos = i
            break
    else:
        sub = s.substr(last_pos + 1, s.length() - last_pos - 1)
        tags1 += sub
        tags2 += sub
        if(used.insert(tags1).second):
            res.push_back(tags1)
        if(used.insert(tags2).second):
            res.push_back(tags2)
        return

    for i in range(last_pos + 1, s.length()):
        if(s[i] == <char>':' or s[i] == <char>'.'):
            sub = s.substr(last_pos + 1, i - last_pos - 1)
            last_pos = i
            if(sub in ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc', 'pri', 'sec', 'ter']):
                tags1 += colon + sub
                break
            else:
                tags2 += colon + sub
    else:
        if(last_pos != s.length() - 1):
            sub = s.substr(last_pos + 1, s.length() - last_pos - 1)
            if(sub in ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc', 'pri', 'sec', 'ter']):
                tags1 += colon + sub
            else:
                tags2 += colon + sub

            if(used.insert(tags1).second):
                res.push_back(tags1)
            if(used.insert(tags2).second):
                res.push_back(tags2)
        return

    for i in range(last_pos + 1, s.length()):
        if(s[i] == <char>':' or s[i] == <char>'.'):
            sub = s.substr(last_pos + 1, i - last_pos - 1)
            last_pos = i
            tags2 += colon + sub

    if(last_pos != s.length() - 1):
        tags2 += colon + s.substr(last_pos + 1, s.length() - last_pos - 1)

    if(used.insert(tags1).second):
        res.push_back(tags1)
    if(used.insert(tags2).second):
        res.push_back(tags2)
        
def create_tags5_without_guesser(tags):
    if('ign' in tags):
        return ['ign']
    cdef vector[string] res
    cdef unordered_set[string] used
    #used.reserve(5000)
    used.reserve(50)

    for tag in tags:
        create_tag5(tag, res, used)
    return res

cdef inline create_tag5(string s, vector[string]& res, unordered_set[string]& used):
    cdef string tags2
    cdef string tags3
    cdef int i
    cdef string sub
    cdef int last_pos = -1
    cdef string colon = string(":")

    for i in range(s.length()):
        if(s[i] == <char>':' or s[i] == <char>'.'):
            sub = s.substr(last_pos + 1, i - last_pos - 1)
            last_pos = i
            if(sub in ['sg', 'pl', 'm1', 'm2', 'm3', 'f', 'n']):
                tags2 += sub + colon
            elif(sub in ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']):
                tags2 += sub + colon
                tags3 += sub + colon

    if(last_pos != s.length()-1):
        sub = s.substr(last_pos + 1, s.length() - last_pos - 1)
        if(sub in ['sg', 'pl', 'm1', 'm2', 'm3', 'f', 'n']):
            tags2 += sub
            if(tags3.length() != 0):
                tags3 = tags3.substr(0, tags3.length() - 1)
        elif(sub in ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']):
            tags2 += sub
            tags3 += sub
        else:
            if(tags2.length() != 0):
                tags2 = tags2.substr(0, tags2.length() - 1)
            if(tags3.length() != 0):
                tags3 = tags3.substr(0, tags3.length() - 1)
    else:
        if(tags2.length() != 0):
            tags2 = tags2.substr(0, tags2.length() - 1)
        if(tags3.length() != 0):
            tags3 = tags3.substr(0, tags3.length() - 1)

    if(tags2 != "" and used.insert(tags2).second):
        res.push_back(tags2)
    if(tags3 != "" and used.insert(tags3).second):
        res.push_back(tags3)
