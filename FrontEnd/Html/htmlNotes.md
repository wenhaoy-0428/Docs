## Basics

### rule of thumbs

1. always declare `<!DOCTYPE html>`

2. An HTML page will validate without the `<html>` and `<body>` tags, however, in older browsers things will breakdown, and omitting both of them wil crash DOM software.

3. `<header>` can be omitted, and browser will add a default one before `<body>`

4. always declare `<meta charset="UTF-8">` for the browser.

5. always declare `<html lang="en-us">` for the search engine.

### Head

1. The `<head>` element is a container for metadata (data about data).<br>
The following elements can be declared inside `<head>`:
    * `<title>`: defines the title of the document. The title must be text-only, and it is shown in the browser's title bar or in the page's tab.
        - defines a title in the browser toolbar
        - provides a title for the page when it is added to favorites
        - displays a title for the page in **search engine**-results
    * `<style>`
    * `<link>`: defines the relationship between the current document and an external resource.
    * `<meta>`: typically used to specify the character set, page description, keywords, author of the document, and viewport settings.
        ```html
        <!-- Define the character set used: -->
        <meta charset="UTF-8">
        <!-- Define keywords for search engines: -->
        <meta name="keywords" content="HTML, CSS, JavaScript">
        <!-- Define a description of your web page: -->
        <meta name="description" content="Free Web tutorials">
        <meta name="author" content="John Doe">
        <!-- Refresh document every 30 seconds -->
        <meta http-equiv="refresh" content="30">
        <!-- Setting the viewport to make your website look good on all devices: -->
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        ```
    * `<script>`
    * `<base>`: specifies the base URL and/or target for all relative URLs in a page.

