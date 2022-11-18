
FRAMEWORK: https://developer.mozilla.org/en-US/docs/Learn/Tools_and_testing/Client-side_JavaScript_frameworks


# Questions


## HTML
1. The difference between HTTP `GET` and `POST` [->Ref](#get-and-post)

2. How to include Jquery in another JS file?
    * Solve: In the html file, use `script` tag to include the Jquery file before including your JS file. [->Ref](https://stackoverflow.com/questions/17921187/using-jquery-in-a-js-file)
    ```html
    <script src="js/jquery.js"></script>
    <script src="js/main.js"></script>
    ```

---

## CSS
1. All pseudo-classes and pseudo-elements [->Ref](https://www.w3schools.com/css/css_pseudo_elements.asp)

2. [How to center elements?](/frontEnd/css/cssNotes.md#center)

3. How to make a responsive table with a scroll bar (scroll bar for table not for the page) [->Ref](/frontEnd/css/cssNotes.md#make-a-scroll-bar-for-table)

4. Why paragraph(block) after the div container (block) that contains floating elements would appear by the side of the floating elements? [->Ref](/frontEnd/css/cssNotes.md#float-gotcha)
    <iframe src="/frontEnd/css/cssSamples/float3.html"></iframe>

5. why `vertical-align` is not working, how to align elements vertically in the center [->Ref](https://stackoverflow.com/questions/79461/how-can-i-vertically-align-elements-in-a-div)

6. Why size of pixel defined in css is different from actual size of pixel of the screen? [->Ref](/frontEnd/html/htmlNotes?id=viewport)
    * Pixels (px) are relative to the viewing device. For low-dpi devices, 1px is one device pixel (dot) of the display. For printers and high resolution screens 1px implies multiple device pixels.

7. What's the difference between `background-origin` and `background-clip`?
    * The `background-origin` property specifies the origin position of a background image, which means the upper left corner of the image can be positioned at `padding-box`(The upper left corner of the padding edge), `border-box` (the upper left corner of the border edge), `content-box`(...)
    * The `background-clip` property specifies the **display area**, meaning the background image is still positioned at specified upper left corner, but only certain area is displayed. In this [example](https://www.w3schools.com/css/tryit.asp?filename=trycss3_background-clip), all images are positioned the same, but only the display areas differ.
    * Related topic can be found [here](/frontEnd/css/cssNotes.md#make-a-background-image-for-the-page)

8. How to add same onclick event to all elements in the same class?
    * You can use for loop to add onclick event to each element of that class.
    * You can also use Jquery to simplify to code.
    * [->Ref](https://stackoverflow.com/questions/4588759/how-do-you-set-a-javascript-onclick-event-to-a-class-with-css)

---

## JS

---

## AppDev

1. How to make an adaptive input filed that adjust height automatically?
   * `<input type="text">` is designed to accept input in a row, and will shift input accordingly when overflows.
   * Use [`<textarea>`](https://www.w3schools.com/tags/tag_textarea.asp) instead.
     ```js
     // rows is set to 1 to adjust the height of the textarea.
     <textarea id="inputField" rows=1 placeholder="Enter your message here"></textarea>
     ```
    * Use JS to dynamically adjust height.
      * `addEventListener`
      1. [textarea内容自动撑开高度，实现高度自适应](https://cloud.tencent.com/developer/article/1840701)
      2. [Creating a textarea with auto-resize](https://stackoverflow.com/questions/454202/creating-a-textarea-with-auto-resize)

