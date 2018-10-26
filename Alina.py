import sys

text = "раз два три раз раз два три" #sys.stdin.read()
words = [a for b in text.split('\n') for a in b.split()]

freq_dict = dict()

for i in range(len(words)):
    freq_dict[words[i]] = words.count(words[i])

top = []

for key, val in freq_dict.items():
    if val == max(freq_dict.values()) and (key not in top):
            top.append(key)
top.sort()

print(max(sort(freq_dict.keys()))
