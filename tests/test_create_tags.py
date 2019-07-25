import time

cas = ['nom', 'gen', 'dat', 'acc', 'inst', 'loc', 'voc']
per = ['pri', 'sec', 'ter']

def uniq(seq):
    seen = set()
    return [ x for x in seq if not (x in seen or seen.add(x))]

def flatten(l):
    return [item for sublist in l for item in sublist]

def create_tags4(tags, features = None, keep_guesser=True): #concraft
    if not keep_guesser and 'ign' in tags:
        return ['ign']
                    # return ['1ign','2ign','1subst:nom','2subst:sg:f','1adj:nom','1subst:gen','2subst:sg:n','2subst:sg:m1','2adj:sg:m3:pos','2subst:sg:m3','1num:acc','2num:pl:m3:rec','1brev','2adj:sg:n:pos','2num:pl:m3:congr','1num:nom','1adj:gen','1adj:loc']
    return uniq(flatten(map(lambda tag: create_tag4(tag), tags)))
def create_tags4_without_guesser(tags, features = None):
    return create_tags4(tags, features = features, keep_guesser=False)

    
def create_tag4(otag, features = None):
    tags = flatten(map(lambda x: x.split('.'), otag.split(':')))
    pos = tags[0]
    tags = tags[1:]
    tags2 = []

    first=None
    for tag in tags:
        if tag in cas or tag in per:
            first=tag
            break

    if first:
        tags.remove(first)
        tags2.append('1'+pos+':'+first)
    else:
        tags2.append('1'+pos) #TODO sprawdzic

    tags2.append('2'+(':'.join([pos]+tags)))

        # print otag, tags2
    return uniq(tags2)

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
        res = create_tags4_without_guesser(inp)
        end = time.time()
        total_time += (end-start)
        inp = []
        for j in res:
            p.write(j)
            p.write('\n')
f.close()
p.close()

print(total_time)
