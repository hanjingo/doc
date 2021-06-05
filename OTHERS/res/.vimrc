" 设置配色
syntax enable
set t_co=256
set t_ut=
colorscheme codedark

set nocompatible              " be iMproved, required
filetype off                  " required

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'fatih/vim-go'
Plugin 'majutsushi/tagbar'
Plugin 'scrooloose/nerdtree'
Plugin 'Valloric/YouCompleteMe'
Plugin 'tomasiser/vim-code-dark' " vscode主题

call vundle#end()            " required
filetype plugin indent on    " required

" vim-go插件
let g:go_fmt_command = "goimports" " 格式化将默认的 gofmt 替换
let g:go_autodetect_gopath = 1
let g:go_list_type = "quickfix"
let g:go_version_warning = 1
let g:go_highlight_types = 1
let g:go_highlight_fields = 1
let g:go_highlight_functions = 1
let g:go_highlight_function_calls = 1
let g:go_highlight_operators = 1
let g:go_highlight_extra_types = 1
let g:go_highlight_methods = 1
let g:go_highlight_generate_tags = 1
let g:godef_split=2

" NERDTree设置 F10
" 打开和关闭NERDTree快捷键
map <F10> :NERDTreeToggle<CR>
" 设置宽度
let NERDTreeWinSize=25

" tagbar插件 F9
nmap <F9> :TagbarToggle<CR>
let g:tagbar_ctags_bin='/usr/local/Cellar/ctags/5.8_2/bin/ctags'
" let g:tagbar_ctags_bin='/usr/bin/ctags'
let g:tagbar_width=60
autocmd BufReadPost *.cpp,*.go call tagbar#autoopen() " go和c++环境自动打开tagbar
let g:tagbar_type_go = {
    \ 'ctagstype' : 'go',
    \ 'kinds'     : [
        \ 'p:package',
        \ 'i:imports:1',
        \ 'c:constants',
        \ 'v:variables',
        \ 't:types',
        \ 'n:interfaces',
        \ 'w:fields',
        \ 'e:embedded',
        \ 'm:methods',
        \ 'r:constructor',
        \ 'f:functions'
    \ ],
    \ 'sro' : '.',
    \ 'kind2scope' : {
        \ 't' : 'ctype',
        \ 'n' : 'ntype'
    \ },
    \ 'scope2kind' : {
        \ 'ctype' : 't',
        \ 'ntype' : 'n'
    \ },
    \ 'ctagsbin'  : 'gotags',
    \ 'ctagsargs' : '-sort -silent'
	\ }

" 缩进
set tabstop=4

" 行号
set number

" 自动换行
set wrap

" 语法高亮
set syntax=on

" 自动缩进
set autoindent
set cindent

" utf8编码
set enc=utf-8
  
" 中文
set langmenu=zh_CN.UTF-8

" 高亮显示当前行
set cursorline

" 搜索模式忽略大小写
set ignorecase

" 设置自动保存
let g:auto_save = 1
let g:auto_save_events = ["InsertLeave", "TextChanged", "TextChangedI", "CursorHoldI", "CompleteDone"]

" 显示cmd
set showcmd

