# TOC generator for typst

When I use typst in neovim I get lost since headings are just `===`

`toccer` is a utility that parses a file and generates a TOC with numbers like
it would be generated in the finalized pdf.

Usage:
```sh
toccer file.typ
```

I only use this through nvim though. I have a binding to have MiniPick show the
output to me. I'd like it if I coud select an entry and go to that line number
but I have not figured out how to do that yet:

```lua
-- call toccer and show in MiniPick
vim.api.nvim_create_user_command("TypstTOC", function() 
  MiniPick.builtin.cli({ command = { 'toccer', vim.fn.expand("%") } })
end, {})

vim.keymap.set("n", "<leader>tc", ':TypstTOC<CR>', { noremap = true, silent = true, desc = "Show TOC (Typst)" })
```

No LLM used.
