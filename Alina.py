numberOfStrings = int(input()) #закомменть эту строку чтобы отлаживаться на своем компе
#numberOfStrings = 1
text = input() #закомменть эту строку чтобы отлаживаться на своем компе
for i in range (0, numberOfStrings - 1): #закомменть эту строку чтобы отлаживаться на своем компе
    text += input()#закомменть эту строку чтобы отлаживаться на своем компе
#text = 'раз раз раз это хардбас два ара ара ара три четыре пять с детства с рифмой я дружу'

words = text.split() #разбили текст на отдельные слова по пробелам
counts = [0 for i in range(len(words))] # определили число слов в тексте

freq_dict = dict(zip(words,counts)) #построили словарь "слово - кол.во"

for i in range(len(words)):
    if freq_dict[words[i]] == 0:
        freq_dict[words[i]] = words.count(words[i])

def maxVal_minKey(MyDict): #как порядошные люди запилили отдельную функцию
    top = []
    for k,v in MyDict.items():
        if v == max(MyDict.values()) and (k not in top):
           top.append(k)
           top.sort()
    return top[0]

print (maxVal_minKey(freq_dict)) #вызываем нашу функцию
