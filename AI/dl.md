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



## Transformer

![transformer](/usr/local/src/github/hanjingo/doc/AI/res/transformer.png)

A transformer is a neural network architecture used for various machine learning tasks, especially in natural language processing and computer vision. It focuses on understanding relationships within data to process information more effectively.

### Why Transformers?

![why_transformers](res/why_transformers.png)

Transformer architecture uses attention to process an entire sentence at once instead of reading words sequentially. This helps overcome limitations of models like RNNs and LSTMs that process data step by step.

### Core Concepts of Transformers

![core_concepts_of_transformers](res/core_concepts_of_transformers.png)

1. Self-Attention mechanism

   The self attention mechanism allows transformers to determine which words in a sentence are most relevant to each other. This is done using a scaled dot-product attention approach.

     Each word in a sequence is mapped to three vectors:

     - $Query (Q)$
     - $Key(K)$
     - $Value(V)$

     Attention scores are computed as: $Attention(Q, K, V) = fotmax(\frac{QK^T}{\sqrt{d_k}})V$.

2. Multi-Head Attention

   Instead of one attention mechanism, transformers use multiple attention heads running in parallel. Each head captures different relationships or patterns in the data, enriching the model’s understanding.

3. Positional Encoding

   Unlike RNNs, transformers lack an inherent understanding of word order since they process data in parallel. To solve this problem Positional Encodings are added to token embeddings providing information about the position of each token within a sequence.

4. Position-wise Feed-Forward networks

   The Feed-Forward Networks consist of two linear transformations with a ReLU activation. It is applied independently to each position in the sequence.This transformation helps refine the encoded representation at each position.

   Mathematically: $FFN(x) = ReLU(xW_1 + b_1)W_2 + b_2$

5. Add & Norm (Residual Connections and Layer Normalization)

   Each sub-layer in the transformer (such as self-attention and feed-forward networks) is followed by an Add & Norm step.

     - Residual Connection (Add): The input of a layer is added to its output. This helps in preserving information and prevents vanishing gradients in deep networks.
     - Layer Normalization (Norm): The combined output is normalized to stabilize training and improve convergence.

6. Embeddings

   Transformers cannot work with raw words as they need numbers. So, each input token (word or subword) is converted into a vector, called an embedding.

7. Encoder-Decoder Architecture

   The encoder-decoder structure is key to transformer models. The encoder processes the input sequence into a vector, while the decoder converts this vector back into a sequence. Each encoder and decoder layer includes self-attention and feed-forward layers.

   Transformers apply attention in three different places:

   - Encoder Self-Attention
     - Q, K, V all come from the encoder’s previous layer.
     - Every word can attend to every other word in the input.
     - This helps the encoder understand full context (long-range meaning).
   - Decoder Self-Attention (Masked)
     - Q, K, V all come from the decoder’s previous layer.
     - Future tokens are masked (blocked), so each position only sees previous tokens.
     - This keeps decoding auto-regressive i.e the model predicts one word at a time.
   - Encoder–Decoder Attention
     - Queries come from the decoder.
     - Keys and Values come from the encoder output.
     - This lets the decoder look at important parts of the input sentence while generating output.

8. Softmax Layer for Output Prediction

   After the decoder processes the sequence, it must predict the next token.

     - The decoder output is passed through a linear layer (whose weights are shared with embeddings).
     - Then the softmax function converts these scores into probabilities.
     - The token with the highest probability becomes the predicted next word.



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



## Challenges

### Vanishing Problems

Vanishing gradients occur when gradients become extremely small during backpropagation, causing early layers to learn very slowly or stop learning. During backpropagation the gradient of the loss L with respect to a weight w_i in layer i is calculated using the chain rule:
$$
\frac{\partial L}{\partial w_i} = \frac{\partial L}{\partial a_n} \cdot \frac{\partial a_n}{\partial a_{n-1}} \cdot \frac{\partial a_{n-1}}{\partial a_{n-2}} \cdots \frac{\partial a_1}{\partial w_i}
$$
where:

- $L$: Loss function.
- $w_i$: Weight parameter in the layer.
- $a_n$: Activation output of layer.
- $\frac{\partial L}{\partial w_i}$: Gradient of loss with respect to weight.

### Exploding Gradients Problems

Exploding gradients occur when gradients grow too large during backpropagation, leading to unstable weight updates and divergence in loss. When derivatives or weights are greater than 1, their repeated multiplication across layers leads to exponential growth.
$$
\prod_{i=1}^{n} \frac{\partial a_i}{\partial a_{i-1}} \longrightarrow \infty
$$
The gradient update rule in gradient descent is:
$$
w_{t+1} = w_t - \eta \cdot \frac{\partial L}{\partial w_t}
$$
where:

- $w_i$: Current weight value at time step $t$.
- $\eta$: Learning rate.
- $\frac{\partial L}{\partial w_t}$: Gradient of loss with respect to weight.
- $w_{t+1}$: Updated weight after applying gradient descent.

If $\frac{\partial L}{\partial w_t}$ is too large weight updates become massive causing the model loss to oscillate or diverge.



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

[4] [Transformers in Machine Learning](https://www.geeksforgeeks.org/machine-learning/getting-started-with-transformers/)

[5] [Vanishing and Exploding Gradients Problems in Deep Learning](https://www.geeksforgeeks.org/deep-learning/vanishing-and-exploding-gradients-problems-in-deep-learning/)

[6] [Deep Learning Tutorial](https://www.geeksforgeeks.org/deep-learning/deep-learning-tutorial/)
