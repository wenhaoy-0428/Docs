# Graphics


## Linear Algebra

### Dot product

Dot product of 2 vectors is the same as their product of length times cos the angle.

$$
\vec{\alpha} \cdot \vec{\beta} = ||\vec{\alpha}|| ||\vec{\beta}|| cos\theta
$$

This is typically useful in Graphics, as we can use the dot product of 2 vectors to find their **angle in between**.

The angle can further tell us if two vectors are in the same direction, forward / backward.


### Cross Product

Cross product is orthogonal to two initial vectors

**Direction determined by right-hand rule**, A x B means index finger from A to B, and the thumb is the direction of C.

$$
||a x b|| = ||a|| ||b|| sin\theta
$$



## Rasterization


Rasterization, to put it briefly, is primarily a method to solve the visibility problem. Visibility involves determining which parts of 3D objects are visible to the camera. Some parts of these objects may be hidden because they are either outside the camera's field of view or obscured by other objects.

> In short, rasterization is a process of converting a 3D model onto 2D screen.


## Transformation


### Rotation

In rotation, the inverse of a rotation is the same as the the transpose of the matrix.

![rotation_inverse](./assets/Screenshot%202024-05-20%20at%2015.58.46-2.png)

> For the negative of $\theta$, the $cos(-\theta) == cos(\theta)$

Also, if a matrix has its inverse matrix the same as its transpose, we call it orthogonal matrix



There're actually 2 ways of representing rotation:
1. Euler Rotation
2. Quaternion.

#### Euler Rotation

Euler Rotation is like how we perceive the world, with 3 axis and freely rotate on those 3 axis. Any rotation can be broken down into 3 consecutive single rotations on each axis. **More importantly, Rotation in 2D can commute, but in 3D can't.**

> Commute first the order of rotation doesn't matter.

Therefore, the order of execution matters. There're 





### View Transformation 


### Projection Transformation

Orthographic Projection vs Perspective Projection

![projection_orthographic_perspective](./assets/Screenshot%202024-05-20%20at%2016.38.09.png)



## Preview 

Preview collection 

## 
Play


// Gradio.. how it uses / customization

// 
BVH

Three.js



