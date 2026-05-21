# AI Summary

[TOC]



![ai_concepts](res/ai_concepts.jpg)

Artificial Intelligence (AI) refers to the simulation of human intelligence in machines, allowing them to perform tasks that typically require human cognitive functions such as learning, reasoning, problem-solving, perception, and decision-making.

## AI Types

![type_of_ai](res/type_of_ai.png)

### Types of AI Based on Functionalities

![type_of_ai_based_functionality](res/type_of_ai_based_functionality.png)

|            **Basis**             |        **Reactive AI**         |   **Limited Memory AI**    |        **Theory of Mind AI**         |                **Self-Aware AI**                |
| :------------------------------: | :----------------------------: | :------------------------: | :----------------------------------: | :---------------------------------------------: |
| Level of Intelligence  |      Basic response-based      |     Learned from data      |     Social/emotional (emerging)      |         Conscious-level (hypothetical)          |
|    Learning Ability    |          No learning           |   Learns from past data    | Limited/experimental social learning |     Self-reflective learning (theoretical)      |
|    Decision-Making     | Rule-based, immediate response | Data-driven, probabilistic | Context + emotion + intention-based  |         Fully autonomous, self-directed         |
| Interaction Complexity |    Simple, fixed responses     | Context-aware interaction  |    Human-like social interaction     | Highly advanced, human-equivalent (theoretical) |
|   Real-World Status    |          Fully exists          |     Widely used today      |            Research stage            |                Not yet achieved                 |



## Hierarchy

![ai_hierarchy](res/ai_hierarchy.png)



## Workflow

![ai_workflow](res/ai_workflow.png)



## Machine Learning (ML)

![ml_workflow](res/ml_workflow.png)

### Supervised Machine Learning

![supervised_ml](res/supervised_ml.png)

### Unsupervised Machine Learning

![unsupervised_ml](res/unsupervised_ml.png)

### Reinforcement Machine Learning

![reinforecement_ml](res/reinforecement_ml.png)



## Deep Learning

![deep_learning_intro](res/deep_learning_intro.png)

### Neural Networks

![neural_network_arch](res/neural_network_arch.png)

### Artificial Neural Networks (ANNs)

![ann_intro](res/ann_workflow.png)

### Convolutional Neural Networks (CNNs)

![cnn_intro](res/cnn_intro.png)

### Recurrent Neural Networks (RNNs)

![rnn_intro](res/rnn_intro.png)

### Long Short-Term Memory Networks (LSTMs)

![lstm_intro](res/lstm_intro.png)

### Generative Adversarial Networks (GANs)

![gan_intro](res/gan_intro.png)

### Autoencoders

![autoencoder_intro](res/autoencoder_intro.png)



## Natural Language Processing (NLP)

![nlp_intro](res/nlp_intro.png)

### Phase

![nlp_phase](res/nlp_phase.png)



## Computer Vision

![cv_intro](res/cv_intro.png)



## Generative AI

![genai_summary](res/genai_summary.png)



## Agentic AI

![agent_intro](res/agent_intro.png)



## Other

### Hardware

![cpu_vs_gpu_vs_tpu](res/cpu_vs_gpu_vs_tpu.png)

### Library/Tools

![ai_tool_stack](res/ai_tool_stack.jpg)

### NLP Python Library

![nlp_python_lib](res/nlp_python_lib.png)



## AI Algorithms

![ai_algo](res/ai_algo.png)



## Challenge

### Ignorable Problems

These are minor issues that have little or no effect on the AI system’s overall performance. They are often harmless and do not require immediate attention.

Examples:

- Small inaccuracies in predictions that don't affect the final result like a slight error in image classification.
- Minor issues in data preprocessing that don't change the outcome.

### Recoverable Problems

Recoverable problems are those where the AI system encounters an issue but can be fixed with intervention, either automatically or manually, such as error-handling functions.

Examples:

- Missing data that can be filled in using statistical methods.
- System crashes that can be fixed by restoring from a backup.

### Irrecoverable Problems

