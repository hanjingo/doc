# Rust Language

[TOC]



## Grammar

### Variables

- immutable variable; for example:

  ```rust
  let var = ...;
  ```

- mutable variable; for example:

  ```rust
  let mut var = ...;
  ```

NOTE: 

1. We can **shadow** a variable by using the same variable's name and repeating the use of the `let` keyword as follows:

   ```rust
   let x = 1; 
   let x = x + 1; 	// correct
   let x = ""; 	// correct
   x = 1; 			// incorrect;
   ```

### Constants

Like immutable variables, `constants` are values that are bound to a name and are not allowed to change. Constants be set only to a constant expression, not the result of a value that could only be computed at runtime. For example:

```rust
const DUR: u32 = 2 * 60;
```

### Data Types

A scalar type represents a single value. Rust has four primary scalar types:

- Integer Type

  | Length | Signed  | Unsigned |
  | ------ | ------- | -------- |
  | 8bit   | `i8`    | `u8`     |
  | 16bit  | `i16`   | `u16`    |
  | 32bit  | `i32`   | `u32`    |
  | 64bit  | `i64`   | `u64`    |
  | 128bit | `i128`  | `u128`   |
  | arch   | `isize` | `usize`  |

  *The `isize` and `usize` types depend on the architecture of the computer your program is running on.*

- Floating-Point Type

  | Length | Signed | Unsigned |
  | ------ | ------ | -------- |
  | 32bit  | `f32`  | -        |
  | 64bit  | `f64`  | -        |

  *the default type is `i64`*

- Numeric Oprations Type

  ```rust
  let sum = 1 + 1; // 2, correct
  let sum = 1 - 1; // 0, correct
  let sum = 1 * 1; // 1, correct
  let sum = 1 / 1; // 1, correct
  let sum = 1 % 1; // 0, correct
  ```

- Character Type

  ```rust
      let a = 'z';
      let b: char = 'ℤ';
      let c = '😻';
  ```

- Compound Type

  `Compound types` can group multiple values into one type. Rust has two primitive compound types:

  1. Tuples

     A `tuple` is a general way of grouping together a number of values with a variety of types into one compound type. Tuplex have a fixed length: once declared, they cannot shrink in size. The usage is as follows:

     ```rust
     let a: (i32, f64, u8) = (1, 2.0, 3);
     
     let b = (1, 2.0, 3);
     let (x, y, z) = b; // x = 1, y = 2.0, z = 3
     
     let arg1 = a.0; // 1
     let arg2 = a.1; // 2.0
     let arg3 = a.2; // 3
     ```

  2. Arrays

     Unlike a tuple, every element of an array **must have the same type**. Arrays in Rust have a fixed length. The usage is as follows:

     ```rust
         let a = [1, 2, 3, 4, 5];
     
         let b: [i32; 5] = [1, 2, 3, 4, 5];
         let b = [3; 5]; // same as: let b = [3, 3, 3, 3, 3]
     
         let arg1 = a[0];  // 1
         // let arg2 = a[10]; // incorrect;
     
         fn hello() -> usize { 5 };
         let idx = hello();
         let arg3 = a[idx]; // compiles successfully. Buf if idx >= 5, panic!
     ```

NOTE:

1. Rust is a statically typed language when we convert a type to another type, we must add a type annotation; for example:

   ```rust
   let var: u32 = "123".parse().expect("invalid number");
   ```

2. If you to change the variable to a value outside the integer type range, **integer overflow** will occur, which can result in one of two behaviors:

   - debug mode: Rust includes checks for integer overflow that cause your program to `panic` at runtime.

   - release mode: Rust **does not** include checks for integer overflow that causes paics. If overflow occurs, Rust performs `two's complement wrapping`.

     In short, values greater than the maximum value the type can hold "wrap around" to the minimum of the values the type can hold. For example, in the case of a `u8`, the value 256 becomes 0, the value 257 becomes 1, and so on.

3. The default floating-point type is `f64`, because on modern CPUs, it's roughly the same speed as `f32`, but is capable of more precision. for example:

   ```rust
   let f1 = 2.0; 	   // default type f64
   let f2: f32 = 2.0; // f32
   ```

4. Rust not support `++` and `--`. for example

   ```rust
   let mut sum = 0;
   sum--; // incorrect
   sum++; // incorrect
   ```

5. A "character" isn't really a concept in Unicode, so your human intuition for what a "character" is may not match up with what a `char` in Rust. So, we suggest using UTF-8 code when typing source code.

