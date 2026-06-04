# TOC generator for typst

When I use typst in nvim I get lost since headings are just `===`

`toccer` is a utility that parses a file and generates a TOC with numbers like
it would be generated in the finalized pdf.

Usage:
```sh
toccer file.typ [n]
```

# nvim integration

I only use this through nvim though, I have it output file and line number so I
can jump to the locations.

The following config generates a command `TypstTOC` that calls the script and
stores the output in the location list:

```lua
-- using vim's location list
vim.api.nvim_create_user_command("TypstTOC", ":lgetexpr system('toccer ' .. expand('%')) | lopen",  {})
```

Then, the file can be navigated using `[l` / `]l` and via the location list buffer.

# configuration

There are some options defined via typst comments: depth and starting heading
number can be configured:

```typ
// toc-depth: 6
// toc-start: 1
```

- `toc-depth` changes how many depth levels are shown.
- `toc-start` changes the starting section number. I sometimes separate
  documents into several typst files.

When not defined, `toc-depth` is 6 and `toc-start`, 1.
