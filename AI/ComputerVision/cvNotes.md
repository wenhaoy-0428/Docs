# Computer Vision


## Image Comparison


1. The L1 distance, also known as the Manhattan distance or the taxicab distance, is a measure of the distance between two points in a coordinate system. It is called L1 distance because it is computed by summing the absolute differences between the corresponding coordinates of the two points.

    `L1 distance = sum(|x1 - x2| + |y1 - y2|)`

2. The L2 distance, also known as the Euclidean distance. 

    `L2 distance = sqrt(sum((x1 - x2)^2 + (y1 - y2)^2))`

> For geometry interpretation of L1 and L2 distance, when the L1 distance is visualized in a 2-dimensional space, the set of points that are at a fixed L1 distance from a given point forms a square-like shape. While L2 forms a circular shape.

![L1_L2_geometry_interpretation](./Assets/Screenshot%202023-05-25%20at%2001.10.43.png)

In L1 distance metric, changing the coordination system like rotating which cause the distant value to be changed, while L2 distance doesn't since its a circle. 

### KNN 

In machine learning, one of the easiest way to classify input is to use `Nearest Neighbor`. (You learnt in stat). There can be multiple distance metric to be used to calculate the input difference. 

A demo can be found at [K-Nearest Neighbors Demo](http://vision.stanford.edu/teaching/cs231n-demos/knn/)

!> Even though KNN is quite useful in some scenarios, but it is never used on images  

* [Curse of dimensionality](https://youtu.be/OoUX-nOEjG0?t=2486): Since KNN uses the nearest k points to classify regions as the same. It requires the region to be densely filled with points to work well. However, in higher dimensional spaces, the points needed to adequately fullfil the space **grow exponentially**, which is extremely bad. 

![curse_of_dimensionality_knn](./Assets/Screenshot%202023-05-25%20at%2012.07.20.png)

* KNN is quick at training time while slow in testing time. 

### Linear Regression

Linear regression is fundamental in image classification and deep learning. It's slow at training time as it will take time to examine through all the training dataset and come up with a weight matrix, but it's quick in testing time as the API should accept an input image and a weight matrix which is already calculated no matter how big it is. 

![linear_regression](./Assets/Screenshot%202023-05-25%20at%2015.45.23.png)

**Linear regression in image classification works like a template and compare compares the image with the weight matrix to calculate the similarity between the template and the input image. (Also sometimes add some bias at the end).**

> Note, we also have a bias parameter, which will be added when the transformation of W is calculated. This is necessary as it not only reduce the probability of overfitting and prevent all decisions to be 0 if the data is 0. 

Linear regression works fundamental in deep learning, but itself doesn't perform well. Since all training dataset are used to calculate a **single** template for each category, image of the same category but in different form and orientation, which can cause the image to dramatically be different, will cause the template to balance them out and looks weird. 

> Since the weight matrix has to be the same as `dimension of the image * num of categories` we can unravel them back into images for each category. 

![linear_regression_visualization](./Assets/Screenshot%202023-05-25%20at%2015.57.21.png)

> The result is that a template in order to match a a horse, may have to heads since the training dataset may have horse images with heads to left and right.

A summary cases where linear regression can struggle is when there is no easy way to draw a single line to separate regions.

![linear_regression_hard_cases](Assets/Screenshot%202023-05-25%20at%2016.15.22.png)

> In the above image, when the dataset falls on regions like above. There is no way for linear regression to draw a linear line to separate them.

#### Loss Function with SVM

In order to find the value of `W` (the weight matrix) we need a way to quantify how good or bad the matrix is. Therefore, we have a **loss function** that takes in a matrix W, training data, and training label then outputs the the error.

![loss_function](Assets/Screenshot%202023-05-30%20at%2014.39.12.png)

Here $L$ is the overall Loss value of the dataset while $f(X_i, W)$ is a predict function and $L_i$ is a local loss function that tells the error rate (loss) of an individual sample. 

For an individual Loss function $L_i$, since we're taking 1 image dot product with the matrix and get result of a vector of `n` which represents the score of being classified into each class. This is exactly what a [Multi-class SVM](../../Stats/statsNotes.md#multi-class-svm) does. Hence, this is also called **multi-class SVM Loss**

![multi_class_svm_loss](Assets/Screenshot%202023-05-30%20at%2014.46.39.png)

There are serval worth noting points are:

1. we have a threshold which is `1` where we would only count the 0 loss when the score of a correct classification is higher than other classification to that threshold. This threshold is also known as a **fixed margin**. The value of margin $\Delta$ doesn't matter and can be set to $1$ for all cases. Because, the score of each classification can be arbitrary if we scale the `W` matrix up and down. 

2. In the above formula, it may be really confusing why we have $+ 1$ inside $s_j - s_{y_j} + 1$. If we wish to make correct classification to be higher than a fixed margin $s_{y_i} \geq s_j + 1$ should be sufficient. We can think of the original formula is the follow then transform it into a switch based notation later. 
$$
L_i = \sum_{j \ne y_i} max(0, s_j - s_{y_i} + \Delta)
$$

> `max` here is a method of [activation function](#activation-function), which will be talked about later in NN,  that introduces non-linearity.

Example: 

![multi_class_svm_loss_example](Assets/Screenshot%202023-05-30%20at%2015.38.06.png)


#### Regularization

The `W` the weight matrix that makes the Loss to be 0 is **not unique**, If `W` can acquire 0 loss, then `2W` can do it as well. This inconsistency makes calculating W more difficult. 

> However, One principle we should always follow is to always pick a simpler models since it's easier to be generalized in the future. 

To tell machine to pick a simpler model whenever possible, we will add a penalty to the Loss function called **Regularization**.

![regularization](Assets/Screenshot%202023-05-30%20at%2016.24.43.png)

L2 Penalty is generally more preferred, since the L2 penalty prefers smaller and more diffuse weight vectors. 

![l2_regularization_penalty](Assets/Screenshot%202023-05-30%20at%2016.27.02.png)


#### SoftMax A.K.A Multinomial Logistic Regression

In Multi-class SVM loss function, we have calculate the score through dot product with the weight matrix, and use the score to calculate the loss. Unlike the SVM which treats the outputs $f(x_i,W)$ as (uncalibrated and possibly difficult to interpret) scores for each class, the SoftMax classifier gives a slightly more intuitive output (normalized class probabilities) and also has a probabilistic interpretation that we will describe shortly.

In SVM, we interpret the score just as higher the better. In SoftMax, we'll transform the score into probability distribution, so that sum of all transformed score will be **1**. 

![softmax](Assets/Screenshot%202023-05-30%20at%2019.08.04.png)

1. We take exponential of the score: **so that all scores no matter negative and positive will result in positive with the same monotonic increment**. 
2. divide the exponential value by the sum: so that all values sum to 1 and live in a probability distribution.
3. We take log maximum likelihood so that the function is easier to deal with. Check [MLE](../../Stats/statsNotes.md#maximum-likelihood-estimation) for more detail.
4. We take negative because Loss function measures how bad the data is, while MLE measures how good the data is.

Example

![softmax_example](Assets/Screenshot%202023-05-30%20at%2019.39.25.png)

Some property of Softmax Loss:

1. The min value of Softmax loss is 0, and max value of softmax loss is infinity. 
2. The min value 0 is only theoretical exists. Since it requires the likelihood function (not logged) to be 1, which means the probability of a correct classification is 1. Due to the fact that probability are calculated through taking exponential of the score, 1 probability means the the score has to be positive infinity while all incorrect scores have to be negative infinity. 
![log_graph](Assets/Screenshot%202023-05-30%20at%2019.52.24.png)
3. Changing the score of the correct class a little bit, will not change the result for SVM since as long as the score is above the margin, it doesn't do anything. While, this may change the loss value of softmax quite a lot. 

In practice, since taking exponential would increase the value drastically, and dealing with large number due to the fact that **Dividing large numbers can be numerically unstable**. A common practice is to subtract all value of the vector by the max, so that the largest value in the vector is 0.

> A reference can be found at the Summary.

A summary of Loss Function:

![loss_summary](Assets/Screenshot%202023-05-30%20at%2019.54.41.png)

### Optimization

In linear regression, loss function is used to quantify the badness of a Weight matrix. The following procedure is always followed regardless of using [Softmax](../../Stats/statsNotes.md#softmax-aka-multinomial-logistic-regression) or [SVM](../../Stats/statsNotes.md#loss-function-with-svm).

![optimization_intro](Assets/Screenshot%202023-05-30%20at%2020.00.30.png)

However, how we find the W that follow the above procedure and find the Weight matrix `W` that minimize the loss?

> Don't forget, we also have a bias parameter that should be considered to reduce the Loss. Then there will be 2 parameters we have to deal with and it's really hard. A trick is that we append the bias parameter into `W` and append a `1` to all training data. So that the matrix multiplication will result in the same.
> ![bias_trick](Assets/Screenshot%202023-06-01%20at%2016.46.53.png)

The topic of Optimization has been discussed in CS357 and STAT428. The simple idea is to take the gradient of Loss function with respect to `W` and add the negative [gradient](../../Math/Calculus/calculusNotes.md#gradient) to `W` which leads us to the minimum. (negative, because [gradient indicates the direction of steepest **ascent**](../../Math/Calculus/calculusNotes.md#why-is-gradient-the-direction-of-steepest-ascent)).

> If you wonder how are we going to find the gradient of Loss function with respect to `W`, since W is a matrix. We are actually have $n$ functions $f_i(w) = w_i$, and use Jacob Matrix and other technics including multivariate chain rule of derivative to do the job. Check out [**Calculating Gradient Descent Manually**](https://towardsdatascience.com/calculating-gradient-descent-manually-6d9bee09aa0b). It contains comprehensive instructions of how gradient is taken step by step including all necessary knowledge of Calculus. Since This resource is GOOOOOOD, a web archive can also be found in this folder. However, do note that the formula in the article is **NOT** the same as the Loss function we discuss here. The `W` in the article is a vector not a matrix, (you can regard it as a colum of the matrix we discussed here.) Also, check [Gradient Calculation](#gradient-calculation) in Assignment 1 for more hand on details.

```py
while True:
    weights_grad = evaluate_gradient(loss_fun, data, weights)
    weights += - step_size * weights_grad
```

> step_size is a hyper-parameter that should always be set ahead of time and is probably the most important one you should consider setting first. Also, weights, the matrix will be set a **random value** at the beginning 

Now, we are calculating gradient using all of the data in the training dataset. This is intuitive that we wish all of our training dataset to contribute matrix `W` to make it outputs the least loss. However, in reality, go over each data and calculate gradient is nearly impossible. Since the dataset can contain millions of data. 

Hence, we'll use `Stochastic Gradient Descent` where we only use a small sample, called **miniBatch** of the whole dataset inside each iteration.

![sgd](Assets/Screenshot%202023-05-31%20at%2014.32.29.png)

### Advanced Optimization

SGD is a great method as we discussed above. However, in reality, vanilla SGD turns out having a lot of problems. 

1. When the Loss function has **high condition number**: radio of the largest to smallest value, meaning the gradient is not evenly distributed and some dimension is greatly more slopped than others. For example, in 2D the gradient graph is more like an ellipse rather a circle. When poor conditioning happens, which is quite often in high dimension, the dominating dimension will have profound weight changes while other dimension will not. Hence, we can have zig-zag track during optimization.

![zig-zig](Assets/Screenshot%202023-07-06%20at%2022.52.03.png)

2. Always remember, using gradient to get optimization gives local minima not global. When encountering local minima or saddle point where gradient is 0, SGD will stuck.

![sdg_local_minima](Assets/Screenshot%202023-07-06%20at%2023.08.14.png)

> In reality, local minima doesn't play a huge problem as it's rarely a case we fall in a point where it's the minima for all dimensions. Saddle point is rather more common in high dimensions.

3. Since, gradient is calculated from mini-batches. So they can be noise and make the optimization path meander a lot.

#### SGD With Momentum

The idea of Momentum is to come up with a **velocity** term and all the gradient are accumulated. Imagine, now we have a rolling ball with momentum that rolling on a slope. The velocity keeps increasing if the slope is continuously decreasing. Even we encounter a local minima or saddle point where gradient is zero, the rolling ball still has momentum, the velocity is not 0, we may still overcome the grooves.

![sgd_momentum](Assets/Screenshot%202023-07-06%20at%2023.14.56.png)

A vivid demonstration can be found at [Gradient Descent with Nesterov Momentum](https://www.youtube.com/watch?v=c4mJ6aKjqS0) to show how momentum defeats grooves.s

> Note, we have a **friction** parameter that normally set to 0.9 shows the degree of *decay* and makes the new gradient more dominant. 

#### Nesterov Momentum

For Nesterov Accelerated Gradient a.k.a NAG is a slightly fancier momentum method. **It calculates gradient after adding up the velocity impact on current spot,** like an **action of look ahead**.

Hence, the actual step is not calculated as sum of some scale of velocity and gradient, which can be viewed as a compound vector through 2 vector both originated from the red dot. Rather, gradient connected after velocity.

![nesterov_momentum_graph](Assets/Screenshot%202023-07-06%20at%2023.43.11.png)

Therefore, equation of Nesterov is as follows. However, now the gradient is not with respect to a single value $x$ rather $x_t + \rho v_t$. Therefore, we normally substitute it with a $\tilde{x}$ and transform the original data input accordingly.

![nesterov_substitution](Assets/Screenshot%202023-07-07%20at%2000.01.08.png)

The derivation is as follows:

$$
\tilde{x_t} = x_t + \rho v_t \longrightarrow \tilde{x}_{t+1} = x_{t+1} + \rho v_{t+1} \hspace*{0.5cm} (1) \\

x_{t+1} = x_t + v_{t+1} \hspace*{0.5cm} (2) \\

(1) (2) \longrightarrow \tilde{x}_{t+1} =  x_t + v_{t+1} + \rho v_{t+1} \hspace*{0.5cm} (3)\\

\tilde{x_t} = x_t + \rho v_t \longrightarrow x_t =  \tilde{x_t} - \rho v_t \hspace*{0.5cm} (4) \\

(3)(4) \longrightarrow \tilde{x}_{t+1} = \tilde{x_t} - \rho v_t + v_{t+1} + \rho v_{t+1} \\


\begin{align*}
\tilde{x}_{t+1} &= \tilde{x_t} - \rho v_t + v_{t+1} + \rho v_{t+1} \\
               &= \tilde{x_t} - \rho v_t + (1 + \rho) v_{t+1}
\end{align*}
$$

#### [AdaGrad](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=2043)

Apart from momentum methods, a simple method we can come up with so address the problem of poor conditioning by dividing the activations by a vector where large activation is over a large value so that we can sort of balance out uneven gradient dimensions. 

![adagrad](Assets/Screenshot%202023-07-07%20at%2016.10.12.png)

> Note, the $1e^{-7}$ is not an important parameter is usually manually set to be round this value. It makes sure the denominator is not zero

One obvious problem can be spotted is that grad_squared is accumulated and is the denominator, which means the value is continuously decreasing to near 0. Hence, we have a getting slower updates to optimization, for saddle points, it may completely stuck.

#### [RMSProp](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=2141)

To address the problem of accumulating gradient sum problem of AdaGrad, RMSProp includes a decay rate parameter. 

![RMSProp](Assets/Screenshot%202023-07-07%20at%2016.22.44.png)

#### [Adam](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=2305)

Adam combines Momentum methods and Squared Gradient methods together with the following form. The performance turns out to be quite well.

![adam](Assets/Screenshot%202023-07-07%20at%2016.31.20.png)

For the bias correction, it solves the problem that when we initialize `second_moment` to be 0, which implies `np.sqt(second_moment) + 1e-7` to be extremely small and being divided by it returns a large value. Hence, in the first iteration the **update value will be huge** caused by the initialization instead of the nature of geometry of the function. 


#### Second-Order Optimization

Like Quasi-Newton's method which uses second derivative(gradient) of the function to find minima is also one of the optimization methods which derives into [BGFS and L-BFGS](https://www.youtube.com/watch?v=_JB0AO7QxSA&list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&index=7&t=2175s). Due to the fact that matrix of second order a.k.a Hessian is $O(n^2)$ and operation to invert it is $O(n^3)$, when dealing with networks the size is unmanageable. Even with L-BFGS the limited memory version that does not form/store the full inverse Hessian does not work well with SGD. (It works well for full-batch).


## Advanced Regularization

In [regularization](#regularization) section we've talked about L2/L1 regularization terms added to training to reduce the likelihood of overfitting. In this section we'll talk more about some of the more commonly used methods.

> The pattern of regularization can be concluded as adding noise or randomness at training time and average out the noise at testing time as an approximation. Hence, [Batch Normalization](#batch-normalization) also has a regularization effect.


### [Model Ensemble](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=3055)

By training multiple models simultaneously with each model may have different parameters, so that we can average out the output to get the final one. 

### [Dropout](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=3479)

During training, dropout randomly sets a fraction of the nodes' activations to zero, effectively dropping them out. This helps regularize the network and encourages it to learn more robust features by reducing reliance on any individual node or feature.

As we have a mask at each layer to randomly dropout neurons during training, note, we didn't modify the original weight matrix, during test time, where we should have the exact same procedure except gradient updates as training **to keep the output behavior the same during training.** However, adding a random mask in testing is intractable and undesirable. We never wish to add any randomness during testing. 

To address the above issue, we scale the output of testing by the number of mask probability. As averaging the randomness is also a solution like discussed in [Batch Normalization](#batch-normalization) but hard or impossible to compute.

Why scaling by probability of dropout can be referred to [Dropout at Test Time](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=3564)

![dropout_approximation](Assets/Screenshot%202023-07-07%20at%2017.29.18.png)

> Note, we can also divide the mask by `p` at training time so that we don't have to scale in testing time.


### Transfer Learning

Overfitting can be reduced by adding more regularization. Sometimes, when we have a small dataset, while there is a similar pre-trained model, we can transfer the model that is trained with a large amount of data and substitute its very last layer with a randomly initialized matrix. Then use our dataset to train the very last layer, which is just a linear classification problem. This turns out to be quite popular and works really wel. With more dataset available we can training more deeper layers.

![transfer_learning](Assets/Screenshot%202023-07-07%20at%2018.48.40.png)


## Neural Network

With the above understanding of how we can use linear regression/SVM/Softmax and optimization to train a model, and their drawbacks when training complex models. For the previous methods, suppose we have an input matrix $x$ with 3072 data points and a weight matrix $W$ with dimension $10x3072$ the result (activation map) will be a $1x10$ matrix and each location describes the score of each category.

In Neural Networks, we are actually now have a small **filters** that is not $10x3072$ big rather $5x5x3$ where 5x5 is the dimension and `3` is the *spatial depth* which is the color channel, meaning this time, we'll not stretch a image into a long vector rather keeping the spatial structure. Next, we'll *slide* the small filter with a custom **stride** over all the input.

![cnn](Assets/Screenshot%202023-07-01%20at%2014.51.31.png)

Hence, we can apply **multiple filters** as a single layer. Note, since we are sliding a filter over the whole dimension with a stride. The formula to calculate the result dimension is $\frac{(N-F)}{stride}  + 1 \text{ where N is the input dimension, F is the dimension of the filter}$.

From the above formula, it's actually not hard to find out that the output is always smaller than the input. If such, the size of input will be quickly shrunk after not many layers. **In order to preserve the dimension of input**, we normally add **paddings of zeros.**. (This doesn't mean down-sampling is bad, it's that it should not shrink too quick, more can be referred to [Pooling](#pooling))

![convolution](Assets/Screenshot%202023-07-01%20at%2014.55.23.png)

> It's always easy to be confused that since we are keeping the spacial structure, meaning we no longer stretch the 3D matrix into a long vector. **The depth is always ignored in the notation.** For example, with notation, a filter of dimension `5x5` is actually a volume of $5x5xn$ where n may be 3 representing the color channel if we are dealing with the first layer, or any numbers that is number of filter in the previous layer. 

For a single filter, we get a matrix of dimension $\frac{(N-F)}{stride}  + 1$ where the depth is `1`. Since, we have multiple filters sliding across the input, so that the output matrix has a depth of number of filters. This can be interpreted as different filters are looking for different things over the same region and more detail can be referred to the [lecture](https://youtu.be/bNb2fEVKeEo?t=3132).

![size_of_CNN_output](Assets/Screenshot%202023-07-01%20at%2015.14.01.png)


### Pooling

Above, we add padding to preserve the input dimension or at least under our control. Down-sampling actually isn't a bad thing, it's bad that we can't shrink under our control. 

Down-sampling can

* help to manage the size of the model
* introduce more variance to the training model

1. One way of doing down-sampling is to add pooling layers in the model, where we can use [Max Pooling](https://youtu.be/bNb2fEVKeEo?t=3360) that is commonly used. 

> Depth are kept during pooling.

2. Or, we increase the stride during convolution, which is getting more and more used in recent years.


### Activation Function

In [Loss function](#loss-function-with-svm) section, we talked about taking `max` after dot product between input matrix with weight matrix. The same is true for NN, after taking the dot product between a [filter](#neural-network) with the portion of matrix underneath it, we will also pass the result into a **activation function** that will produce the activation map (the score). 

Not just a normal random function, an activation function is a **non-linear** function. The reason we have to introduce non-linearity to the model is phenomenon. Otherwise, the whole model, no matter how any layers there are, can be reduced into a single linear equation. More of why non-linearity is important can be referred to [Why must a nonlinear activation function be used in a backpropagation neural network?](https://stackoverflow.com/questions/9782071/why-must-a-nonlinear-activation-function-be-used-in-a-backpropagation-neural-net)


#### Why Activation function should be zero centered

Take a look at Sigmoid activation function: 

$$
\sigma(x) = \frac{1}{1+e^{-x}}
$$

![sigmoid](Assets/Screenshot%202023-07-05%20at%2017.06.25.png)

The above graph shows sigmoid activation function is not zero centered as all of its outputs are positive. The problem this will introduce is when we tries to find the gradient using backpropagation, that is the partial gradient, imagine it's a **vector** `v`, times the local gradient, which is vector `x`, where x is the output from a sigmoid function. 

If vector `x` is all positive. The value of gradient will be either negative or negative based on value of vector `v`. Remember, `v` is also calculated through the same process of `x` using gradient of a sigmoid function, and hence are all positive or negative. If this is the case, finding the optimization of the model can only be in direction of all positive or negative. To simplify, this means in a 2D dimension we can only have directions in the **first** or **third** quadrants. 

> In a 2D dimension, the gradient is a vector [x, y]. If x, y have the same sign (both negative or positive), the vector direction either points to the first quadrant (x,y both positive) or third quadrant (both negative).

By following the gradient that can only be in limited directions, in 2D, the optimization procedure looks like a zig-zag line. This may drastically decrease the performance, if the optimal gradient direction can be easily expressed.

![zero-center](Assets/Screenshot%202023-07-05%20at%2017.29.52.png)

> The same can be applies to [data preprocessing](#data-preprocessing), centering data around zero can also help eliminate the problem for the first layer but first layer only.



## Data Preprocessing 

Only zero centering is done for CV. Normally, there should have done normalization, but that doesn't make much sense for images.

### [Why Normalization is important?](https://youtu.be/_JB0AO7QxSA?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=313)

For un-normalized data, Loss is very sensitive to changes in weight matrix, as each data point (neuron) can be quite large, and thus the result after dot product can drastically differ. Therefore, it's harder to optimize in a subtle way.

For normalized data, Loss is less sensitive as all data are zero centered within range.



## Weight Matrix Initialization

Weight Initialization can be tricky:

1. when we set them all to zero, meaning no matter what value of the input, the output will be the same (0), this will cause the gradient for all inputs to be the same. 

2. When setting matrix to be very small value, after chaining each layer, the output after each layer will be drastically decreased and will be quickly shrunk to 0. No only that, based backpropagation that gradient is equal to upstream gradient times local gradient, where local gradient is the input from downstream, which is a value near 0. Thus gradient will also be near 0. More on this can be referred to [Weight Initialization on small value](https://youtu.be/wEoyxE0GP2M?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=2250)

![weight_initialization_small](Assets/Screenshot%202023-07-05%20at%2022.48.25.png)

3. When setting the matrix to be large, or 1, for activation function like `tanh` or `sigmoid` the value will be saturated to 1 or -1. The same is for gradient to be 0.

![weight_initialization_big](Assets/Screenshot%202023-07-05%20at%2022.49.22.png)

### Xavier Initialization 

Scaling the value based on the input size for each layer is the idea and works very well.

![Xavier](Assets/Screenshot%202023-07-05%20at%2023.09.32.png)

> Notes, xavier assumes linear activation, hence, ReLu which breaks half of the input doesn't work well with it.
> The solution to address this is to divide the number of input size by 2. Such the formula became `W = ..... / np.sqrt(fan_in / 2)`

## Batch Normalization

With [Weight Matrix Initialization](#weight-matrix-initialization), we found it not easy to deal with in order to keep the output in a nice distribution that can use. So why not we normalize the data in such way directly.

Also, we normalize data in [data preprocessing](#data-preprocessing) to reduce some problems like gradient explode. However, during training, some neuron inside a particular layer may result in a much larger value than others, and hence cause instability again. **Hence, it sounds a good idea if we keep normalizing data during training.**

![batch_normalization](Assets/Screenshot%202023-07-05%20at%2023.45.30.png)

Remember, in reality, due to the size of input, we often use [Stochastic Gradient Descent](#optimization) with mini-batches. Hence, we'll normalize each batch after fully connected layer (calculated by dot product with Weight and input), before or after activation function (non-linear function). 

> In [Stanford Lecture](https://youtu.be/wEoyxE0GP2M?list=PL3FW7Lu3i5JvHM8ljYj-zLfQRF3EO8sYv&t=3108), BN happens before activation, but some of [tutorial video](https://youtu.be/dXB-KQYkzNU?t=225) tells to do it after activation

Also, in order to control the degree of normalization, **we also scale and shift the result by another 2 parameters.** And these 2 parameters are learned during training. 

> The reason to control the degree of normalization is that, for example, if the activation function is `tanh` or `sigmoid`, normalizing data will cause all the input to the activation function be centered and no data around the upper and lower boundaries thus no saturations. However, some saturations may help improve the training. Hence, we'll add the 2 parameters to control that. And to extreme which normally doesn't happen, the normalized data can be scale and shift back to its original identity.

> Since mean and standard deviations for each batch are not learned parameters rather computed, in test time, they are inappropriate to be calculated based on test inputs (that will be pointless as we have 1 target each time and the mean and standard deviation on single target is pointless). Instead, they are computed value like average value from training.

## Training

Start Training: 

1. [Data Preprocessing](#data-preprocessing)

2. Choose Architecture: How many layers are we gonna have? How many filers?

3. Fine Tune the model:
   1. Check the Loss is reasonable by looking at the loss. Based on the architecture we choose, for example if we use [softmax](#softmax-aka-multinomial-logistic-regression) to calculate the loss function, the maximum loss value is around `log(10)` (2.3). Hence, we can should have a loss around this value. Also, when adding [Regularization](#regularization) term in the model, the loss value should increase.
   2. The model should overfit for small data with really small loss. 
   3. When having barely improving Loss, this is probably due to too small learning rate.
   4. When having NaN during training, this is called gradient explosion and are normally caused by too large learning rate.
   5. When tuning hyper parameters, we normally set a coarse range then find fine tune it later. When we our best hyper parameter near the boundaries of the range we set, this may potentially mean our range is the limit factor, and may be the best value of the hyper parameter is not within the range we set. Hence, we should try to expand the range and make the best hyper parameter value lies in the middle of the range as possible.  














## Assignments

### Assignment1

In Image cleaning, data is often **transposed** to standard dimensions `(samples, height, width, channels)`. 

```py
X = X.reshape(10000, 3, 32, 32).transpose(0, 2, 3, 1).astype("float")
```

> 1. It changes the shape of `X` to have 4 dimensions, where the first dimension represents the number of samples (10000), the second dimension represents the number of channels (3), and the last two dimensions represent the height and width of the data (32x32). 
> 2. This reorders the dimensions of X. The original order of the dimensions was (samples, channels, height, width). The transpose() function rearranges the dimensions to (samples, height, width, channels).

#### Gradient Calculation

```py
def svm_loss_naive(W, X, y, reg):
    """
    Structured SVM loss function, naive implementation (with loops).

    Inputs have dimension D, there are C classes, and we operate on minibatches
    of N examples.

    Inputs:
    - W: A numpy array of shape (D, C) containing weights.
    - X: A numpy array of shape (N, D) containing a minibatch of data.
    - y: A numpy array of shape (N,) containing training labels; y[i] = c means
      that X[i] has label c, where 0 <= c < C.
    - reg: (float) regularization strength

    Returns a tuple of:
    - loss as single float
    - gradient with respect to weights W; an array of same shape as W
    """
    dW = np.zeros(W.shape)  # initialize the gradient as zero

    # compute the loss and the gradient
    num_classes = W.shape[1]
    num_train = X.shape[0]
    loss = 0.0
    for i in range(num_train):
        scores = X[i].dot(W)
        correct_class_score = scores[y[i]]
        for j in range(num_classes):
            if j == y[i]:
                continue
            margin = scores[j] - correct_class_score + 1  # note delta = 1
            if margin > 0:
                loss += margin
                ########## Mycode
                dW[:, j] += X[i]
                dW[:, y[j]] -= X[i]
                ##########

    # Right now the loss is a sum over all training examples, but we want it
    # to be an average instead so we divide by num_train.
    loss /= num_train

    # Add regularization to the loss.
    loss += reg * np.sum(W * W)

    #############################################################################
    # TODO:                                                                     #
    # Compute the gradient of the loss function and store it dW.                #
    # Rather that first computing the loss and then computing the derivative,   #
    # it may be simpler to compute the derivative at the same time that the     #
    # loss is being computed. As a result you may need to modify some of the    #
    # code above to compute the gradient.                                       #
    #############################################################################
    # *****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    dW /= num_train   # scale gradient ovr the number of samples
    dW += 2 * reg * W # append partial derivative of regularization term

    # *****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return loss, dW
```

In the above code where we try to find the gradient of Loss function w.r.t matrix `W`. First we write down the function Loss function based on the provided procedure:

$$
L = \frac{1}{N}\sum_{i}^N max(0, (\sum_{j}^C [X_i \cdot W]_j - [X_i \cdot W]_{y_i} + 1)) + (reg\sum W * W)
$$

Where N is the number of images, and C is number of classes.

From the above formula, it's relative hard to compute the gradient, since We to take the Jacobian matrix between a Vector $X_i$ and a matrix $W$. Also, $[X_i \cdot W]_{y_i}$ is just the dot product of $X_i$ with $y_i$th column of $W$, and same applies to $[X_i \cdot W]_j$, so we can reduce the formula into the following where we calculate with vector dot product directly.

$$
L = \frac{1}{N}\sum_{i}^N max(0, (\sum_{j}^C X_i \cdot u - X_i \cdot v + 1)) + (reg\sum W * W)
$$

Where $u = W \cdot [0,0,..1_j..,0]^T$ where only `j`th row is 1 and all other row of vector is 0. $v = W \cdot [0,0,..1_{y_j}..,0]$ where only $y_j$th row of the vector is 1. 

By doing so 
$$
\begin{align*}
\frac{d}{dW}X_i \cdot u &= \frac{d}{du}\frac{du}{dW} \\
&= \frac{d}{du}\cdot[0,0,..1_j..,0] \\
&= X_i \cdot [0,0,..1_j..,0] \\
\end{align*}
$$

Note: $X_i \cdot [0,0,..1_j..,0]$ is a matrix the same size as $W$ contains all `0` except the $j_th$ Column equal to $X_i$. The same for $v$.

For detail calculus please refer to [**Calculating Gradient Descent Manually**](https://towardsdatascience.com/calculating-gradient-descent-manually-6d9bee09aa0b).

> Note, the derivative of a matrix by vector is a 3rd degree tensor. And the calculation can be followed at [Derivative of a vector with respect to a matrix](https://math.stackexchange.com/questions/1621948/derivative-of-a-vector-with-respect-to-a-matrix) -> [NN - 6 - Backpropagation: Compute the Derivatives - Part 1](https://youtu.be/x4RNPJD-IkQ?t=553)
