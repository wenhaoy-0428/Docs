## SvelteKit

Whereas Svelte is a component framework, SvelteKit is an app framework (or ‘metaframework’, depending on who you ask) that solves the tricky problems of building something production-ready:

* Routing
* Server-side rendering
* Data fetching
* Service workers
* TypeScript integration
* Prerendering
* Single-page apps
* Library packaging
* Optimised production builds
* Deploying to different hosting providers
* ...and so on

SvelteKit apps are **server-rendered by default**


At its core, SvelteKit’s job boils down to three things:

**Routing** — figure out which route matches an incoming request
**Loading** — get the data needed by the route
**Rendering** — generate some HTML (on the server) or update the DOM (in the browser)

### Routing

SvelteKit uses **filesystem-based** routing

**page**: `+page.svelte `

**layout**: `+layoiut.svelte` where `{@render children()}` is used to render children

**dynamic route**: `[slug]`

### loading

Every page of your app can **declare a load function** in a `+page.server.js` file alongside the `+page.svelte file`. As the file name suggests, this module only ever runs on the server, including for client-side navigations.

We can access this data in `+page.svelte` via the `data` prop


```js
// +page.server.js
import { posts } from './data.js';

export function load() {
	return {
		summaries: posts.map((post) => ({
			slug: post.slug,
			title: post.title
		}))
	};
}

// +page.svelte
<script lang="ts">
	let { data } = $props();
</script>

<h1>blog</h1>

<ul>
	{#each data.summaries as { slug, title }}
		<li><a href="/blog/{slug}">{title}</a></li>
	{/each}
</ul>
```

The **layout** (and any page below it) inherits data from the parent `+layout.server.js`, as well, `data` is an object that contains all the parent data.

> data fetched from `+page.server.js` doesn't pass down along the tree though.

```js
// +layout.server.js
import { posts } from './data.js';

export function load() {
	return {
		summaries: posts.map((post) => ({
			slug: post.slug,
			title: post.title
		}))
	};
}

// child/+page.server.js

import { error } from '@sveltejs/kit';
import { posts } from '../data.js';

export function load({ params }) {
	const post = posts.find((post) => post.slug === params.slug);

	if (!post) error(404);

	return {
		post
	};
}


// child/+page.svelte
<script>
	let { data } = $props();
</script>
// data 
{
    summaries: {...},
    post: {...}
}

```


### FormActions

Like formAction in Nextjs to handle form submision, we can also define actiions in `+page.server.js`


```js
//+page.server.js
export const actions = {
	create: async ({ cookies, request }) => {
		const data = await request.formData();
		db.createTodo(cookies.get('userid'), data.get('description'));
	},

	delete: async ({ cookies, request }) => {
		const data = await request.formData();
		db.deleteTodo(cookies.get('userid'), data.get('id'));
	}
};


// +page.svelte
	<form method="POST">
		<label>
			add a todo:
			<input
				name="description"
				autocomplete="off"
			/>
		</label>
	</form>

```

we can also define named actions.


```js
<form method="POST" action="?/create">
	<label>
		add a todo:
		<input
			name="description"
			autocomplete="off"
		/>
	</label>
</form>

```

The action attribute **can be any URL** — if the action was defined on another page, you might have something like `/todos?/create`


We can also retrieve the returned value from the action using `form` prop

```js
<script lang="ts">
	let { data, form } = $props();
</script>

<div class="centered">
	<h1>todos</h1>

	{#if form?.error}
		<p class="error">{form.error}</p>
	{/if}

	<form method="POST" action="?/create">
		<label>
			add a todo:
			<input
				name="description"
				value={form?.description ?? ''}
				autocomplete="off"
				required
			/>
		</label>
	</form>
```

In the action we can use `fail` to send error back

```js
import { fail } from '@sveltejs/kit';
export const actions = {
	create: async ({ cookies, request }) => {
		const data = await request.formData();
				try {
			db.createTodo(cookies.get('userid'), data.get('description'));
		} catch (error) {
			return fail(422, {
				description: data.get('description'),
				error: error.message
			});
		}
	},
    ...
}
```
### Enhance Form

`use:enhance`

when JavaScript is enabled, use:enhance will emulate the browser-native behaviour except for the full-page reloads. It will:

* update the form prop
* invalidate all data on a successful response, causing load functions to re-run
* navigate to the new page on a redirect response
* render the nearest error page if an error occurs

```js
<form method="POST" action="?/create" use:enhance>
```

With `use:enhance`, we can go further than just emulating the browser’s native behaviour. By providing a callback, we can add things like pending states and optimistic UI.

```js

<script>
	import { fly, slide } from 'svelte/transition';
	import { enhance } from '$app/forms';

	let { data, form } = $props();

		let creating = $state(false);
	let deleting = $state([]);
	
</script>



<form
	method="POST"
	action="?/create"
	use:enhance={() => {
		creating = true;

		return async ({ update }) => {
			await update();
			creating = false;
		};
	}}
>
```