2. Viewport is the user's visible area of a web page on device.<br>
For a better understanding, detail explaination can be found [here](#viewport)
`width=device-width`: sets the page width to follow the screen-width of the device
`initial-scale=1.0`: sets initial zoom level when the page is first loaded by the browser
    ```html 
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    ```


### Links

1. How the linked page will be opened can be defined using `taget` attribute in `<a>`.<br>
The target attribute can have one of the following values:
    * `_self` - Default. Opens the document in the same window/tab as it was clicked
    * `_blank` - Opens the document in a new window or tab
    * `_parent` - Opens the document in the parent frame
    * `_top` - Opens the document in the full body of the window

2. Use mailto: inside the href attribute to create a link that opens the user's email program (to let them send a new email)

    ```html
    <a href="mailto:someone@example.com">Send email</a>
    ```

3. Button to link

    ```html
    <button onclick="document.location='default.asp'">HTML Tutorial</button>
    ```

4. You can jump to a specific part of a page, by adding `id`.

    ```html
    <!-- some file -->
    <h2 id="C4">Chapter 4</h2>
    <!-- another file -->
    <a href="html_demo.html#C4">Jump to Chapter 4</a>
    ```

### Image

1. The HTML `<map>` tag defines an image map. An image map is an image with clickable areas. The areas are defined with one or more `<area>` tags.
[->Ref](https://www.w3schools.com/html/html_images_imagemap.asp)

    ```html
    <!-- usemap has is the same as the name of the map below -->
    <img src="workplace.jpg" alt="Workplace" usemap="#workmap">

    <map name="workmap">
    <area shape="circle" coords="337,300,44" href="coffee.htm" onclick="myFunction()">
    </map>

    <script>
    function myFunction() {
    alert("You clicked the coffee cup!");
    }
    </script>
    ```

2.  The `<picture>` element contains one or more `<source>` elements, each referring to different images through the srcset attribute. This way the browser can choose the image that best fits the current view and/or device. Therefore, it's a good practice to achieve responsive HTML. [->Ref](https://www.w3schools.com/html/html_images_picture.asp)

    ```html
    <picture>
    <source media="(min-width: 650px)" srcset="img_food.jpg">
    <source media="(min-width: 465px)" srcset="img_car.jpg">
    <img src="img_girl.jpg">
    </picture>
    ```
?> Note: Always specify an `<img>` element as the last child element of the `<picture>` element. The `<img>` element is used by browsers that do not support the `<picture>` element, or if none of the `<source>` tags match.

### Table

1.  Browsers can use `<thead>` to enable scrolling of the table body independently of the header and footer. Also, when printing a large table that spans multiple pages, **these elements can enable the table header and footer to be printed at the top and bottom of each page.**

    ```html
    <table>
    <thead>
        <tr>
        <th>Month</th>
        <th>Savings</th>
        </tr>
    </thead>
    <tbody>
        <tr>
        <td>January</td>
        <td>$100</td>
        </tr>
        <tr>
        <td>February</td>
        <td>$80</td>
        </tr>
    </tbody>
    <tfoot>
        <tr>
        <td>Sum</td>
        <td>$180</td>
        </tr>
    </tfoot>
    </table>
    ```
2. `<colgroup>` tag specifies a group of one or more columns in a table for formatting. To define different properties to a column within a `<colgroup>`, use the `<col>` tag within the `<colgroup>` tag.

    ```html
    <table>
    <colgroup>
        <col span="2" style="background-color:red"> 
        <!-- sets the background-color of the first 2 column to red -->
        <col style="background-color:yellow">
        <!-- sets the background-color of the third colum to yellow -->
    </colgroup>
    <tr>
        <th>ISBN</th>
        <th>Title</th>
        <th>Price</th>
    </tr>
    ...
    ```
    <iframe src="/FrontEnd/Html/HtmlSamples/colgroup.html"></iframe>

3. Headers can be vertical/horizontal. They can also occupy multiple rows/cols by using `rowspan`/`colspan` respectively. [->Ref](https://www.w3schools.com/html/html_table_headers.asp)

### List

1. Description List has a term and description pair effect.

    ```html
    <dl>
    <dt>Coffee</dt>
    <dd>- black hot drink</dd>
    <dt>Milk</dt>
    <dd>- white cold drink</dd>
    </dl>
    ```
    <iframe src="/FrontEnd/Html/HtmlSamples/dl.html" name="iframe_a" height="100px" width="100%"></iframe>


### Block/Inline

1. block-level elements always starts on a new line, and take up the full width available (stretch as far as it can);<br>
inline elements are the opposite to block-level ones.<br>
    * `<div>` is commonly used for blocks.
    * `<span>` is commonly used for inline.

### Iframes

1. Iframes can be used as above, it can also be the `target` of a link.
    ```html
    <iframe src="demo_iframe.htm" name="iframe_a" title="Iframe Example"></iframe>
    <p><a href="https://www.w3schools.com" target="iframe_a">W3Schools.com</a></p>
    ```

### Semantic Elements

1. Elements that can be understood from it's name. Semantic elements make the web page more reusable and easier for disabled people.
    * `<article>`
    * `<details>`
    * `<figcaption>`
    * `<figure>`
        ```html
        <figure>
        <img src="pic_trulli.jpg" alt="Trulli">
        <figcaption>Fig1. - Trulli, Puglia, Italy.</figcaption>
        </figure>
        ```
    * [->Ref](https://www.w3schools.com/html/html5_semantic_elements.asp)


### Entities

1. special characters like `<`, `>` will be interpreted as opening tags and closing tags, therefore, we can use `entity name` or `entity number`..
    * `&entity_name;`
    * `&#entity_number;`
    * **Note: don't forget the semi colon**
    ```html
    &lt;
    &#60;
    ```

2. A commonly used entity is `&nbsp` which stand for *non-breaking space*. words on the left/right hand side of it, will not be separated by new line.

    ```html
    10&nbsp;km/h
    ```


### Responsive HTML

#### ViewPort

1. Backgrounds: There's something we need agree on first.
    1. We know that if we put a static picture onto a smaller screen, in order to maintain how this picture looks, the picture we see will be squashed.<br>
      and the size of this image will be small. The same thing happens to pages.
    2. viewport width has a default value. such as 900px as lowest and 1920 as highest.    
    3. `viewport width = Math.max(document.documentElement.clientWidth || 0, window.innerWidth || 0)`
    4. CSS pixels are different from resolutions. `CSS pixels * CSS pixel ratio = Resolution` [->Ref](https://webspeedtools.com/viewport-vs-screen-resolution-vs-dpr-vs-ppi/)

    viewport is the window that you see things through. <br>
    - **When the screen size is large enough to contain all the elements**, meaning it's larger than the widest element with fixed width, viewport width will vary with the browser size up to a limit such as 1920px. <br>
    - **When the screen size is smaller than the widest element**, viewport will shrink to a point where it's the smallest default value such as 900px, or it's tinny bit larger than the widest element if the width is larger than the default value, so that element is contained without scrollbar.

    The problem here is: When using a smaller device, the browser will render everything based on the viewport size which is larger than the device sceen size. The viewport will be squashed just like rule `#1` into the screen.
    <img src='/FrontEnd/Html/assets/viewport1.png' style="display:block" height=200px></img>

    Experiments can be done with this HTML and Chrome browser.

    <iframe src="/FrontEnd/Html/HtmlSamples/viewport.html" title="viewport experiment"></iframe>

    **In summary**, the browser will always try to fit the viewport in scale 1 into our screen, and if we change `image/div and etc.` to responsive like width 100%, then with `viewport=device-width`, viewport will always be set to the screen size, and therefore, everything looks good.

2. Text can also be set responsive by setting `font-size=Xvw` where `vw` stands for viewport width. There are also viewport units including `vw`, `vh`, `vmin(based on the smaller dimension of the viewport)`, `vmax(based on the larger dimension of the viewport)`

3. Media Queries is a more advanced technic to design responsive web page. Details can be found here [TODO]()

4. Bootstrap is a CSS framework that mostly used to build responsive web page. [TODO]()


### Form

1. `<label>` defines a label for many form elements, is useful for screen-reader users, because the screen-reader will read out loud the label when the user focus on the input element. The `for` attribute of the `<label>` tag should be equal to the id attribute of the `<input>` element to bind them together.

    ```html
    <form action="/action_page.php" target="_blank" method="post" autocomplete="on">
    <label for="fname">First name:</label><br>
    <input type="text" id="fname" value="John"><br><br>
    <input type="submit" value="Submit">
    </form>
    ```

2. The `<input type="submit">` defines a button for submitting the form data to a `form-handler`. The form-handler is [CGI(Common Gateway Interface)](/server/serverNotes#what-is-cgi)<br>
**Notice that each input field must have a name attribute to be submitted.**  **If the name attribute is omitted, the value of the input field will not be sent at all.**. In the example from the above, the `FirstName` input will not be submitted as it does't declare a name attribute.

3. Attributes:
    * `target`: specifies where to display the response that is received after submitting the form.
    * `autocomplete`: specifies whether a form should have autocomplete on or off. When autocomplete is on, the browser automatically complete values based on values that the user has entered before.
    * `novalidate`: specifies that the form-data (input) should not be validated when submitted, for example, anything can be submitted in an email input.


### HTTP Methods [->Ref](https://www.w3schools.com/tags/ref_httpmethods.asp)

#### GET and POST

1. Get Method
    * Back/Reload is harmless
    * GET requests can be cached
    * GET requests remain in the browser history
    * GET requests can be bookmarked
    * GET requests should never be used when dealing with sensitive data
    * GET requests have length restrictions
    * GET requests are only used to request data (not modify)

2. Post Method
    * Back/Reload will cause the data to be resubmitted
    * POST requests are never cached
    * POST requests do not remain in the browser history
    * POST requests cannot be bookmarked
    * POST requests have no restrictions on data length



