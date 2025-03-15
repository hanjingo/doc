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

*NOTE:* 

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

*NOTE:*

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

*NOTE:*

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

*NOTE:*

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

*NOTE:*

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

The advantages to using an enum rather than a struct:

- We attach data to each variant of the enum directly, so there is no need for an extra struct.
- Each variant can have different types and amounts of associated data.

Enums Example:

```rust
		enum IP {
        V4(u8, u8, u8, u8),
        V6(String),
    }
    let home = IP::V4(127, 0, 0, 1);
    let loopback = IP::V6(String::from("::1"));

    enum Message {
        Quit,
        Move{x: i32, y: i32},
        Write(String),
        ChangeColor(i32, i32, i32),
    }
    impl Message {
        fn Call(&self) {
        }
    }
    let msg1 = Message::Write(String::from("hello"));
    msg1.Call();

    let some1 = Option::Some(5); // Option prefix is not a must
    let some2 = Some('e');
    let some3 : Option<i32> = None;

    let x: i8 = 5;
    let y: Option<i8> = Some(5);
    // let sum = x + y; // incorrect! the trait `Add<Option<i8>>` is not implemented for `i8`
```

*NOTE:*

1. Rust does not have nulls, but it does have an enum that can encode the concept of a value being present or absent. This enum is `Option<T>`, and it is defined by the stadard library as follows:

   ```rust
   enum Option<T> {
   	None,
     Some(T),
   }
   ```

### Match

When the match expression executes, it compares the resulting value against the pattern of each arm, in order.

Another useful feature of match arms is that they can bind to the parts of the values that match the pattern. This is how we can extract values out of enum variants.

Match Example:

```rust
    enum Coin {
        Penny,
        Nickel,
    }
    fn match_coin(coin: Coin) -> u8 {
        match coin {
            Coin::Penny => {
                println!("match Penny");
                1
            }
            Coin::Nickel => 5,
        }
    }
    println!("{}", match_coin(Coin::Penny));
    println!("{}", match_coin(Coin::Nickel));

    fn plus_one(x: Option<i32>) -> Option<i32> {
        match x {
            Some(i) => Some(i + 1),
            other => None,
            _ => None, // same as: other => None,
        }
    }
    let five = Some(5);
    let six = plus_one(five);  // match Some(i)
    let none = plus_one(None); // match other
```

*NOTE:*

1. Matches in Rust are `exhaustive`: we must exhaust every last possibility in order for the code to be valid

   ```rust
       fn plus_one(x: Option<i32>) -> Option<i32> {
           match x {
               Some(i) => Some(i + 1),
           }
       }
       let five = Some(5);
       let six = plus_one(five);
   		let none = plus_one(None); // incorrect
   ```

2. Using `if let` means less typing, less indentation, and less boilerplate code. However, you lose the exhaustive checking that match enforces.

   ```rust
       match coin {
       	Coin::Quarter(state) => println!("{}", state),
         _ => count += 1,
   		}
   		// same as
   		if let Coin::Quarter(state) = coin {
       	println!("{}", state);  
   		} else {
       	count += 1;  
   		}
   ```

### Error Handling

#### panic

```rust
fn main() {
    // panic!("crash");

    let v = vec![1, 2, 3];
    // v[100]; // incorrect! index out of bounds
}
```

*NOTE:*

1. To protect your program from `buffer overread`, if you try to read an element at an index that doesn't exist, Rust will stop execution and refuse to continue.

#### Result

```rust
use std::fs::File;
use std::io::ErrorKind;
fn main() {
  let result = File::open("hello.txt");
  let ret = match result {
    Ok(file) => file,
    Err(error) => match error.kind() {
      ErrorKind::NotFound => match File::create("hello.txt") {
        OK(fc) => fc,
        Err(e) => panic!("Problem creating the file: {e:?}"),
      },
      other_error => {
        panic!("Problem opening the file: {other_error:?}");
      }
    },
  };
  
  let greeting_file = File::open("hello.txt")?; // incorrect!
}

fn read_username_from_file1() -> Result<String, io::Error> {
  let mut username = String::new();
  File::open("hello.txt")?.read_to_string(&mut username)?;
  Ok(username)
}

fn read_username_from_file2() -> Result<String, io::Error> {
  fs::read_to_string("hello.txt")
}
```

