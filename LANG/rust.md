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

**NOTE:** 

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

**NOTE:**

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

**NOTE:**

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
  	let a = [10, 20, 30, 40, 50]
  	for elem in a.iter() { // 10 20 30 40 50
    	println!("elem={}", elem);  
  	}
  
  	for elem in (1..4).rev() { // 1 2 3 4
    	println!("{}", elem);  
  	} 
  ```

**NOTE:**

1. Rust will not automatically try to convert non-Boolean types to a Boolean. You must be explicit and always provide `if` with a Boolean as its condition.

### Ownership And Lifespan

Rust use this rule to allocate memory: memory is managed through a system of ownership with a set of rules that the compiler checks at compile time. None of the ownership features slow down your program while it's running.

Ownership Rules:

- Each value in Rust has a variable that's called its `owner`.
- There can be only one owner at a time.
- When the owner goes out of scope, the value will be dropped.

Ownership example:

```rust
fn main() {
    fn hello() { // s is not valid here; it's not yet declared
        let s = "hello"; // s is valid from this point forward
    } // this scope is now over, and s is no longer valid

    let s1 = String::from("hello");
    let s2 = s1; // shallow copy
    println!("{s1}, s2={s2}"); // incorrect! the pointer of string has moved to s2

    let s1 = String::from("hello");
    let s2 = s1.clone(); // deep copy
    println!("s1={s1}, s2={s2}");

    let x = 5; 
    let y = x;
    println!("x={x}, y={y}");

    fn takes_ownership(arg: String) { // arg comes into scope
        println!("{arg}");
    } // Here, args goes out of scope and `drop` is called. The backing memory is freed.
    let s = String::from("hello");
    takes_ownership(s);
    println!("{s}"); // incorrect, value borrowed here after move

    fn makes_copy(arg: i32) { // arg comes into scop
        println!("{arg}");
    } // Here, arg goes out of scope. Nothing special happens.
    let x = 5;
    makes_copy(x);

    fn gives_ownership() -> String { // will move its return value into the function that calls it
        let str = String::from("yours"); // str comes into scope
        str // str is returned and moves out to the calling function
    }
    let s1 = gives_ownership();

    fn takes_and_gives_back(arg: String) -> String { // arg comes into scope
        arg // arg is returned and moves out to the calling function
    }
    let s2 = String::from("hello");
    let s3 = takes_and_gives_back(s2); // s2 is moved into takes_and_gives_back, which also moves its return value into s3
  
    fn change(s: &String) { // s is a reference to a String
       s.push_str(", world"); // incorrect! `s` is a `&` reference, so the data it refers to cannot be borrowed as mutable
  	} // Here, s goes out of scope. But because it does not have ownership of what it refers to, it is not dropped.
  	let s4 = String::from("hello");
  	change(&s4); // borrowing from s4
  	println!("s4={s4}");
  
  	fn change_mut(s: &mut String) {
      s.push_str(", world");
  	}
    let mut s5 = String::from("hello");
  	change_mut(&mut s5);
  	println!("s5={s5}");

    let mut s6 = String::from("hello");
    let r1 = &s6;
    let r2 = &s6; 
    let r3 = &mut s6; // incorrect! We cannot have a mutable reference while we have an immutable one to the same value.
    println!("{}, {}, and {}", r1, r2, r3); 

    let mut s7 = String::from("hello");
    let r1 = &s7; // ok
    let r2 = &s7; // ok
	  println!("{r1}, {r2}"); 
	// variables r1 and r2 will not be used after this point.

	let r3 = &mut s7; // ok
	println!("{r3}");

    fn dangle() -> &String { // incorrect! this function's return type contains a borrowed value, but there is no value for it to be borrowed from
    	let s = String::from("hello");
    	&s // returns a reference to data owned by the current function
    } // Here, s goes out of scope, and is dropped. Its memory goes away; Danger!

    let s8 = String::from("hello");
    println!("{}", &s8[0..2]); 					// he
    println!("{}", &s8[..2]);  					// he
    println!("{}", &s8[3..s8.len()]);   // lo
    println!("{}", &s8[3..]);           // lo
    println!("{}", &s8[0..s8.len()]);		// hello
    println!("{}", &s8[..]);						// hello
  	fn find_word(arg: &String) -> &str {
  		&arg[0..2]
  	}
  	let ret = find_word(&s8);
  	s8.clear(); // incorrect! ret mutable borrow from s8. Rust disallows the mutable reference in `clear`.
  	println!("{ret}");
}
```

**NOTE:**

1. Rust will never automatically create "deep" copies of your data. Therefore, any `automatic` copying can be assumed to be inexpensive in terms of runtimes performance.

2. Any group of simple scalar values can implement `Copy`, and nothing that requires allocation or is some form of resource can implement `Copy`. Here are some of the types that implement `Copy`:
   - All the integer types, such as `u32`.
   - The Boolean type, `bool`, with values `true` and `false`.
   - All the floating-point types, such as `f64`.
   - The character type, `char`.
   - Tuples, if they only contain types that also implement `Copy`. For example, `(i32, i32)` implements `Copy`, but `(i32, String)` does not.

3. The ownership of a variable follows the same pattern every time: assigning a value to another variable moves it. When a variable that includes data on the heap goes out of scope, the value will be cleaned up by `drop` unless ownership of the data has been moved to another variable.

4. We're **not allowed** to modify something we have a reference to.

5. At any given time, you can have **either one** mutable reference **or any** number of immutable references. (see NOTE 6, 8).

6. Mutable references have one big restriction: if you have a mutable reference to a value, you can have **no other references** to that value. For example:

   ```rust
   let mut s = String::from("hello");
   let r1 = &mut s;
   let r2 = &mut s; // incorrect! cannot borrow `s` as mutable more than once at a time
   println!("r1={r1}, r2={r2}");
   ```

7. `Data races` cause undefined behavior and can be difficult to diagnose and fix when you're trying to track them down at runtime; Rust prevents this problem by refusing to compile code with data races! A `data race` is similar to a race condition and happens when these three behaviors occur:

   - Two ro more pointers access the same data at the same time.
   - At least one of the pointers is being used to write to the data.
   - There's not mechanism being used to synchronize access to the data.

8. We cannot have a mutable reference while we have an immutable one to the same value. For example:

   ```rust
       let mut s6 = String::from("hello");
       let r1 = &s6; // ok
       let r2 = &s6; // ok
       let r3 = &mut s6; // incorrect!
   ```

9. A reference's scope starts from where it is introduced and continues through the last time that reference is used. For example:

   ```rust
       let mut s6 = String::from("hello");
       let r1 = &s6; // ok
       let r2 = &s6; // ok
   		println!("{r1}, {r2}"); 
   		// variables r1 and r2 will not be used after this point.
   
   		let r3 = &mut s6; // ok
   		println!("{r3}");
   ```

10. In Rust, the compiler guarantees that references will never be dangling references: if you have a reference to some data, the compiler will ensure that the data will not go out of scope before the reference to the data does. For example:

    ```rust
    fn dangle() -> &String { // incorrect! this function's return type contains a borrowed value, but there is no value for it to be borrowed from
            let s = String::from("hello");
            &s // returns a reference to data owned by the current function
        } // Here, s goes out of scope, and is dropped. Its memory goes away; Danger!
    ```

11. A slice is a kind of reference, so it does not have ownership.

### OOP

Struct Example:

```rust
fn main() {
    struct User {
        active: bool,
        username: String,
        email: String,
        sign_in_count: u64,
    }
    
    let mut user1 = User {
        active: true,
        username: String::from("user1"),
        email: String::from("def"),
        sign_in_count: 1,
    };
    user1.username = String::from("new user1");
    println!("{}", user1.username);
    
    fn build_user(email: String, username: String) -> User {
        User {
            active: true,
            username: username,
            email, // the field name same as parameter email, init shorthand!
            sign_in_count: 1,
        }
    }
    let user2 = build_user(String::from("hello"), String::from("user2"));

    let user3 = User {
        username: String::from("user3"),
        ..user1 // after that, we can't use user1 fields(active, email, sign_in_count) any more, because this fields has been moved
    };
    println!("{}", user1.username); // ok
    // println!("{}", user1.email);    // incorrect, value has been moved

    struct Color(i32, i32, i32);
    let black = Color(0, 0, 0);
    struct Point(i32, i32, i32);
    let origin = Point(0, 0, 0); // black and origin values are different types because they’re instances of different tuple structs. 

    struct UnitLikeStruct;
    let obj = UnitLikeStruct;

    #[derive(Debug)] // print out debugging information
    struct Rectangle {
        width: u32,
        height: u32,
    };
    let rec1 = Rectangle {
        width: 30,
        height: 30,
    };
    println!("{rec1:?}");  // flat style
    println!("{rec1:#?}"); // another style

    let rec2 = Rectangle {
        width: dbg!(3 * 10),
        height: 30,
    };
    dbg!(&rec2);

    impl Rectangle {
        fn area(&self) -> u32 { // associated functions
            self.width * self.height
        }
    };
    impl Rectangle {
        fn can_hold(&self, other: &Rectangle) -> bool { // associated functions
            self.width > other.width && self.height > other.height
        }
        fn square(size: u32) -> Self {
            Self {
                width: size,
                height: size,
            }
        }
    };
    let rec3 = Rectangle {
        width: 10,
        height: 10,
    };
    println!("rec3.area()={}", rec3.area());
    println!("rec1.can_hold(rec2)={}", rec1.can_hold(&rec2));
    println!("rec1.can_hold(rec3)={}", rec1.can_hold(&rec3));

    let rec4 = Rectangle::square(1);
    println!("{rec4:#?}");
}

