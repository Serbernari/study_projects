from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics import confusion_matrix, accuracy_score


from keras.preprocessing.sequence import pad_sequences
from keras.models import Sequential
from keras.layers import *
from keras.utils.np_utils import to_categorical
from keras.initializers import Constant
from keras.optimizers import RMSprop
import re

import matplotlib.pyplot as plt

from keras.preprocessing.text import Tokenizer
from keras.models import Sequential
from keras.layers import Embedding
from keras import layers
from keras.preprocessing import sequence
from sklearn.model_selection import cross_validate   
from sklearn.neural_network import MLPClassifier   
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer 
from sklearn.model_selection import train_test_split
from sklearn.metrics import f1_score
import numpy as np
import pandas as pd
import os

from scipy.sparse import csr_matrix
from keras.preprocessing.text import one_hot

# Test train split
labels = []
texts = []
         
data = pd.read_csv("intents.csv",sep = ',', header = None, names = ['type', 'text'])
classes = np.array(data['type'])
texts = np.array(data['text'])
#classes = classes - 1
tokenizer = Tokenizer(num_words=10000)
tokenizer.fit_on_texts(texts)
phrases_emb = tokenizer.texts_to_sequences(texts)
word_index = tokenizer.word_index
#print('Found %s unique tokens.' % len(word_index))
max_features = len(word_index)+1
lenths =[]
for sz in phrases_emb:
    lenths.append(len(sz))

max_len = max(lenths)
phrases_emb = sequence.pad_sequences(phrases_emb, maxlen=max_len)
x_train, x_test, y_train, y_test = train_test_split(phrases_emb, classes, test_size = 0.2, random_state = 42, stratify=classes)

from gensim.models import FastText, KeyedVectors
modelFT = KeyedVectors.load('181//model.model')

word_index = tokenizer.word_index
print('Found %s unique tokens.' % len(word_index))

num_words = min(max_features, len(word_index)) + 1
print(num_words)

embedding_dim = 300
embedding_matrix = np.zeros((num_words, embedding_dim))
for word, i in word_index.items():
    if len(word) == 1:
        word = '  '+word+'  '
    embedding_vector = modelFT.get_vector(word)
    embedding_matrix[i] = embedding_vector
print(np.linalg.norm(embedding_matrix[0]))

model = Sequential()
print(embedding_matrix[0])
print(embedding_matrix[1])
print(embedding_matrix[2])
print(embedding_matrix[3])
print(y_train[:10])
print(y_test[:10])
model.add(Embedding(num_words,
                    embedding_dim,
                    input_length=max_len, trainable = False, weights = [embedding_matrix]))
#model.add(SpatialDropout1D(0.2))
model.add(Bidirectional(LSTM(64, return_sequences=False)))
#model.add(Dropout(0.25))
model.add(Dense(units=10, activation='softmax'))
model.summary()

#model.layers[0].set_weights([embedding_matrix])
#model.layers[0].trainable = False
model.compile(loss = 'sparse_categorical_crossentropy', optimizer=RMSprop(clipnorm=1.0),metrics = ['accuracy'])

batch_size = 128
indices = np.arange(0, len(y_train), 1, dtype=np.int32)
np.random.shuffle(indices)
history = model.fit(x_train[indices], y_train[indices]-1, epochs=5, batch_size=batch_size, verbose=1, validation_split=0.1)
#print (x_train, y_train)
plt.plot(history.history['acc'])
plt.plot(history.history['val_acc'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'validation'], loc='upper left')
plt.show()

plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'validation'], loc='upper left')
plt.show()
