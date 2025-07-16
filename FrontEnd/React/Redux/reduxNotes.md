# Redux

This is the basic idea behind Redux: a single centralized place to contain the global state in your application, and specific patterns to follow when updating that state to make the code predictable.

The whole global state of your app is stored in an object tree inside a single **store**. The only way to change the state tree is to create an **action**, an object describing what happened, and **dispatch** it to the store. To specify how state gets updated in response to an action, you write pure **reducer** functions that calculate a new state based on the old state and the action.


## React Redux

Using Redux with any UI layer requires the same consistent set of steps:

1. Create a Redux store
2. Subscribe to updates
3. Inside the subscription callback:
   1. Get the current store state
   2. Extract the data needed by this piece of UI
   3. Update the UI with the data
4. If necessary, render the UI with initial state
5. Respond to UI inputs by dispatching Redux actions

The process of subscribing to the store, checking for updated data, and triggering a re-render can be made more generic and reusable. **A UI binding library like React Redux handles the store interaction logic, so you don't have to write that code yourself.**


Therefore, in order to use Redux in a React project, we need to install both **Redux (Redux Toolkit)** and **React Redux**.


## Store

The current Redux application state lives in an object called the store .

## Dispatch

The Redux store has a method called dispatch. The only way to update the state is to call `store.dispatch()` and pass in an action object.

## Reducer

It's a function that takes **state** and **action** as arguments, and returns the next state of the app.


Reducers must always follow some specific rules:

1. They should only calculate the new state value based on the state and action arguments
2. They are not allowed to modify the existing state. Instead, they must make immutable updates, by copying the existing state and making changes to the copied values.
3. They must not do any asynchronous logic, calculate random values, or cause other "side effects"


> You can think of dispatching actions as "triggering an event" in the application. Something happened, and we want the store to know about it. Reducers act like event listeners, and when they hear an action they are interested in, they update the state in response.

typically you would use `createSlice` to write reducers.

If we're using TypeScript, we need to tell TS what the type of `action.payload` will be. The `PayloadAction` type declares that "this is an action object, where the type of `action.payload` is..." whatever type you supplied. In this case, we know that the UI has taken the numeric string that was typed into the "amount" textbox, converted it into a number, and is trying to dispatch the action with that value, so we'll declare that this is `action: PayloadAction<number>`.

### Writing Async Logics with Thunks


## [Slice](https://redux.js.org/tutorials/essentials/part-2-app-structure#redux-slices)

A "slice" is a collection of Redux reducer logic and actions for a single feature in your app, typically defined together in a single file. The name comes from splitting up the root Redux state object into multiple "slices" of state.

Creating slices of states
```ts
// Slices contain Redux reducer logic for updating state, and
// generate actions that can be dispatched to trigger those updates.
export const counterSlice = createSlice({
  name: 'counter',
  initialState,
  // The `reducers` field lets us define reducers and generate associated actions
  reducers: {
    increment: state => {
      // Redux Toolkit allows us to write "mutating" logic in reducers. It
      // doesn't actually mutate the state because it uses the Immer library,
      // which detects changes to a "draft state" and produces a brand new
      // immutable state based off those changes
      state.value += 1
    },
    decrement: state => {
      state.value -= 1
    },
    // Use the PayloadAction type to declare the contents of `action.payload`
    incrementByAmount: (state, action: PayloadAction<number>) => {
      state.value += action.payload
    }
  }
})

// Export the generated action creators for use in components
export const { increment, decrement, incrementByAmount } = counterSlice.actions

// Export the slice reducer for use in the store configuration
export default counterSlice.reducer
```

Create store that contains the all the slices by adding their reducers.

```ts
import { configureStore } from '@reduxjs/toolkit'
import usersReducer from '../features/users/usersSlice'
import postsReducer from '../features/posts/postsSlice'
import commentsReducer from '../features/comments/commentsSlice'

export const store = configureStore({
  reducer: {
    users: usersReducer,
    posts: postsReducer,
    comments: commentsReducer
  }
})
```

## Selectors

Whenever reading states, we're reading the `RootState` of the store, therefore, it's convenient to have `Selectors`

Selector functions are normally called with the entire Redux root state object as an argument. They can read out specific values from the root state, or do calculations and return new values.

**Ideally, only your reducer functions and selectors should know the exact state structure, so if you change where some state lives, you would only need to update those two pieces of logic.**

Because of this, it's often a good idea to define reusable selectors directly inside slice files, rather than always defining them inside of a component.

`useSelector` hook allows us to pass-in a selector function to retrieve the corresponding state.

```ts
// useAppSelector is a custom wrapper around useSelector
// and selectSearch is a selector function
const search = useAppSelector(selectSearch);
```

```ts
export const useAppSelector = useSelector.withTypes<RootState>();

export const inputSettingsSlice = createSlice({
  name: "inputSettings",
  // ....
  selectors: {
    selectSearch: (state: InputSettingsState) => state.search, 
  },
});
```

### [**Optimizing Selectors with Memoization**](https://redux.js.org/usage/deriving-data-selectors#optimizing-selectors-with-memoization)

`useSelector` rely on `===` reference equality checks of the return values to determine if the component needs to re-render. If a selector always returns new references, it will force the component to re-render even if the derived data is effectively the same as last time.

> This is especially common with array operations like `map` and `filter`, which return new array reference.

Also, selector functions used with `useSelector` will be re-run after **EVERY** dispatched action, regardless of what section of the Redux root state was updated.

Therefore:

1. AVOID putting expensive logics inside a selector function.
2. use Memoization to cache the result and only call the selector function when the input changes.

**Reselect** is a lib that comes out of the box when using Redux Took Kit, that allows us to have easy memoization by using its `createSelector` API.

It accepts input selectors / and one output selector, where the input selectors acts like a dependency array, and the output selector will only be run when the input selector returns different values based on the result of `===` reference equality with their previous values.

> So that the input selectors will still always run whenever a dispatch is issued, but the output selector is cached to reduce its overhead of running **expensive** logics.

```ts
export const messagesSlice = createSlice({
  name: "messages",
  // ...
  reducers: {
    // ...
  },
  selectors: {
    // memoized selector to get all messages
    selectMessages: createSelector(
      // input selector, and be an array, or just as arguments.
      (state: MessagesState) => state.messages,
      // output selector
      (messages) => Object.values(messages)
    ),
  },
});
```

In the above example, `selectMessages` will always return a new reference thus, causes re-renders, and by wrapping it with `createSelector`, the issue is solved.

> Note, the output selector will receive the output of the input selectors, instead of the root states.

```ts
const selectA = state => state.a
const selectB = state => state.b
const selectC = state => state.c

const selectABC = createSelector([selectA, selectB, selectC], (a, b, c) => {
  // do something with a, b, and c, and return a result
  return a + b + c
})
```

****
## Nested

use combineReducers()

## Initialization

https://redux.js.org/usage/structuring-reducers/using-combinereducers#defining-state-shape