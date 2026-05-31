# Natural Language Processing (NLP)

[TOC]



![nlp_intro](res/nlp_intro.png)

Natural Language Processing (NLP) helps machines to understand and process human languages, either in text or audio form. It is used across a variety of applications, from speech recognition to language translation and text summarization.

## Tasks

![nlp_tasks](res/nlp_tasks.png)

### Text Classification

Text classification is a fundamental task in natural language processing (NLP) that involves categorizing text documents into predefined classes or categories based on their content.

### Sentiment Analysis

Sentiment Analysis is the process of analyzing textual data to determine the emotional tone expressed in it. It classifies text as positive, negative or neutral and can also detect more nuanced emotions like happy, sad, angry or frustrated.

### Text Summarization

Text summarization has become increasingly important as massive amounts of textual data is generated daily. The ability to extract key information quickly is important.

### Named Entity Recognition (NER)

TODO

### Text Generation

Text generation in natural language processing (NLP) has improved significantly with Transformer-based models like GPT and BERT. These models use self-attention to understand how words relate to each other in a sentence which is very slow and costly, especially when working with long sequences of text.

### Machine Translation

Machine translation is the process of converting text from one language to another using AI models. Modern systems, such as Google Translate, rely on advanced architectures like Transformers to understand and generate accurate translations.

---



## Workflow

![nlp_workflow](res/nlp_workflow.png)

### Lexical and Morphological Analysis

**Lexical Analysis** focuses on identifying and processing words (or lexemes) in a text. It breaks down the input text into individual tokens that are meaningful units of language, such as words or phrases.

**Morphological Analysis** deals with *morphemes*, which are the smallest units of meaning in a word. It is important for understanding the structure of words and their parts by identifying free morphemes and bound morphemes.

#### Tokenization

![nlp_tokenization1](res/nlp_tokenization1.png)

![nlp_tokenization2](res/nlp_tokenization2.png)

![nlp_tokenization3](res/nlp_tokenization3.png)

Tokenization is the process of breaking text into smaller units called tokens, which helps machines process and analyze language effectively.

Types of Tokenization in NLP:

![nlp_tokenization_types](res/nlp_tokenization_types.png)

- Word Tokenization

  Word tokenization is the most commonly used method, where text is divided into individual words. It works well for languages with clear word boundaries, like English

- Character Tokenization

  In Character Tokenization, the textual data is split and converted to a sequence of individual characters. This is beneficial for tasks that require a detailed analysis, such as spelling correction or for tasks with unclear boundaries. It can also be useful for modelling character-level language.

- Sub-word Tokenization

  This strikes a balance between word and character tokenization by breaking down text into units that are larger than a single character but smaller than a full word. This is useful when dealing with morphologically rich languages or rare words.

- Sentence Tokenization

  Sentence tokenization is also a common technique used to make a division of paragraphs or a large set of sentences into separate sentences as tokens. This is useful for tasks requiring individual sentence analysis or processing.

- N-gram Tokenization

  N-gram tokenization splits words into fixed-sized chunks (size = n) of data.

#### POS(Part-of-Speech) Tagging

Parts of Speech (PoS) tagging is a fundamental task in Natural Language Processing (NLP) where each word in a sentence is assigned a grammatical category such as noun, verb, adjective or adverb. This process helps machines to understand the structure and meaning of sentences by identifying the roles of words and their relationships.

![nlp_pos_tagging_types](res/nlp_pos_tagging_types.png)

- **Rule-based POS tagging** assigns POS tags based on predefined grammatical rules. These rules are crafted based on morphological features (like word endings) and syntactic context, making the approach highly interpretable and transparent.
- **Statistical POS Tagging** uses probabilistic models to assign grammatical categories (e.g noun, verb, adjective) to words in a text. Unlike rule-based methods, which rely on handcrafted rules, it learns patterns from large annotated corpora using machine learning techniques.
- **Transformation-Based Tagging (TBT)** refines POS tags through a series of context-based transformations. Unlike statistical taggers that rely on probabilities or rule-based taggers, it starts with initial tags and improves them iteratively by applying transformation rules.

#### Stemming

