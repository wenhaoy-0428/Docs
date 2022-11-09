## Questions

1. How to mock a static method? [->Ref](https://stackoverflow.com/questions/51757105/googletest-mock-c-singleton) [->Ref](https://stackoverflow.com/questions/9191530/how-to-unit-test-singleton-class-c)

2. How to mock a static method or free function? [->Ref](http://google.github.io/googletest/gmock_cook_book.html#mocking-free-functions)

// TODO: [Best GMOCK Tutorial](https://www.youtube.com/watch?v=vxCH4AuVRgo)

<iframe width="560" height="500" src="https://www.youtube.com/embed/vxCH4AuVRgo" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

3. How to mock a method with optional parameter? [->Ref](https://stackoverflow.com/questions/38500334/how-to-mock-method-with-optional-parameter-in-google-mock)

## Basics

1. It's important to know that in the design pattern of using gMock, the mocked object should be the member variable of the test target.

2. The mocked methods must also be `virtual`.

3. For non-virtual methods, direct mock is ok, but polymorphism can't be used.

4. For a better design to solve the problem in `3.` is to use `template`. Definition and Implementation of Template should all be in a header file. Refer to [Template](/cpp/cppNotes#template) in cpp notes to avoid traps.

