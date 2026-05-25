# Artificial Intelligence (AI) Algorithms

[TOC]



![ai_algo](res/ai_algo.png)

## Search Algorithms

Search algorithms in AI help find solutions by exploring possible paths or options in a problem space. AI uses them in tasks like pathfinding, decision making and game playing. These algorithms work by searching through a set of possibilities to reach a goal, either blindly without extra information or with guidance using heuristics.

![search_algorithm_types](res/search_algorithm_types.png)

### Uniformed Search Algorithms

Uninformed search also called blind search explores the search space without any domain specific knowledge or heuristics. It treats all nodes equally and chooses which path to explore next based solely on general rules like node depth or path cost.

#### Depth First Search

TODO

#### Breadth First Search

TODO

#### Uniform Cost Search

TODO

### Informed Search Algorithms

Informed search uses domain knowledge in the form of heuristics to make smarter decisions during the search process. These heuristics estimate how close a state is to the goal, guiding the search more efficiently.

#### Greedy Search

TODO

#### A* Tree Search

TODO

#### A* Graph Search

TODO

### Local Search Algorithms

#### Hill-Climbing Search Algorithm

Hill-Climbing search algorithm is a straightforward local search algorithm that iteratively moves towards better solutions. It is often used for optimization problems where the goal is to find the peak of a landscape, represented by an objective function.

#### Simulated Annealing

Simulated Annealing is inspired by the annealing process in metallurgy, where materials are heated and then gradually cooled to remove defects. It allows for occasional moves to worse solutions to escape local optima, with the probability of such moves decreasing over time.

#### Genetic Algorithms

Genetic Algorithms (GAs) are inspired by the process of natural selection and evolution. They work with a population of solutions and evolve them over time using genetic operators like selection, crossover, and mutation.

#### Tabu Search

Tabu Search enhances local search by using a memory structure called the tabu list to avoid revisiting previously explored solutions. This helps to prevent cycling back to local optima and encourages exploration of new areas.

---



## Optimization Algorithms

### Gradient Descent

![gradient_descent_in_bgd_sgd_mbgd](res/gradient_descent_in_bgd_sgd_mbgd.png)

Gradient Descent is an optimization algorithm used to minimize the error of a machine learning model by updating parameters in the direction of decreasing loss.

Formula:
$$
\text{General Update Rule:} w = w - \alpha\frac{\partial L}{\partial w} \\
b = b - \alpha \frac{\partial L}{\partial b}
$$
where:

- $\alpha$: learning rate
- $L$: loss function
- $\frac{\partial L}{\partial w}, \frac{\partial L}{\partial b}$: gradients of loss

#### Gradient Descent in Linear Regression

![gradient_descent_in_linear_regression](res/gradient_descent_in_linear_regression.png)

Gradient Descent helps the Linear Regression model find the best values of weight $w$ and bias $b$ so that the prediction error becomes as small as possible. It starts with random values and gradually adjusts them in the direction that reduces the loss.

Formula:
$$
\hat{y} = wx + b \\
L = \frac{1}{2n} \sum_{i = 1}^{n}(y_i - \hat{y_i})^2
$$
where:

- $x$: input feature
- $w$: weight (slope of the line)
- $b$: bias/intercept
- $\hat{y}$: predicted output
- $y_i$: true target value
- $n$: number of samples
- $L$: MSE loss

#### Gradient Descent in Logistic Regression

Gradient descent helps logistic regression find optimal parameter values by reducing prediction error over time.

Formula:
$$
\sigma(z) = \frac{1}{1 + e^{-z}} \\
L = -\frac{1}{n} \sum_{i = 1}^{n}(y_i \ln(\hat{p_i}) + (1 - y_i)\ln(1 - \hat{p_i}))
$$

where:

- $z = w \cdot x + b$: linear combination
- $\sigma(z)$: sigmoid output
- $\hat{P_i}$: predicted probability
- $y_i \in \{0, 1\}$: actual label
- $n$: number of samples
- $L$: cross-entropy loss

#### Gradient Descent in Softmax Regression

Gradient descent helps the softmax regression model learn optimal parameters by reducing prediction error and improving class probabilities.

Formula:
$$
\hat{p_{i, k}} = \frac{e^{z_{i,k}}}{\sum_{j = 1}^{K}e^{z_{i, j}}} \\
L = -\frac{1}{n} \sum_{i = 1}^{n} \sum_{k = 1}^{K}y_{i, k}\ln(\hat{p_{i,k}})
$$
where:

