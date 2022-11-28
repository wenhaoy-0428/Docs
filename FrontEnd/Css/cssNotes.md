## Questions

1. [What is stack context](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Positioning/Understanding_z_index/The_stacking_context)

## Index
1. There are four different techniques to create multi-column layouts.
    * [CSS framework: BootStrap](#TODO)
    * [CSS float property](#float)
    * [CSS flexbox](#flexbox)
    * [CSS grid](#grid)


## Shorthands

Some properties like `font`, `background`, `padding`, `border`, and `margin` are called shorthand properties. This is because shorthand properties set several values in a single line.

!> One less obvious aspect of using CSS shorthand is how omitted values reset. A value not specified in CSS shorthand reverts to **its initial value**. This means an omission in CSS shorthand can override previously set values.

### [How CSS Works](https://developer.mozilla.org/en-US/docs/Learn/CSS/First_steps/How_CSS_works#how_does_css_actually_work)

![Process](./Assets/rendering.svg)




## Cascading oder

Some properties are inherited from the parent nodes, such as `color`. There are several inheritance values allowing us to control how the property works.
Refer to [Controlling inheritance](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Cascade_and_inheritance#controlling_inheritance) for better demonstration. 

Property [all](https://developer.mozilla.org/en-US/docs/Web/CSS/all) can be used to set all inherited properties at once.


The cascading order is calculated based on: 
1. Source Order: 
    1. Inline style (inside an HTML element)
    2. External and internal style sheets (in the head section), **the value from the last read style sheet will be used.**
    3. Browser default
2. [Specificity](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Cascade_and_inheritance#specificity_2)
    - [Selectors](#selector) can be classified into `ID, CLASS, ELEMENT` categories. They can be thought as a 3 digit number in which, `ID` plays as the hundreds place, and `CLASS` as the tens place, and `ELEMENT` as ones place. 
    > No matter how many `ELEMENT` specificity adds up, it can be more specific than 1 single `CLASS` specificity, same for `CLASS` to `ID`.
3. Importance: 
```css
p {
    border: none !important;
}
```

## Selector

1. Simple Selector
2. Combinator selectors
3. Pseudo-class selectors
4. Pseudo-elements selectors
5. Attribute selectors
6. Priority can be referred to [Cascading Order](#cascading-oder)


#### Selector List

We can combine multiple selector into a single list separated by `,`. 
```css
h1, .special {
  color: blue;
}
```
> Doing so makes the stylesheet more succinct but when any one of selector in the selector list becomes invalid, the whole whole selector list is ignored.

#### Simple Selector
select elements based on name, id, class

1. element selector: the selector is the element name.
    ```css
    p {
    text-align: center;
    color: red;
    }
    ``
2. id selector: the id of an element is unique within a page, so the id selector is used to select one unique element
    ```css
    #para1 {
    text-align: center;
    color: red;
    }
    ```
!> id can't start with a number

3. class selector:
    ```css
    .center {
    text-align: center;
    color: red;
    }
    ```

4. universal selector:
    ```css
    * {
    text-align: center;
    color: blue;
    }
    ```

* the precedence of selector: `id` > `class` > `element` > `universal`; The **latter** declared selectors have higher precedence: the same attributes declared within same kind selector will be overwritten by latter declared ones.

* simple selectors can be combined
    ```css
    /* element a with class highlight in hover pseudo-class state */
    a.highlight:hover {
    color: #ff0000;
    font-size: 22px;
    }
    ```

> selector.css
<iframe src="/FrontEnd/Css/CssSamples/index.html" height="40px"></iframe>

#### Combinator selectors [->Ref](https://www.w3schools.com/css/css_combinators.asp)
combinations of elements (element `?` element)

1. All have the same precedence, latter declared ones have higher precedence.


#### Pseudo-class selectors

1. A pseudo-class is used to define a special state of an element.

    ```css
    /* unvisited link */
    a:link {
    color: #FF0000;
    }
    ```
2. more example
    * matches the first `<i>` element in all `<p>` elements:
    ```css
    /* use of descendant and pseudo-class */
    p i:first-child {
    color: blue;
    }
    ```

#### Pseudo-element selectors

1. used to style specified parts of an element.

2. example
    ```css
    p::first-line {
    color: #ff0000;
    font-variant: small-caps;
    }

    h1::before {
    content: url(smiley.gif);
    }
    ```

?> All Pseudo-classes and Pseudo-elements [->Ref](https://www.w3schools.com/css/css_pseudo_elements.asp)

3. `::before` and `::after`: TODO
#### Attribute Selectors

1.  is used to select elements with a specified attribute.

2. example
    ```css
    input[type="text"] {
    width: 150px;
    display: block;
    margin-bottom: 10px;
    background-color: yellow;
    }

    input[type="button"] {
    width: 120px;
    margin-left: 35px;
    display: block;
    }
    ```
3. attributes with value starts with "a whole word" "a string"/ ends with ... [->Ref](https://www.w3schools.com/css/css_attribute_selectors.asp)

## Text

1. `text-overflow` allows us to specify the behavior when the container is not big enough to contain the texts.
    ```css
    p.test1 {
    white-space: nowrap; /* specify text to be one line only */
    width: 200px;
    border: 1px solid #000000;
    overflow: hidden;
    text-overflow: clip;
    }

    p.test2 {
    white-space: nowrap;
    width: 200px;
    border: 1px solid #000000;
    overflow: hidden;
    text-overflow: ellipsis;
    }
    ```
2. `clip` will cut the text directly, and `ellipsis` will add `...` at the end.
3. Both attributes requires `overflow` is set to `hidden`.

## Center

1. `text-align` : `left/right`, `center`, `justified` where `justified` makes sure each line is stretched so that every line has equal width just like a magazine square.

2. Setting the `width` of a **block-level** element will prevent it from stretching out to the edges of its container. Then, you can set the **margins to auto**, to horizontally center the element within its container. The element will take up the specified width, and the remaining space will be split equally between the two margins:

3. Center Vertically - Using position & transform [->Ref](#2d-transform)
    ```css
    .center {
    height: 200px;
    position: relative;
    border: 3px solid green;
    }
    .center p {
    margin: 0;
    position: absolute; /* make it relative to the body */
    top: 50%; /* top left corner vertically in the middle*/
    left: 50%; /* top left corner horizontally in the middle */
    transform: translate(-50%, -50%);
    }
    ```

4. more can be found here[->Ref](https://www.w3schools.com/css/css_align.asp)


## [CSS layer](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Cascade_and_inheritance#the_effect_of_css_location)
//TODO


## [Box Model](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/The_box_model)

Box have `block boxes` and `inline boxes`, Boxes have an `inner` display type and an `outer` display type.

**Outer display type**: Indicates how elements behave relative to other elements that are outside of the current element.
For [display: block/inline;](#display) sets the outer display attributes.

**Inner display type**:  Dictates how elements inside that box are laid out.
For [display: flex;](#flexbox) sets the inner display type, while maintaining the `block` outer display type.

Margins doesn't count into the Box size. Refer to [Box-sizing](#box-sizing) for details about how standard and alternate box model using `box-sizing: border-box`.





#### Margin Collapse

1. Top and bottom margins of elements are sometimes collapsed into a single margin that is equal to the largest of the two margins.
Check out [Mastering margin collapsing](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Box_Model/Mastering_margin_collapsing) for more details.
Check this classic [Example](https://stackoverflow.com/questions/9519841/why-does-this-css-margin-top-style-not-work)
    <iframe src="/FrontEnd/Css/CssSamples/collapse.html"></iframe>

#### Box-Sizing

1. First checkout the [Box Model](#box-model) of HTML.
2. !> `width` of element specifies the the width of the `content` only. Therefore, the total width of an element may be larger than expected.
3. `box-sizing: border-box;` makes sure the total width is `300px`, and content size will be adjusted accordingly.
    ```css
    div.ex1 {
    width: 300px;
    background-color: yellow;
    }

    div.ex2 {
    width: 300px;
    padding: 25px;
    background-color: lightblue;
    /*box-sizing: border-box;*/
    }
    ```
    <iframe src="/FrontEnd/Css/CssSamples/boxSizing.html"></iframe>

## Units

#### Percentage

When working with `percentages` as the value of a property, percentages are normally calculated against the parent element's **corresponding property**. For example, `width: 50%` represents `50%` width of the parent element. 

When [working with padding and margin](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Sizing_items_in_CSS#percentage_margins_and_padding), percentages are refer to [inline size](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Handling_different_text_directions#logical_properties_and_values) of the containing block — therefore the width when working in a horizontal language. Thus, they have equal padding all around.

#### fr

The `fr` unit distributes available space, not all space. Therefore, if one of your tracks has something large inside it, there will be less free space to share.

## Replacement elements

Images, forms, videos.. are replacement elements as CSS cannot affect the internal layout of these elements — only their position on the page amongst other elements.

For `img`, we can use `width: 100%, height: 100%` to stretch the `img` to fill the area. Or use `object-fit: cover` to manipulate how `img` is displayed in its container. 

#### [Replaced elements in layout](https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Images_media_form_elements#replaced_elements_in_layout)

However, in layout, like [grid](#grid) the img will not be stretched to fill the whole area like others do. 




## Display

1. `display: none`: The element will be hidden, and the page will be displayed as if the element is not there

2. `visibility: hidden`: The element will still take up the same space as before. The element will be hidden, but still affect the layout

3. `display: inline-block`: The difference between `inline-block` and `inline` is that the former one allows to set a width and height on the element, and top and bottom margins/paddings are respected, while the latter one doesn't. The difference between `inline-block` and `block` is that the former one does't stretch as wide as possible and add a line break after itself. Demonstration can be found here [->Ref](https://www.w3schools.com/css/tryit.asp?filename=trycss_inline-block_span1)

## Position

1. `position: static`
2. `position: relative`: is positioned relative to its **normal** position. use in combination with `left/right/top/bottom`(Other content will not be adjusted to fit into any gap left by the element.)
3. `position: absolute`: is positioned relative to the nearest positioned ancestor, if no positioned ancestor body is used as reference. *positioned ancestor stands for an ancestor with position attribute specified other than `static`*. [Example](https://www.w3schools.com/css/tryit.asp?filename=trycss_image_text_center), The absolute position frees the element from the normal flow of the text. That element is then above all other elements and **has no influence on the position of the elements within the design**. [->Ref](https://disenowebakus.net/en/position-div-css).
    <iframe src="/FrontEnd/Css/CssSamples/absolute.html"></iframe>

    * **absolutely positioned elements that have height and width set to auto are sized so as to fit their contents**[->Ref](https://stackoverflow.com/questions/31398209/does-adding-a-position-absolute-to-a-block-element-make-it-behave-like-an-inlin)
    <iframe src="/FrontEnd/Css/CssSamples/absolute1.html"></iframe>

    * absolute elements can set `left` and `right` not only by px, but by percentage, and the percentage is relative to the width of it's parent (the one with relative position).

> Refer to [containing block](https://developer.mozilla.org/en-US/docs/Web/CSS/Containing_block#identifying_the_containing_block) to find out the parent of a absolute element.


4. `position: fixed`: fixed relative to the viewport.

elements' positions are calculated as the offset from its `containing block`, refers to [ the rules of identifying the containing block](https://developer.mozilla.org/en-US/docs/Web/CSS/Containing_block#identifying_the_containing_block) for a more comprehensive understanding.


When more than one positioned elements and they start to overlap, and positioned elements later in the source order win over positioned elements earlier in the source order. Or the one with higher `z-index`
## float

1. `float: left/right/none/inherit`: The floated element is moved to the left or right and removed from normal flow, and the surrounding content floats around it.
    <iframe src="/FrontEnd/Css/CssSamples/float1.html"></iframe>
    <iframe src="/FrontEnd/Css/CssSamples/float2.html"></iframe>

2. `float` property will disregard target element's display property as always generate `display: block`, and if no `width` specified, it will only occupy space as it needs as opposed to standard block element behavior of taking up 100% width automatically. [->Ref](https://stackoverflow.com/questions/9774282/css-display-property-when-a-float-is-applied)



> While we can add a margin to the float to push the surrounding **text**(content away not element) away, we can't add a margin to the text to move it away from the float. This is because a floated element is taken out of normal flow and the boxes of the following items actually run behind the float. [->Ref](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Floats#visualizing_the_float)

Refer [Visualize formatting model](https://developer.mozilla.org/en-US/docs/Web/CSS/Visual_formatting_model#line_boxes) to better understand why only **text** are pushed away not element.


3. `clear: none/left/right/both/both/inherit`: specifies an element is pushed below a floating element when it is on the floating element's left/right/both side. For example, `clear: left` means if it's left side has a floating element, then it will be pushed blow that element.
    <iframe src="/FrontEnd/Css/CssSamples/clear.html" style="height: 200px"></iframe>

#### [Fix floating element that is larger than its container.](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Floats#the_clearfix_hack)

1. add `overflow: auto` property to its container, however, `overflow: auto` will add scroll bar when necessary.

2. Use `clearfix hack`
    ```css
    .clearfix::after {
        content: "";
        clear: both;
        display: block;
    }
    ```

This works as `::after` will insert an element after the container. If we add `content: "afterElement` we'll see such:

![clearfix1](/FrontEnd/Css/Assets/Screenshot%202022-11-28%20at%2022.18.15.png)

If we make it `block` or `clear` it won't change anything, however, a `block` with `clear` will be put underneath the float. 

3. Add new [BFC](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_Flow_Layout/Intro_to_formatting_contexts)(Block Formatting Context) to the container.
```css
display: flow-root;
```

> Add new BFC is the best modern approach without any side-effects.

#### float gotcha

1. Why paragraph is aside of floating elements? instead of below?
    * Because the div container is so thin, and floating elements overflow outside the elements, and the paragraph is actually below the div, only the texts are wrapped around.
    <iframe src="/FrontEnd/Css/CssSamples/float3.html"></iframe>
    * This is a better demonstration.
    <iframe src="/FrontEnd/Css/CssSamples/float4.html"></iframe>


## Math

1. `calc()` function performs a calculation to be used as the property value.
    ```css
    #div1 {
    position: absolute;
    left: 50px;
    width: calc(100% - 100px);
    border: 1px solid black;
    background-color: yellow;
    padding: 5px;
    }
    ```
2. `min(), max()` are also available.

## Counter

1. CSS has counter `variable` that automatically increases when certain elements is inserted.
    ```css
    body {
    counter-reset: section; /* Create a counter named section */
    }

    h2::before {
    counter-increment: section;
    content: "Section " counter(section) ": ";
    }
    ```
    In the above example, for every `h2` element, `Section #counter` will be inserted before it's content.

    `::before` can be referred here.[->Ref](#pseudo-element-selectors)

## 2D Transform

1. `translate()`: moves an element **from** its current position.
    ```css
    div {
        transform: translate(50px, 100px); /* move right by 50 px, and down by 100px */
    }
    div {
        position: absolute;
        top: 50%;
        left: 50%;
        transform: translate(-50%, -50%);
    }
    ```
    * In the second example above, `position` is set for `top & left` to be effective. `top: 50%` moves the div downwards by 50% of the viewport height, and `left:50%` moves the div rightwards by 50% of the viewport width, therefore, the upper left corner of div is now at the very center of its parent. However, the content now is not centered. This is where `transform` comes to help. `translate` moves div left(that's what minus sign means) by 50% of its **own width** and up by 50% of its **own height**. Now, div's central point is at the center.

2. `transform-origin`: specifies the origin for an element's transformations.

#### Transform gotcha
1. `transform-origin` is actually a set of transform operations

```css
transform-origin: -100% 50%;
transform: rotate(45deg);
```

is identical to 

```css
transform-origin: 0 0;
transform: translate(-100%, 50%) rotate(45deg) translate(100%, -50%); 
```

2. `transform-origin` no longer works after `translate` is ever called on the element. (I don't know why, but this is how I see). `translate` also moves the `transform-origin` the same amount from the center. Therefore, the `scale` will be originated to the upper left corner as `translate(-50%, -50%)` shifts origin 50% of width to the left and 50% of height to the top.
[->Ref](https://developer.mozilla.org/en-US/docs/Web/CSS/transform-origin)

<iframe src="/FrontEnd/Css/CssSamples/transformOrigin.html" style="height: 500px"></iframe>

## Transition

1. To create a transition effect, two factors are needed
    * The property to add effect on, that is when what property changes the effect will apply on.
    * The duration, by default it's 0s.

2. Several property can be set the same time.
    ```css
    div {
        transition: width 2s, height 2s, transform 2s;
    }
    ```
3. The `transition-timing-function: ease/linear/ease-in/ease-out/ease-in-out/cubic-bezier(n,n,n,n)` property specifies the speed curve of the transition effect.

4. Use `transition-delay` to specify that after a certain amount of time before the effect starts.

5. `all` keyword ca be used, when we want to specify the same effect on all properties. And, `all` is actually the default value, so it can be omitted.
    ```css
    transition: all 1s ease-in;
    transition: 1s ease-in; /* the effect is the same as above*/
    ```


## Animations

1. To create an animation on an element.
    1. first use `@keyframes` to create animation **styles**  into which the element will change its style over time.
    2. bind the element with the animation using `animation-name` property.
    3. specify `animation-duration`, `animation-delay`. `animation-iteration-count: infinite` and etc.

    ```css
    /* The animation code */
    @keyframes example {
        from {background-color: red;}
        to {background-color: yellow;}
    }

    /* The element to apply the animation to */
    div {
        width: 100px;
        height: 100px;
        background-color: red;
        animation-name: example; /* Binding */
        animation-duration: 4s;
    }
    ```
2. `from` & `to` can be replaced by percentage to add more styles.
    ```css
    @keyframes example {
        0%   {background-color:red; left:0px; top:0px;}
        25%  {background-color:yellow; left:200px; top:0px;}
        50%  {background-color:blue; left:200px; top:200px;}
        75%  {background-color:green; left:0px; top:200px;}
        100% {background-color:red; left:0px; top:0px;}
    }
    ```

3. `animation-delay` can be set to negative, e.g. `2s`, which means the animation will start playing as if it has already played for 2seconds, and the first 2seconds are cut.

4. `animation-direction` property specifies whether an animation should be played forwards, backwards or in alternate cycles, where `alternate` means the animation is played forwards first, then backwards, which requires the `animation-iteration-count` to be at least 2.

5. `animation-fill-mode` specifies what the element will look like before and after the animations, which will overrides the predefined behaviors.
    ```css
    div {
    width: 100px;
    height: 100px;
    background: red; /* This will be override */
    position: relative;
    animation-name: example;
    animation-duration: 3s;
    animation-delay: 2s;
    animation-fill-mode: backwards;
    }

    @keyframes example {
    from {top: 0px; background-color: yellow;} /* element will be yellow before starts and be red after ends */
    to {top: 200px;}
    }
    ```
6. animations are applied once element is shown or the name of the animation is added to the element.

6. Example
    <iframe src="/FrontEnd/Css/CssSamples/animation.html" width=1px></iframe>
## StyleImage

1. `filter` can be applied on images. [->Ref](https://www.w3schools.com/cssref/css3_pr_filter.asp)
    ```css
    .blur {filter: blur(4px);}
    .brightness {filter: brightness(250%);}
    .contrast {filter: contrast(180%);}
    .grayscale {filter: grayscale(100%);}
    .huerotate {filter: hue-rotate(180deg);}
    .invert {filter: invert(100%);}
    .opacity {filter: opacity(50%);}
    .saturate {filter: saturate(7);}
    .sepia {filter: sepia(100%);}
    .shadow {filter: drop-shadow(8px 8px 10px green);}
    ```

## Variable

1. CSS variables have access to the DOM, which means that you can create variables with local or global scope, change the variables with JavaScript, and change the variables based on media queries.

2. The `var(--name, value)` function is used to insert css values, where the **name has to be started with two dashes** and is required and case sensitive, and `value` is a fallback value in case the variable is undefined. 

3. Scope
    * To create a variable with global scope, declare it inside the `:root` selector. The :root selector matches the document's root element.
    * To create a variable with local scope, declare it inside the selector that is going to use it.

    ```css
    /* global scope */
    :root {
    --blue: #1e90ff;
    --white: #ffffff; 
    }
    body { 
        --green: green;
        background-color: var(--blue); 
        /* local scope */
        color: var(--green);
    }

    h2 { border-bottom: 2px solid var(--blue); }
    ```
4. Local variables will override global variables if same names are given.

5. Use JS to get variable value and set variable value.
    ```html
    <script>
    // Get the root element
    var r = document.querySelector(':root');

    // Create a function for getting a variable value
    function myFunction_get() {
    // Get the styles (properties and values) for the root
    var rs = getComputedStyle(r);
    // Alert the value of the --blue variable
    alert("The value of --blue is: " + rs.getPropertyValue('--blue'));
    }
    // Create a function for setting a variable value
    function myFunction_set() {
    // Set the value of variable --blue to another value (in this case "lightblue")
    r.style.setProperty('--blue', 'lightblue');
    }
    </script>
    ```js

6. It's also convenient to change the appearance using `variable` in combination with [media](#media)
    ```css
    @media screen and (min-width: 450px) {
    .container {
        --fontsize: 50px;
    }
    :root {
        --blue: lightblue;
    }
    }
    ```

7. variables defined in parent elements will also be accessible by child elements.

## Media-Query

1. Background: 
    * The `@media` rule, introduced in CSS2, made it possible to define different style rules for different media types. 
    * Media queries in CSS3 extended the CSS2 media types idea: Instead of looking for a type of device, they look at the capability of the device, such as width, orientation of the device.

2. Syntax: `mediatype` is optional if neither `not` nor `only` is used, and `all` is implied.
    ```css
    @media not|only mediatype and (expressions) {
        CSS-Code;
    }
    ```

3. The result of the query is true if the specified **media type matches the type of device** the document is being displayed on and **all expressions** in the media query are true. When a media query is true, the corresponding style sheet or style rules are applied, following the normal cascading rules.

4. style sheet can also be used depending on media queries.
    ```html
    <link rel="stylesheet" media="mediatype and|not|only (expressions)" href="print.css">
    ```

5. Example:
    ```css
    /* When the width is between 600px and 900px OR above 1100px - change the appearance of <div> */
    @media screen and (max-width: 900px) and (min-width: 600px), (min-width: 1100px) {
        div.example {
            font-size: 50px;
            padding: 50px;
            border: 8px solid black;
            background: yellow;
        }
    }
    ```

## [FlexBox](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Flexbox#why_flexbox)

The Flexible Box Layout Module, makes it easier to design flexible responsive layout structure **in 1 dimension**, either  either as a row or as a column, without using float or positioning

    <iframe src="/FrontEnd/Css/CssSamples/flex.html" height="200px"></iframe>

    > Removing flex in the above example will cause top margin of the items to [collapse](#margin-collapse) with the container.

The direct child elements of a flex container automatically becomes flexible (flex) items.

#### Property Methods

[justify-content](https://www.w3schools.com/css/css3_flexbox_container.asp#justify-content) specifies the flex items along the main axis.

[align-items](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Flexbox#horizontal_and_vertical_alignment) species the flex items on the cross axis. `baseline` is an interesting attribute.

`align-self` can be used to override `align-items` for individual flex items.

[align-content](https://www.w3schools.com/css/css3_flexbox_container.asp#align-content) species vertically alignment of flex lines, which flex lines are each horizontal line when flex wraps.

5. //TODO: Perfect Center

It's really powerful to use FlexBox in combination with [Media Queries](#media-query) to create a responsive web page.
    * One way of doing this is change row flex to colum flex when needed.
    ```css
    .flex-container {
        display: flex;
        flex-direction: row;
    }

    /* Responsive layout - makes a one column layout instead of a two-column layout */
    @media (max-width: 800px) {
        .flex-container {
            flex-direction: column;
        }
    }
    ```
    * Another way of doing this is using percentages.
    ```css
    .flex-container {
        display: flex;
        flex-wrap: wrap;
    }

    .flex-item-left {
        flex: 50%;
    }

    .flex-item-right {
        flex: 50%;
    }

    /* Responsive layout - makes a one column layout instead of a two-column layout */
    @media (max-width: 800px) {
        .flex-item-right, .flex-item-left {
            flex: 100%;
        }
    }
    ```





## Grid

1. While [flexbox](#flexbox) is designed for one-dimensional layout, Grid Layout is designed for two dimensions — lining things up in rows and columns.The CSS Grid Layout Module offers a grid-based layout system, with rows and columns, making it easier to design web pages without having to use floats and positioning.

2. An HTML element becomes a grid container when its display property is set to grid or inline-grid. All **direct** children of the grid container automatically become grid items.

3. `grid-template-columns: auto auto auto;` specifies how many columns are used, `grid-column-start: 1; *end: 3` specifies the grid item starts from index 1 inclusive to index 3 inclusive, with starting index 1.

    <iframe src="/FrontEnd/Css/CssSamples/grid.html" height="200px"></iframe>

```css
.container {
  display: grid;
  grid-template-columns: repeat(3, 1fr); 
  /* same as 1fr 1fr 1fr */
  gap: 20px;
}
```

> `repeat()` can be used to reduce the amount of code.

#### [Use gird-row to rearrange grid item](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Grids#line-based_placement)
Order of grid item by default is the order the item is defined, but it can also be reordered by `grip-row`, `grid-col`. The `grid-row property` is a shorthand property for the `grid-row-start` and the `grid-row-end` properties



#### [Positioning with grid-template-areas](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Grids#positioning_with_grid-template-areas)

Another way to rearrange items is to use `grid-area` in the container and 

```css
.container {
  display: grid;
  grid-template-areas:
    "header header"
    "sidebar content"
    "footer footer";
  grid-template-columns: 1fr 3fr;
  gap: 20px;
}

header {
  grid-area: header;
}
```

The cons of this is that:

- You need to have every cell of the grid filled.
- To span across two cells, repeat the name.
- To leave a cell empty, use a . (period).
- Areas must be rectangular — for example, you can't have an L-shaped area.
- Areas can't be repeated in different locations.


`grid-area` can also be used in grid item directly:

`grid-area: 2 / 1 / span 2 / span 3;` states: start on row-line 2 and column-line 1, and span 2 rows and 3 columns:

The grid-area property can also be used to assign names to grid items. Where a period sign represents a grid item with no name. Each row is defined by apostrophes (' ')

    <iframe src="/FrontEnd/Css/CssSamples/gridArea.html" height="200px"></iframe>

#### Gap

The `gap` properties (`column-gap`, `row-gap` and `gap`) used to be prefixed by `grid-`, but this has been changed in the spec in order to make them usable in multiple layout methods. The prefixed versions will be maintained as an alias, so they'll be safe to use for some time. To be on the safe side, you could double up and add both properties to make your code more bulletproof

#### [The implicit and explicit grid](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Grids#the_implicit_and_explicit_grid)

`grid-template-columns` specifies the size of column tracks and is the `explicit` grid in this example. The rows are `implicit` grids as they expand automatically to accommodate their content. If you wish to give implicit grid tracks a size, you can use the `grid-auto-rows` and `grid-auto-columns` properties

```css
.container {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  grid-auto-rows: 100px;
  /* grid-auto-rows: minmax(100px, auto); */
  gap: 20px;
}
```

> [minmax()](https://developer.mozilla.org/en-US/docs/Web/CSS/minmax) can be used to specify the min and max size for a grid. Thus, it can expand when necessary.

#### [Fit most columns automatically](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Grids#as_many_columns_as_will_fit)

Use the `repeat()` and `minmax()` mentioned above, we can achieve to adjust the number of columns accordingly.

```css
.container {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
  grid-auto-rows: minmax(100px, auto);
  gap: 20px;
}
```

#### [Grid frameworks in CSS Grid](https://developer.mozilla.org/en-US/docs/Learn/CSS/CSS_layout/Grids#grid_frameworks_in_css_grid)

--- 


## Technics

### Make a scroll bar for table

Add a container element (like `<div>`) with overflow-x:auto around the `<table>` element to make it responsive:

<iframe src="/FrontEnd/Css/CssSamples/responsiveTable.html" width=1px></iframe>

### Make floating elements not just side by side, but with equal hight  [->Ref](https://www.w3schools.com/css/tryit.asp?filename=trycss_float_boxes_flex)

1. using Fixed height.

2. using flexBox [->Ref](TODO);

### specify css for different screen size

1. use [media](#media) and `screen` which specifies that for screen size smaller than 700, the width of `responsive class` is `49%`:
    ```css
    @media only screen and (max-width: 700px) {
        .responsive {
            width: 49.99999%;
            margin: 6px 0;
        }
    }
    ```

### Make a background image for the page.

``` css
html {
  background: url(img_man.jpg) no-repeat center fixed; /* When fixed is specified, no-repeat is unnecessary */ 
  /* if no fixed specified, the background image will be stretched as the page grows longer*/ 
  background-size: cover;
}
```
1. `background-repeat: no-repeat`
2. `background-position: center`: put the image in the center of html.
3. `background-attachment: fixed`: the image doesn't move as the page scrolls.
4. `background-size: cover`: scale the image to cover the whole area of html.
5. `html` element is always at least the height of the browser window.

### Use text-shadow property to create a create a plain border around some text
1. multiple shadows are used, and each one use `-1px` as shadowing to `left, top, right, bottom` by 1px accordingly.
    ```css
    h1 {
    color: coral;
    text-shadow: -1px 0 black, 0 1px black, 1px 0 black, 0 -1px black;
    }
    ```
<iframe src="/FrontEnd/Css/CssSamples/textShadow.html" height=100px></iframe>

### How to make a tooltip

1. Use `after` property with empty content to create a black square box.

2. Define the border that we are not interested in into transparent.

3. center the tooltip.

<iframe src="/FrontEnd/Css/CssSamples/tooltip.html" height=100px></iframe>

###  Image Hover Overlay

1. [->Ref](https://www.w3schools.com/css/css3_images.asp)


### User Interface

* A div element can be resizable by adding `resize: horizontal/vertical/both/none` attribute.

### How to make a circle?

* make the `border-radius:50%` with equal height and width.
    ```css
    .dot {
    height: 25px;
    width: 25px;
    background-color: #bbb;
    border-radius: 50%;
    display: inline-block;
    }
    ```