*NOTE:*

1. The `?` operator can only be used in functions that have a return type of Result, because it is defined to work in the same way as the match expression. for example:

   ```rust
   use std::fs::File;
   fn main() {
     let f = File::open("hello.txt")?; // incorrect! the `?` operator can only be used in a function that returns `Result` or `Option`
   }
   ```

2. It's advisable to have your panic when it's possible that your code could end up in a bad state. In this context, a `bad state` is when some assumption, guarantee, contract, or invariant has been broken, such as when invalid values, contradictory values, or missing values are passed to your code--plus one or more of the following:

   - The bad state is not something that's `expected` to happen occasionally.
   - Your code after this point needs to rely on not being in this bad state.
   - There's not a good way to encode this information in the types you use.

3. Rust doesn't care where you define your functions, only that they're defined somewhere in a scope that can be seen by the caller.

4. Rust did not support auto return value.

### Iterators & Closures

```rust
fn main() {
  let list = vec![1, 2, 3];
  println!("Before defining closure: {list:?}");
  
  let only_borrows = || println!("From colsure: {list:?}");
  println!("Before calling closure: {list:?}");
  
  only_borrows();
  println!("After calling closure: {list:?}");
  
  let itr = list.iter();
  for val in itr {
    println!("Got: {val}");
  }
}
```

### Trait & Template & Lifetime

```rust
fn largest<T: std::cmp::PartialOrd>(list: &[T]) -> &T {
    let mut largest = &list[0];
    for item in list {
      if item > largest {
        largest = item;
      }
    }
    largest
}
pub trait Summary {
  fn summarize(&self)->String;
}
pub struct NewsArticle {
  pub headline: String,
  pub location: String,
  pub author: String,
  pub content: String,
}
impl Summary for NewsArticle {
  fn summarize(&self)->String {
    format!("{}, by {} ({})", self.headline, self.author, self.location)
  }
}
fn some_function<T, U>(t: &T, u: &U)->i32
where
	T: Display + Clone,
	U: Clone + Debug,
{
  ...
}
fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    let result = largest(&number_list);
    println!("the largest number is {result}");
  
  	let char_list = vec!['y', 'm', 'a', 'q'];
  	let result = largest(&char_list);
    println!("the largest char is {result}");
}
```

*NOTE:*

1. Rust accomplishes this by performing monomorphization of the code that is using generics at compile time. `Monomorphization` is the process of turning generic code into specific code by filling in the concrete types that are used when compiled.

2. We can use `trait bounds` to constrain generic types to ensure the type will be limited to those that implement a particular trait and behavior:

   ```rust
   pub fn notify<T: Summary>(item1: &T, item2: &T) {...}
   ```

3. The main aim of lifetimes is to prevent dangling references, which cause a program to reference data other than the data it's intended to reference. For example:

   ```rust
   fn main() {
     let r;
     {
       let x = 5;
       r = &x;
     }
     println!("r:{r}");
   }
   ```

4. Lifetime annotations have a slightly unusual syntax: the names of lifetime parameters must start with a single quote (') and are usually all lowercase and very short, like generic types. Most people use the name `'a`. We place lifetime parameter annotations after the `&` of a reference, using a space to separate the annotation from the reference's type.

5. As with generic type parameters, we need to declare genric lifetime parameters inside angle brackets between the function name and the parameter list. The constraint we want to express in this signature is that all the references in the parameters and the return value must have the same lifetime. For example:

   ```rust
   fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
     if x.len() > y.len() {
       x
     } else {
       y
     }
   }
   ```

6. When returning a reference from a function, the lifetime parameter for the return type needs to match the lifetime parameter for one of the parameters. If the reference returned does `not` refer to one of the parameters, it must refer to a value created within this function, which would be a dangling reference because the value will go out of scope at the end of the function. For example:

   ```rust
   fn longest<'a>(x: &str, y: &str)->&'a str {
     let result = String::from("really long string");
     result.as_str() // incorrect! borrowed value must be valid for the lifetime 'a as defined
   }
   ```

7. The compiler uses three rules to figure out what lifetimes references have when there aren't explicit annotations:

   - The first rule is that each parameter that is a reference gets its own lifetime parameter.
   - The second rule is if there is exactly one input lifetime parameter, that lifetime is assigned to all output lifetime parameters: `fn foo<'a>(x:&'a i32)->&'a i32`.
   - The third rule is if there are multiple input lifetime parameters, but one of them is `&self` or `&mut` self because this is a method, the lifetime of self is assigned to all output lifetime parameters.

