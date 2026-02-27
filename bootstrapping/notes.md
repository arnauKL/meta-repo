# Quines, compilers, languages, Trusting Trust and self-reproducing code

Notes on a video by Tsoding: [link](https://www.youtube.com/watch?v=QGm-d5Ch5JM)
that I treated as a lecture.

## The q language

The `q.q` file calls the `q` function.

The compiler takes the code written in the _q_ language and outputs it in _C_.

This simplifies implementing a first version in _C_.

To run:
```bash
./q < q.q
```

This executes the q compiler and gives it the contents of the q.q file via
_stdin_.

The program needs to output its source code twice. That's why it's useful to
store the whole program inside of the `self` variable.

But how?

We need an anchor, a character that when found will make the new compiler print
out its source code again.

`my anchor -> ?`

We need to avoid using that anchor anywhere else, hence we use ASCII. (ascii
for ? -> 63)

Then the output string needs to escape itself to be able to be a valid string in
C. This means turning all \n into \\n, " into \", and \ into \\ (This might not
show on markdown).

This works :)

## Malicious code

Once we have this working, we can 'lie' and add arbitrary code at the end of
what we are outputting. This code will never be seen in the new _q_ language, it
will only be seen in the intermediate C language we used.

This means that the new q compiler with this arbitrary code (which I
appropriately named `maliciousq`), when compiling _q_ code will do stuff that is
nowhere to be found inside of the q.q file it is compiling, it will be present
only in the binary (again, and in the intermediate C code).

```bash
$ ./maliciousq < q.q > evilqcompiler.c
$ nvim evilqcompiler.c
```

The source for the new binary will contain the _"malicious"_ code I added at the
end even though the `q.q` file that generated it does not call any function to
do that explicitly.

The `q.q` file only calls the `q` function, which we defined to be the function
to generate the compiler. In the self-hosted version of the compiler (q.q),
there could be pieces of code carried along but never visible.

In this case this is very obvious since a file appears but this is what Thompson
talked about in his Touring award lecture: _Trusting Trust_.
