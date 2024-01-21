# [Formik](https://formik.org/docs/tutorial)

This is a integrated form library that enables you to have many predefined functionalities where all you need is to pass in the required props.

## [Render Your component inside the Filed](component)

There are a few different ways to render things with `<Field>`.

- `<Field as>`
- `<Filed children>`
- `<Filed component>

Then you can pass in props you would normally pass to the `component` to `Field`.

# Material UI

This is a UI library that provides a ton of UI components to use with defined animations and styles.

When working with `Tailwind`, follow the [instruction](https://mui.com/material-ui/guides/interoperability/#tailwind-css). The `important: '#root',` is necessary in some situations.

For example, When dealing with `Divider` setting `className` won't effect the original element as the CSS MaterialUI uses has more specificity over Tailwind.

# Joi

Joi is a form validation library.

# [TailwindCSS](https://www.youtube.com/watch?v=pfaSUYaSgRo)

This is a CSS library that enables template CSS to use where you need to include className to the component to apply the predefined style. The syntax of use Tailwind is completely different from the original CSS.

# [React Transition Group](https://reactcommunity.org/react-transition-group/)

[Intro video](https://www.youtube.com/watch?v=IF6k0uZuypA)

`RTG` is a library allows you to use CSS transitions to animate the state changes of React components, including the animation when a component is rendered and unmounted. This library doesn't provide any animations itself rather the time slot where you can add your own animations using CSS.

There're several states when a component is rendered.

- `enter -> enter-active -> enter-done`

- `exit -> exit-active -> active-done`

The usage of this library is to wrap the component you wish to animate into `CSSTransition` tag, and the **first** child element will be injected with classNames corresponding to the states mentioned above.

For example, className `abc-enter` will be injected to the first child element when the children is mounted. Then `abc-enter` will be swapped by `abc-enter-active`, then `abc-enter-done` (`done` state will remain) Because difference classNames are applied to the component, we can add CSS to the corresponding className and achieve transition animations.

!> Note, the original CSS of the component will be applied once the component is mounted, meaning before the component enters the `enter` state, the original CSS is already applied. `RTG` only **joins** the CSS attributes of the state Classes to the original CSS. So, maybe add some of the original CSS to `done` to have a fluent animation if necessary.

> When using `RTG` with `Tailwind`/`MaterialUI` or other libraries, other libraries may apply preflight CSS that have a higher specificity. Meaning the CSS attributes joined from `RTG` state classes may not be applied. To solve this add `!important` tag.

## Appearance animation

When trying to applying animations on the appearance of a component, we'll use `enter` and `enter-active` states.

> Normally, the time between states are only **1** tick, meaning the state will shift from `enter` to `enter-active` then `enter-done` immediately.

We'll use `timeout` prop of `CSSTransition` to apply a delay when shifting to `enter-done`. Meaning, we have a long time slot between `active` and `done` but still only 1 tick between `enter` and `active`.

We'll then add `transition` to `active` with duration the **same** as the `timeout` in CSS. Thus, we can apply appearance transition effect in the `timeout` with `duration` the same value. We can have `duration` shorter or longer than `timeout` but the state will be forced into `done` resulting inconsistent animation.

## [Dynamic Sliding direction](https://www.youtube.com/watch?v=506ZDh0uVT8)

When implementing a slider, we have opposite sliding directions for back and forth. To achieve this, we can set different classNames to `CSSTransition` depending on the whether the action is going back or forth.

The problem with is the above situation is that, once the component if mounted, you can no longer can change its classNames. Meaning, when we switch back to forth, the exiting component will have a wrong direction while the entering component has the right direction.

To solve this problem, we need to use `childFactory` which is a method can be used to access children of `TransitionGroup`. Code details can be found at [Right and left sliding with react-transition-group](https://stackoverflow.com/questions/69809477/right-and-left-sliding-with-react-transition-group). To have a slightly better understanding on why `childFactory` works refer to [React TransitionGroup and React.cloneElement do not send updated props](https://stackoverflow.com/questions/41404232/react-transitiongroup-and-react-cloneelement-do-not-send-updated-props)
