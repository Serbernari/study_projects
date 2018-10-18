<<<<<<< HEAD
#numberOfStrings = int(input())
numberOfStrings = 1
#text = input()
#for i in range (0, numberOfStrings - 1):
    #text += input()
text = 'q w e r t y u i o p a s d f g h j k l z x c v b n m'
=======
numberOfStrings = int(input()) #закомменть эту строку чтобы отлаживаться на своем компе
#numberOfStrings = 1
text = input() #закомменть эту строку чтобы отлаживаться на своем компе
for i in range (0, numberOfStrings - 1): #закомменть эту строку чтобы отлаживаться на своем компе
    text += input()#закомменть эту строку чтобы отлаживаться на своем компе
#text = 'раз раз раз это хардбас два ара ара ара три четыре пять с детства с рифмой я дружу'
>>>>>>> 6e3f97e0d99d3ce96024498b06311d151ab8ef62

words = text.split() #разбили текст на отдельные слова по пробелам
counts = [0 for i in range(len(words))] # определили число слов в тексте

freq_dict = dict(zip(words,counts)) #построили словарь "слово - кол.во"

for i in range(len(words)):
    if freq_dict[words[i]] == 0:
        freq_dict[words[i]] = words.count(words[i])

<<<<<<< HEAD
def maxVal_minKey(MyDict):
=======
def maxVal_minKey(MyDict): #как порядошные люди запилили отдельную функцию
>>>>>>> 6e3f97e0d99d3ce96024498b06311d151ab8ef62
    top = []
    for k,v in MyDict.items():
        if v == max(MyDict.values()) and (k not in top):
           top.append(k)
           top.sort()
    return top[0]

<<<<<<< HEAD
print (maxVal_minKey(freq_dict))
=======
print (maxVal_minKey(freq_dict)) #вызываем нашу функцию
>>>>>>> 6e3f97e0d99d3ce96024498b06311d151ab8ef62