These are severe issues that cause permanent damage or failure, making it impossible for the system to recover. They can lead to significant performance loss.

Examples:

- Corrupted training data that causes bias and reduces the model's effectiveness.
- Adversarial attacks that make the model untrustworthy.
- Overfitting, where the model becomes too specialized and cannot adapt to new data.



## Application

### AI in Manufacturing

![ai_in_manufacturing](res/ai_in_manufacturing.png)

### AI in Transportation

![ai_in_transportation](res/ai_in_transportation.png)



## Summary

### AI Agent vs MCP vs RAG

![agent_vs_mcp_vs_rag](res/agent_vs_mcp_vs_rag.jpg)

An AI agent is a software program that can interact with its environment, gather data, and use that data to achieve predetermined goals. AI agents can choose the best actions to perform to meet those goals.

Model Context Protocol (MCP) is an open standard that allows AI models (like Claude) to connect to databases, APIs, file systems, and other tools without needing custom code for each new integration.

RAG (Retrieval-Augmented Generation) is about what the model knows at runtime. The model stays frozen. No retraining. When a user asks a question, a retriever fetches relevant documents (PDFs, code, vector DBs), and those are injected into the prompt.

### Traditional AI vs Agentic AI

|      Feature       |                        Traditional AI                        |                          Agentic AI                          |
| :----------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| **Core Function**  |            Performs specific, preprogrammed tasks            |      Executes tasks autonomously using predefined goals      |
| **Typical output** | Deterministic results—answers, classifications, predictions  |           Actions, decisions, multi-step workflows           |
|    **Autonomy**    | Low as it requires explicit instructions, operates within set boundaries | High as it plans, adapts, and makes decisions with minimal human direction |
|    **Learning**    | Learns from labeled data, often needs retraining for new situations | Learns from experience, adapts strategies and workflows in real time |
|   **Use cases**    |      Data sorting, image recognition, basic diagnostics      | Workflow automation, dynamic planning, virtual assistants, problem solving |
|  **Scalability**   |          Requires manual oversight as systems grow.          | Oversees and coordinates whole systems hence reducing manual monitoring. |
|  **Adaptability**  |  Struggles with unexpected changes and may need retraining.  | Adjusts strategies and learns in real time and is best suited for fast-changing situations. |
| **Business value** |   Automates simple, rule-based jobs, increases consistency   | Automates complex operations, reduces manual work, and enables personalized tasks |

### AI vs ML vs DL

|       **Aspect**        |                              AI                              |                              ML                              |                              DL                              |
| :---------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| **Scope & Application** | Broad – includes ML, DL, expert systems, robotics, computer vision, NLP, symbolic AI, etc. | Narrower – focuses on data-driven algorithms and statistical learning. |  Narrowest – focuses specifically on deep neural networks.   |
|   **Core Techniques**   | Rule-based systems, search algorithms, expert systems, ML, DL, reinforcement learning, NLP. | Supervised learning, unsupervised learning, reinforcement learning, regression, classification, clustering. | CNNs (Convolutional Neural Networks), RNNs (Recurrent Neural Networks), LSTMs, Transformers, GANs. |
|      **Data Type**      | Can work with structured, semi-structured or unstructured data depending on the approach. | Mainly structured and labeled data (though some algorithms handle unstructured data). |  Primarily unstructured data (images, audio, text, video).   |
| **Learning Dependency** | May or may not involve learning (AI can be purely rule-based). |        Always involves learning from historical data.        | Fully dependent on large-scale learning with neural networks. |
|  **Model Complexity**   | Can range from simple decision trees to complex hybrid AI systems. | Relatively simpler – linear models, trees, SVMs, ensemble methods. | Very complex – multi-layer neural networks with millions to billions of parameters. |
|  **Computation Power**  | Low to high, depending on the AI technique (expert systems vs DL). |      Moderate – runs well on CPUs for most algorithms.       |  Very high – requires GPUs/TPUs for training large models.   |



## Reference

