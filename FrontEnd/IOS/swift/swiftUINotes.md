# SwiftUI

SwiftUI is different from [Swift](#swift). It uses the same syntax of Swift but provides many functionalities for build an UI.

## Layout Model

In SwiftUI, the layout system is based on a different approach called the "**flexible box layout**" or "**flexbox**" model.

Flexbox is a layout model that is commonly used in modern UI frameworks and provides flexible and dynamic positioning of views. It allows you to easily create responsive and adaptive layouts by specifying flexible constraints and alignment properties.

By default, in SwiftUI, a single view without any siblings will be centered both horizontally and vertically within its parent container. 

> Always remember that all modifiers returns a **NEW** view. Check out [How layout works in SwiftUI – Layout and Geometry SwiftUI Tutorial](https://www.youtube.com/watch?v=GyC5-loVAIk)

In the following view, we have two `frame` modifier been used which is a good illustration of modifiers return a **New** view as well as the layout system.

```swift
struct HikeBadge: View {
    var name: String
    
    var body: some View {
        VStack(alignment: .center) {
            Badge()
                .frame(width: 300, height: 300)
                .scaleEffect(1.0/3.0)
                .frame(width: 100, height: 100)
            Text(name)
                .font(.caption)
                .accessibilityLabel("Badge for \(name).")
        }
    }
}
```

In SwiftUI, you can use container views like `VStack`, `HStack`, and `ZStack` along with alignment and spacing modifiers to achieve similar layout effects as the traditional box model. These container views and modifiers allow you to control the positioning, alignment, and spacing of views within a layout.

While the terminology and specific syntax may differ from the traditional CSS box model, the principles of creating layouts with flexible and responsive behavior are similar in both approaches. SwiftUI's layout system offers a powerful and intuitive way to create dynamic and adaptive user interfaces.


## Positioning

The `offset()` modifier in SwiftUI moves the **content** of a view but does not affect the position of the view's border. If you are applying a border to a view and want to move both the content and the border together, you can wrap the view in a **container** (VStack) and apply the `offset()` modifier to the container instead.



## View and Modifiers

A view can be viewed as a React component. For example, `Text("hello world")`. However, this doesn't gives us a good-looking Text component. In order to style it, like using css. We use **modifiers**. `Text("hello world").opacity(0.5)` [Modifiers](https://developer.apple.com/documentation/swiftui/view/modifier(_:)) are special functions that are built-in to `View` protocol. Hence, all subclasses/structs have access to these built-in modifiers.

In SwiftUI, the underlying mechanism of modifiers is based on the concept of functional programming and immutable data. When you apply a modifier to a view, **you are essentially creating a new instance of the modified view rather than modifying the original view directly**. This approach ensures immutability and allows for efficient view updates and rendering.

Since a modifier applies to a view and returns a new view, and a new view has the built-in modifier functions, now we can chain the modifiers.


## [Spacer](https://developer.apple.com/documentation/swiftui/spacer/init(minlength:))

Spacer adds as much empty spaces along the axis as possible. Hence, we can use it to create effect that moves away components or To direct the layout to use the full width of the device.

```swift
HStack {
    Label("\(scrum.attendees.count)", systemImage: "person.3")
    Spacer()
    Label("\(scrum.lengthInMinutes)", systemImage: "clock")
        .padding(.trailing, 20)
}
```


## Leading Dot

In swift, it's fairly common to see code like the following where we have `alignment: .leading`. It may be confusing at the first glance that we have a leading dot for variable `leading`.

```swift
struct ContentView: View {
    var body: some View {
        VStack(alignment: .leading) {
            Text("Turtle Rock")
                .font(.title)
            Text("Joshua Tree National Park")
                .font(.subheadline)
        }
    }
}
```

[VStack](https://developer.apple.com/documentation/swiftui/vstack/init(alignment:spacing:content:)) has the following syntax and hence compiler **can infer** the type of alignment to be [HorizontalAlignment](https://developer.apple.com/documentation/swiftui/horizontalalignment) where `leading` is one of the attributes. 

```swift
init(
    alignment: HorizontalAlignment = .center,
    spacing: CGFloat? = nil,
    @ViewBuilder content: () -> Content
)
```

Indeed, the first snippet of code could have be written as `VStack(alignment: HorizontalAlignment.leading)`. However, since compiler can infer the type, we can omit `HorizontalAlignment` and it's a common practice to omit it.

More info can be referred to [Why do I see some variables used with leading dot? [duplicate]](https://stackoverflow.com/questions/48418123/why-do-i-see-some-variables-used-with-leading-dot)



## ViewUpdate

To update a view, there are multiple ways of marking the variable as need the view to be updated in reflect to the changes. They are `@State` `@StateObject` `@ObservedObject` and `@EnvironmentObject`. The main difference can be found at this article [SwiftUI: @State vs @StateObject vs @ObservedObject vs @EnvironmentObject](https://levelup.gitconnected.com/state-vs-stateobject-vs-observedobject-vs-environmentobject-in-swiftui-81e2913d63f9) which gives thorough and easy to understand comparison.




## @State

`@` is called property wrapper, `@State` wrapper is the same as `useState` in React that marks the variable as a state that needs to be monitored to update the view.

Typically, @State is defined to wrap simple type, like integer and bool, whose values are value typed. Therefore, they are local and copied when passing around.

If you pass a state property to a subview, SwiftUI updates the subview any time the value changes in the container view, but the subview can’t modify the value. 

```swift
struct ParentView: View {
    @State private var count: Int = 0

    var body: some View {
        VStack {
            Text("Count: \(count)")
            Button("Increment") {
                count += 1
            }
            // Pass count to the subview
            ChildView(count: count)
        }
    }
}

struct ChildView: View {
    let count: Int // Read-only property

    var body: some View {
        Text("Child Count: \(count)")
            .padding()
    }
}
```


To enable the subview to modify the state’s stored value, pass a Binding instead， [by using the `$ prefix` to access a binding to the state.](https://developer.apple.com/documentation/swiftui/state#Share-state-with-subviews)


## @Binding

Back to React, we have can pass state variables to the children, and pass a setter to the children to let the children to update the parent state. In swiftUI, this is done by `@Binding` wrapper that creates a reference bound.

If we only like to pass the state to the child view with read-only access, like passing props in React, we don't can directly pass the state to the child view as a parameter.

However, if we want the child to be able to edit the state like the setter of React, we have to create `@Binding` in the child view and pass the state with `$` prefix.

By prefixing a state variable with `$`, you pass a binding, which is like a reference to the underlying value. When the user interacts with the map, the map updates the region value to match the part of the map that’s currently visible in the user interface.

```swift
struct PlayButton: View {
    @Binding var isPlaying: Bool


    var body: some View {
        Button(isPlaying ? "Pause" : "Play") {
            isPlaying.toggle()
        }
    }
}

struct PlayerView: View {
    var episode: Episode
    @State private var isPlaying: Bool = false


    var body: some View {
        VStack {
            Text(episode.title)
                .foregroundStyle(isPlaying ? .primary : .secondary)
            PlayButton(isPlaying: $isPlaying) // Pass a binding.
        }
    }
}
```

## State with Complex data type

A prerequisite before reading this section is **Struct** is a value type, any changes to its attributes will cause a destroy and recreate procedure. **Class** on the other hand is a reference type.

For a struct, even the attributes are marked variable, you can not modify the attributes of a constant struct.

```swift
struct User {
    var name: String
}

let user: User = User(name: "hello")
user.name = "user" // This will cause error.
```

**The view update procedure is observer pattern that monitors the variables changes.**

Since any changes to the attributes of a Struct will cause the struct variable itself to be recreated. It means **it's totally fine to use @State with struct.**



```swift
struct UserProfile {
    var name: String
}

struct ParentView: View {
    @State private var userProfile = UserProfile(name: "Alice") // Using @State with a struct

    var body: some View {
        VStack {
            Text("User Name: \(userProfile.name)")
                .font(.largeTitle)
            
            // Pass the userProfile to the child view
            EditView(userProfile: $userProfile)
        }
        .padding()
    }
}


struct EditView: View {
    @Binding var userProfile: UserProfile

    var body: some View {
        VStack {
            TextField("Enter name", text: $userProfile.name)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
        }
    }
}
```

However, this is not the case for `Class`. Since class is a reference type, we can mark the class variable as constant while its attributes as variable, and changes to its attributes will not cause changes to the class variable itself.

Therefore, the following code will update the value, but the view will stay the same.

```swift
class User {
```

To solve the problem to allow us to use class and monitor class, we need [`@StateObject`](#stateobject) and @ObservedObject together with [@ObservableObject] to monitor changes to the underline properties of a class.

> ! Before diving in, `StateObject` and `ObservableObject` are deprecated can the transition to `State` and Observable is more recommended as the official doc [Migrating from the Observable Object protocol to the Observable macro](https://developer.apple.com/documentation/swiftui/migrating-from-the-observable-object-protocol-to-the-observable-macro) says.


> Here a question comes out. If we can use `Struct` in pair with `@State` to have the same effect as using `class` in pair with `@StateObject` what are the difference. In many cases, they do achieve the similar effect. However, in rae cases, especially when dealing with network requests that encounter asynchronous functions that requires references, struct is not going to work. Therefore, in practice, Model as well as ViewModels are often using **Class** 

### ObservableObject

Declare a new model type that conforms to the `ObservableObject` protocol from the `Combine` framework and SwiftUI subscribes to your observable object, and updates any views that need refreshing when the data changes.

An observable object needs to **publish** any changes to its data, so that its subscribers can pick up the change.

`@Published`: The @Published property wrapper is used within an ObservableObject to mark a property as observable. When a property marked with @Published changes, it triggers an update to any SwiftUI views that are observing that object. It is commonly used in conjunction with the ObservableObject protocol to create observable data models that can be shared across multiple views.

```swift
final class ModelData: ObservableObject {
    @Published var landmarks: [Landmark] = load("landmarkData.json")
}
```

**`ObservableObject` protocol can only be used with classes**. This is due to the fact that structs are copied rather than referenced, if you were to change a property of a struct, the change would not be recognized by any subscribers because they would be observing a different instance (a copy) rather than the original.

However, `@Published` property wrapper can wrap structs within a class. This is due to the fact that a new structs will be created each time its value/inner values are mutated. Therefore, the `@Published` wrapper can notice changes, while for a class the reference value will not change. 


### StateObject

This is deprecated already, this section is only help to understand the basics.

> [Migrating from the Observable Object protocol to the Observable macro](https://developer.apple.com/documentation/swiftui/migrating-from-the-observable-object-protocol-to-the-observable-macro)

Read [State with Complex data type](#state-with-complex-data-type) first to understand why StateObject is used.

In summary, @StateObject is used to monitor **changes of the attributes of a class.**. So that even the class variable itself is not changing due to its reference property, we can still know we should update the view in reflect of the changes of its attributes. 

**So StateObject is an observer, but @ObservedObject is an observer to class attribute changes as well.**

The difference is as follow:

`@StateObject`: A property wrapper type that **instantiates** an observable object.

`@ObservedObject`: A property wrapper that does **basically** the same as `@StateObject`. However, when the view is recreated for some reason (parent rerendering), it will be recreated. Therefore, it **CAN NOT** be used a the source of truth. 

```swift
final class CounterViewModel: ObservableObject {
    @Published var count = 0

    func incrementCounter() {
        count += 1
    }
}

struct CounterView: View {
    @ObservedObject var viewModel = CounterViewModel()

    var body: some View {
        VStack {
            Text("Count is: \(viewModel.count)")
            Button("Increment Counter") {
                viewModel.incrementCounter()
            }
        }
    }
}

struct RandomNumberView: View {
    @State var randomNumber = 0

    var body: some View {
        VStack {
            Text("Random number is: \(randomNumber)")
            Button("Randomize number") {
                randomNumber = (0..<1000).randomElement()!
            }
        }.padding(.bottom)
        
        CounterView()
    }
}
```

When the `randomNumber` causes the View to redraw, subView `CounterView` will re-draw as well causing the ObservedObject `viewModel` to be re-instantiate. This is not expected. `@StateObject` is indeed needed in this time.

**Due to the property of `@ObservedObject`, it is used in a subView, while the parent view uses `@StateObject` that acts as the single source of truth.**

In summary, `@ObservedObject` is like the `props` of React, where `@StateObject` is `useState`. Props allows the subView to have a reference to the state. or in another words, `@ObservedObject` is the same as `@Binding` in terms of usage.

### [@EnvironmentObject](https://www.hackingwithswift.com/quick-start/swiftui/how-to-use-environmentobject-to-share-data-between-views)

> [Migrating from the Observable Object protocol to the Observable macro](https://developer.apple.com/documentation/swiftui/migrating-from-the-observable-object-protocol-to-the-observable-macro)

No matter of @State of @StateObject, we're using prop drilling that passes states down the view hierarchy one level after another. This is cumbersome if we have a huge hierarchy. Therefore, @EnvironmentObject is the same as `Context` of React, that allows to read all the contexts set by the parent view.

The usage is as follows, the parent view uses `.environment()` view modifier to provide @StateObjects as context to **ALL** children views.

Any children views can use `@EnvironmentObject` to access the context without passing the states around.

```swift
struct ContentView: View {
    @StateObject var settings = GameSettings()

    var body: some View {
        NavigationStack {
            ...
        }
        .environmentObject(settings)
    }
}

// Our observable object class
class GameSettings: ObservableObject {
    @Published var score = 0
}

// A view that expects to find a GameSettings object
// in the environment, and shows its score.
struct ScoreView: View {
    @EnvironmentObject var settings: GameSettings

    var body: some View {
        Text("Score: \(settings.score)")
    }
}
```


Here, I'll only discuss the usage of using `StateObject` and `EnvironmentObject` together. In the following code, we use instantiate a StateObject then pass it to the Environment so that subViews can declare variable with `@EnvironmentObject` wrapper can gain access to this EnvVariable. The question is that why bother creating a `StateObject` in the first place rather than passing `ModelData()` directly to the `.environmentObject` modifier?

```swift
@main
struct LandmarksApp: App {
    // Mark it as StateObject so that ModelData is instantiate here once.
    // So that subViews don't have to instantiate modelData themselves as
    // if such each time we enter the subView, an instance is created.
    @StateObject private var modelData = ModelData()
    
    var body: some Scene {
        WindowGroup {
            LandmarkListView()
                .environmentObject(modelData)
        }
    }
}
```

The reason for this that in subViews, the variable is accessed through `@EnvironmentObject` which is similar to `@ObservableObject` doesn't handle instantiation. Hence, by passing `ModelData()` as the argument, we instantiate a modelData each time we enter `LandmarkListView()`. This is typically not what we want. 


### [Migrating from the Observable Object protocol to the Observable macro](https://developer.apple.com/documentation/swiftui/migrating-from-the-observable-object-protocol-to-the-observable-macro)

With the basic idea of what `ObservableObject`, `@StateObject`, `@EnvironmentObject` are, we should now NOT be using them but use `@Observable`, and `@State` only.


## [LazyVGrid](https://www.youtube.com/watch?v=vHvb7LH8VuE)

It's very useful that LazyGrids offers pinedView option that allows the header of sections to be pinned when the user is within that particular section.

> It's very odd that the section defined in the body of a grid, instead of having the grid defined within the section body.

## NavigationStack

Unlike normal NavigationView which is deprecated already and is view based, NavigationStack is data based. That each navigation view is designed to handle 1 specific data type. So that the same data type will be handled the same.

This is done by using `navigationDestination` modifier, inside which is the navigate-to view and `for` specifies the data type it handles. `NavigationLink` is a button that accepts value as input to the navigate-to view. It's `value` will be used to match the `for` in navigationDestination.

```swift
NavigationStack {
    List(parks) { park in
        NavigationLink(park.name, value: park)
    }
    .navigationDestination(for: Park.self) { park in
        ParkDetails(park: park)
    }
}
```

With the above being said. Without `navigationDestination`, NavigationLink is no use.

The benefit of use data based navigation is that we can programmatically add new paths by having a **path state**. 

The following 1mins of the video gives a quick overview of [NavigationStack](https://youtu.be/oxp8Qqwr4AY?t=485)

## SafeArea

All the views are within the same area by default. However, for backgrounds, we may want them to extend the whole screen by using `ignoresSafeArea`. 

The trick can be typically used is to have a color as background and using `ZSTACK`, a demo can be found in [this video](https://youtu.be/_0NDKxvfg40?list=PLwvDm4VfkdphqETTBf-DdjCoAvhai1QpO&t=503). As well as using background is recommended. (`background` is just another view)


## Animation and Transition

Transitions are used for mounting on/off animations while Animations are used when stateful properties are changed.

## [Difference between ZStack vs Background/Overlay](https://stackoverflow.com/questions/63446213/difference-between-a-zstack-or-using-overlay)



## Edit Mode

To avoid updating the global app state before confirming any edits — such as while the user enters their name — **the editing view operates on a copy of itself.**

## MVVM

In React development, we often add functions inside a view so that even the data manipulation logics are also declared within the same functional component. In MVVM design pattern, we have separate files for 

1. Model: That only stores the data definition.
2. View: The UI definition as well as additional functions that are specific only for UI rendering.
3. ViewModel: An intermediate layer between View and Model, that delegates all Model logics.

The benefit of this approach is that ViewModel defined as a class, can be easily mocked for unit testing.
Also, normally a view may be interacting with multiple models. Using the ViewModel intermediate layer, we can encapsulate all models inside the ViewModel, while only exposing the ViewModel itself to the view.


```swift
class Model {
    ...
}

class AnotherModel {
    ...
}

@Observable
class ViewModel {
    var model: Model()
    var anotherModel: AnotherModel()

    func getModelCount() -> Int {
        ...
    }
    ...
}

struct MyView: View {
    @State vm: ViewModel
    
    var body: some View {
        ...
    }
}
```

## [Documentations](https://www.youtube.com/watch?v=O8_meC7hIwI)


## Safe Coding

`if let & guard`
    

## Swift

## HowTo

##### How to get the dimension of current view

1. [GeometryReader](https://developer.apple.com/documentation/swiftui/geometryreader) can be used to determine the dimension of current view. It's container that wraps children view while providing dimension information (width and height) that childView can access.

```swift
struct ContentView: View {
    var body: some View {
        GeometryReader { geometry in
            Text("Viewport width: \(geometry.size.width)")
        }
    }
}
```

##### [How to draw a rounded border for a view](https://www.appcoda.com/swiftui-border/)



#### [How to inject view into a parent view](https://stackoverflow.com/questions/67488568/inject-a-view-into-a-view-in-swiftui)



##### [How to solve the flicking shadow when using contextMenu](https://stackoverflow.com/questions/65492918/swiftui-shadow-glitch-after-context-menu)