### Smart Pointer

```rust
use crate::List::{Cons, Nil};
use std::ops::Deref;

impl<T> Deref for MyBox<T> {
  type Target = T;
  fn deref(&self) -> &Self::Target {
    &self.0
  }
}
struct MyBox<T>(T);
impl<T> MyBox<T> {
  fn new(x: T) -> MyBox<T> {
    MyBox(x)
  }
}

enum List {
    Cons(i32, Box<List>),
    Nil,
}

struct CustomSmartPointer {
  data: String,
}
impl Drop for CustomSmartPointer {
  fn drop(&mut self) {
    println!("Dropping CustomSmartPointer with data `{}`!", self.data);
  }
}

fn main() {
    let list = Cons(1, Box::new(Cons(2, Box::new(Cons(3, Box::new(Nil))))));
  
  	let x = 5;
  	let y = &x;
  	assert_eq!(5, *y);
  
  	let y = Box::new(x);
  	assert_eq!(5, *y);
  
  	let y = MyBox::new(x);
  	assert_eq!(5, *y);
  
  	let c = CustomSmartPointer{
    	data: String::from("some data"),  
  	};
  	println!("CustomSmartPointer created.");
//  	c.drop(); // incorrect! explicit destructor calls not allowed
  	std::mem::drop(c);
  	println!("CustomSmartPointer dropped before the end of main.");
}
```

*NOTE:*

1. `Deref coercion` is a convenience that Rust performs on arguments to functions and methods. Deref coercion converts a reference to a type that implements `Deref` into a reference to a type that `Deref` can convert the original type into.

2. Rust does deref coercion when it finds types and trait implementations in three cases:

   - From `&T` to `&U` when `T: Deref<Target=U>`
   - From `&mut T` to `&mut U` when `T: DerefMut<Target=U>`
   - From `&mut T` to `&U` when `T: Deref<Target=U>`

3. Rust doesn't let us call drop explicitly because Rust would still automatically call drop on the value at the end of main. This would be a `double free` error because Rust would be trying to clean up the same value twice.

4. Preventing memory leaks entirely is not one of Rust's guarantees in the same way that disallowing data races at compile time is, meaning memory leaks are memory safe in Rust. We can see that Rust allows memory leaks by using `Rc<T>` and `RefCell<T>:` it's possible to create references where items refer to each other in a cycle. This creates memory leaks because the reference count of each item in the cycle will never reach 0, and the values will never be dropped. For example:

   ```rust
   use crate::List::{Cons, Nil};
   use std::cell::RefCell;
   use std::rc::Rc;
   
   #[derive(Debug)]
   enum List {
     Cons(i32, RefCell<Rc<List>>),
     Nil,
   }
   impl List {
     fn tail(&self)->Option<&RefCell<Rc<List>>> {
       match self {
         Cons(_, item) => Some(item),
         Nil => None,
       }
     }
   }
   
   fn main() {
     let a = Rc::new(Cons(5, RefCell::new(Rc::new(Nil))));
     println!("a initial rc count = {}", Rc::strong_count(&a));
     println!("a next item = {:?}", a.tail());
     
     let b = Rc::new(Cons(10, RefCell::new(Rc::clone(&a))));
     println!("a rc count after b creation = {}", Rc::strong_count(&a));
     println!("b initial rc count = {}", Rc::strong_count(&b));
     println!("b next item = {:?}", b.tail());
     
     if let Some(link) = a.tail() {
       *link.borrow_mut() = Rc::clone(&b);
     }
     println!("b rc count after changing a = {}", Rc::strong_count(&b));
     println!("a rc count after changing a = {}", Rc::strong_count(&a));
   }
   ```

