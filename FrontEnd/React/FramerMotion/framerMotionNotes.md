# Framer Motion



## Animation

#### Animate

`Animate` is the key prop that is used to define animation. For example: `<motion.div animate={{ x: 100 }} />`. The component will be animated to this state when mounted.

#### Initial
In order to define how this animation starts in the first place, we can use `initial` prop which defines the initial style of the component on mounted and starts to transit from the initial style to styles defined in `animate` prop.

#### Transition

In order to further config how the transition from `initial` to `animate`, for example, the `duration`, a `transition` prop is accepted.

#### Variants

In all the above props, each element has to define its own `animate` and this will create many duplicate code if multiple elements share the same animate prop. This is where `variant` comes to play. We can first define an object `const item = { hidden: { x: -10, opacity: 0 } }` and pass the object name to the `variants` prop of a component. Thus, we can have 1 definition and share it to all the components. All the keys of the object can be passed to `animate`, `initial`, [exit](#animatepresence) props.

```js
const list = { hidden: { opacity: 0 } }
const item = { hidden: { x: -10, opacity: 0 } }

return (
  <motion.ul animate="hidden" variants={list}>
    <motion.li variants={item} />
    <motion.li variants={item} />
    <motion.li variants={item} />
  </motion.ul>
)
```

One more thing that variants allow us to do is that we can define `transition` to each of object item individually

```js
const container = {
  hidden: { opacity: 0 },
  show: {
    opacity: 1,
    transition: {
      delayChildren: 0.5
    }
  }
}
```

##### Propagation

Variants not only give us neater code, but they also provide prop propagation. For all children elements defined using `motion`, as long as they define `variants` prop, they will inherit the `initial`, `animate`, [exit](#animatepresence) props of their parent unless they define their own. Note, the keys inside `variants` prop has to be the same as their parent's. In the following example, both variants have to have the same keys: `visible` and `hidden`

```js
const list = {
  visible: { opacity: 1 },
  hidden: { opacity: 0 },
}

const item = {
  visible: { opacity: 1, x: 0 },
  hidden: { opacity: 0, x: -100 },
}

return (
  <motion.ul
    initial="hidden"
    animate="visible"
    variants={list}
  >
    <motion.li variants={item} />
    <motion.li variants={item} />
    <motion.li variants={item} />
  </motion.ul>
)

```

##### Orchestration

One more thing that we can only do with variants is orchestration which defines the animation order of **between children and parent**. This is done by add more attributes inside `transition`. However, it would only work with transition defined inside a variant. 

But by using variants, we gain access to extra transition props like when, `delayChildren`, and `staggerChildren` that can let parents orchestrate the execution of child animations.


## AnimatePresence

Normally, when a component is unmounted, it is instantly removed from the tree, and no animation can be applied. To add animation when the component is unmounted, wrap it with `AnimatePresence`. This detects **direct** children are removed from the React tree, trigger any **contained** `motion components` that have an extra prop `exit` which defines the exiting animation. Sometimes, for example, react router, the `route` element is swapped but not unmounted, to overcome this add `key` prop to the direct child:

In React, changing a component's `key` makes React treat it as an entirely new component. So the old one is unmounted before the new one is mounted. So by changing the `key` of a single child of AnimatePresence, we can easily make components like slideshows.

```js
export const Slideshow = ({ image }) => (
  <AnimatePresence>
    <motion.img
      key={image.src}
      src={image.src}
      initial={{ x: 300, opacity: 0 }}
      animate={{ x: 0, opacity: 1 }}
      exit={{ x: -300, opacity: 0 }}
    />
  </AnimatePresence>
)
```

> Note, `AnimatePresence` only works when the component defines it is still mounted while its direct component is unmounted.

Such as unmounting `LoadingIndictor` while App is still mounted. Also, exit prop of nested `motion` will also be activated. Also, you can't use ternary operator inside.

```js
function App {
  <AnimatePresence>
    {showLoadingIndicator && <LoadingIndicator />}
  </AnimatePresence>


  <AnimatePresence>
    // This will not work
    {showLoadingIndicator ? <LoadingIndicator /> : null} 
  </AnimatePresence>
}
```


