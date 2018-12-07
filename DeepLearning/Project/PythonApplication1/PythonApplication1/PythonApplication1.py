
#!/usr/bin/env python
# coding: utf-8

# In[1]:


#get_ipython().run_line_magic('env', 'CUDA_DEVICE_ORDER=PCI_BUS_ID')
#get_ipython().run_line_magic('env', 'CUDA_VISIBLE_DEVICES=1')


# In[2]:


#get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib.pyplot as plt
import os
from PIL import Image
import numpy as np
import glob


# In[3]:


from keras.applications.resnet50 import ResNet50


# In[240]:


from keras.layers import Flatten, Dense, Conv2D, Activation, Dropout, MaxPooling2D, BatchNormalization
from keras.models import Sequential, load_model


# In[34]:


from sklearn.model_selection import train_test_split
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import KFold, cross_val_score
from keras.utils import Sequence
from keras.callbacks import ModelCheckpoint


# In[6]:


import keras.backend as K


# In[7]:


import torch


# In[8]:


import torchvision


# In[10]:


mask = np.array(Image.open('mask_2.png'))
mask = 1*(mask[...,0]==255).astype(np.uint8)


# In[11]:


def mask_face(img):
    return img*mask


# In[ ]:


hydro_fp = glob.glob("data/Hydro/*/*from*.JPG")
norma_fp = glob.glob("data/Norm/*/*from*.JPG")


# In[ ]:


hydro_fp_train = hydro_fp[:-10]
hydro_fp_test = hydro_fp[-10:]


# In[45]:


norma_fp_train = norma_fp[:-20]
norma_fp_test = norma_fp[-20:]


# In[48]:


hydro_data_train = np.stack([np.array(Image.open(fp).resize((376,376))) for fp in hydro_fp_train])
hydro_data_test = np.stack([np.array(Image.open(fp).resize((376,376))) for fp in hydro_fp_test])


# In[49]:


norm_data_train = np.stack([np.array(Image.open(fp).resize((376,376))) for fp in norma_fp_train])
norm_data_test = np.stack([np.array(Image.open(fp).resize((376,376))) for fp in norma_fp_test])


# In[54]:


#all_data = np.concatenate([hydro_data, norm_data])
#all_labels = np.zeros(all_data.shape[0])
#all_labels[:hydro_data.shape[0]]=1


# In[55]:


X_train = np.concatenate([hydro_data_train, norm_data_train])
y_train = np.zeros(X_train.shape[0])
y_train[:hydro_data_train.shape[0]] = 1.


# In[56]:


X_test = np.concatenate([hydro_data_test, norm_data_test])
y_test = np.zeros(X_test.shape[0])
y_test[:hydro_data_test.shape[0]] = 1.


# In[57]:


X_train*=mask[None,...,None]


# In[58]:


X_test*=mask[None,...,None]


# In[18]:


#X_train, X_test, y_train, y_test = train_test_split(all_data, all_labels, stratify=all_labels)


# In[59]:


transforms_pytorch = torchvision.transforms.Compose([
    torchvision.transforms.ToPILImage(),
    torchvision.transforms.ColorJitter(hue=.05, saturation=.05),
    torchvision.transforms.RandomHorizontalFlip(),
    torchvision.transforms.RandomRotation(5)
    #torchvision.transforms.RandomCrop()
])


# In[60]:


class dumb_af_generator():
    def __init__(self, X, y):
        self.X = X
        self.y = y
    def generate(self):
        while True:
            X_ = np.stack([np.array(transforms_pytorch(img)) for img in self.X])
            yield X_, self.y
 


# In[61]:


dg = dumb_af_generator(X_train, y_train)


# In[62]:


resnet = ResNet50(include_top=False, weights='imagenet', input_tensor=None, input_shape=(376,376,3), pooling=None)


# In[63]:


resnet.trainable = False


# In[ ]:


resnet.summary()


# In[ ]:


resnet_preds = resnet.predict(all_data)


# In[ ]:


resnet_preds.shape


# In[64]:


def get_model():
    model = Sequential()
    model.add(resnet)
    model.add(MaxPooling2D(pool_size=(3,3)))
    model.add(Conv2D(32,1))
    model.add(Activation('relu'))
    model.add(MaxPooling2D())
    model.add(Conv2D(16,1))
    model.add(Activation('relu'))
    model.add(Flatten())
    model.add(Dropout(0.5))
    model.add(Dense(128))
    model.add(Dropout(0.5))
    #model.add(Activation('relu'))
    model.add(Dense(1))
    model.add(Activation('sigmoid'))
    model.compile('adam', 'binary_crossentropy', metrics=['accuracy'])
    return model


