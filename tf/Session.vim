let SessionLoad = 1
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Documents/EPs/mac0328/tf
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +53 DIGRAPHmatrix.h
badd +197 DIGRAPHmatrix.c
badd +96 DIGRAPHlists.h
badd +1 DIGRAPHlists.c
badd +1 ~/Documents/EPs/mac0328/guidelines
badd +1 DIGRAPHrand.c
badd +33 DIGRAPHrand.h
badd +1 DIGRAPHproto.c
badd +1 DIGRAPHproto.h
badd +24 GRAPHrand.c
badd +26 GRAPHrand.h
badd +46 Makefile
badd +56 DIGRAPHlists_test.c
badd +19 DIGRAPHmatrix_test.c
badd +100 rastro.c
badd +1 README.txt
badd +87 compsfortes.c
argglobal
silent! argdel *
argadd DIGRAPHmatrix.h
argadd DIGRAPHmatrix.c
edit DIGRAPHlists.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 117 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 121 + 119) / 239)
argglobal
edit DIGRAPHlists.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 162 - ((46 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
162
normal! 027|
wincmd w
argglobal
edit DIGRAPHlists.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 348 - ((15 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
348
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 117 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 121 + 119) / 239)
tabedit DIGRAPHmatrix.h
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 120 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 118 + 119) / 239)
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
let s:l = 53 - ((52 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
53
normal! 011|
wincmd w
argglobal
edit DIGRAPHmatrix.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 333 - ((40 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
333
normal! 021|
wincmd w
exe 'vert 1resize ' . ((&columns * 120 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 118 + 119) / 239)
tabedit compsfortes.c
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 117 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 121 + 119) / 239)
argglobal
edit compsfortes.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 74 - ((38 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
74
normal! 030|
wincmd w
argglobal
edit DIGRAPHlists.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 96 - ((0 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
96
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 117 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 121 + 119) / 239)
tabedit Makefile
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 120 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 118 + 119) / 239)
argglobal
edit Makefile
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 46 - ((37 * winheight(0) + 29) / 58)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
46
normal! 0
wincmd w
argglobal
edit README.txt
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
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 120 + 119) / 239)
exe 'vert 2resize ' . ((&columns * 118 + 119) / 239)
tabnext 3
if exists('s:wipebuf') && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
let g:this_session = v:this_session
let g:this_obsession = v:this_session
let g:this_obsession_status = 2
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
