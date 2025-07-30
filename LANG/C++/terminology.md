English | [中文版]

# Terminology

- The process of creating a regular class, function, or member function from a template by substituting actual values for its arguments is called **template instantiation**. This resulting entity(class, function, or member function) is generically called a **specialization**.
- A **declaration** is a C++ construct that introduces or reintroduces a name into a C++ scope. This introduction always includes a partial classification of that name, but the details are not required to make a valid declaration. 
- The declaration of a class template or function template is called a **definition** if it has a body.
- **Template parameters** are those names that are listed after the keyword `template` in the template declaration or definition (`T` and `N` in our example).
- **Template arguments** are the items that are substituted for template parameters (`double` and `10` in our example). Unlike template parameters, template arguments can be more than just "names".
- **Template metaprogramming:** Using the template instantiation mechanism to perform nontrivial computations at compile time.
- **Curiously Recurring Template Pattern (CRTP)**: This pattern refers to a general class of techniques that consists of passing a derived class as a template argument to one of its own base classes.
- **Expression templates**: It was originally invented in support of numeric array classes, and that is also the context in which we introduce it here.
- **SFINAE(substitution-failure-is-not-an-error) principle**: An overloaded function template can be followed by explicit template arguments that are invalid for some of the templates.
- **Reference counting**: For each object that is pointed to, keep a count of the number of pointers to it, and when that count drops to zero, delete the object.
- A function object (also called a functor) is any object that can be called using the **function call syntax**.

