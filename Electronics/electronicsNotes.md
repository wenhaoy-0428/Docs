# Jargons

* The output is digital (It has 2 states, either high or low)
* 


# Laws


## Ohm's Law

# Impedance 

https://www.youtube.com/watch?v=UrCFv2qCELI

# Components




## Resistor


## Capacitor


#### Capacitor blocks DC



## [Inductor](https://www.youtube.com/watch?v=uW-M8eBHq9U&t=7s)

Inductor uses coils to take advantages of [Electromagnetism](#electromagnetism). When a current changes from 0 to maximum, the coil incurs **induced current** that is opposite to the current to resist.

This can be interpret as the followings. In the [Electromagnetism](#electromagnetism), we introduced the direction of induced current when a magnet approaches to the center of the coil. when a magnet approaches to the center, the magnetic flux increases which is the same result of increasing the current. Therefore, the direction of the induced current is opposite to the current flow.


#### Inductance

The equation of EMF according to [Electromagnetism](#electromagnetism) is 

$$
\varepsilon = -N \frac{d\Phi}{dt}
$$

where $\varepsilon$ is *electro-motive force*, $N$ is the *number of turns* in the coil, and $\Phi$ is the *magnetic flux*.

And we also know, EMF is incurred by changes in magnetic flux, and magnetic flux is incurred by current changes. Therefore, the above equation can be slitted into 2 stages.

$$
\varepsilon = -N \frac{d\Phi}{dt} = -N \frac{d\Phi}{di}\frac{di}{dt}
$$

where $i$ is the current.

Now, $-N \frac{d\Phi}{di}$ is actually a new variable that is called **inductance**

$$
L = -N \frac{d\Phi}{di}
$$

**Inductance shows property of any electronics that for 1 amps of changes in current, the number of voltage change.**

Inductance is determined by the same factor of [magnetic flux](#magnetic-flux) and coil diameter.

1. Coil turns
2. amps of current
3. core permeability
4. coil diameter.

> Therefore, a stronger L, cause a stronger voltage change (EMF) when current changes. With stronger EMF, we get a stronger magnetic flux.


#### Why inductor is used?





# Electromagnetism

When a wire has current flowing, a magnetic ring is created around the wire.

![magnetic_ring](Assets/v2-f028dfbbae85bbc14b84c484fe0073a3_1440w.jpg)

> The direction of the ring can be determined using **RIGHT** hand's principle, where thumb is pointing the current direction and the 4 fingers are pointing to the direction of the magnetic ring.

![ring_direction](Assets/v2-6cd1289c37de1130982241baba26eada_1440w.jpg)


We have such a ring for each point on the wire. However, they're in parallel and independent. 

![wire_rings](Assets/Screenshot%202023-12-29%20at%2017.07.34.png)

If we convert the wire into a coil, the rings are next to each other and can be combined into a larger magnetic filed.

![coil_magnetic](Assets/Screenshot%202023-12-29%20at%2017.08.58.png)


### Magnetic Flux

Magnetic flux is a measurement of the total magnetic field which passes through a given area. 

For a closed circuit, the following changes can affect the magnetic flux.

1. increasing current.
2. increasing the number of turns in a coil.
3. inserting a magnet into **center** of the coil.

### [Faraday's Law and Lenz's Law](https://www.khanacademy.org/science/physics/magnetic-forces-and-magnetic-fields/magnetic-flux-faradays-law/a/what-is-faradays-law)

When the magnetic fields ([magnetic flux](#magnetic-flux)) changes, this will induce **Electromotive Force** (EMF), which can be regarded as voltage as they even share the same unit. With EMF, **Induced current** is created, just like voltage creates current.

> It's the **changes** of magnetic flux cause the EMF, not magnetic flux cause EMF.

> **Also inducted current same as normal current will also create a new magnetic field**

The magnitude of the EMF is described by **Faraday's law.**


$$
\varepsilon = -N \frac{d\Phi}{dt}
$$

where $\varepsilon$ is *electro-motive force*, $N$ is the *number of turns* in the coil, and $\Phi$ is the *magnetic flux*.

The direction of the induced current is described by **Lenz's Law**. More specifically, it states the any magnetic field produced by an induced current will be in the **opposite** direction to the **change** in the original field.

[For example](https://zh.wikipedia.org/zh-hk/楞次定律), when a magnet approaches a coil, according to [magnetic flux](#magnetic-flux), we know adding a magnet near the center of a coil will increase the magnetic flux. Therefore, a positive **change** of magnetic flux occurs as the magnet approaches to the coil, thus induced current is created.

According to Lenz's law, in order to **prevent** the changes, a force of pushing the magnet away is created by the induced current. So the direction of the force is to the *left*. This is same as have a magnet with N on the left, and S on the right. Applying [right-hand rule of coil](
https://zhuanlan.zhihu.com/p/85791685?utm_id=0), where thumb is pointing to the N, and the fingers are pointing to the current, we know the direction of the induced current is counter-clockwise.


![lenz_example](Assets/Screenshot%202023-12-29%20at%2017.36.11.png)

More of the basics can be found at [Ref1](https://zhuanlan.zhihu.com/p/85791685?utm_id=0),













