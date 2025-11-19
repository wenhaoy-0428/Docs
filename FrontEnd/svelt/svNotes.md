# Svelt


## Reactivity

### State

```js
<script>
	let count = $state(0);

	function increment() {
		// TODO implement
		count += 1;
	}
</script>

<button onclick={increment}>
	Clicked {count}
	{count === 1 ? 'time' : 'times'}
</button>

```

### Derived state

Similar to `useCallback` in react

```js
<script>
	let numbers = $state([1, 2, 3, 4]);
	let total = $derived(numbers.reduce((t, n) => t + n, 0));

	function addNumber() {
		numbers.push(numbers.length + 1);
		console.log(numbers);
	}
</script>

<p>{numbers.join(' + ')} = {total}</p>

<button onclick={addNumber}>
	Add a number
</button>

```

### Effect

Similar to `useEffect` in react `$effect` is run each time the **state** it reads changes, and calls the clean up function before running the new round of effect.

> The cleanup function is called immediately before the effect function re-runs when interval changes, and also when the component is destroyed.

> If the effect function doesn’t read any state when it runs, it will only run once, when the component mounts.




```js
<script>
	let elapsed = $state(0);
	let interval = $state(1000);

	$effect(() => {
		const id = setInterval(() => {
			elapsed += 1;
		}, interval);

		return () => {
			clearInterval(id);
		}
	});
</script>

<button onclick={() => interval /= 2}>speed up</button>
<button onclick={() => interval *= 2}>slow down</button>

<p>elapsed: {elapsed}</p>
```


### Global State


The counter will be updated simultaneously

```js
// shared.svelte.js
export const counter = $state({
	count: 0
});

// counter.svelte.js
<script>
	import { counter } from './shared.svelte.js';
</script>

<button onclick={() => counter.count += 1}>
	clicks: {counter.count}
</button>

// app.svelte

<script>
	import Counter from './Counter.svelte';
</script>

<Counter />
<Counter />
<Counter />
```


### Props

declare `$props` inside the nested component allows parent component to pass props

```js
// app.svelte
<script>
	import Nested from './Nested.svelte';
</script>

<Nested answer={42} />


// child component
<script>
	let { answer } = $props();

</script>
// let { answer = "abc" } = $props(); for default values

<p>The answer is {answer}</p>
```


Handlers can also be passed just like props in React
```js
<script>
	import Stepper from './Stepper.svelte';

	let value = $state(0);
</script>

<p>The current value is {value}</p>

<Stepper increment={() => value =+ 1} decrement={() => value -= 1}/>
```


### Conditional Rendering

HTML doesn’t have a way of expressing logic, like conditionals and loops. Svelte does.

To conditionally render some markup, we wrap it in an `if block`. 

```js
<script>
	let count = $state(0);

	function increment() {
		count += 1;
	}
</script>

<button onclick={increment}>
	Clicked {count}
	{count === 1 ? 'time' : 'times'}
</button>

{#if count > 10}
	<p>{count} is greater than 10</p>
{/if}


// if/else if/else
{#if count > 10}
	<p>{count} is greater than 10</p>
{:else if count < 5}
	<p>{count} is less than 5</p>
{:else}
	<p>{count} is between 5 and 10</p>
{/if}
```

### Loop
`#each` blocks is similar to `map` in js

```js
	<div>
	{#each colors as color, i}
		<button
			style="background: {color}"
			aria-label={color}
			aria-current={selected === color}
			onclick={() => selected = color}
		>{i + 1}</button>
	{/each}
</div>
```


Always use `key` in the each block, in the [following example](https://svelte.dev/tutorial/svelte/keyed-each-blocks), when clicking the `remove button`, svelte will not act like react to re-render the whole component that depends on state, instead:

1. It removes the last component. (Thing)
    > So the DOM becomes <Thing name="apple" />, <Thing name="banana" /> .... <Thing name="egg">
2. It then updates the `name` value in the remaining DOM nodes (the text node containing ‘doughnut’ now contains ‘egg’, and so on), but not the emoji.
   > `things` becomes `["banana", "carrot", "doughnut", "egg"]`

Since Svetle works like **the component ‘runs’ once, and subsequent updates are ‘fine-grained’.** So name will be passed, so that `emoji` defined in `<Thing />` will not change as it was defined as a constant.



```js
// app
<script>
	import Thing from './Thing.svelte';

	let things = $state([
		{ id: 1, name: 'apple' },
		{ id: 2, name: 'banana' },
		{ id: 3, name: 'carrot' },
		{ id: 4, name: 'doughnut' },
		{ id: 5, name: 'egg' }
	]);
</script>

<button onclick={() => things.shift()}>
	Remove first thing
</button>

{#each things as thing}
	<Thing name={thing.name} />
{/each}


// thing
<script>
	const emojis = {
		apple: '🍎',
		banana: '🍌',
		carrot: '🥕',
		doughnut: '🍩',
		egg: '🥚'
	};

	// `name` is updated whenever the prop value changes...
	let { name } = $props();

	// ...but `emoji` is fixed upon initialisation
	const emoji = emojis[name];
</script>

<p>{emoji} = {name}</p>
```

> One way to fix it would be to make emoji a $derived value. But it makes more sense to remove the first <Thing> component altogether rather than remove the last one and update all the others.



### Binding

In Svelte, binding creates a two-way connection between a variable in your script and an element in your template. When one changes, the other automatically updates.

Take input as an exmaple, where we can define a `state` and use an event handler to update its value. 

```js
<script>
	let name = $state('world');
</script>

<input oninput={(e) => {name = e.target.value}} value={name} />

<h1>Hello {name}!</h1>
```

We can also use `binding` to reduce the boilerplate code


```js
<script>
	let name = $state('world');
</script>

<input bind:value={name} />

<h1>Hello {name}!</h1>
```


### className

There's a shorthand of assigning `className` with the same state.


```js
<script>
	let flipped = $state(false);
</script>

<button
		class="card {flipped ? 'flipped' : ''}"
		onclick={() => flipped = !flipped}
	>


<button
	class={["card", { flipped }]}
	onclick={() => flipped = !flipped}
>
```


Sometimes, in order to control the style of the child, we can use custom css variable


```js
// box
<style>
	.box {
		width: 5em;
		height: 5em;
		border-radius: 0.5em;
		margin: 0 0 1em 0;
		background-color: var(--color, #ddd); // here
	}
</style>

// parent
<div class="boxes">
	<Box --color="red" />
	<Box --color="green" />
	<Box --color="blue" />
</div>
```

> since css can only be applied to real DOM, while `Box` is not, this feature works by wrapping each component in an element with `display: contents`, where needed, and applying the custom properties to it. If you inspect the elements, you’ll see markup like this:

```js
<svelte-css-wrapper style="display: contents; --color: red;">
	<!-- contents -->
</svelte-css-wrapper>
```

> Because of display: contents this won’t affect your layout, but the extra element can affect selectors like .parent > .child.

Also, we can define global css to control the children, but this approach is regarded rude and should be used as the last resort.

```js
// parent
<style>
	.boxes :global(.box:nth-child(1)) {
		background-color: red;
	}

	.boxes :global(.box:nth-child(2)) {
		background-color: green;
	}

	.boxes :global(.box:nth-child(3)) {
		background-color: blue;
	}
</style>
```