[1] [What is Artificial Intelligence (AI)](https://www.geeksforgeeks.org/artificial-intelligence/what-is-artificial-intelligence-ai/)

[2] [Types of AI Based on Capabilities](https://www.geeksforgeeks.org/artificial-intelligence/types-of-ai-based-on-capabilities/)

[3] [Types of AI Based on Functionalities](https://www.geeksforgeeks.org/artificial-intelligence/types-of-ai-based-on-functionalities/)

[4] [Machine Learning Tutorial](https://www.geeksforgeeks.org/machine-learning/machine-learning/)

[5] [What is a Neural Network](https://www.geeksforgeeks.org/deep-learning/neural-networks-a-beginners-guide/)

[6] [Artificial Neural Networks and its Applications](https://www.geeksforgeeks.org/deep-learning/artificial-neural-networks-and-its-applications/)

[7] [Introduction to Convolution Neural Network](https://www.geeksforgeeks.org/machine-learning/introduction-convolution-neural-network/)

[8] [Introduction to Recurrent Neural Networks](https://www.geeksforgeeks.org/machine-learning/introduction-to-recurrent-neural-network/)

[9] [Generative Adversarial Network (GAN)](https://www.geeksforgeeks.org/deep-learning/generative-adversarial-network-gan/)

[10] [Supervised Machine Learning](https://www.geeksforgeeks.org/machine-learning/supervised-machine-learning/)

[11] [What is Unsupervised Learning](https://www.geeksforgeeks.org/machine-learning/unsupervised-learning/)

[12] [Reinforcement Learning](https://www.geeksforgeeks.org/machine-learning/what-is-reinforcement-learning/)

[13] [Phases of Natural Language Processing (NLP)](https://www.geeksforgeeks.org/machine-learning/phases-of-natural-language-processing-nlp/)

[14] [What is LSTM - Long Short Term Memory?](https://www.geeksforgeeks.org/deep-learning/deep-learning-introduction-to-long-short-term-memory/)

[15] [Autoencoders in Machine Learning](https://www.geeksforgeeks.org/machine-learning/auto-encoders/)

[16] [EP129: The Ultimate Walkthrough of the Generative AI Landscape](https://blog.bytebytego.com/p/ep129-the-ultimate-walkthrough-of)

[17] [EP167: Top 20 AI Concepts You Should Know](https://blog.bytebytego.com/p/ep167-top-20-ai-concepts-you-should)

[18] [The Open Source AI Stack](https://blog.bytebytego.com/i/155048027/the-open-source-ai-stack)

[19] [AI Agent versus MCP](https://blog.bytebytego.com/i/164838806/ai-agent-versus-mcp)

[20] [How does AI work?](https://www.geeksforgeeks.org/artificial-intelligence/how-does-ai-work/)

[21] [Artificial Intelligence (AI) Algorithms](https://www.geeksforgeeks.org/artificial-intelligence/ai-algorithms/)

[22] [Agentic AI vs. Traditional AI](https://www.geeksforgeeks.org/artificial-intelligence/agentic-ai-vs-traditional-ai/)

[23] [What is Agentic AI](https://www.geeksforgeeks.org/artificial-intelligence/what-is-agentic-ai/)

[24] [Types of AI Based on Functionalities](https://www.geeksforgeeks.org/artificial-intelligence/types-of-ai-based-on-functionalities/)

[25] [Artificial intelligence vs Machine Learning vs Deep Learning](https://www.geeksforgeeks.org/artificial-intelligence/artificial-intelligence-vs-machine-learning-vs-deep-learning/)

[26] [Problem Solving in Artificial Intelligence](https://www.geeksforgeeks.org/artificial-intelligence/problem-solving-in-artificial-intelligence/)

[27] [AI in Manufacturing : Revolutionizing the Industry](https://www.geeksforgeeks.org/artificial-intelligence/ai-in-manufacturing-revolutionizing-the-industry/)

[28] [AI in Transportation](https://www.geeksforgeeks.org/artificial-intelligence/ai-in-transportation/)