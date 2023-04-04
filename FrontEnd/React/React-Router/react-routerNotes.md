# [React Router](https://reactrouter.com/en/main/start/overview)

React Router is a client-side routing library for React.

It supports **two** different syntax to define routing:

1. JSX:

```js
// Configure nested routes with JSX
createBrowserRouter(
  createRoutesFromElements(
    <Route path="/" element={<Root />}>
      <Route path="contact" element={<Contact />} />
      <Route
        path="dashboard"
        element={<Dashboard />}
        loader={({ request }) =>
          fetch("/api/dashboard.json", {
            signal: request.signal,
          })
        }
      />
      <Route element={<AuthLayout />}>
        <Route
          path="login"
          element={<Login />}
          loader={redirectIfUser}
        />
        <Route path="logout" />
      </Route>
    </Route>
  )
);
```

> Note: `createRoutesFromElements` is required.

2. Plain Object

```js
// Or use plain objects
createBrowserRouter([
  {
    path: "/",
    element: <Root />,
    children: [
      {
        path: "contact",
        element: <Contact />,
      },
      {
        path: "dashboard",
        element: <Dashboard />,
        loader: ({ request }) =>
          fetch("/api/dashboard.json", {
            signal: request.signal,
          }),
      },
      {
        element: <AuthLayout />,
        children: [
          {
            path: "login",
            element: <Login />,
            loader: redirectIfUser,
          },
          {
            path: "logout",
            action: logoutUser,
          },
        ],
      },
    ],
  },
]);
```




## [Fetch Data while Routing](https://reactrouter.com/en/main/start/overview#data-loading)

Data can be fetched when routing using `loader` attribute of a route, and `useLoaderData` in the landing component to retrieve.


## [Actions and Form](https://reactrouter.com/en/main/components/form)

In comparison of [Controlled vs Uncontrolled Forms](https://goshacmd.com/controlled-vs-uncontrolled-inputs-react/), controlled forms are more widely used as it enables instant validations and other benefits. **The one at this point, we will talk about is UI synchronization**. However, we have to write many `states` and `state handlers` for each field.

Now, react router provides a `Form` that handles UI synchronization by automatically calling loader of the page after submission of the form is completed.

`Form` has an attribute of `action` which is a relative URL defined in the `React Router Routes`. Thus, when the form is submitted, it can also navigate to a different URL if wishes. The URL corresponding `action` will be called. Note: at this time, the **action in the Routes** is a function. This function will have access to the form data and use it to submit or other things. Note, the real submission is prevented. Thus, we have to call submission to the server using Fetch/Axios. 

More details can be found in this video: [React Router in Depth #10 - Forms & Actions](https://www.youtube.com/watch?v=tvE8B1HBoOQ)


> Note, loader of a URL is automatically called after the action function is complete. Thus, if we set the `Form's action` to current page URL, we can end up with a free loader without reloading the page. 

## [Fetcher](https://www.youtube.com/watch?v=H8Qm_N_5Re0)

Fetcher is used to do a manual loading or submitting.


