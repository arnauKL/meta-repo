# bol

'bol' is my markup language, named after my cat.
My goal is to build a compiler that talks to pandoc.

I am making this this to learn about language lexing/parsing
and as a markup language I can use for my notes.

```
Source (.bol)
    -> Lexer + Parser
        -> Pandoc JSON AST
            -> Pandoc
                -> literally whatever 
```

## References:
- https://www.buildyourownlisp.com/
- https://docs.racket-lang.org/pollen/


## Right now:
- The basic lexer works (can distinguish basic chars)

## Todo:
- Define the markup propperly


## How I want the end result to look

This is an idea of what I'd like the final result to look like.
Right now this is far from reality.

```bol
(h1 Sample text)

This should also be treated as normal text.

Two newlines or more lead to a paragraph break. This is how (b bold text) and (e
italic text) look like.

The parentheses enter 'markup mode', they need to be escaped to be used
in regular prose \(I might regret this later on\).

The first element after a parenthesis is the function used.
Some examples are h1, h2, b, e, ul, ol.

I am unsure with some features. For instance, I want to add the functionality
vim has, where the keyword can be the shortest version of itself that does not
collide with other keywords \(aka 'e' for 'emphasis'\). This might make it hard
to have short names if I add many markup elements and I really want common
elements like italics or bolds to just be 'e' or 'b'.
```


## Markup definition

The markup is minimal and may vary at any time.
I'm considering adding `:foo` parameters.

- `h1`, `h2`, `h3`, `h4`, `h5`, `h6` headings
- `em`: emphasis
- `b`: bold
- `m`: monospaced text
- `ol`: ordered lists
- `ul`: unordered lists 
- `dl`: definition lists
- `i`: item in lists
- `cb`: code blocks
- `hr`: horizontal rule
- `a`: links
- `sub`: subscript
- `sup`: superscript
- ...


I still don't know how to handle raw blocks:

```bol
(cb :lang py (
    def main() -> None:
        print("This won't work")
    ))
```
