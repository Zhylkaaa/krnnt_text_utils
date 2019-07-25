import time

def uniq(seq):
    seen = set()
    return [ x for x in seq if not (x in seen or seen.add(x))]

def flatten(l):
    return [item for sublist in l for item in sublist]

def create_tags5(tags, features=None, keep_guesser=True):  # concraft
    if not keep_guesser and 'ign' in tags:
        return ['ign']
            # return ['ign','sg:loc:m3','sg:nom:n','pl:nom:m3','pl:acc:m3','loc','sg:gen:m3','pl:gen:m3','sg:nom:m1','sg:nom:m3','gen','nom','acc','sg:nom:f']

    return uniq(flatten(map(lambda tag: create_tag5(tag), tags)))

cas = ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']
nmb = ['sg', 'pl']
gnd = ['m1', 'm2', 'm3', 'f', 'n']

def create_tags5_without_guesser(tags, features=None):
    return create_tags5(tags, features=features, keep_guesser=False)

def create_tag5(otag, features=None):

    tags = flatten(map(lambda x: x.split('.'), otag.split(':')))

    tags_out = []
    tags2 = []
    tags3 = []
    for tag in tags:
        if tag in nmb:
            tags2.append(tag)
        elif tag in cas:
            tags2.append(tag)
            tags3.append(tag)
        elif tag in gnd:
            tags2.append(tag)

    for tagsX in [tags2, tags3]:
        if tagsX:
            tags_out.append(':'.join(tagsX))

    return uniq(tags_out)

inp = []
total_time = 0.0

f = open('features.txt')
lines = f.readlines()
p = open('out1.txt', 'w+')

for i in lines:
    if(i != "EOW\n"):
        inp.append(i[:-1])
    else:
        start = time.time()
        res = create_tags5_without_guesser(inp)
        end = time.time()
        total_time += (end-start)
        inp = []
        for j in res:
            p.write(j)
            p.write('\n')
f.close()
p.close()

print(total_time)