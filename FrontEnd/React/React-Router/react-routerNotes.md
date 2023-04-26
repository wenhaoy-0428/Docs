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


#### How to use React Router to implement Protected Routers

Please follow [this video](https://www.youtube.com/watch?v=2k8NleFjG7I) for a very quick demonstration first or alternatively read [this article](https://medium.com/@dennisivy/creating-protected-routes-with-react-router-v6-2c4bbaf7bc1c) first.

A more detail step by step tutorial can be found in [this video](https://www.youtube.com/watch?v=oUZjO00NkhY) including `role based` protection.

!> At this very moment, React Router doesn't support a clean and nice way to block firing `loaders` in child routes when the path name matches. The related problem I encountered is posted [here](https://stackoverflow.com/questions/76023757/how-to-prevent-child-loader-from-being-fired-if-not-rendered-in-react-router). The problem is answered by the official crew at [github](https://github.com/remix-run/react-router/issues/9529). 


> Note: If we use states inside the `PrivateRoute`, like the following code snippet. `Outlet` is never used. Reason of this is that whenever the pages refreshed or after login. The PrivateRoutes is rendered and `isAuthenticated` is `false` and a navigation is triggered. Only after `PrivateRoutes` finishes rendering, `useEffect` will take place and `isAuthenticated` will be true. However, even its true the page is now at `login` and thus we'll stuck in the login page.

```js
export const PrivateRoutes = () => {
  const [isAuthenticated, setIsAuthenticated] = useState(true);

  useEffect(() => {
    let checkAuth = async () => {
      try {
        let response = await axios.get(API_CHECK_AUTH);
        console.log(response);
        setIsAuthenticated(true);
      } catch (e) {
        console.log(e);
      }
    };
    checkAuth();
  });

  useEffect(() => {
    console.log(isAuthenticated);
  });

  return isAuthenticated ? <Outlet /> : <Navigate to="/account/login" />;
};
```

My solve to the above problem is to use `loader` in PrivateRoutes which happens before rendering. or use context that is set before PrivateRoutes renders.

1. loader:

```js
/**
 * loader function that tries to check authentication before render and redirect page if necessary
 * @returns null if authenticated and redirect otherwise
 * @deprecated
 */
const loadPrivate = async () => {
  try {
    let response = await axios.get(API_CHECK_AUTH);
    console.log(response);
    return null;
  } catch (e) {
    console.log(e);
  }
  return redirect("/account/login");
};

<Route element={<PrivateRoutes />} loader={loadPrivate}>
...
</Route>
```

2. Context

```js
export const PrivateRoutes = () => {
  const { auth } = useAuth();
  return auth ? <Outlet /> : <Navigate to="/account/login" />;
};


export function useAuth() {
  return useContext(AuthContext);
}

export function AuthProvider({ children }) {
  const [auth, setAuth] = useState(false);

  useEffect(() => {
    let checkAuth = async () => {
      try {
        let response = await axios.get(API_CHECK_AUTH);
        console.log(response);
        setAuth(true);
      } catch (e) {
        console.log(e);
      }
    };
    checkAuth();
  });

  return (
    <AuthContext.Provider value={{ auth, setAuth }}>
      {children}
    </AuthContext.Provider>
  );
}

```


## PageTransition

Transition animation can be easily done with [Framer Motion](../FramerMotion/framerMotionNotes.md). 

#### Before React-Router V6, routes are created in this way:

```js

function Temp() {
  const location = useLocation();
  console.log(location);
  useEffect(() => {
    console.log("changes");
    console.log(location.pathname);
  });
  return (
    <AnimatePresence mode="wait">
      <Routes key={location.pathname} location={location}>
        <Route path="/account/login" element={<Login />}></Route>
        <Route path="/account/register" element={<Register />}></Route>
      </Routes>
    </AnimatePresence>
  );
}
```

The `key` prop is necessary to let AnimatePresence to know its direct children is re-mounted. An official reference can be found [here](https://www.framer.com/motion/animate-presence/##exit-animations)

The `location` prop is also required. It's original intention is to filter all children `Route` that matches the location. If not specified, default url object will be used. An official reference can be found [here](https://reactrouter.com/en/main/components/routes). 

However, it's problematic for animation if we don't specify `location` prop. The reason is that **During** transition, we'll have 2 routes mounted on the tree the same time. The *old* Route will gradually be animated out and unmounted, the *new* Route will be mounted and animated in. The problem here is by default, `Route` will read the latest pathname, hence, both the old and new Routes will have the same URL which points the new content. The will cause problem for animation. **MAY BE**, for framer motion it will does nothing when the unmounting and mounting components are the same.

More reference can be found [1](https://github.com/remix-run/react-router/issues/4351), [2](https://zhuanlan.zhihu.com/p/51949609)

##### After React-Router V6.4

`createBrowserRouter` and `createRoutesFromElements` does not accept other components aside of `Route`. The detail can be following by this [stack-overflow](https://stackoverflow.com/questions/74190609/exit-animations-with-animatepresence-framer-motion-and-createbrowserrouter-r)
