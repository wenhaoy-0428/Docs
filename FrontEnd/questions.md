
## CSS


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
