# CHAPTER 23 XML



Extensible Markup Language(XML).

In electronic document processing, a `markup language` is a formal description of what part of the document is content, what part is markup, and what the markup means.

An XML representation has significant advantages when it is used to exchange data between organizations, and for storing complex structured information in files:

- First, the presence of the tags makes the message `self-documenting`; that is, a schema need not be consulted to understand the meaning of the text.
- Second, the format of the document is not rigid.
- Third, XML allows nested structures.
- Finally, since the XML format is widely accepted, a wide variety of tools are available to assist in its processing, including programming language APIs to create and to read XML data, browser software, and database tools.

In addition to elements, XML specifies the notion of an `attribute`.

The `document type definition (DTD)` is an optional part of an XML document.

Here are some of the limitations of DTDs as a schema mechanism:

- Individual text elements and attributes cannot be typed further.
- It is difficult to use the DTD mechanism to specify unordered sets of subelements.
- There is a lack of typing in IDs and IDREFSs.

XML Schema offers several benefits over DTDs, and is widely used today:

- It allows the text that appears in elements to be constrained to specific types, such as numeric types in specific formats or complex types such as sequences of elements of other types.
- It allows user-defined types to be created.
- It allows uniqueness and foreign-key constraints.
- It is integrated with namespaces to allow different parts of a document to conform to different schemas.

In addition to the features we have seen, XML Schema supports several other features that DTDs do not, such as these:

- It allows types to be restricted to create specialized types, for instance by specifying minimum and maximum values.
- It allows complex types to be extended by using a form of inheritance.

The describe the XPath and XQuery languages:

- XPath is a language for path expressions and is actually a building block for XQuery.
- XQuery is the standard language for querying XML data. It is modeled after SQL but is significantly different since it has to deal with nested XML data. XQuery also incorporates XPath expressions.

A `tree model` of XML data is used in all these languages. An XML document is modeled as a `tree`, with `nodes` corresponding to elements and attributes.

A `path expression` in XPath is a sequence of location steps separated by "/".

XPath supports a number of other features:

- Selection predicates may follow any step in a path, and are contained in square brackets.
- XPath provides several functions that can be used as part of predicates, including testing the position of the current node in the sibling order and the aggregate function `count()`, which counts the number of nodes matched by the expression to which it is applied.
- The function `id("foo")` returns the node (if any) with an attribute of type ID and value "foo". The function id can even be applied on sets of references, or even strings containing multiple references separated by blanks, such as IDREFS.
- The `|` operator allows expression results to be unioned.
- An XPath expression can skip multiple levels of nodes by using "//".
- A step in the path need not just select from the children of the nodes in the current node set.
- The built-in function `doc(name)` returns the root of a named document; the name could be a file name or a URL.

There are several alternatives for storing XML data in nonrelational data-storage systems:

- Store in flat files.
- Create an XML database.

Some relational databases support `native storage` of XML.

The `Simple Object Access Protocol (SOAP)` defines a standard for invoking procedures, using XML for representing the procedure input and output.

A site providing such a collection of SOAP procedures is called a `Web service`.

The `Web Services Description Language (WSDL)` is a language used to describe a Web service's capabilities.

There is also a standard called `Universal Description, Discovery, and Integration (UDDI)` that defines how a directory of available Web services may be created and how a program may search in the directory to find a Web service satisfying its requirements.
