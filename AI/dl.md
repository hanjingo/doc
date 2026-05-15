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

**Artificial neural networks (ANNs)**, or connectionist systems, are computing systems vaguely inspired by the biological neural networks that constitute animal brains. Such systems "learn" to perform tasks by considering examples, generally without being programmed with any task-specific rules.

![ann_workflow](res/ann_workflow.png)

- Input Layer: This is where the network receives information.
- Hidden Layers: These layers process the data received from the input layer. The more hidden layers there are, the more complex patterns the network can learn and understand. Each hidden layer transforms the data into more abstract information.
- Output Layer: This is where the final decision or prediction is made.

### Convolutional Neural Networks(CNNs)

![cnn_intro](res/cnn_intro.png)

Convolutional neural networks(CNNs) are used in computer vision. CNNs have also been applied to acoustic modeling for automatic speech recognition(ASR).

### Recurrent Neural Networks(RNNs)

![rnn_intro](res/rnn_intro.png)

**Recurrent neural networks(RNNs)** are designed to work on sequential data. Whereas a conventional feedforward neural network maps a single output, RNNs map a sequence of inputs to an output by operating in a recurrent loop in which the output for a given step in the input sequence serves as input to the computation for the following step. In effect, this creates an internal "memory", called the `hidden` state, that allows RNNs to understand context and order.

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



## Mixed Precision

![mixed_precision_training](res/mixed_precision_training.png)

Mixed Precision Training is a deep learning optimization technique that uses both 16-bit (half precision) and 32-bit (single precision) floating point representations during model training. It is designed to reduce memory usage and speed up computation without significantly affecting model accuracy.

Mixed precision combines:

- Float32: for critical operations requiring high accuracy.
- Float16: for less sensitive operations where precision loss is acceptable.

Benefits:

1. Faster Training: Float16 operations execute faster on GPUs with specialized hardware (like NVIDIA Tensor Cores).
2. Lower Memory Usage: Reducing variable sizes from 32 bits to 16 bits nearly halves memory usage, enabling larger models or larger batch sizes.
3. Comparable Accuracy: When used with techniques like loss scaling, models trained with mixed precision perform similarly to full precision models.



## Summary

### Artificial Neurons vs Biological Neurons

![biological_neurons_to_artificial_neurons](res/biological_neurons_to_artificial_neurons.png)

|         Aspect         |                      Biological Neurons                      |                      Artificial Neurons                      |
| :--------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|     **Structure**      |        Dendrites: Receive signals from other neurons.        | Input Nodes: Receive data and pass it on to the next layer.  |
|           -            |           Cell Body (Soma): Processes the signals.           |     Hidden Layer Nodes: Process and transform the data.      |
|           -            |     Axon: Transmits processed signals to other neurons.      |   Output Nodes: Produce the final result after processing.   |
|    **Connections**     |    Synapses: Links between neurons that transmit signals.    | Weights: Connections between neurons that control the influence of one neuron on another. |
| **Learning Mechanism** | Synaptic Plasticity: Changes in synaptic strength based on activity over time. | Backpropagation: Adjusts the weights based on errors in predictions to improve future performance. |
|     **Activation**     | Activation: Neurons fire when signals are strong enough to reach a threshold. | Activation Function: Maps input to output, deciding if the neuron should fire based on the processed data. |



## Reference

[1] [OpenAI CLIP: The Model That Learnt Zero-Shot Image Recognition Using Text](https://blog.bytebytego.com/p/openai-clip-the-model-that-learnt)

[2] [What is Mixed Precision Training?](https://www.geeksforgeeks.org/deep-learning/what-is-mixed-precision-training/)

[3] [Artificial Neural Networks and its Applications](https://www.geeksforgeeks.org/deep-learning/artificial-neural-networks-and-its-applications/)
