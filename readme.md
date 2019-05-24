# Toy Lexer

A toy lexer for a hypothetical toy language.

This lexer is supposed to:

  - Transform valid source code into a sorted array of tokens.
  - Validate source code by aborting with an error if it is invalid.


## Characteristics

Recognized operations have prefix notation.
The output produced by the lexer is an array of token ids and their
values.


### Working features

  - binary operators: +, * and =
  - constant integers
  - constant strings
  - identifiers
