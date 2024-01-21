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

### Stateful variables

You use the `@State` attribute to establish a source of truth for data in your app that you can modify from more than one view. SwiftUI manages the underlying storage and automatically updates views that depend on the value. This is the same as React states which is used to update UIs.

```swift
@State private var region = MKCoordinateRegion(
    center: CLLocationCoordinate2D(latitude: 34.011_286, longitude: -116.166_868),
    span: MKCoordinateSpan(latitudeDelta: 0.2, longitudeDelta: 0.2)
)
```

The view containing the `@State` property remains **immutable**. You cannot modify the `@State` property directly from within the view. Instead, you modify it indirectly by using the `$ prefix` to access a binding to the state.

By prefixing a state variable with `$`, you pass a binding, which is like a reference to the underlying value. When the user interacts with the map, the map updates the region value to match the part of the map that’s currently visible in the user interface.

### ObservableObject

Declare a new model type that conforms to the `ObservableObject` protocol from the `Combine` framework and SwiftUI subscribes to your observable object, and updates any views that need refreshing when the data changes.

An observable object needs to **publish** any changes to its data, so that its subscribers can pick up the change.

`@Published`: The @Published property wrapper is used within an ObservableObject to mark a property as observable. When a property marked with @Published changes, it triggers an update to any SwiftUI views that are observing that object. It is commonly used in conjunction with the ObservableObject protocol to create observable data models that can be shared across multiple views.

```swift
final class ModelData: ObservableObject {
    @Published var landmarks: [Landmark] = load("landmarkData.json")
}
```

### StateObject and EnvironmentObject

`@StateObject`: A property wrapper type that **instantiates** an observable object. More detail how this one is used should be referred to [SwiftUI: @State vs @StateObject vs @ObservedObject vs @EnvironmentObject](https://levelup.gitconnected.com/state-vs-stateobject-vs-observedobject-vs-environmentobject-in-swiftui-81e2913d63f9) which gives thorough and easy to understand comparison. 


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


## Edit Mode

To avoid updating the global app state before confirming any edits — such as while the user enters their name — **the editing view operates on a copy of itself.**

    

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