# In[ ]:


def get_model_simple():
    model = Sequential()
    model.add(resnet)
    #model.add(MaxPooling2D(pool_size=(3,3)))
    model.add(Conv2D(16,1))
    #model.add(Activation('relu'))
    #model.add(MaxPooling2D())
    #model.add(Conv2D(16,1))
    #model.add(Activation('relu'))
    model.add(Flatten())
    model.add(Dropout(0.5))
    model.add(Dense(64))
    model.add(Dropout(0.5))
    #model.add(Activation('relu'))
    model.add(Dense(1))
    model.add(Activation('sigmoid'))
    model.compile('adam', 'binary_crossentropy', metrics=['accuracy'])
    return model


# In[268]:


def get_model_simple_mk2():
    model = Sequential()
    model.add(resnet)
    model.add(BatchNormalization())
    model.add(MaxPooling2D())
    model.add(Conv2D(32,1))
    model.add(Activation('relu'))
    model.add(BatchNormalization())
    model.add(MaxPooling2D())
    model.add(Conv2D(16,1))
    model.add(Activation('relu'))
    model.add(BatchNormalization())
    #model.add(MaxPooling2D())
    #model.add(Conv2D(16,1))
    #model.add(Activation('relu'))
    model.add(MaxPooling2D())
    model.add(Conv2D(8,1))
    model.add(Activation('relu'))
    model.add(BatchNormalization())
    model.add(Conv2D(1,1))
    model.add(Flatten())
    model.add(Activation('sigmoid'))
    model.compile('adam', 'binary_crossentropy', metrics=['accuracy'])
    return model


# In[269]:


model = get_model_simple_mk2()


# In[270]:


model.summary()


# In[249]:


K.set_value(model.optimizer.lr, 1e-5)


# In[ ]:


checkpoint = ModelCheckpoint('currentbest_checkpoint.h5', monitor='val_acc', save_best_only=True)


# In[ ]:


from keras.callbacks import *

