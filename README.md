# simple-interpreter
An interpreter for the language simple, a relatively low level interpreted programming language.

## syntax
simple is a very *simple* language (hence the name), and doesn't have a lot of complex features.
### variable declaration
Variables are always passed by value, not reference, and can only store one of the pre defined primitve types:
* INT (whole positive and negative numbers)
* REAL (positive and negative numbers)
* CHAR (an ascii character)
* ARR (an array containing a predetermained number of values of all 1 type)

#### Variables are declared as follows:
\<type\>::\<name\>
#### And defined:
\<name\> = \<expression\> | \<literal\> | \<name\>

### flow control
Instead of function calls or OOP, simple gives you the GOTO, TAG and RETURN keywords:
* TAG
    * used to name a specific line of code to be used with GOTO
    * usage: TAG \<name\>
* GOTO
    * used to jump to a specific line of code
    * usage: GOTO \<tag name\>
* RETURN
    * return to the line after the last time GOTO was called
    * usage: RETURN

### conditionals and loops
The only conditional is IF, and the only loop is FOR:
* IF
    * calls GOTO on a given tag if a given INT is 1
    * usage: IF \<integer\> THEN \<tag name\>
* FOR
    * calls GOTO on a specific tag repeatedly, incrementing a variable each time based off a given start, end, and increment
    * usage: FOR \<integer or real\> \<integer or real\> \<integer or real\> \<tag name\>