6. The length of a tuple is variable; by contrast, the length of arrays is fixed.

### Functions

`fn <name> (<parameters>) [-> <return value>] {<body>}`

- name

- parameters

  ```rust
  fn main() { ... }
  
  fn world(a: i32) {...}
  
  fn world(a: i32, b : u32, c : f64, d: char) -> bool {...}
  ```

- body

  - **Statements** are instructions that perform some action and do not return a value

    If statements do not return values, you can't assign a `let` statement to another variable, as follows:

    ```rust
    let x = (let y = 6); // there isn't anything for x to bind to!
    ```

  - **Expressions** evaluate to a resultant value. 

    That is, expressions do not include ending semicolons. If you add a semicolon to the end of an expression, you turn it into a statement, and it will then not return a value.

    Calling a function is an expression. Calling a macro is an expression. A new scope block created with curly brackets is an expression, for example:

    ```rust
        let y = {
            let x = 3;
            x + 1 // NOTICE, there is not an ending semicolon!!!
        };
        println!("The value of y={y}"); // y=4
    ```
    
  
- return value

  ```rust
      fn hello(arg: i32) -> i32 { arg + 1 }
      let var1 = hello(5); // 6
      println!("var1={var1}");
  
      fn world(arg: i32) -> i32 { return arg + 1; }
      let var2 = world(5); // 6
      println!("var2={var2}");
  
      fn err_func(arg: i32) -> i32 { arg + 1; }
      let var3 = err_func(5); // incorrect! Nothing is returned
  ```

#### Handling Failure

```rust
std::io::stdin().read_line(&mut val).expect("Fail to read line");
```

NOTE:

1. Rust doesn't care where you define your functions, only that they're defined somewhere in a scope that can be seen by the caller.
2. Rust did not support auto return value.

### Control Flow

- if expressions

  ```rust
      let num = 3;
      if num < 5 {
          println!("num < 5");
      } else if num > 5 && num < 10 {
          println!("num > 5 && num < 10");
      } else {
          println!("num > 10")
      }
  
      if num { // incorrect! the condition isn't a bool
          println!("incorrect")
      }
  
      if num == 3 { // correct
          println!("true")
      }
  
      let ret1 = if num > 5 { true } else { false };   // correct, ret1 = false
      let ret2 = if num > 5 { true } else { "hello" }; // incorrect!
  ```
  
- loop

  ```rust
      let mut counter = 0;
      let ret = loop {
          counter += 1;
          if counter == 10 {
              break counter * 2;
          }
      };
      println!("ret = {ret}"); // 20
  
      let mut counter = 0;
      'counting: loop {
          let mut remain = 10;
          loop {
              if remain == 9 {
                  break; // quiet inner loop
              }
              if counter == 2 {
                  break 'counting; // quiet outter loop. all loops end
              }
              remain -= 1;
          }
          counter += 1;
      }
      println!("counter = {counter}"); // 2
  ```
  
- while

  ```rust
      let mut num = 3;
      while num != 0 { // 3 2 1
          println!("{num}");
          num -= 1;
      }
  ```
  
- for ... in ...

  ```rust
  
  ```

NOTE:

1. Rust will not automatically try to convert non-Boolean types to a Boolean. You must be explicit and always provide `if` with a Boolean as its condition.

### Ownership And Lifespan

### Enums

### Match

### Error Handling

### Concurrency

### OOP

#### Structs

---



## Std

### IO

```rust
use std::io
```

stdin()

```rust
let mut var = String::new();
std::io::stdin().read_line(&mut var);
```

### cmp



---



## 3rd party



---



## Compile and Build

### Project Heritage

### Cargo cmd

| Cargo cmd | option               | example                                      |
| --------- | -------------------- | -------------------------------------------- |
| new       |                      | cargo new hello                              |
| update    |                      | cargo update                                 |
| build     | --debug<br>--release | cargo build --debug<br>cargo build --release |
| run       |                      |                                              |
| doc       | --open               | cargo doc --open                             |

### Cargo config

Include external dependency (when we include an external dependency, Cargo fetches the latest versions of verything that dependency needs from [Crates.io](https://crates.io/)):

```toml
# Cargo.toml
[dependencies]
rand = "0.8.5"
```



---



## Best Practice

### TODO

---



## Reference

[1] [The Rust Programming Language](https://doc.rust-lang.org/book/title-page.html)

