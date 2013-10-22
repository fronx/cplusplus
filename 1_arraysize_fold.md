<i>This file is the documentation for [1_arraysize_fold.cpp](1_arraysize_fold.cpp). It doesn't exactly go line by line, but almost. Maybe you want to [look at the program](1_arraysize_fold.cpp) before reading the explanations given here.</i>

# Array size, function templates, and something like folds

The program starts by importing `iostream`, so we can print to `stdout` via `cout`, and `numeric`, so we get the array iterator `accumulate`.

```cpp
#include <iostream>
#include <numeric>
```

Now that those libraries are included, the real journey through the world of function overloading using template functions can begin.

## Determining the size of an array

C arrays (which we're also using here even though it's C++) are really quite dumb data structures that come with no metadata, so things like the size of the array, or the type of its elements, can't be read from the memory representation at runtime. However, certain things can be known at compile time, because the compiler is a smart little (huge) thing that analyzes the code and keeps a record of all kinds of stuff it knows about your variables.

In the case of static arrays whose content is specified once and never changes, the compiler allows itself to know their size and the type of their elements. To the compiler, those two pieces of information make up the type of the array itself, such as `int a[10]` (except that `a` is just a name, but you get the idea).

If we want to know the size of an array, it seems like a rather smart idea to just ask the compiler what it is, rather than computing it somehow (e.g. by dividing the size (in bytes) of the array by the size of its first element, or by looping through the array and counting).

The way you can do that in C++ is by defining a generic function, i.e. a function that works on multiple types that either get filled in by a human programmer or by the compiler, and working with the information that's available when it matches a given function call. And here is how you do that:

```cpp
template <typename T, std::size_t Size>
std::size_t arraysize(T (&)[Size]) { return Size; }
```

And here is how it would be used (copied from the `main` function):
```cpp
int a[] = { 1, 2, 3, 4 };
std::cout << arraysize(a) // 4
```

The two lines (`template…` and `std::size_t…`) belong together, meaning, the first line defines elements that are used by the second line. (In fact, you could even remove the line break and have them as one line.)

### What is a function template?

A template defines a set of functions. You can imagine the functions living in a multi-dimensional space where each point represents a concrete function with different coordinates, or parameters. That space is defined inside of the angle brackets after the keyword `template`: `<typename T, std::size_t Size>`. What that declaration says is that our function space has two dimensions: the first one is called `T` and has the type `typename`, which means that `T` can stand for any concrete type, such as `int`, `float`, `char`, or whatever. The second dimension is called `Size` and covers all possible values of the type `std::size_t` (btw: `std` is just a namespace prefix). Let's actually draw a coordinate system, just for the purpose of better imagination:

````
o--int--float--char--...---> T (order not significant)
|
0   x     x     x
|
1   x     x     x
|
2   x     x     x
|
|
V Size

T    ∈ typename
Size ∈ std::size_t
````

Every `x` in the picture represents one concrete function. What the function template allows us to do is specify all of those functions in just one small, generic declaration, by defining the space, give the axes names, and use those names inside of the function definition.

