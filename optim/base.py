from typing import BinaryIO, Iterable, List, TypeVar

cas = ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc', 'nom\n', 'gen\n', 'dat\n', 'acc\n', 'inst\n', 'loc\n', 'voc\n']
per = ['pri', 'sec', 'ter', 'pri\n', 'sec\n', 'ter\n']

def uniq(seq: Iterable) -> List:
    seen = set()
    return [x for x in seq if not (x in seen or seen.add(x))]


def flatten(l: Iterable) -> List:
    return [item for sublist in l for item in sublist]

def create_tags4(tags, features=None, keep_guesser=True):  # concraft
    if not keep_guesser and 'ign\n' in tags:
        return ['ign\n']
        # return ['1ign','2ign','1subst:nom','2subst:sg:f','1adj:nom','1subst:gen','2subst:sg:n','2subst:sg:m1','2adj:sg:m3:pos','2subst:sg:m3','1num:acc','2num:pl:m3:rec','1brev','2adj:sg:n:pos','2num:pl:m3:congr','1num:nom','1adj:gen','1adj:loc']
    return uniq(flatten(map(lambda tag: create_tag4(tag), tags)))

def create_tags4_without_guesser(tags, features=None):
    return create_tags4(tags, features=features, keep_guesser=False)

def create_tag4(otag, features=None):
    tags = flatten(map(lambda x: x.split('.'), otag.split(':')))
    pos = tags[0]
    tags = tags[1:]
    tags2 = []

    first = None
    for tag in tags:
        if tag in cas or tag in per:
            first = tag
            break

    if first:
        tags.remove(first)
        tags2.append('1' + pos + ':' + first)
    else:
        tags2.append('1' + pos)  # TODO sprawdzic

    tags2.append('2' + (':'.join([pos] + tags)))

    # print otag, tags2
    return uniq(tags2)

f = open('/home/krnnt/sample_features_tags.txt')
lines = f.readlines()
print(len(lines))
print(type(lines[0]))
tags = []
out = []
for i in lines:
    if(str(i) == "EOW\n"):
        #print('Ok')
        for j in create_tags4_without_guesser(tags):
            out.append(j)
        tags = []
    else:
        tags.append(i)

f.close()
f = open('/home/krnnt/create_tags4_without_guesser.txt')
lines = f.readlines()
print(len(lines))
print(len(out))
out2 = []
for i in lines:
    if(i=='\n' or i==''):
        continue
    out2.append(i)
f.close()
f = open('out.txt','w+')

for i in out:
    f.write(i)
    f.write('\n')
f.close()