### Concurrency

```rust
use std::thread;
use std::time::Duration;
use std::sync::mpsc;
use std::rc::Rc;
use std::sync::{Arc, Mutex};
use std::thread;
fn main() {
  // spawn + join
  let handle = thread::spawn(||{
    for i in 1..10 {
      println!("hi number {i} from the spawned thread!");
      thread::sleep(Duration::from_millis(1));
    }
  });
  handle.join().unwrap();
  for i in 1..5 {
    println!("hi number {i} from the main thread!");
    thread::sleep(Duration::from_millis(1));
  }
  
  // channel
  let (tx, rx) = mpsc::channel(); // mpsc: multiple producer, single consumer
  thread::spawn(move || {
    let vals = vec![
      String::from("hi"),
      String::from("from"),
      String::from("the"),
      String::from("thread"),
    ];
    for val in vals {
      tx.send(val).unwrap();
      thread::sleep(Duration::from_secs(1));
    }
  });
  thread::spawn(move || {
    let vals = vec![
      String::from("more"),
      String::from("messages"),
      String::from("for"),
      String::from("you"),
    ];
    for val in vals {
      tx.send(val).unwrap();
      thread::sleep(Duration::from_secs(1));
    }
  });
  for received in rx {
    println!("Got: {received}");
  }
  
  // mutex
  let counter = Arc::new(Mutex::new(0));
  let mut handles = vec![];
  for _ in 0..10 {
    let counter = Arc::clone(&counter);
    let handle = thread::spawn(move || {
      let mut num = counter.lock().unwrap();
      *num += 1;
    });
    handles.push(handle);
  }
  
  for handle in handles {
    handle.join().unwrap();
  }
  println!("Result: {}", *counter.lock().unwrap());
}
```

*NOTE:*

1. By adding the `move` keyword before the closure, we force the closure to take ownership of the values it's using rather than allowing Rust to infer that it should borrow the values. For example:

   ```rust
   use std::thread;
   fn main() {
     let v = vec![1, 2, 3];
     let handle = thread::spawn(move || {
       println!("Here's a vector: {:?}", v);
     });
     handle.join().unwrap();
   }
   ```

2. Unfortunately, `Rc<T>` is not safe to share across threads. When `Rc<T>` manages the reference count, it adds to the count for each call to clone and subtracts from the count when each clone is dropped. But it doesn't use any concurrency primitives to make sure that changes to the count can't be interrupted by another thread.

### Unsafe

```rust
extern "C" {
  fn abs(input: i32) -> i32;
}

#[no_mangle]
pub extern "C" fn call_from_c() {
  println!("Just called a Rust function from C!");
}

unsafe trait Foo {}
unsafe impl Foo for i32 {}

fn add_one(x: i32) -> i32 {
  x + 1
}

fn do_twice(f: fn(i32)->i32, arg: i32) -> i32 {
  f(arg) + f(arg)
}

fn returns_closure() -> Box<dyn Fn(i32) -> i32> {
  Box::new(|x| x + 1)
}

fn main() {
  // unsafe
  unsafe fn dangerous() {}
  unsafe {
    dangerous(); // incorrect!
  }
  unsafe {
    println!("Absolute value of -3 according to C:{}", abs(-3));
  }
  
  // function pointer
  let answer = do_twice(add_one, 5);
  println!("The answer is: {answer}");
}
```

*NOTE:*

1. Different from references and smart pointers, raw pointers:

   - Are allowed to ignore the borrowing rules by having both immutable and mutable pointers or multiple mutable pointers to the same location.
   - Aren't guaranteed to point to valid memory.
   - Are allowed to be null.
   - Don't implement any automatic cleanup.

2. We must call the dangerous function within a separate unsafe block. If we try to call dangerous without the unsafe block, we'll get an error. For example:

   ```rust
   fn main() {
     unsafe fn dangerous() {}
     unsafe {
       dangerous(); // incorrect! call to unsafe function
     }
   }
   ```

