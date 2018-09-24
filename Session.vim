let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/local/CGRA350/assignment3/ass3-local
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +120 srctree/src/a3.cpp
badd +477 srctree/src/ex1.cpp
badd +3 srctree/src/ex1.hpp
badd +76 srctree/src/asf.hpp
badd +200 srctree/src/asf.cpp
badd +38 srctree/src/main.cpp
badd +44 srctree/src/a3.hpp
badd +7 srctree/CMakeLists.txt
badd +37 srctree/src/CMakeLists.txt
badd +5 srctree/include/skeleton/skeleton.hpp
badd +53 srctree/include/skeleton/skeleton.cpp
badd +1 srctree/res/shaders/simple.fs.glsl
badd +1 srctree/src/drawStyle.hpp
argglobal
silent! argdel *
$argadd srctree/src/a3.cpp
edit srctree/src/a3.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 51 - ((49 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
51
normal! 07|
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOcsF
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