class CyclicLR(Callback):
    """This callback implements a cyclical learning rate policy (CLR).
    The method cycles the learning rate between two boundaries with
    some constant frequency, as detailed in this paper (https://arxiv.org/abs/1506.01186).
    The amplitude of the cycle can be scaled on a per-iteration or 
    per-cycle basis.
    This class has three built-in policies, as put forth in the paper.
    "triangular":
        A basic triangular cycle w/ no amplitude scaling.
    "triangular2":
        A basic triangular cycle that scales initial amplitude by half each cycle.
    "exp_range":
        A cycle that scales initial amplitude by gamma**(cycle iterations) at each 
        cycle iteration.
    For more detail, please see paper.
    
    # Example
        ```python
            clr = CyclicLR(base_lr=0.001, max_lr=0.006,
                                step_size=2000., mode='triangular')
            model.fit(X_train, Y_train, callbacks=[clr])
        ```
    
    Class also supports custom scaling functions:
        ```python
            clr_fn = lambda x: 0.5*(1+np.sin(x*np.pi/2.))
            clr = CyclicLR(base_lr=0.001, max_lr=0.006,
                                step_size=2000., scale_fn=clr_fn,
                                scale_mode='cycle')
            model.fit(X_train, Y_train, callbacks=[clr])
        ```    
    # Arguments
        base_lr: initial learning rate which is the
            lower boundary in the cycle.
        max_lr: upper boundary in the cycle. Functionally,
            it defines the cycle amplitude (max_lr - base_lr).
            The lr at any cycle is the sum of base_lr
            and some scaling of the amplitude; therefore 
            max_lr may not actually be reached depending on
            scaling function.
        step_size: number of training iterations per
            half cycle. Authors suggest setting step_size
            2-8 x training iterations in epoch.
        mode: one of {triangular, triangular2, exp_range}.
            Default 'triangular'.
            Values correspond to policies detailed above.
            If scale_fn is not None, this argument is ignored.
        gamma: constant in 'exp_range' scaling function:
            gamma**(cycle iterations)
        scale_fn: Custom scaling policy defined by a single
            argument lambda function, where 
            0 <= scale_fn(x) <= 1 for all x >= 0.
            mode paramater is ignored 
        scale_mode: {'cycle', 'iterations'}.
            Defines whether scale_fn is evaluated on 
            cycle number or cycle iterations (training
            iterations since start of cycle). Default is 'cycle'.
    """

    def __init__(self, base_lr=0.001, max_lr=0.006, step_size=2000., mode='triangular',
                 gamma=1., scale_fn=None, scale_mode='cycle'):
        super(CyclicLR, self).__init__()

        self.base_lr = base_lr
        self.max_lr = max_lr
        self.step_size = step_size
        self.mode = mode
        self.gamma = gamma
        if scale_fn == None:
            if self.mode == 'triangular':
                self.scale_fn = lambda x: 1.
                self.scale_mode = 'cycle'
            elif self.mode == 'triangular2':
                self.scale_fn = lambda x: 1/(2.**(x-1))
                self.scale_mode = 'cycle'
            elif self.mode == 'exp_range':
                self.scale_fn = lambda x: gamma**(x)
                self.scale_mode = 'iterations'
        else:
            self.scale_fn = scale_fn
            self.scale_mode = scale_mode
        self.clr_iterations = 0.
        self.trn_iterations = 0.
        self.history = {}

        self._reset()

    def _reset(self, new_base_lr=None, new_max_lr=None,
               new_step_size=None):
        """Resets cycle iterations.
        Optional boundary/step size adjustment.
        """
        if new_base_lr != None:
            self.base_lr = new_base_lr
        if new_max_lr != None:
            self.max_lr = new_max_lr
        if new_step_size != None:
            self.step_size = new_step_size
        self.clr_iterations = 0.
        
    def clr(self):
        cycle = np.floor(1+self.clr_iterations/(2*self.step_size))
        x = np.abs(self.clr_iterations/self.step_size - 2*cycle + 1)
        if self.scale_mode == 'cycle':
            return self.base_lr + (self.max_lr-self.base_lr)*np.maximum(0, (1-x))*self.scale_fn(cycle)
        else:
            return self.base_lr + (self.max_lr-self.base_lr)*np.maximum(0, (1-x))*self.scale_fn(self.clr_iterations)
        
    def on_train_begin(self, logs={}):
        logs = logs or {}

        if self.clr_iterations == 0:
            K.set_value(self.model.optimizer.lr, self.base_lr)
        else:
            K.set_value(self.model.optimizer.lr, self.clr())        
            
    def on_batch_end(self, epoch, logs=None):
        
        logs = logs or {}
        self.trn_iterations += 1
        self.clr_iterations += 1

        self.history.setdefault('lr', []).append(K.get_value(self.model.optimizer.lr))
        self.history.setdefault('iterations', []).append(self.trn_iterations)

        for k, v in logs.items():
            self.history.setdefault(k, []).append(v)
        
        K.set_value(self.model.optimizer.lr, self.clr())


# In[260]:


clr = CyclicLR(base_lr=1e-5,max_lr=5e-5, step_size=10)


# In[271]:


model.fit_generator(dg.generate(), steps_per_epoch=1, validation_data=[X_test, y_test], epochs=200, 
                    callbacks=[clr]
                   )


# In[ ]:


model.fit(X_train, y_train, validation_data=[X_test, y_test], epochs=5, verbose=1)


# In[ ]:


clf = KerasClassifier(build_fn=get_model, epochs=5, verbose=0)


# In[ ]:


kf = KFold(n_splits=4)
kf.get_n_splits(resnet_preds, all_labels)


# In[ ]:


cvs = cross_val_score(clf, resnet_preds, all_labels, cv=kf)


# In[ ]:


cvs


# In[275]:


model = load_model('honest_acc80.h5')


# In[191]:


y_pred = model.predict(X_test)


# In[ ]:


#model.save('init_acc_84.h5')


# In[30]:


from sklearn.metrics import confusion_matrix


# In[95]:


y_test.sum()


# In[274]:


confusion_matrix(y_test>0.5, y_pred>0.5)


# In[130]:


model.save('honest_acc80.h5')


# In[ ]:


np.lo


# In[ ]:


np.logical_and(y_test>0.5, y_pred<0.5).shape


# In[ ]:


_ = plt.hist(y_pred[y_test>0.5], bins=100)
_ = plt.hist(y_pred[y_test<0.5], bins=100)

