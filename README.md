# tcl-cpp-interface
Implementation of a C++ interface for the Tcl C API.

## Development
### Code navigation and autocompletion
This project exports compilation commands by default to
`compile_commands.json`. This enables integration into language servers like
[clangd](https://clang.llvm.org/extra/clangd/) and
[ccls](https://github.com/MaskRay/ccls) that implement the [Language Server
Protocol](https://langserver.org/) (LSP). With the appropriate client plugin, any editor can become a fully-fleged IDE.

The compilation database is generated in the directory of build (`build` if
you're following the standard build instructions). To avoid any extra
configuration, it is necessary to make a link to that file in the project root:
~~~ sh
ln -s build/compile_commands.json ./
~~~

Finally, install the appropriate client plugin on your IDE. As examples, there are
- Visual Studio Code: [vscode-clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) or [vscode-ccls](https://marketplace.visualstudio.com/items?itemName=ccls-project.ccls)
- Vim: [vim-lsp](https://github.com/prabirshrestha/vim-lsp) or [LanguageClient-neovim](https://github.com/autozimu/LanguageClient-neovim)
- Emacs: [emacs-lsp](https://github.com/emacs-lsp/lsp-mode)
