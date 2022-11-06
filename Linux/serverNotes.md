## Questions:
1. [What is CGI?](#what-is-cgi)
2. [What exactly is Apache?](#what-is-apache)
3. [What's node.js server and how's it different from Apache](#is-nodejs-a-server)

#### What is CGI (Common Gateway Interface) [->Ref](https://zhuanlan.zhihu.com/p/246268005) :id=what-is-cgi

CGI is a standard method used to generate dynamic content on web pages. CGI stands for Common Gateway Interface and provides an interface between the HTTP server and **programs generating web content**. These programs are better known as CGI scripts. They are written in a scripting language. The Network Component provides such a scripting language. The HTTP server processes the script source file line by line and calls the CGI functions as needed. The output from a CGI function is sent to the web client (browser) as a part of the web page.

ps: CGI programs are like c programms, CGI script are like php and python. For better understanding, please combine this section with [Difference between node.js and Apache](#is-nodejs-a-server-what39s-the-difference-between-it-and-apache).

```plantuml
@startuml
Browser -> Server : Request Forms
note right of Browser : The request is a URL like\nwww.google.com/scriptName?num1=10&num2=20\nwhere scriptName is the CGI program to run and num1 and num2 are the variables to pass in.

Server -> CGI_Program : Parse and Process the requests

CGI_Program -> Server : Return the processed conntent in stardard out.

Server -> Browser : Return the content
@enduml
```

To better demonstrate, here's the code written myself in the `webDev` project.

```html
<!-- index.html -->
    <body>
        <form action="usr.php" method="post">
            <div class="imgcontainer">
                <img src="./assets/avatar.png" alt="Avatar" class="avatar">
            </div>
            <div class="login_container">
                <label for="usrname"><b>用户名</b></label>
                <input type="text" name="usrname" placeholder="Enter UserName" required>
                 <button type="submit" class="login_button">Login</button>
            </div>
        </form>
    </body>
```

```php
// usr.php
<?php
include 'valid_usrs.php';

session_start();

function redirect($page) {
    header("Location: " . $page);
    exit;
}

if(!isset($_SESSION['UserName'])) {
    if (isset($_POST['usrname'])) {
        if ($_POST['usrname'] == "Buyer") {
            redirect("buyer.php");
        }
        if(!in_array($_POST['usrname'], $valid_names)) {
            redirect("index.html");

        } else {
            $_SESSION['UserName'] = $_POST['usrname'];
        }
    }
}
?>
// Everything Above is the CGI Script/Program, and everything below is the content CGI Script/Program returns
<DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <title></title>
        <script src="./js/jquery-3.6.0.js"></script>
        <script src="./js/usr.js"></script>
        <link rel="stylesheet" href="./css/fontawesome/all.css">
        <link rel="stylesheet" href="./css/usr.css">

    </head>
    ....
```

#### What exactly is Apache? [->Ref](https://www.nginx.com/blog/nginx-vs-apache-our-view/) :id=what-is-apache

Apache is a **Web Server Software**, which means, it's only a program running on a `server`, where server here refers the actual hardware. It's the same program I ever wrote in CS241.
The basic logic it runs is that it create a process/thread for each connection, and invoke the CGI according to the request or html file if the request is static.

#### Is node.js a server? What's the difference between it and Apache? [>Ref](https://stackoverflow.com/questions/38821947/how-does-a-node-js-server-compare-with-nginx-or-apache-servers) :id=is-nodejs-a-server

1. node.js is the runtime environment to run javaScript on a server. Therefore, with node.js, javaScript now can create, open, read, write, delete, and close files on the server. Therefore make it much it much like backend language as C or java. Because now node.js is capable of doing these sysem programming, you can also write a server using it, using `listen`. 

2. You can definitely write a node.js server, listening to a port and process the request. Now, your'll write code that will play **both the role of a server and CGI**. However, that's normally not the case in production. [当然你在你的服务器上直勾勾挂个 Node.js 监听 80 端口对外也不是不可以。但是通常真正线上（个人玩具除外）的做法是，Node.js 监听本地的某个端口，然后前面挂个 Nginx 监听 80 端口反向代理到 Node.js 上](https://www.zhihu.com/question/57688289). 

The `Ref` also notified that:

?>Then some developers started simply using HTTP as their app->server protocol. In effect, the app is also an HTTP server. The advantage of this is that you don't need to implement any new, possibly buggy, possibly not tested protocol and you can debug your app directly using a web browser (or also commonly, curl). And you don't need a modified web server to support your app, just any web server that can do reverse proxying or redirects.

---
## Notes

### Build FTP server [->Ref](https://help.aliyun.com/document_detail/60152.html)