Stemming is an important text-processing technique that reduces words to their base or root form by removing prefixes and suffixes. This process standardizes words which helps to improve the efficiency and effectiveness of various natural language processing (NLP) tasks.

![nlp_stemming_algo](res/nlp_stemming_algo.png)

#### Lemmatization

![nlp_lemmatization](res/nlp_lemmatization.png)

Lemmatization is an important text pre-processing technique in Natural Language Processing (NLP) that reduces words to their base form, known as a "lemma."

### Syntactic Analysis

![parsing](res/parsing.png)

**Parsing**, also known as **syntactic analysis**, is the process of analyzing a sequence of [tokens](https://www.geeksforgeeks.org/compiler-design/token-patterns-and-lexems/) to determine the grammatical structure of a program. It takes the stream of tokens, which are generated by a lexical analyzer or tokenizer, and organizes them into a parse tree or syntax tree.

Types of Parsing:

![parsing_types](res/parsing_types.png)

#### TOP DOWN PARSERS (TDP)

Method of building a parse tree from the start symbol (root) down to the leaves (end symbols). The parser begins with the highest-level rule and works its way down, trying to match the input string step by step.

#### BOTTOM UP PARSERS (BUP)

Method of building a parse tree starting from the leaf nodes (the input symbols) and working towards the root node (the start symbol). The goal is to reduce the input string step by step until we reach the start symbol, which represents the entire language.

### Semantic Analysis

**Semantic Analysis** focuses on understanding the meaning behind words and sentences. It ensures that the text is not only grammatically correct but also logically coherent and contextually relevant. It aims to understand dictionary definitions of words and their usage in context and also find whether the arrangement of words in a sentence makes logical sense.

#### Named Entity Recognition (NER)

TODO

#### Word Sense Disambiguation (WSD)

TODO

### Disclosure integration

**Disclosure integration** is the process of understanding how individual sentences or segments of text connect and relate to each other within a broader context. This phase ensures that the meaning of a text is consistent and coherent across multiple sentences or paragraphs. It is important for understanding long or complex texts where the meaning focuses on previous statements.

### Pragmatic Analysis

Pragmatic analysis helps in understanding the deeper meaning behind words and sentences by looking beyond their literal meanings. While semantic analysis looks at the direct meaning, it considers the speaker's or writer's intentions, tone, and context of the communication.

---



## Text Representation Techniques

### One Hot Encoding

One‑Hot Encoding is a data preprocessing technique used to convert categorical variables into a numerical format that machine learning models can understand. It represents each category as a separate binary column, where a value of **1** indicates the presence of that category, and **0** indicates its absence.

**Workflow:**

Imagine we have a dataset with fruits, their categorical values, and corresponding prices. Using one-hot encoding, we can transform these categorical values into numerical form. For example:

- Wherever the fruit is "Apple," the Apple column will have a value of 1, while the other fruit columns (like Mango or Orange) will contain 0.

- This pattern ensures that each categorical value gets its own column represented with binary values (1 or 0), making it usable for machine learning models.

  | **Fruit** | **Categorical value of fruit** | **Price** |
  | :-------: | :----------------------------: | :-------: |
  |   apple   |               1                |     5     |
  |   mango   |               2                |    10     |
  |   apple   |               1                |    15     |
  |  orange   |               3                |    20     |

  The output after applying one-hot encoding on the data is given as follows,

  | **Fruit_apple** | **Fruit_mango** | **Fruit_orange** | **price** |
  | :-------------: | :-------------: | :--------------: | :-------: |
  |        1        |        0        |        0         |     5     |
  |        0        |        1        |        0         |    10     |
  |        1        |        0        |        0         |    15     |
  |        0        |        0        |        1         |    20     |

### Bag of words (BoW) model

In Natural Language Processing (NLP), text data must be converted into numerical form so that machine learning algorithms can process it. The Bag of Words (BoW) model is a simple and commonly used method for this purpose.

- Converts text (sentence, paragraph, or document) into a collection of words
- Counts how often each word appears in the text
- Ignores word order and grammar, focusing only on frequency

### TF-IDF (Term Frequency-Inverse Document Frequency)

TF-IDF (Term Frequency–Inverse Document Frequency) is a statistical method used in natural language processing and information retrieval to evaluate how important a word is to a document in relation to a larger collection of documents. TF-IDF combines two components:

1. **Term Frequency (TF):** Measures how often a word appears in a document. A higher frequency suggests greater importance. If a term appears frequently in a document, it is likely relevant to the document’s content
   $$
   TF(t, d) = \frac{\text{Number of times term t appears in document d}}{\text{Total number of terms in document d}}
   $$

2. **Inverse Document Frequency (IDF):** Reduces the weight of common words across multiple documents while increasing the weight of rare words. If a term appears in fewer documents, it is more likely to be meaningful and specific
   $$
   IDF(t, D) = \log \frac{\text{Total number of documents in corpus D}}{\text{Number of documents containing term t}}
   $$

### N-gram

N-gram is a language modelling technique that is defined as the contiguous sequence of n items from a given sample of text or speech. The N-grams are collected from a text or speech corpus. Items can be:

- Words like “This”, “article”, “is”, “on”, “NLP” → unigrams
- Word pairs likw “This article”, “article is”, “is on”, “on NLP” → bigrams
- Triplets (trigrams) or larger combinations

#### N-gram Language Model

N-gram models predict the probability of a word given the previous $n − 1$ words. For example, a trigram model uses the preceding two words to predict the next word:

**Goal:** Calculate $p(w∣h)$, the probability that the next word is $w$, given context/history $h$.

Example: For the phrase: “This article is on…”, if we want to predict the likelihood of “NLP” as the next word:

> p("NLP" | "This", "article", "is", "on")

**Chain Rule of Probability**

The probability of a sequence of words is computed as:
$$
P(w_1, w_2, ..., w_n) = \prod_{i = 1}^{n} P(w_i | w_1, w_2, ..., w_{i - 1})
$$
**Markov Assumption**

To reduce complexity, N-gram models assume the probability of a word depends only on the previous n−1 words
$$
P(w_i | w_1, ..., w_{i - 1}) \approx P(w_i | w_{i - (n - 1)}, ..., w_{i - 1})
$$

#### Evaluating Language Models

1. **Entropy**: Measures the uncertainty or information content in a distribution.
   $$
   H(p) = \sum_{x}p(x) \cdot (- \log{(p(x))})
   $$
   It always give non negative.

2. **Cross-Entropy:** Measures how well a probability distribution predicts a sample from test data.
   $$
   H(p, q) = - \sum_{x}p(x) \log{(q(x))}
   $$
   Usually ≥ entropy; reflects model “surprise” at the test data.

3. **Perplexity:** Exponential of cross-entropy; lower values indicate a better model.
   $$
   Perplexity(W) = \sqrt[N]{\prod_{i = 1}^{N} \frac{1}{P(w_i | w_{i - 1})}}
   $$

### Latent Semantic Analysis (LSA)

![latent_semantic_analysis](res/latent_semantic_analysis.png)

Latent Semantic Analysis (LSA) is a method used to find hidden meanings in text. It looks at how words appear in different documents and discovers patterns in their usage. Instead of just counting how often words show up LSA tries to understand the context and relationship between words. It works by turning text into a big table of word counts and then using math to shrink that table down keeping only the most important parts. This helps computers group similar words and documents together based on meaning not just exact words.

### Latent Dirichlet Allocation (LDA)

Latent Dirichlet Allocation (LDA), the most widely applied topic modeling method, works as an unsupervised probabilistic model. It assumes that similar documents will share similar word usage and thus, will likely belong to the same topics. Each document is viewed as a mixture of topics and each topic is characterized by a distribution over words.

---



## Embedding

### Embedding Techniques

![embedding_in_nlp](res/embedding_in_nlp.png)

#### Word2Vec

Word2Vec is a word embedding technique in NLP that represents words as vectors in a continuous space. Developed by Google, it captures semantic relationships by assigning similar vectors to words with similar meanings.

Two main architectures:

- CBOW (Continuous Bag of Words)

  ![cbow](res/cbow.png)

  The CBOW model predicts the current word given context words within a specific window. The input layer contains the context words and the output layer contains the current word. The hidden layer contains the dimensions we want to represent the current word present at the output layer. 

- Skip Gram

  ![skip_gram](res/skip_gram.png)

  The Skip gram predicts the surrounding context words within specific window given current word. The input layer contains the current word and the output layer contains the context words. The hidden layer contains the number of dimensions in which we want to represent current word present at the input layer.

#### GloVe

GloVe (Global Vectors for Word Representation) is an unsupervised learning algorithm that generates dense word embeddings by analyzing co-occurrence patterns in a large text corpus, capturing semantic relationships between words.

Workflow:

1. Preprocess the Text

   First, we split the text into individual words (tokenization) so that we can work with them.

2. Creating the Vocabulary

   After tokenization, we create a list of all unique words in the text and then count how often each word appears.

3. Building a Co-occurrence Matrix

   Now, we build a co-occurrence matrix where we count how often each word appears near other words in a given context (usually within a window of fixed size around the word).

4. Performing Dot Product

   The aim is to learn word vectors such that the dot product of two word vectors reflects how often the words co-occur in the context. This ensures that words that appear in similar contexts will have similar vector representations.

5. Training the Word Vectors

   The model learns word embeddings by adjusting vectors based on how often words appear together. It aims to capture meaningful relationships between words using co-occurrence information.

   - Optimizes word vectors by minimizing the difference between predicted and actual co-occurrence relationships
   - Uses measures like Pointwise Mutual Information (PMI) to represent word associations
   - Adjusts vectors so that words with similar contexts have similar representations

6. Embedding Matrix

   After training, the model outputs an embedding matrix where each word is represented by a dense vector. These vectors are able to capture the semantic and syntactic relationships between words.

#### FastText

FastText embeddings are a type of word embedding developed by Facebook's AI Research (FAIR) lab. They are based on the idea of subword embeddings, which means that instead of representing words as single entities, FastText breaks them down into smaller components called character n-grams. By doing so, FastText can capture the semantic meaning of morphologically related words, even for out-of-vocabulary words or rare words, making it particularly useful for handling languages with rich morphology or for tasks where out-of-vocabulary words are common.

#### ELMo

ELMo (Embeddings from Language Models) generates word vectors by considering the entire sentence. Unlike traditional methods, ELMo derives word meanings from the internal states of a deep bi-directional LSTM network trained as a language model.

Workflow:

1. Pre-training Phase

   ![elmo_pre_training](res/elmo_pre_training.png)

   A bidirectional language model (biLM) is trained on a large text corpus. The model uses two separate LSTMs:

   - The forward LSTM reads the sentence from left to right and predicts the next word.
   - The backward LSTM reads from right to left and predicts the previous word.

2. Task-specific Integration

   Once trained, the biLM is used to generate embeddings for specific NLP tasks.

   - ELMo embeddings are added to the input of a downstream model, such as a classifier.
   - biLM can be either frozen to preserve general knowledge or fine-tuned on the specific task to improve performance.
   - The downstream model learns to use these embeddings for improved predictions.

#### BERT

![bert](res/bert.png)

BERT (Bidirectional Encoder Representations from Transformers) is a machine learning model designed for natural language processing tasks, focusing on understanding the context of text.

Workflow:

![bert_workflow](res/bert_workflow.png)

Architecture:

![bert_arch](res/bert_arch.png)

BERT uses a multilayer bidirectional Transformer encoder to understand text by capturing context from both directions. Unlike the original Transformer, which has both encoder and decoder, BERT uses only the encoder for language understanding tasks.

#### Doc2Vec

Doc2Vec is also called a Paragraph Vector a popular technique in Natural Language Processing that enables the representation of documents as vectors. 

Doc2Vec is a neural network-based approach that learns the distributed representation of documents. It is an unsupervised learning technique that maps each document to a fixed-length vector in a high-dimensional space. The vectors are learned in such a way that similar documents are mapped to nearby points in the vector space. This enables us to compare documents based on their vector representation and perform tasks such as document classification, clustering, and similarity analysis.

There are two main variants of the Doc2Vec approach: 

- Distributed Memory (DM)

  ![dm_arch](res/dm_arch.png)

- Distributed Bag of Words (DBOW)

  ![dbow_arch](res/dbow_arch.png)

#### RoBERTa

The rise of transformer models brought major progress in natural language processing, especially with BERT. RoBERTa (Robustly Optimized BERT Pretraining Approach) kept the same architecture but refined the training process to achieve better results. By making some minor changes in BERT, RoBERTa produced stronger language representations without changing the model’s core design.

#### DistilBERT

*DistilBERT* is a distilled version of BERT meaning it is trained using *knowledge distillation* a technique where a smaller model (student) learns from a larger model (teacher). It retains 97% of BERT’s performance while being 40% smaller and 60% faster making it highly efficient for NLP tasks such as text classification, sentiment analysis and question-answering.

![distil_bert_workflow](res/distil_bert_workflow.png)

### Vector Database

#### Milvus

![milvus](res/milvus.png)

Milvus is an open-source vector database designed for managing and searching large-scale embedding data efficiently. It is widely used in AI, machine learning, and semantic search applications where similarity search and retrieval play a key role.

#### FAISS

![faiss](res/faiss.png)

[Faiss](https://github.com/facebookresearch/faiss) (Facebook AI Similarity Search) is an open-source library developed by Meta for efficient similarity search and clustering of dense vectors. It is designed to handle datasets ranging from a few million to over a billion high-dimensional vectors, making it a backbone for modern recommendation systems, search engines, and AI applications.

---



## Model Training

Traditional Machine Learning Techniques:

- [Machine Learning#Naive Bayes](ml.md)
- [Machine Learning#Logistic Regression](ml.md)
- [Machine Learning#Support Vector Machines (SVM)](ml.md)
- [Machine Learning#Random Forest (Bagging Algorithm)](ml.md)

Deep Learning Techniques:

- [Deep Learning#Artificial Neural Networks(ANNs)](dl.md)
- [Deep Learning#Recurrent Neural Networks(RNNs)](dl.md)
- [Deep Learning#Long Short-Term Memory Networks (LSTMs)](dl.md)
- Gated Recurrent Unit (GRU)
- Seq2Seq Models
- Deep Learning#Transformer Models

### GPT (Generative Pre-trained Transformer)

Generative Pre trained Transformer (GPT) is a language model that understands and generates human like text. It learns patterns and relationships between words from large data and can perform multiple language tasks using a single model.

GPT models are built upon the [transformer architecture](transformer.md) introduced in 2017, which uses self attention mechanisms to process input data in parallel, allowing for efficient handling of long range dependencies in text. The core process involves:

1. **Pre-training:** The model is trained on vast amounts of text data to learn language patterns, grammar, facts and some reasoning abilities.
2. **Fine-tuning:** The pre-trained model is further trained on specific datasets with human feedback to align its responses with desired outputs.

GPT architecture:

![gpt_arch](res/gpt_arch.png)

### Transformer XL

Transformer XL is an extension of the vanilla [transformer architecture](transformer.md) designed to address the challenges associated with them for language modeling task as highlighted above. It introduces two key features:

- Segment-level recurrent mechanism
- Relative Positional Encoding

#### Segment-level recurrent mechanism

In a standard Transformer, the hidden state at a given position is a vector that encodes information about the token at that position and its relationships with other tokens in the sequence. The hidden state is updated through self-attention mechanisms and feedforward layers in each layer of the Transformer.

The segment-level recurrent mechanism involves updating the hidden states not only within the current segment but also by attending to the hidden states from previous segments. This enables the model to extend its context window beyond the current segment.

Let:

- $S_{\tau}$ and $S_{\tau + 1}$ be two segments
- $L$ be the length of sequence
- $D$ be the hidden dimension of the layer
- $n$ be the number of layers

Now the hidden state being feed into nth layer of segment $S_{\tau + 1}$ depends not only the hidden state of $S_{\tau + 1}$ at $n$- 1but also the hidden state of layer $n - 1$ at $S_{\tau}$. The two hidden state vectors are concatenated along the length dimension. This is expressed as:
$$
h_{\tau + 1}^{\sim n - 1} = [SGh_{\tau}^{n - 1} \oplus SGh_{\tau + 1}^{n - 1}]
$$
Here we take the hidden state from previous layer of same segment and hidden state from previous layer of last segment and concatenate its. The SG denotes that the gradient is not backpropagated through previous layer.

This modified hidden state is used in for key and value calculation to key QKV matrices.
$$
q_{\tau + 1}^{n} = h_{\tau + 1}^{n - 1}W_q \\
k_{\tau + 1}^{n} = h_{\tau + 1}^{\sim n - 1}W_{k}^{T} \\
v_{\tau + 1}^{n} = h_{\tau + 1}^{\sim n - 1}W_{v}^{T} 
$$
Note that modified hidden state is used only for K and V. The Query calculation remains dependent only on hidden state of current segment previous layer. The gradient remains within a segment, but the additional history allows the network to model long-term dependency and avoid context fragmentation.

With this recurrence mechanism applied to every two consecutive segments of a corpus, it essentially creates a segment-level recurrence in the hidden states. Notice that the recurrent dependency between $h_{\tau + 1}^{n}$ and $h_{\tau}^{n - 1}$ shifts one layer downwards per segment. This can be visualized as below:

![segment_lvl_recurrent_mechanism_training_phase](res/segment_lvl_recurrent_mechanism_training_phase.png)

![segment_lvl_recurrent_mechanism_evaluation_phase](res/segment_lvl_recurrent_mechanism_evaluation_phase.png)

#### Relative Positional Encoding

In the original transformer paper, we add the positional encoding vector (U) with the embedding vector(E). We multiply the result of this with weight matrices $W_q$ and $W_k$ to get the Q and K vectors.

The attention score between $i$ and $j$ token is obtained by multiplying the Query of $i$th vector with Key of $j$th vector.

This attention score between two tokens at position $i$ and $j$ from the original transformer architecture can be mathematically decomposed into U and E vectors as below:
$$
A_{ij} = E_{x_i}^{T}W_{q}^{T}W_{k}E_{x_j} + E_{x_i}^{T}W_{q}^{T}W_{k}U_{j} + U_{i}^{T}W_{q}^{T}W_{k}E_{x_j} + U_{i}^{T}W_{q}^{T}W_{k}U_{j}
$$
here:

- $A_{ij}$ Is the attention score between words at position $i$ and $j$
- $E_{x_i}$ and $E_{x_j}$ are the embedding vectors for word at $i$ and $j$
- $U_i$ and $U_j$ are the positional encoding vectors at position $i$ and $j$
- $W_q$ and $W_k$ are the query and key matrix

The attention score in transformer XL architecture can mathematically be formulated as below:
$$
A_{ij} = E_{x_i}^{T}W_{q}^{T}W_{k}E_{x_j} + E_{x_i}^{T}W_{q}^{T}W_{k}R_{i - j} + u^{T}W_{k, E}E_{x_j} + v^{T}W_{K, R}U_{j}
$$

- $U_j$ are replaced by $R_{i - j}$ which is a positional bedding based on distance between $i$ and $j$ instead of absolute position of $j$
- The terms $U_i W_q$ in part 3 remains constant for all query positions. The author replaced this with two new vecotrs U and V which are learned during the training. These vectors represent global content bias (since the third part has vecotr $E_j$) and global positional bias (since the fourt part has vecotr $R_{i - j}$).
- The weight matrix $W_K$ in term 3 and 4 is separated the two weight matrices $W_{K, E}$ and $W_{K, R}$ for producing the content-based key vectors and position-based key vectors respectively.

### T5 (Text-to-Text Transfer Transformer)

![t5](res/t5.png)

*T5 (Text-to-Text Transfer Transformer)* is a transformer-based model developed by Google Research. Unlike traditional NLP models that have task-specific architectures, T5 treats every NLP task as a text-to-text problem. This unified framework allow it to be applied to various tasks such as translation, summarization and question answering.

T5 follows a simple yet effective principle i.e it convert all NLP problems into a text-to-text format. Model uses encoder-decoder architecture similar to Transformer-based sequence-to-sequence models. It works by:

1. Task Formulation as Text-to-Text

   Instead of treating different NLP tasks separately it reformulates each problem into a text-based input and output.

2. Encoding the Input

   The input text is tokenized using SentencePiece, then passed through the encoder which generates a contextual representation.

3. Decoding the Output

   The decoder takes the encoded representation and generates the output text in a autoregressive manner.

4. Training the Model

   T5 is pre-trained using a denoising objective where portions of text are masked and the model learns to reconstruct them. It is then fine-tuned for various tasks.

### Transfer Learning with Fine-Tunning

Natural Language Processing (NLP) has transformed models like BERT which can understand language context deeply by looking at words both before and after a target word. While BERT is pre-trained on vast amounts of general text making it adapt it to specific tasks like sentiment analysis that requires fine tuning. This process customizes BERT’s knowledge to perform well on domain-specific data while saving time and computational effort compared to training a model from scratch.

---



## Summary

### Tokenization Challenges

![nlp_tokenization_challenges](res/nlp_tokenization_challenges.png)

### Stemming vs Lemmatization

|                           Stemming                           |                        Lemmatization                         |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| Reduces words to their root form, often resulting in invalid words. | Reduces words to their base form (lemma), ensuring a valid word. |
|             Based on simple rules or algorithms.             | Considers the word's meaning and context to return the base form. |
|             May not always produce a valid word.             |                Always produces a valid word.                 |
|                  Example: "Better" → "bet"                   |                  Example: "Better" → "good"                  |
|                  No context is considered.                   |          Considers the context and part of speech.           |

### Bottom-Up vs Top-Down Parser

|       Feature       |               Top-down Parsing               |           Bottom-up Parsing           |
| :-----------------: | :------------------------------------------: | :-----------------------------------: |
|    **Direction**    |      Builds a tree from root to leaves.      |  Builds a tree from leaves to root.   |
|   **Derivation**    |          Uses leftmost derivation.           | Uses rightmost derivation in reverse. |
|   **Efficiency**    | Can be slower, especially with backtracking. | More efficient for complex grammars.  |
| **Example Parsers** |        Recursive descent, LL parser.         |       Shift-reduce, LR parser.        |

### BERT vs GPT

|                                      |                             BERT                             |                             GPT                              |
| :----------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|           **Architecture**           | Bidirectional; predicts masked words based on left, right context. | Unidirectional; predicts next word given preceding context.  |
|     **Pre-training Objectives**      | BERT is pre-trained using a masked language model objective and next sentence prediction. |     GPT is pre-trained using Next word prediction only.      |
|      **Context Understanding**       |         Strong at understanding and analyzing text.          | Strong in generating coherent and contextually relevant text. |
|       **Tasks and Use Cases**        | Commonly used in tasks like text classification, NER, sentiment analysis, and QA | Applied to tasks like text generation, chat, summarization, etc. |
| **Fine-tuning vs Few-Shot Learning** | Fine-tuning with labeled data to adapt its pre-trained representations to the task at hand. | GPT is designed to perform few-shot or zero-shot learning, where it can generalize with minimal task-specific data. |

### BERT vs RoBERTa

|       Feature        |        BERT         |                RoBERTa                |
| :------------------: | :-----------------: | :-----------------------------------: |
|   **Architecture**   | Transformer Encoder |             Same as BERT              |
| **Masking Strategy** |       Static        |                Dynamic                |
|  **Training Data**   |        16GB         |                 160GB                 |
|    **Batch Size**    |         256         |              Up to 8,000              |
|  **Training Steps**  |         1M          | 500K–1.5M (varied across experiments) |
|    **Optimizer**     |        Adam         |    Adam with tuned hyperparameters    |

---



## Reference

[1] [Natural Language Processing (NLP) Tutorial](https://www.geeksforgeeks.org/nlp/introduction-to-natural-language-processing-nlp/)

[2] [Phases of Natural Language Processing (NLP)](https://www.geeksforgeeks.org/machine-learning/phases-of-natural-language-processing-nlp/)

[3] [NLTK - NLP](https://www.geeksforgeeks.org/python/nltk-nlp/)

[4] [NLP Libraries in Python](https://www.geeksforgeeks.org/nlp/nlp-libraries-in-python/)

[5] [What is Tokenization?](https://www.geeksforgeeks.org/nlp/what-is-tokenization/)

[6] [POS(Parts-Of-Speech) Tagging in NLP](https://www.geeksforgeeks.org/nlp/nlp-part-of-speech-default-tagging/)

[7] [Introduction to Stemming](https://www.geeksforgeeks.org/machine-learning/introduction-to-stemming/)

[8] [Parsing - Introduction to Parsers](https://www.geeksforgeeks.org/compiler-design/introduction-of-parsing-ambiguity-and-parsers-set-1/)

[9] [Lemmatization with NLTK](https://www.geeksforgeeks.org/python/python-lemmatization-with-nltk/)

[10] [One Hot Encoding in Machine Learning](https://www.geeksforgeeks.org/machine-learning/ml-one-hot-encoding/)

[11] [Bag of words (BoW) model in NLP](https://www.geeksforgeeks.org/nlp/bag-of-words-bow-model-in-nlp/)

[12] [Understanding TF-IDF (Term Frequency-Inverse Document Frequency)](https://www.geeksforgeeks.org/machine-learning/understanding-tf-idf-term-frequency-inverse-document-frequency/)

[13] [N-Gram Language Modelling with NLTK](https://www.geeksforgeeks.org/nlp/n-gram-language-modelling-with-nltk/)

[14] [Latent Semantic Analysis](https://www.geeksforgeeks.org/machine-learning/latent-semantic-analysis/)

[15] [Latent Dirichlet Allocation and Topic Modelling](https://www.geeksforgeeks.org/machine-learning/latent-dirichlet-allocation-and-topic-modelling/)

[16] [Word Embedding using Word2Vec](https://www.geeksforgeeks.org/python/python-word-embedding-using-word2vec/)

[17] [Glove Word Embedding in NLP](https://www.geeksforgeeks.org/nlp/glove-word-embedding-in-nlp/)

[18] [Word Embeddings Using FastText](https://www.geeksforgeeks.org/nlp/word-embeddings-using-fasttext/)

[19] [Overview of Word Embedding using Embeddings from Language Models (ELMo)](https://www.geeksforgeeks.org/python/overview-of-word-embedding-using-embeddings-from-language-models-elmo/)

[20] [BERT Model - NLP](https://www.geeksforgeeks.org/nlp/explanation-of-bert-model-nlp/)

[21] [Doc2Vec in NLP](https://www.geeksforgeeks.org/nlp/doc2vec-in-nlp/)

[22] [Overview of RoBERTa model](https://www.geeksforgeeks.org/machine-learning/overview-of-roberta-model/)

[23] [DistilBERT in Natural Language Processing](https://www.geeksforgeeks.org/nlp/distilbert-in-natural-language-processing/)

[24] [Introduction to Generative Pre-trained Transformer (GPT)](https://www.geeksforgeeks.org/artificial-intelligence/introduction-to-generative-pre-trained-transformer-gpt/)

[25] [Transformer XL: Beyond a Fixed-Length Context](https://www.geeksforgeeks.org/nlp/trasformer-xl-beyond-a-fixed-length-context/)

[26] [T5 (Text-to-Text Transfer Transformer)](https://www.geeksforgeeks.org/nlp/t5-text-to-text-transfer-transformer/)

[27] [Transfer Learning with Fine-Tuning in NLP](https://www.geeksforgeeks.org/nlp/transfer-learning-and-fine-tuning-in-nlp/)

[28] [Dataset for Text Classification](https://www.geeksforgeeks.org/nlp/dataset-for-text-classification/)

[29] [Classification of Text Documents using Naive Bayes](https://www.geeksforgeeks.org/machine-learning/classification-of-text-documents-using-the-approach-of-naive-bayes/)

[30] [Text Classification using Logistic Regression](https://www.geeksforgeeks.org/machine-learning/text-classification-using-logistic-regression/)

[31] [RNN for Text Classifications in NLP](https://www.geeksforgeeks.org/nlp/rnn-for-text-classifications-in-nlp/)

[32] [Text classification using CNN](https://www.geeksforgeeks.org/nlp/text-classification-using-cnn/)

[33] [Sentiment Analysis using VADER - Using Python](https://www.geeksforgeeks.org/python/python-sentiment-analysis-using-vader/)

[34] [Tokenization in NLP](https://www.geeksforgeeks.org/nlp/nlp-how-tokenizing-text-sentence-words-works/)