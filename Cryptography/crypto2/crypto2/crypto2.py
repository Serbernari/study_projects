alph = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
matrix2 =  [[0 for x in range(32)] for y in range(32)] 
dict = {}
dict_sorted  = {}

for x in range(32):
    dict.update({alph[x]: x})
for x in range(32):
    dict_sorted.update({alph[x]: 0})
f = open('D:/text.txt', 'r')
text1 = f.read()
text2 = ''
f.close()

for x in range(len(text1)):
    if (alph.find(text1[x]) >= 0):
     text2 += text1[x]

for x in range(len(text2)):
    new = 1 + dict_sorted[text2[x]]
    dict_sorted.update({text2[x]: new })

dict_sorted = sorted(dict_sorted.items(), key=lambda x: x[1], reverse=1)
alph =''
for x in range(32):
    alph+=str(dict_sorted[x][0])
for x in range(32):
    dict.update({alph[x]: x})


for x in range(len(text2)-1):

   matrix2[dict[text2[x]]][dict[text2[x+1]]] += 1


for i in range(32):
    for j in range(32):
        print(matrix2[i][j], " ", end="")
    print('\n')


