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
badd +41 srctree/src/app_renderer.cpp
badd +134 srctree/src/a3_dogui.cpp
badd +90 srctree/src/a3.hpp
badd +100 srctree/src/cgra/mesh.hpp
badd +124 srctree/src/main.cpp
badd +293 srctree/src/a3.cpp
badd +6 srctree/src/a3_kfwin.cpp
badd +38 srctree/src/boneCurve.cpp
badd +26 srctree/src/boneCurve.hpp
badd +20 srctree/src/drawStyle.hpp
badd +153 srctree/src/cgra/mesh.cpp
badd +21 srctree/src/splineMath.cpp
badd +20 srctree/src/splineMath.hpp
badd +137 srctree/include/skeleton/skeleton.cpp
badd +2 srctree/src/asf.cpp
badd +123 srctree/src/asf.hpp
badd +105 srctree/include/skeleton/skeleton.hpp
badd +6 srctree/src/CMakeLists.txt
badd +27 srctree/src/a3-filesave.cpp
badd +0 srctree/src/a3_dogui.cppd
badd +24 srctree/res/shaders/pick.fs.glsl
badd +15 srctree/res/shaders/pick2.fs.glsl
badd +16 srctree/src/app_renderer.hpp
badd +21 srctree/res/shaders/simple.vs.glsl
badd +16 srctree/res/shaders/lambert.fs.glsl
badd +0 srctree/res/shaders/simple.fs.glsl
badd +214 priman.asf
argglobal
silent! argdel *
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnew
tabnext -7
edit srctree/src/a3_dogui.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
3wincmd k
wincmd w
wincmd w
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 112 + 106) / 212)
exe '2resize ' . ((&lines * 19 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 112 + 106) / 212)
exe '3resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 3resize ' . ((&columns * 112 + 106) / 212)
exe '4resize ' . ((&lines * 16 + 30) / 61)
exe 'vert 4resize ' . ((&columns * 112 + 106) / 212)
exe '5resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 5resize ' . ((&columns * 112 + 106) / 212)
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
let s:l = 39 - ((13 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
39
normal! 033|
wincmd w
argglobal
if bufexists('srctree/src/asf.hpp') | buffer srctree/src/asf.hpp | else | edit srctree/src/asf.hpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 45 - ((12 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
45
normal! 0
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
argglobal
if bufexists('srctree/src/asf.cpp') | buffer srctree/src/asf.cpp | else | edit srctree/src/asf.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 347 - ((5 * winheight(0) + 8) / 16)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
347
normal! 093|
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
exe 'vert 1resize ' . ((&columns * 112 + 106) / 212)
exe '2resize ' . ((&lines * 19 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 112 + 106) / 212)
exe '3resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 3resize ' . ((&columns * 112 + 106) / 212)
exe '4resize ' . ((&lines * 16 + 30) / 61)
exe 'vert 4resize ' . ((&columns * 112 + 106) / 212)
exe '5resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 5resize ' . ((&columns * 112 + 106) / 212)
tabnext
edit srctree/res/shaders/simple.vs.glsl
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 29 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 78 + 106) / 212)
exe '2resize ' . ((&lines * 28 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 78 + 106) / 212)
exe 'vert 3resize ' . ((&columns * 146 + 106) / 212)
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
let s:l = 21 - ((10 * winheight(0) + 14) / 29)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
21
normal! 0
wincmd w
argglobal
if bufexists('srctree/res/shaders/simple.fs.glsl') | buffer srctree/res/shaders/simple.fs.glsl | else | edit srctree/res/shaders/simple.fs.glsl | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 3 - ((2 * winheight(0) + 14) / 28)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
3
normal! 0
wincmd w
argglobal
if bufexists('srctree/res/shaders/pick.fs.glsl') | buffer srctree/res/shaders/pick.fs.glsl | else | edit srctree/res/shaders/pick.fs.glsl | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 25 - ((24 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
25
normal! 015|
wincmd w
exe '1resize ' . ((&lines * 29 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 78 + 106) / 212)
exe '2resize ' . ((&lines * 28 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 78 + 106) / 212)
exe 'vert 3resize ' . ((&columns * 146 + 106) / 212)
tabnext
edit srctree/src/drawStyle.hpp
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
let s:l = 1 - ((0 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 012|
tabnext
edit srctree/include/skeleton/skeleton.hpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
wincmd _ | wincmd |
split
3wincmd k
wincmd w
wincmd w
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 24 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 88 + 106) / 212)
exe '2resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 88 + 106) / 212)
exe '3resize ' . ((&lines * 11 + 30) / 61)
exe 'vert 3resize ' . ((&columns * 88 + 106) / 212)
exe '4resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 4resize ' . ((&columns * 88 + 106) / 212)
exe '5resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 5resize ' . ((&columns * 123 + 106) / 212)
exe '6resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 6resize ' . ((&columns * 123 + 106) / 212)
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
let s:l = 53 - ((14 * winheight(0) + 12) / 24)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
53
normal! 0
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
argglobal
if bufexists('srctree/include/skeleton/skeleton.cpp') | buffer srctree/include/skeleton/skeleton.cpp | else | edit srctree/include/skeleton/skeleton.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 427 - ((8 * winheight(0) + 5) / 11)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
427
normal! 0
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
argglobal
if bufexists('srctree/src/asf.cpp') | buffer srctree/src/asf.cpp | else | edit srctree/src/asf.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 339 - ((32 * winheight(0) + 23) / 47)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
339
normal! 028|
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
exe '1resize ' . ((&lines * 24 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 88 + 106) / 212)
exe '2resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 88 + 106) / 212)
exe '3resize ' . ((&lines * 11 + 30) / 61)
exe 'vert 3resize ' . ((&columns * 88 + 106) / 212)
exe '4resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 4resize ' . ((&columns * 88 + 106) / 212)
exe '5resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 5resize ' . ((&columns * 123 + 106) / 212)
exe '6resize ' . ((&lines * 10 + 30) / 61)
exe 'vert 6resize ' . ((&columns * 123 + 106) / 212)
tabnext
edit srctree/src/main.cpp
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
let s:l = 124 - ((28 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
124
normal! 0
tabnext
edit srctree/src/a3.hpp
set splitbelow splitright
wincmd _ | wincmd |
split
1wincmd k
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 88 + 106) / 212)
exe '2resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 123 + 106) / 212)
exe '3resize ' . ((&lines * 10 + 30) / 61)
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
let s:l = 113 - ((1 * winheight(0) + 23) / 47)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
113
normal! 0
wincmd w
argglobal
if bufexists('srctree/src/a3.cpp') | buffer srctree/src/a3.cpp | else | edit srctree/src/a3.cpp | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 274 - ((26 * winheight(0) + 23) / 47)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
274
normal! 050|
wincmd w
argglobal
enew
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
wincmd w
exe '1resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 1resize ' . ((&columns * 88 + 106) / 212)
exe '2resize ' . ((&lines * 47 + 30) / 61)
exe 'vert 2resize ' . ((&columns * 123 + 106) / 212)
exe '3resize ' . ((&lines * 10 + 30) / 61)
tabnext
edit srctree/src/app_renderer.cpp
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
let s:l = 42 - ((1 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
42
normal! 024|
tabnext
edit srctree/src/a3_dogui.cpp
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
let s:l = 98 - ((22 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
98
normal! 05|
tabnext 7
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
