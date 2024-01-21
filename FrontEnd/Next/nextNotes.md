# [NextJS](https://www.youtube.com/watch?v=Sklc_fQBmcs&t=139s)

`NextJS` is a framework designed for [React](/FrontEnd/React/reactNotes.md) applications. Unlike normal React app that uses `Client Side Rendering` (CSR), NextJS uses `Server Side Rendering` (SSR) and `Static Site Generation` (SSG).

Normal `CSR` sends bundled files including HTML, JS and Assets to the user, after which the browser will receive an **empty** HTML and only after `React` finishes executing the JS file will the content be properly rendered. Thus, there will be a huge bottleneck when the application is large. 

`SSR`, on the other hand, will render the HTML on the server for each request, and sends the rendered HTML to the client. Thus, the user receives a fully functional, ready-to-go HTML right away, and uses the received JS file for future interactivity. 