In the source code, I've picked the name `T` for a type whose identity we don't know yet (it's a pretty common name to use), and the name `Size` for the other parameter/dimension, which has the type `std::size_t`. (That type is predefined somewhere as an `unsigned int`.) Those two template parameters are placeholders that will be filled in when the function `arraysize` gets called.

Let's move on to the function declaration (line 2) that makes use of those parameters. It consists of the following parts:
````
std::size_t      // the return type
arraysize        // the function name
(T (&)[Size])    // an anonymous function argument of yet unknown, but knowable type
{ return Size; } // the function body
````

The interesting part is the argument declaration `(T (&)[Size])`. It specifies the type of just one argument, but does it in a pretty interesting way. Let's break it down by looking at increasingly complex examples, starting with simpler alternatives that wouldn't do what we want here, but would still be valid argument declarations:

````
0. int a       // the argument has the type `int`, and we give it the name `a`

1. T a         // the argument has the type `T`, and we give it the name `a`

2. T a[]       // the argument has the type `array of T`, we give it the name `a`,
               // and we ignore the size of the array

3. T (&a)[]    // same as 2, but the argument is passed in as a reference,
               // rather than a value (which would be a copy)

4. T (&)[]     // same as 3, but we don't even bother giving the argument a name,
               // because we're not really planning on using it

5. T (&)[Size] // boom, we've arrived at our example!
               // same as 4, but now we do care about the size of the array,
               // and give it the name `Size`, so we can use it as a value in
               // the function body
````

To summarize, what does the function do? It extracts the *size* of the array argument from the *type* of the argument, gives it the name `Size`, and returns that as the result of the function. Since the type of `Size` is `std::size_t`, that's also the return type of the function.

The precondition for all this working is that the compiler has been able to match the function signature to a function call. It is possible to make the mistake and define function templates (generic functions) and function calls that don't fit together or are ambiguous, but in this example they do fit together: `T` ("any type") matches `int` ("the concrete type of integer numbers"), and the argument has an array type, so the parameter `[Size]` exists, and we've declared `Size` to have the right type for an array size by declaring its type to be `std::size_t`, so the whole argument (which was `int a[4]`) matches.

Okay, phew. That was the hardest part. The rest of the program is easy.

## Binary operations

Let's look at these generic functions:

```cpp
template <typename T>
T add (T &a, T &b) { return a + b; }

template <typename T>
T mul (T &a, T &b) { return a * b; }
```

Here is how they're used:

```cpp
int a[] = { 1, 2, 3, 4 };
add(a[2], a[3]) // 7
mul(a[1], a[2]) // 6
```

When the compiler sees a call like `add(a[2], a[3])`, it matches the types of the arguments and the name of the function to existing function signatures. In our case, the function signature for `add` is generic, parameterized by some unknown but knowable type `T`. What it says is that `add` is a function that takes two arguments that have to have the same type (`T`), and returns a value that's also of type `T`. And the way it does that is by using the `+` operator internally (`+` is itself generic).

Same for `mul`, except that it uses `*` instead of `+`.

If you were to draw a coordinate system, as above, for the dimensions of either of those functions, it would look rather boring:
````
    x     x     x
o--int--float--char--...---> T (order not significant)

T ∈ typename
````

<i>Aside: The function body implies that there is a condition suitable types have to satisfy: the operator `+` (resp. `*`) has to be defined for it. The generic function signature itself knows nothing about this, which means it may be a little too generic. I don't know if C++ supports any sort of constraints on types, which would be a solution, but I assume that being too generic does not usually lead to big problems in practice.</i>

Movin' on:

```cpp
template <typename T, std::size_t Size>
T sum (T (&a)[Size])
{
  return std::accumulate(a, a + Size, static_cast<T>(0), add<T>);
}

template <typename T, std::size_t Size>
T prod (T (&a)[Size])
{
  return std::accumulate(a, a + Size, static_cast<T>(1), mul<T>);
}
```

Here are two functions that use `add`/`mul` internally, but instead of calling it on only two arguments, they iterate over an array and call it multiple times while accumulating a result value. So `sum` returns the sum of all elements of an array, and `prod` returns the result of multiplying all elements of an array.

The way we tell the iterator function `std::accumulate` what to do is by passing the `add` (resp. `mul`) function as an argument. `std::accumulate` is the closest C++ equivalent (that I've found) to `reduce`, `inject`, or `foldl` in other languages. If you don't know folds yet, <a href="http://en.wikipedia.org/wiki/Fold_(higher-order_function)">go and read about them</a>, and then come back.

`accumulate` takes four arguments: start, end, initial value, and a binary operation. "Start" has to point to the beginning of an array, which is easily done by just giving it a reference to the whole array. "End" has to point to the end of the same array. In the implementation, we're using the same trick as in the `arraysize` function to extract the size from the type of the argument, and then add that to the "start" argument.

The initial value for addition has to be 0, because `0 + anything` is still `anything`, and it must be 1 for multiplication, because `1 * anything` is still `anything`. (Yes, it's the [identity element of a monoid](http://en.wikipedia.org/wiki/Monoid) etc…) In the code we also explicitly cast the initial value to `T` because if the concrete type is `float`, we need to use `0.0`, and if it's `int`, we need to use `0`. `static_cast<T>` does that for us.

We have to pass on the type `T` to the binary operation, as in `add<T>` and `mul<T>`, because even though we know that `accumulate` will call those functions on elements of an array whose items have the type `T`, the compiler doesn't. So we kind of help it out there and let it know that `add` and `mul` are expected to receive arguments of the same type `T` as the outer functions `sum` and `prod`. Because in theory that type could be anything; it really depends on the implementation of `accumulate`, which we can't see right here, but whatever that implementation says is not enough for the compiler to understand that relationship.

## Main

And finally, we're putting it all together into a little test program:

```cpp
int main ()
{
  int   a[] = { 1, 2, 3, 4 };
  float b[] = { 1.1, 2.5, 3.4 };
  std::cout << arraysize(a)             // 4
            << arraysize(b)             // 3
            << "\n" << mul(a[1], a[2])  // 6
            << "\n" << mul(b[1], b[2])  // 8.5
            << "\n" << sum(a)           // 10
            << "\n" << sum(b)           // 7
            << "\n" << prod(a)          // 24
            << "\n" << prod(b)          // 9.35
            << "\n"
  ;
  return 0;
}
```

The End.
