FRAMEWORK: https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Client-side_JavaScript_frameworks

# Questions

## HTML

1. The difference between HTTP `GET` and `POST` [->Ref](#get-and-post)

2. How to include Jquery in another JS file?
   - Solve: In the html file, use `script` tag to include the Jquery file before including your JS file. [->Ref](https://stackoverflow.com/questions/17921187/using-jquery-in-a-js-file)
   ```html
   <script src="js/jquery.js"></script>
   <script src="js/main.js"></script>
   ```

---

## CSS

1. All pseudo-classes and pseudo-elements [->Ref](https://www.w3schools.com/css/css_pseudo_elements.asp)

2. [How to center elements?](/FrontEnd/Css/cssNotes.md#center)

3. How to make a responsive table with a scroll bar (scroll bar for table not for the page) [->Ref](/FrontEnd/Css/cssNotes.md#make-a-scroll-bar-for-table)

4. Why paragraph(block) after the div container (block) that contains floating elements would appear by the side of the floating elements? [->Ref](/FrontEnd/Css/cssNotes.md#float-gotcha)
<iframe src="/FrontEnd/Css/cssSamples/float3.html"></iframe>

5. why `vertical-align` is not working, how to align elements vertically in the center [->Ref](https://stackoverflow.com/questions/79461/how-can-i-vertically-align-elements-in-a-div)

6. Why size of pixel defined in css is different from actual size of pixel of the screen? [->Ref](/FrontEnd/html/htmlNotes?id=viewport)

   - Pixels (px) are relative to the viewing device. For low-dpi devices, 1px is one device pixel (dot) of the display. For printers and high resolution screens 1px implies multiple device pixels.

7. What's the difference between `background-origin` and `background-clip`?

   - The `background-origin` property specifies the origin position of a background image, which means the upper left corner of the image can be positioned at `padding-box`(The upper left corner of the padding edge), `border-box` (the upper left corner of the border edge), `content-box`(...)
   - The `background-clip` property specifies the **display area**, meaning the background image is still positioned at specified upper left corner, but only certain area is displayed. In this [example](https://www.w3schools.com/css/tryit.asp?filename=trycss3_background-clip), all images are positioned the same, but only the display areas differ.
   - Related topic can be found [here](/FrontEnd/Css/cssNotes.md#make-a-background-image-for-the-page)

8. How to add same onclick event to all elements in the same class?
   - You can use for loop to add onclick event to each element of that class.
   - You can also use Jquery to simplify to code.
   - [->Ref](https://stackoverflow.com/questions/4588759/how-do-you-set-a-javascript-onclick-event-to-a-class-with-css)

---

## JS

1. [What's the difference between `let`, `var` and `const`?](/FrontEnd/Js/jsNotes.md#difference-between-let-var-const-bare)
2. [Why variables can be used before declaration?](/FrontEnd/Js/jsNotes.md#hoisting)
3. [What is `this`?](/FrontEnd/Js/jsNotes.md#this)
4. [What's the back-tick](/FrontEnd/Js/jsNotes.md#string-template)
5. [What's the difference between null and undefined](https://www.geeksforgeeks.org/undefined-vs-null-in-javascript/)
6. [Is JS pass by value?](/FrontEnd/Js/jsNotes.md#pass-by-sharing)
7. [What's the difference between map and object](https://www.geeksforgeeks.org/map-vs-object-in-javascript/)
8. [How to define read only property?](https://stackoverflow.com/questions/7757337/defining-read-only-properties-in-javascript)
9. [How to get a computed property name](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/get#using_a_computed_property_name)
10. [What is prototype and prototype chain in JS](/FrontEnd/Js/jsNotes.md#prototype)
11. [What is class fields](/FrontEnd/Js/jsNotes.md#class-fields)
12. [Why does console.log(this) in node return an empty object?](https://stackoverflow.com/questions/42631698/why-does-console-logthis-in-node-return-an-empty-object)
13. [What are species in JS](#TODO)
14. [https://stackoverflow.com/questions/650764/how-does-proto-differ-from-constructor-prototype](/FrontEnd/Js/jsNotes.md#prototype-with-constructor)
15. [How to make sure the order when including multiple external JS files?](/FrontEnd/Js/jsNotes.md#script-loading-strategies)
16. [How to create an abstract base class](https://stackoverflow.com/questions/597769/how-do-i-create-an-abstract-base-class-in-javascript)
17. [What is User Agent](https://developer.mozilla.org/en-US/docs/Glossary/User_agent)
18. [How to edit js code in browser](https://stackoverflow.com/questions/16494237/chrome-dev-tools-modify-javascript-and-reload)
19. [What is closure](/FrontEnd/Js/jsNotes.md#closure)
20. [How to force focus on a element](https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Client-side_JavaScript_frameworks/React_accessibility#prepare_the_heading)

---

## AppDev

1. How to make an adaptive input filed that adjust height automatically?
   - `<input type="text">` is designed to accept input in a row, and will shift input accordingly when overflows.
   - Use [`<textarea>`](https://www.w3schools.com/tags/tag_textarea.asp) instead.
     ```js
     // rows is set to 1 to adjust the height of the textarea.
     <textarea id="inputField" rows=1 placeholder="Enter your message here"></textarea>
     ```
   - Use JS to dynamically adjust height.
     - `addEventListener`
     1. [textarea 内容自动撑开高度，实现高度自适应](https://cloud.tencent.com/developer/article/1840701)
     2. [Creating a textarea with auto-resize](https://stackoverflow.com/questions/454202/creating-a-textarea-with-auto-resize)

## React

1. [How can I transition height: 0; to height: auto; using CSS?](https://stackoverflow.com/questions/3508605/how-can-i-transition-height-0-to-height-auto-using-css)

## Misc

1. What is `npm` or `yarn`?
   `npm` is a package manager tool. There's a also a package registry, that is the central place (server) where a package manager tool downloads all the packages from, named the same.

`yarn` is also a package manager tool.

> Since `yarn` is package manager tools, and `npm` is a package registry, it's possible that we use `yarn` as tool and `npm` registry running behind.