- $z_{i,k}$: score(logit) for class k for sample $i$
- $\hat{P_{i,k}}$: probability that sample $i$ belongs to class $k$.
- $K$: number of classes
- $y_{i,k}$: one-hot encoded true label
- $n$: number of samples
- $L$: multiclass cross-entropy loss

#### Gradient Descent in Neural Network

Gradient descent helps a neural network learn optimal weights by reducing prediction error, working together with backpropagation to improve performance.

Hidden Layer:
$$
a^{(1)} = ReLU(W^{(1)}x + b^{(1)})
$$
Output Layer:
$$
\hat{y} = softmax(W^{(2)}a^{(1)} + b^{(2)})
$$
Loss:
$$
L = \sum_{k = 1}^{K}y_k \ln(\hat{y_k})
$$
where:

- $W^{(1)}, W^{(2)}$: weight matrices
- $b^{(1)}, b^{(2)}$: bias vectors
- $a^{(1)}$: hidden layer activations
- $x$: input vector
- $\hat{y}$: softmax output probabilities
- $y_k$: true class label (one-hot)
- $K$: number of classes
- $L$: cross-entropy loss

#### Mini-Batch Gradient Descent

Mini-batch gradient descent updates model parameters using small data subsets, balancing the speed of [SGD](#Stochastic Gradient Descent (SGD)) and the stability of batch gradient descent for efficient and stable training.

Algorithm:

Let:

- $\theta$ = model parameters
- $\text{max\_iters}$ = number of epochs
- $\eta$ = learning rate

For itr = 1, 2, 3, ..., max_iters:

- Shuffle the training data. It is optional but often done for better randomness in mini-batch selection.
- Split the dataset into mini-batches of size $b$.

For each mini-batch $(X_{mini}, y_{mini})$:

1. Forward Pass on the batch X_min:

   Make predictions on the mini-batch
   $$
   \hat{y} = f(X_{mini}, \theta)
   $$
   Compute error in predictions $J(\theta)$ with the current values of the parameters
   $$
   J(\theta) = L(\hat{y}, y_{mini})
   $$

2. Backward Pass:

   Compute gradient:
   $$
   \nabla_{\theta}J(\theta) = \frac{\partial J(\theta)}{\partial \theta}
   $$

3. Update Parameters:

   Gradient descent rule: 
   $$
   \theta = \theta - \eta \nabla_{\theta}J(\theta)
   $$

### Momentum-Based Gradient Optimizer

Momentum-based optimizers improve standard gradient descent by adding a momentum term that helps move more efficiently across the loss surface.

Formula:
$$
v_{t + 1} = \beta v_{t} + (1 - \beta)\nabla L(w_t) \\
w_{t + 1} = w_t - \eta v_{t + 1}
$$
where:

- $v_t$ is the velocity i.e., a running average of gradients
- $\beta$ is the momentum factor, typically a value between 0 and 1 (often around 0.9)
- $\nabla L(w_t)$ is the current gradient of the loss function
- $\eta$ is the learning rate

#### Nesterov Accelerated Gradient (NAG)

Nesterov Accelerated Gradient is an improved version of momentum optimization that computes the gradient at a look-ahead position, leading to more accurate and faster updates.

Formula:
$$
v_{t + 1} = \beta v_t + \nabla L(w_t - \eta \beta v_t) \\
w_{t + 1} = w_t - \eta v_{t + 1}
$$

#### AdaMomentum

AdaMomentum is an advanced optimization technique that combines adaptive learning rates with momentum, allowing the optimizer to adjust more effectively based on recent gradient information.

Formula:
$$
v_{t + 1} = \beta v_t + (1 - \beta)\nabla L(w_t) \\
w_{t + 1} = w_t - \eta_{t} v_{t + 1}
$$

#### RMSProp (Root Mean Square Propagation)

RMSProp is an optimization algorithm that adapts the learning rate for each parameter, helping improve training stability, especially for complex and non-stationary problems.

Formula:
$$
s_{t + 1} = \beta s_t + (1 - \beta)(\nabla L(w_t))^2 \\
w_{t + 1} = w_t - \frac{\eta}{\sqrt{s_{t + 1}} + \epsilon} \nabla L(w_t)
$$

### Stochastic Gradient Descent (SGD)

![stochastic_gradient_descent](res/stochastic_gradient_descent.png)

Stochastic Gradient Descent (SGD) is an optimization algorithm used in machine learning, especially for large datasets, that updates model parameters efficiently using small batches or single samples.

The Stochastic Gradient Descent (SGD) update rule is:
$$
\theta = \theta - \eta \nabla_\theta J(\theta; x_i, y_i)
$$
where:

- $x_i$ and $y_i$ represent the features and target of the i-th training example.
- The gradient $\nabla_\theta J(\theta; x_i, y_i)$ is now calculated for a single data point or a small batch.

### Adagrad Optimizer

Adagrad is an optimization method that adapts the learning rate for each parameter based on past gradients, improving learning for features with different frequencies.

Adagrad adapts the learning rate for each parameter by using the accumulated sum of squared gradients, allowing more efficient and stable training:

1. Initialization

   Adagrad begins by initializing the parameter values randomly, just like other optimization algorithms. Additionally, it initializes a running sum of squared gradients for each parameter which will track the gradients over time.

2. Gradient Calculation

   For each training step, the gradient of the loss function with respect to the model's parameters is calculated, just like in standard gradient descent.

3. Adaptive Learning Rate

   Adagrad adjusts the learning rate for each parameter based on the accumulated sum of squared gradients, instead of using a fixed rate.

   - Learning rate is updated as:
     $$
     l_{r_t} = \frac{\eta}{\sqrt{G_t + \epsilon}}
     $$

   - $\eta$ is the global learning rate (a small constant value)

   - $G_{t}$ is the sum of squared gradients for a given parameter up to time step $t$

   - $\epsilon$ is a small value added to avoid division by zero (often set to $1e - 8$)

   - As $\sqrt{G_t + \epsilon}$ increases, the learning rate decreases over time

   - This helps stabilize training and prevents large updates

4. Parameter Update

   The model's parameters are updated by subtracting the product of the adaptive learning rate and the gradient at each step:
   $$
   \theta_{t + 1} = \theta_{t} - l_{r_t} \cdot \nabla_{\theta}
   $$
   where:

   - $\theta_{t}$ is the current parameter
   - $\nabla_{\theta}J(\theta)$ is the gradient of the loss function with respect to the parameter

#### RMSProp (Root Mean Square Propagation)

RMSProp improves Adagrad by using an exponentially decaying average of squared gradients instead of accumulating them, preventing the learning rate from shrinking too quickly.

Formula:
$$
G_t = \gamma G_{t - 1} + (1 - \gamma)(\nabla_{\theta}J(\theta))^{2}
$$
where:

- $G_t$ is the accumulated gradient
- $\gamma$ is the decay factor (typically set to 0.9)
- $\nabla_{\theta}J(\theta)$ is the gradient

parameter update:
$$
\theta_{t + 1} = \theta_{t} - \frac{\eta}{\sqrt{G_t + \epsilon}} \cdot \nabla_{\theta}J(\theta)
$$

#### AdaDelta

AdaDelta is an improved version of Adagrad that avoids excessive accumulation of past gradients by using moving averages, leading to more stable and consistent updates.

Formula:
$$
\Delta \theta_{t + 1} = -\frac{\sqrt{E[\Delta \theta]_{t}^{2}}}{\sqrt{E[\nabla_{\theta}J(\theta)]_{t}^{2} + \epsilon}} \cdot \nabla_{\theta}J(\theta)
$$
where:

- $[\Delta\theta]_{t}^{2}$ is the running average of past squared parameter updates.

#### Adam (Adaptive Moment Estimation)

Adam is an optimization algorithm that combines the benefits of momentum and adaptive learning rates, making it robust and widely used in deep learning.

Adam has the following update rules:

- First moment estimate ($m_t$): $m_t = \beta_{1}m_{t - 1} + (1 - \beta_{1})\nabla_{\theta}J(\theta)$
- Second moment estimate ($v_t$): $v_t = \beta_{2}v_{t - 1} + (1 - \beta_2)(\nabla_{\theta}J(\theta))^{2}$
- Corrected moment estimates: $\hat{m_t} = \frac{m_t}{1 - \beta_{1}^{t}}$, $\hat{v_t} = \frac{v_t}{1 - \beta_{2}^{t}}$
- Parameter update: $\theta_{t + 1} = \theta_{t} - \frac{\eta}{\sqrt{\hat{v_t}} + \epsilon} \cdot \hat{m_t}$

### RMSProp Optimizer

RMSProp is an adaptive optimization algorithm that improves training speed and stability by adjusting the learning rate for each parameter based on recent gradients.

RMSProp was developed to overcome the limitations of earlier methods like [SGD](#Stochastic Gradient Descent (SGD)) and [Adagrad](#Adagrad Optimizer) by improving learning rate adaptation.

Formula:

1. Compute the gradient $g_t$ at time step $t$
   $$
   gt = \nabla\theta
   $$

2. Update the moving average of squared gradients
   $$
   E[g^2]_{t} = \gamma E[g^2]_{t - 1} + (1 - \gamma)
   $$
   where $\gamma$ is the decay rate.

3. Update the parameter $\theta$ using the adjusted learning rate
   $$
   \theta_{t + 1} = \theta_{t} - \frac{\eta}{\sqrt{E[g^2]_{t} + \epsilon}}
   $$
   where $\eta$ is the learning rate, and $\epsilon$ is a small constant added for numerical stability.

### Adam Optimizer

Adam (Adaptive Moment Estimation) optimizer combines the advantages of Momentum and RMSprop techniques to adjust learning rates during training. It works well with large datasets and complex models because it uses memory efficiently and adapts the learning rate for each parameter automatically.

Adam combines two optimization techniques, Momentum and RMSProp, to achieve faster and more stable training:

1. Momentum

   Momentum accelerates gradient descent by using a moving average of past gradients, helping reduce oscillations and speed up convergence. The update rule with momentum is:
   $$
   w_{t + 1} = w_t - \alpha m_t
   $$
   where:

   - $m_t$ is the moving average of the gradients at time $t$
   - $\alpha$ is the learning rate
   - $w_t$ and $w_{t + 1}$ are the weights at time $t$ and $t + 1$, respectively

   The momentum term $m_t$ is updated recursively as:
   $$
   m_t = \beta_{1}m_{t - 1} + (1 - \beta_{1})\frac{\partial L}{\partial w_t}
   $$
   where:

   - $\beta_{1}$ is the momentum parameter (typically set to 0.9)
   - $\frac{\partial L}{\partial w_t}$ is the gradient of the loss function with respect to the weights at time $t$

2. RMSprop (Root Mean Square Propagation)

   RMSprop is an adaptive learning rate optimization method that improves AdaGrad by using an exponentially weighted moving average of squared gradients. This prevents the learning rate from decreasing too quickly during training. The update rule for RMSprop is:
   $$
   w_{t + 1} = w_t - \frac{\alpha_{t}}{\sqrt{v_t + \epsilon}} \frac{\partial L}{\partial w_t}
   $$
   where:

   - $v_t$ is the exponentially weighted average of squared gradients:
     $$
     v_t = \beta_{2}v_{t - 1} + (1 - \beta_{2})(\frac{\partial L}{\partial w_t})^{2}
     $$

   - $\epsilon$ is a small constant (e.g., 10−810−8) added to prevent division by zero

Adam optimizer combines the momentum and RMSprop techniques to provide a more balanced and efficient optimization process. The key equations governing Adam are as follows:

- First moment (mean) estimate: $m_t = \beta_{1}m_{t - 1} + (1 - \beta_{1})\frac{\partial L}{\partial w_t}$

- Second moment (variance) estimate: $v_t = \beta_{2}v_{t - 1} + (1 - \beta_{2})(\frac{\partial L}{\partial w_t})^{2}$

- Bias correction: Since both $m_t$ and $v_t$ are initialized at zero, they tend to be biased toward zero, especially during the initial steps. To correct this bias, Adam computes the bias-corrected estimates:

  $\hat{m_t} = \frac{m_t}{1 - \beta_{1}^{t}}$, $\hat{v_t} = \frac{v_t}{1 - \beta_{2}^{t}}$

- Final weight update: The weights are then updated as:

  $w_{t + 1} = w_t - \frac{\hat{m_t}}{\sqrt{\hat{v_t}} + \epsilon} \alpha$

Key Parameters:

- $\alpha$: The learning rate or step size (default is 0.001)
- $\beta_{1}$ and $\beta_{2}$: Decay rates for the moving averages of the gradient and squared gradient, typically set to $\beta_{1}$= 0.9 and $\beta_2$ = 0.999
- $\epsilon$: A small positive constant used to avoid division by zero when computing the final update

---



## Automated Planning

TODO

---



## Summary

### Batch vs Stochastic vs Mini-Batch Gradient Descent

|               **Type**                |          **Update Strategy**          |       **Speed and Efficiency**        |       **Noise in Updates**       |       **Memory Usage**        |
| :-----------------------------------------: | :-----------------------------------------: | :-----------------------------------------: | :------------------------------------: | :---------------------------------: |
|      **Batch Gradient Descent**       |     Uses entire dataset for each update     |         Slow, high computation cost         |           Smooth and stable            | High (needs full dataset in memory) |
| **Stochastic Gradient Descent (SGD)** |     Updates using one sample at a time      |   Fast updates but less efficient overall   |          Highly noisy updates          |                 Low                 |
|    **Mini-Batch Gradient Descent**    | Uses small batches of datatraining examples | Fast and efficient (supports vectorization) | Moderate noise—dependent on batch size |              Moderate               |

### Local Search Algorithms Comparison

|      **Feature/Aspect**      |   **Hill-Climbing**   |      **Simulated Annealing**       |      **Genetic Algorithm**       |      **Tabu Search**      |
| :--------------------------: | :-------------------: | :--------------------------------: | :------------------------------: | :-----------------------: |
|       **Inspiration**        |    Climbing a hill    |      Annealing in metallurgy       | Natural selection and evolution  |    Memory-based search    |
|       **Search Space**       |         Local         | Broad (with controlled randomness) |  Very broad (population-based)   |     Broad with memory     |
| **Moves to Worse Solutions** |          No           |        Yes (probabilistic)         |   Yes (via mutation/crossover)   |  Rare (with aspiration)   |
|   **Avoids Local Optima**    |          No           |                Yes                 |               Yes                |            Yes            |
|       **Memory Usage**       |          Low          |               Medium               |               High               |      Medium to High       |
| **Parameter Tuning Needed**  |        Minimal        |    High (temperature, cooling)     | High (population, mutation rate) | Medium (tabu size, rules) |
|          **Speed**           |         Fast          |              Moderate              |  Slower (population evolution)   |         Moderate          |
|        **Complexity**        |        Simple         |              Moderate              |               High               |         Moderate          |
|      **Best Use Case**       | Small/simple problems |  Problems with many local optima   |  Complex optimization problems   | Problems prone to cycling |

---



## Reference

[1] [Artificial Intelligence (AI) Algorithms](https://www.geeksforgeeks.org/artificial-intelligence/ai-algorithms/)

[2] [Search Algorithms in AI](https://www.geeksforgeeks.org/machine-learning/search-algorithms-in-ai/)

[3] [Gradient Descent Algorithm in Machine Learning](https://www.geeksforgeeks.org/machine-learning/gradient-descent-algorithm-and-its-variants/)

[4] [Stochastic Gradient Descent (SGD)](https://www.geeksforgeeks.org/machine-learning/ml-stochastic-gradient-descent-sgd/)

[5] [Gradient Descent Algorithm in Machine Learning](https://www.geeksforgeeks.org/machine-learning/gradient-descent-algorithm-and-its-variants/)

[6] [Mini-Batch Gradient Descent with Python](https://www.geeksforgeeks.org/machine-learning/ml-mini-batch-gradient-descent-with-python/)

[7] [Momentum-based Gradient Optimizer - ML](https://www.geeksforgeeks.org/machine-learning/ml-momentum-based-gradient-optimizer-introduction/)

[8] [Adagrad Optimizer in Deep Learning](https://www.geeksforgeeks.org/machine-learning/intuition-behind-adagrad-optimizer/)

[9] [RMSProp Optimizer in Deep Learning](https://www.geeksforgeeks.org/deep-learning/rmsprop-optimizer-in-deep-learning/)

[10] [Local Search Algorithm in Artificial Intelligence](https://www.geeksforgeeks.org/artificial-intelligence/local-search-algorithm-in-artificial-intelligence/)

[11] [Adversarial Search Algorithms in Artificial Intelligence (AI)](https://www.geeksforgeeks.org/artificial-intelligence/adversarial-search-algorithms/)

[12] [Automated Planning in AI](https://www.geeksforgeeks.org/artificial-intelligence/automated-planning-in-ai/)