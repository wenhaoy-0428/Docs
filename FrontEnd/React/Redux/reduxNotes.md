# Redux

This is the basic idea behind Redux: a single centralized place to contain the global state in your application, and specific patterns to follow when updating that state to make the code predictable.

The whole global state of your app is stored in an object tree inside a single **store**. The only way to change the state tree is to create an **action**, an object describing what happened, and **dispatch** it to the store. To specify how state gets updated in response to an action, you write pure **reducer** functions that calculate a new state based on the old state and the action.


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

## Slice

A "slice" is a collection of Redux reducer logic and actions for a single feature in your app, typically defined together in a single file. The name comes from splitting up the root Redux state object into multiple "slices" of state.



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




## Nested

use combineReducers()

## Initialization

https://redux.js.org/usage/structuring-reducers/using-combinereducers#defining-state-shape