
function myFunc() {
    import('./second.mjs').then((Module)=> {
        Module.default();
    })
}


myFunc();
Module.default();