3. You'll use default type parameters in two main ways:

   - To extend a type without breaking existing code.
   - To allow customization in specific cases most users won't need.

### TEST

Tests are Rust functions that verify that the non-test code is functioning in the expected manner. The bodies of test functions typically perform these three actions:

1. Set up any needed data or state.
2. Run the code you want to test.
3. Assert the result are what you expect.

```rust
// run: cargo new adder --lib

// lib.rs
pub fn add(left: usize, right: usize) -> usize {
    left + right
}

pub struct Guess {
    value: i32,
}
impl Guess{
  pub fn new(value: i32) -> Guess {
    if value < 1 || value > 100 {
      panic!("Guess value must be between 1 and 100, got {value}.");
    }
    Guess{value}
  }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn it_works() {
        let result = add(2, 2);
        assert_eq!(result, 4);
      	assert_ne!(result, 1);
    }

    #[test]
    fn greeting_contains_name() {
        let result = "carol";
        assert!(
            result.contains("Carol"),
            "Greeting did not contain name, value was `{}`",
            result,
        );
    }
  
    #[test]
  	#[should_panic(expected = "less than or equal to 100")]
  	fn greater_than_100() {
    	Guess::new(200);  
  	}
}
#[derive(Debug)]
struct Rectangle {
  width: u32,
  height: u32,
}
impl Rectangle {
  fn can_hold(&self, other: &Rectangle) -> bool {
    self.width > other.width && self.height > other.height
  }
}
// run: cargo test
```

*NOTE:*

1. When you run multiple tests, by default they run in parallel using threads. Make sure your tests don't depend on each other or on any shared state, including a shared environment, such as the current working directory or environment variables. If you don't want to run the tests in parallel or if you want more fine-grained control over the number of threads used, you can send the `--test-threads` flag and the number of threads you want to use to the test binary. For example

   ```sh
   cargo test -- --test-threads=1
   ```

2. If we want to see printed values for passing tests as well, we can disable the output capture behavior by using the `--nocapture` flag. For example:

   ```sh
   cargo test -- --nocapture
   ```

3. We can pass the name of any test function to cargo test to run only that test. For example:

   ```sh
   cargo test one_hundred
   ```

4. We can specify part of a test name, and any test whose name matches that value will be run.

5. Rather than listing as arguments all tests you do want to run, you can instead annotate the time-consuming tests using the ignore attribute to exclude specific tests. For example:

   ```rust
   #[test]
   #[ignore]
   fn expensive_test() {...}
   ```



---



## Std

### Vector

```rust
fn main() {
    let v:Vec<i32> = Vec::new();
    let v=vec![1, 2, 3];
    let mut v = Vec::new();
    v.push(5);

    let v = vec![1, 2, 3, 4, 5];
    let third: &i32 = &v[2];
    println!("v[2]={third}"); // 3
    let second: Option<&i32> = v.get(1); // 2
    match second {
        Some(second) => println!("the second element is {second}."),
        None => println!("there is no second element!"),
    }
    //let not_exist = &v[100]; // incorrect! panic! index out of bounds
    let not_exist: Option<&i32> = v.get(100); // not panic!

    let mut v = vec![1, 2, 3];
    let first: &i32 = &v[0];
    // v.push(4); // incorrect! panic! cannot borrow `v` as mutable because it is also borrowed as immutable
    for e in &mut v {
        println!("{e}");
    }

    enum my_enum {
        Int(i32),
        Float(f64),
        Text(String),
    };
    let row = vec![
        my_enum::Int(3),
        my_enum::Text(String::from("blue")),
        my_enum::Float(123.456),
    ];
}
```

*NOTE:*

1. The `[]` method will cause the program to panic while it references a nonexistent element.

2. When the `get` method is passed an index that is outside the vector, it returns `None` without panicking.

3. When the program has a valid reference, the borrow checker enforces the ownership and borrowing rules to ensure this reference and any other references to the contents of the vector remain valid. For example:

   ```rust
       let mut v = vec![1, 2, 3];
       let first: &i32 = &v[0];
       v.push(4); // incorrect! panic! cannot borrow `v` as mutable because it is also borrowed as immutable
   ```

