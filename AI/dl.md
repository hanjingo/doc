# Deep Learning

[TOC]



![ml_hierarchy](/usr/local/src/github/hanjingo/doc/AI/res/ml_hierarchy.png)

*Deep learning is a subset of machine learning, which is itself a subset of artificial intelligence.*

In machine learning, deep learning(DL) focuses on utilizing multilayered neural networks to perform tasks such as classification, regression, and representation learning. The field takes inspiration from biological neuroscience and revolves around stacking artificial neurons into layers and "training" them to process data.

## Intro

![deep_learning_intro](res/deep_learning_intro.png)

Deep learning algorithms can be applied to unsupervised learning tasks. This is an important benefit because unlabeled data is more abundant than labeled data.



## Neural Networks

![neural_network_arch](res/neural_network_arch.png)

A deep neural network(DNN) is an artificial neural network with multiple layers between the input and output layers. There are different types of neural networks, but they always consist of the same components: neurons, synapses, weights, biases, and functions. These components, as a whole, function in a way that mimics functions of the human brain, and can be trained like any other ML algorithm.

### Artificial Neural Networks(ANNs)

![ann_intro](res/ann_intro.png)

Artificial neural networks (ANNs), or connectionist systems, are computing systems vaguely inspired by the biological neural networks that constitute animal brains. Such systems "learn" to perform tasks by considering examples, generally without being programmed with any task-specific rules.

### Convolutional Neural Networks(CNNs)

![cnn_intro](res/cnn_intro.png)

Convolutional neural networks(CNNs) are used in computer vision. CNNs have also been applied to acoustic modeling for automatic speech recognition(ASR).

### Recurrent Neural Networks(RNNs)

![rnn_intro](res/rnn_intro.png)

Recurrent neural networks(RNNs) are designed to work on sequential data. Whereas a conventional feedforward neural network maps a single output, RNNs map a sequence of inputs to an output by operating in a recurrent loop in which the output for a given step in the input sequence serves as input to the computation for the following step. In effect, this creates an internal "memory", called the `hidden` state, that allows RNNs to understand context and order.

### Long Short-Term Memory Networks (LSTMs)

![lstm_intro](res/lstm_intro.png)

### Generative Adversarial Networks (GANs)

![gan_intro](res/gan_intro.png)

### Contrastive Language-Image Pre-training (CLIP)

![clip_intro](res/clip_intro.png)

CLIP (Contrastive Language-Image Pre-training) is a neural network that connects vision and language. Released in January 2021, it can classify images into any categories you want without being specifically trained for that task. Just tell it what you’re looking for in plain English, and it can recognize it. This “zero-shot” capability makes CLIP different from almost every computer vision system that came before it.



## Autoencoder

![autoencoder_intro](res/autoencoder_intro.png)

An autoencoder is a type of neural network architecture designed to efficiently compress (encode) input data down to its essential features, then reconstruct (decode) the original input from this compressed representation.

### Transformer models

The transformer model is a type of neural network architecture that excels at processing sequential data, most prominently associated with large language models (LLMs). Transformer models have also achieved elite performance in other fields of artificial intelligence(AI), such as computer vision, speech recognition, and time series forecasting.

### Mamba model

Mamba is a neural network architecture, derived from state space models (SSMs), used for language modeling and other sequence modeling tasks. The Mamba architecture's fast inference speed and computational efficiency, particularly for long sequences, make it the first competitive alternative to the transformer architecture for autoregressive large language models(LLMs).

### Graph neural network

TODO



## Reference

[1] [OpenAI CLIP: The Model That Learnt Zero-Shot Image Recognition Using Text](https://blog.bytebytego.com/p/openai-clip-the-model-that-learnt)