```

**NOTE:**

1. Rust doesn't allow us to mark only certain fields as mutable.

2. The struct update syntax uses `=` like an assignment; this is because it moves the data. For example:

   ```rust
   		let mut user1 = User {
           active: true,
           username: String::from("user1"),
           email: String::from("def"),
           sign_in_count: 1,
       };
   		let user3 = User {
           username: String::from("user3"),
           ..user1 // after that, we can't use user1 fields(active, email, sign_in_count) any more, because this fields has been moved
       };
       println!("{}", user1.username); // ok
       println!("{}", user1.email);    // incorrect, value has been moved
   ```

3. Calling the `dbg!` macro prints to the standard error console stream (`stderr`), as opposed to `println!`, which prints to the standard output console stream (`stdout`). For example:

   ```rust
   		#[derive(Debug)] // print out debugging information
       struct Rectangle {
           width: u32,
           height: u32,
       };
   
       let rec2 = Rectangle {
           width: dbg!(3 * 10),
           height: 30,
       };
       dbg!(&rec2);
   ```

4. Rust doesn't have an equivalent to the `->` operator; instead, Rust has a feature called `automatic referencing and dereferencing`. Calling methods is one of the few places in Rust that has this behavior.

### Enums

Enums Example:

```rust
```

**NOTE:**

1. Rust does not have nulls, but it does have an enum that can encode the concept of a value being present or absent. This enum is `Option<T>`, and it is defined by the stadard library as follows:

   ```rust
   enum Option<T> {
   	None,
     Some(T),
   }
   ```

### Match

### Error Handling

### Concurrency

### Trait

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