4. When we need to store elements of a different type in a vector, we can define and use an enum. For example:

   ```rust
   		enum my_enum {
           Int(i32),
           Float(f64),
           Text(String),
       };
       let row = vec![
           my_enum::Int(3),
           my_enum::Text(String::from("blue")),
           my_enum::Float(123.456),
       ];
   ```

### String

```rust
fn main() {
    let mut s = String::new();

    let data = "hello world";
    let s = data.to_string();
    let s = "hello world".to_string();
    let s = String::from("hello world");
    
    let mut s1 = String::from("c++ and ");
    let s2 = "rust";
    s1.push_str(s2);
    println!("s1 = {}", s1); // c++ and rust

    let s3 = String::from("hello ");
    let s4 = String::from("world");
    // let s5 = s3 + &s4; // incorrect! borrow of moved value: `s3`

    let s6 = String::from("abc");
    let s7 = String::from("def");
    let s8 = String::from("123");
    let s9 = s6 + "-" + &s7 + "-" + &s8;
    println!("{}", s9); // abc-def-123

    let s6_1 = String::from("abc");
    let s7_1 = String::from("def");
    let s8_1 = String::from("123");
    let s9_1 = format!("{s6_1}:{s7_1}:{s8_1}");
    println!("{}", s9_1); // abc:def:123

    let s10 = String::from("hello");
    // let c = s10[0]; // incorrect! string indices are ranges of `usize`

    let hello = "hello";
    let slice = &hello[0..3];
    println!("{}", slice); // hel

    for c in "hello".chars() {
        println!("{c}");
    }
}
```

*NOTE:*

1. Strings are UTF-8 encoded, so we can include any properly encoded data in them.

2. If you try to access parts of a `String` using indexing syntax in Rust, you'll get an error. For example:

   ```rust
       let s10 = String::from("hello");
       // let c = s10[0]; // incorrect! string indices are ranges of `usize`
   ```

### Hash Map

```rust
use std::collections::HashMap;
fn main() {
    let mut scores = HashMap::new();
    scores.insert(String::from("key1"), 1);
    scores.insert(String::from("key2"), 2);
    let key = String::from("key1");
    let value = scores.get(&key).copied().unwrap_or(0);
    println!("{}", value); // 1

    scores.insert(String::from("key1"), 3); // 3, 2
    scores.entry(String::from("key2")).or_insert(4); // 3, 2
    scores.entry(String::from("key3")).or_insert(5); // 3, 2, 5
    for (k, v) in &scores {
        println!("{k}:{v}"); // 3,2,5
    }

    let key4 = String::from("key4");
    let value4 = String::from("value4");
    let mut hm = HashMap::new();
    hm.insert(key4, value4);
    // println!("{}", key4); // incorrect! value borrowed here after move
}

```

*NOTE:*

1. Each key can only have one value associated with it at a time.
2. By default, HashMap uses a cryptographically secure hashing function that can provide resistance to Denial of Service (DoS) attacks (This is not thefastest hashing algorithm available).

---



## 3rd party



---



## Compile and Build

### Module system

Rust has a module system that enables the reuse of code in an organized fashion.

Every module definition in Rust starts with the keyword. For example:

```rust
mod network {...}
```

The rules for item visibility:

1. If an item is public, it can be accessed through any of its parents modules.
2. If an item is private, it can be accessed only by its immediate parent module and any of the parent's child modules.

For example:

```rust
mod outermost {
  pub fn f1() { println!("f1"); }
  fn f2() { println!("f2"); }
  mod inside {
    pub fn f3() { println!("f3"); }
    fn f4() { println!("f4"); }
  }
}
```

To bring all the items in a namespace into scope at once, we can use the `*` syntax, which is called the `glob operator`. For example:

```rust
enum TrafficLight {
  Red,
  Yellow,
  Green,
}
use TrafficLight::*;
fn main() {
  let red = Red;
  let yellow = Yellow;
  let green = Green;
}
```



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

