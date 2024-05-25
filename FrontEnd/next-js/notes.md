# Next JS

Next.JS is a framework built upon React that is so popular and gives us the freedom to choose CSR, SSR, SSG, ISR with EXTREMELY simple configurations, and even use in a mixture.

## Router

Before starting, read in combine with [Everything I Know About UI Routing](https://gist.github.com/ryanflorence/f812198561c58aec1326ac800e6ea519) to help with understanding some of the glossaries.

NextJS provides default routing functionalities. Therefore, we don't have to use third-party libraries like [React Router](https://reactrouter.com/en/main) (the most popular react routing library) to maintain routing and navigation.

> You may wonder why do we bother using external routing library instead of just passing the url with different path? The reason is React by design is to build **Single Page Application** (SPA). Meaning, there is only 1 full page request at the beginning. Therefore, routing has to be handled separately.

There're 2 routers that NextJS provides, one is [Pages Router](#pages-router) will is the last generation router, and will not be the future. Another one is [App Router](#app-router) which is just introduced in 2023 and **is the way to go**.

![page_router_vs_app_router](./assets/Screenshot%202024-04-05%20at%2022.17.03.png)

### [Pages Router](https://nextjs.org/docs/pages/building-your-application/routing/pages-and-layouts)

Pages router is 

1. File-Based Routing: Each page corresponds to a single JavaScript file in the pages directory. This structure is simple, intuitive and maps to the traditional URL per page mindset.

    > Since Pages Router is file based, each page is independent to one another. We can have a different folder called `components` (or whatever) to store the shared react components.

2. Layouts: the exact same concept of a wrapper that wraps children component to give them a shared look, like Navigation Bar and footer in all pages. Next.JS gives a way to [customize app](https://nextjs.org/docs/pages/building-your-application/routing/pages-and-layouts#single-shared-layout-with-custom-app) so that we only have to wrap the app component to provide the layout through the entire application.

    > However, layout is one of the major drawbacks of Pages router. Even though NextJS also provides a way of [customizing certain page](https://nextjs.org/docs/pages/building-your-application/routing/pages-and-layouts#per-page-layouts) with different layout while using the uniform app layout. **We're still having a hard time to implement nested layout**.

    > Suppose all the sub-urls of `dashboard` share a different layout than the app layout, there's no easy way of doing so but manually add the layout to the EACH file of the sub-urls. A comprehension walkthrough of creating such nested layout using Pages Router can be found at [A guide to Next.js layouts and nested layouts](https://blog.logrocket.com/guide-next-js-layouts-nested-layouts/).

3. Don't confuse: even though Pages Router is file based, doesn't mean it acts like a traditional URL routing. Instead the [Link]() navigation function allows to do client-side route transitions between pages, **similar** to a single-page application. This is done by prefetching.
    > Any <Link /> in the viewport (initially or through scroll) will be prefetched by default (including the corresponding data) for pages using Static Generation. The corresponding data for server-rendered routes is fetched only when the <Link /> is clicked. 
4. Also, for shared components, like the uniform app layout, that doesn't change during path changes, their states wil be preserved, and will not be re-rendered. 
    >From [official](https://nextjs.org/docs/pages/building-your-application/routing/pages-and-layouts): When navigating between pages, we want to persist page state (input values, scroll position, etc.) for a Single-Page Application (SPA) experience.
    > This layout pattern enables state persistence because the React component tree is maintained between page transitions. With the component tree, React can understand which elements have changed to preserve state. 
    > [Navigate Between Pages](https://nextjs.org/learn-pages-router/basics/navigate-between-pages/client-side) gives a comprehensive demo


### [App Router](https://nextjs.org/docs/app/building-your-application/routing)

App router on the other hand is component-based routing. Where each file is not a page, but a component. By utilizing nesting, problem of nested layout can be easily solved with no repeated code.

Since it's component based, [partial rendering](https://nextjs.org/docs/app/building-your-application/routing/linking-and-navigating#4-partial-rendering) comes out of the box, and real SPA experience is achieved.

![partial_rendering](./assets/Screenshot%202024-04-05%20at%2022.50.00.png)


### Comparison between app/pages router

A detailed text version of comparison between Pages/App Routers can be found at [Exploring the Evolution: Next.js 13 App Router vs. Page Router](https://www.linkedin.com/pulse/exploring-evolution-nextjs-13-app-router-vs-page-louis-nwadike).

A video version can be found at [Pages Router vs App Router in Next.js - Key Differences](https://www.youtube.com/watch?v=GJPEgai_dKw)

> Both resources gives enough insights on the differences not discussed above.

### [API Routes](https://nextjs.org/docs/pages/building-your-application/routing/api-routes)

API routes is not a router, but a backend API endpoint that NextJS offers. Therefore, with NextJS api we don't have to write our backend using a different backend framework, **making NextJS a fullstack framework**. [Checkout Is Next.JS backend is better than node.js(express) ?](https://www.reddit.com/r/nextjs/comments/161lj3y/is_nextjs_backend_is_better_than_nodejsexpress/)

More importantly, all the NextJS apis are function based, and called **serverless functions**. 

The term [Severless](https://www.youtube.com/watch?v=W_VV2Fx32_Y) refers to unnecessary to maintain the server stuff (done by the provider), by providing API functions. The provider will automatically expand the server as needed. One of such services is [AWS lambda](https://www.youtube.com/watch?v=97q30JjEq9Y)





