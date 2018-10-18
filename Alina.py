#numberOfStrings = int(input())
numberOfStrings = 1
#text = input()
#for i in range (0, numberOfStrings - 1):
    #text += input()
text = 'q w e r t y u i o p a s d f g h j k l z x c v b n m'

words = text.split() #разбили текст на отдельные слова по пробелам
counts = [0 for i in range(len(words))] # определили число слов в тексте

freq_dict = dict(zip(words,counts)) #построили словарь "слово - кол.во"

for i in range(len(words)):
    if freq_dict[words[i]] == 0:
        freq_dict[words[i]] = words.count(words[i])

def maxVal_minKey(MyDict):
    top = []
    for k,v in MyDict.items():
        if v == max(MyDict.values()) and (k not in top):
           top.append(k)
           top.sort()
    return top[0]

print (maxVal_minKey(freq_dict))