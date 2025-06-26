## Basics

### Traditional Setup without build step

Vue can be used in 2 approaches: with and without a build step.

Below is an example using vue without a build step, and by using ES modules, we can also achieve modular design.

```js
<!-- index.html -->
<div id="app"></div>

<script type="module">
  import { createApp } from 'vue'
  import MyComponent from './my-component.js'

  const app = createApp(MyComponent).mount('#app')
</script>****
```

```js
// my-component.js
import { ref } from 'vue'
export default {
  setup() {
    const count = ref(0)
    return { count }
  },
  template: `<div>Count is: {{ count }}</div>`
}
```

`MyComponent` is the root component, for additional component, we need to register them

```js
app.component('TodoDeleteButton', TodoDeleteButton)
```

### Single-File Component (SFC) with a build step

In real world, Vue projects are typically developed with [Single-File Component](https://vuejs.org/guide/scaling-up/sfc.html) (SFC) that encapsulates the component's logic (JavaScript), template (HTML), and styles (CSS) in a single file. 

```js
<script setup>
import { ref } from 'vue'
const count = ref(0)
</script>

<template>
  <button @click="count++">Count is: {{ count }}</button>
</template>

<style scoped>
button {
  font-weight: bold;
}
</style>
```

> SFC is only supported when **building tools** are used.


[Why SFC is more preferred?](https://vuejs.org/guide/scaling-up/sfc.html#why-sfc)


### [Styles](https://vuejs.org/guide/introduction.html#api-styles)

Vue components can be authored in two different API styles: **Options API** and **Composition API.**

> Composition API is newer



## [Template Syntax](https://vuejs.org/guide/essentials/template-syntax.html)

### Directives

**Directives** are prefixed with `v-` to indicate that they are special attributes provided by Vue, and they apply special reactive behavior to the rendered DOM.


`v-show`

`v-if`



### [`v-html`](https://vuejs.org/guide/essentials/template-syntax.html#raw-html)

The double mustaches interpret the data as plain text, not HTML.

```js
<p>Using text interpolation: {{ rawHtml }}</p>
```

Therefore, in case `rawHTML` data property is a HTML element, any HTML tags in `rawHtml` will be displayed as text rather than being rendered as HTML.

```
Using text interpolation: <span style="color: red">This should be red.</span>
```

To dynamically render HTML content, we can use `v-html` directive, so that the inner HTML of `span` will be `rawHTML` and rendered.

```js
<p>Using v-html directive: <span v-html="rawHtml"></span></p>
```

> Any data binding side `rawHTML` is ignored, and this is not a good way to compose template, instead you should use components to compose template.

### Attribute Bindings

Mustaches cannot be used inside HTML attributes. Instead, use a `v-bind` directive:

```js
<div v-bind:id="dynamicId"></div>
// shorthand
<div :id="dynamicId"></div>
// same-name shorthand
<div :id></div>
<div v-bind:id></div>
```

Binding object is also possible

```js
const objectOfAttrs = {
  id: 'container',
  class: 'wrapper',
  style: 'background-color:green'
}

<div v-bind="objectOfAttrs"></div>
```



