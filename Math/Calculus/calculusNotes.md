# Calculus

This is a recap of Calculus concepts that I encountered but find it hard to remember and prove the concepts.


## [Derivative](https://www.youtube.com/watch?v=ay8838UZ4nM)

Derivative is the slop of function. It's calculated through limits and the title link shows the prove process.

## Gradient

To take derivative of a function that contains more than just 1 variable, $x_1, x_2...x_n$. This time the derivative of the function is a vector of **partial derivatives**. By saying partial derivatives. 

$$
F(x, y) = ax + by \\

gradient = [\frac{df}{dx}, \frac{df}{dy}] \\
= [a, b]
$$

https://zhuanlan.zhihu.com/p/38525412?utm_id=0


### Why is gradient the direction of steepest ascent?

Gradient has a property that it points to the direction of **steepest** (has the fastest change rate) ascent.

Fist, lets consider why ascent, not descent. 

[This is a natural choice.](https://math.stackexchange.com/questions/2693706/why-is-gradient-in-the-direction-of-ascent-but-not-descent) This is a manually set behavior and doesn't have any mathematical meaning behind the scene. Since gradient is just a vector of partial derivatives, it doesn't tell anything more. 

Then, the question becomes what do you mean it is manually set, and in the following graph the green line is not increasing, but decreasing.

![gradient_ascent](Assets/Screenshot%202023-05-31%20at%2021.25.57.png)

The green line is decreasing with a slope of **4**. However, we represent its slope as **-4**. This negative is important, because we have y axis going uphill as positive (ascent). Math never says going uphill is positive, it's us people manually set it to be positive. Same as we naturally set the direction of gradient to be ascent thus, the green line has a negative slope. 

All in all, it is negative relative to the rule we set gradient is in direction of Positive (ascent). If we manually set gradient is in direction of descent. Then the slope of green line will be **4** while the slope of blue line will be **-4**. This is totally valid, but does't follow the convention. Imagine, we naturally believes right is positive in a number line, and left is negative.


Now, [why the steepest?](https://math.stackexchange.com/questions/223252/why-is-gradient-the-direction-of-steepest-ascent)

Since from a single point in a multi-dimensional space, there are infinite directional paths meaning infinite [Directional Derivative](#directional-derivative). Since directional derivative is a vector product with the gradient.

$$
grad(f(a)) \cdot v = \mid grad(f(a))\mid \mid v \mid \cos(\theta) \\
\text{where v is a unit vector and } \theta \text{ is the angle}
$$

Hence, the directional derivative will be maximize only when $\theta$ is 0. Hence, it's the original gradient. 

More reference can be found at [Why the gradient is the direction of steepest ascent](https://youtu.be/TEB2z7ZlRAw) and [梯度的方向为什么是函数值增加最快的方向](https://zhuanlan.zhihu.com/p/38525412?utm_id=0)



## Directional Derivative

When we have the gradient of a function, for example that contains 2 variables, we only have the slope rate in x axis and y axis. However, in reality, in a multi-dimensional space, the number of paths that originate from a single point is infinite many. So how can we find slope of a particular direction? Here comes Directional Derivative.

![directional derivative](Assets/Screenshot%202023-05-31%20at%2021.14.55.png)

**Hence, derivative of a particular direction is just the product between the direction vector and the gradient.**

> Note the direction vector should better be a unit vector.