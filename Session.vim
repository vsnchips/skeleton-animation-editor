let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>(neocomplete_auto_refresh) =neocomplete#mappings#refresh()
inoremap <silent> <Plug>(neocomplete_start_manual_complete) =neocomplete#mappings#manual_complete()
inoremap <silent> <Plug>(neocomplete_start_auto_complete) =neocomplete#mappings#auto_complete()
inoremap <silent> <Plug>(neocomplete_start_omni_complete) 
inoremap <silent> <expr> <Plug>(neocomplete_start_unite_quick_match) unite#sources#neocomplete#start_quick_match()
inoremap <silent> <expr> <Plug>(neocomplete_start_unite_complete) unite#sources#neocomplete#start_complete()
inoremap <silent> <expr> <Plug>(neosnippet_start_unite_snippet) unite#sources#neosnippet#start_complete()
inoremap <silent> <expr> <Plug>(neosnippet_jump) neosnippet#mappings#jump_impl()
inoremap <silent> <expr> <Plug>(neosnippet_expand) neosnippet#mappings#expand_impl()
inoremap <silent> <expr> <Plug>(neosnippet_jump_or_expand) neosnippet#mappings#jump_or_expand_impl()
inoremap <silent> <expr> <Plug>(neosnippet_expand_or_jump) neosnippet#mappings#expand_or_jump_impl()
inoremap <expr> <BS> neocomplete#smart_close_popup()."\"
inoremap <silent> <Plug>(matchup-c_g%) :call matchup#motion#insert_mode()
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
inoremap <silent> <expr> <Plug>delimitMateS-BS delimitMate#WithinEmptyPair() ? "\<Del>" : "\<S-BS>"
inoremap <silent> <Plug>delimitMateBS =delimitMate#BS()
inoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
inoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
inoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
inoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
inoremap <expr> <PageUp> pumvisible() ? "\<PageUp>\\" : "\<PageUp>"
inoremap <expr> <PageDown> pumvisible() ? "\<PageDown>\\" : "\<PageDown>"
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
imap <silent> <expr> <S-Tab> SpaceVim#mapping#shift_tab()
inoremap <S-CR> o
inoremap <silent> <C-S-Up> :m .-2==gi
inoremap <silent> <C-S-Down> :m .+1==gi
noremap <expr>  max([winheight(0) - 2, 1]) ."\".(line('w0') <= 1 ? "H" : "L")
nnoremap <silent>  :call zvim#util#CopyToClipboard()
noremap <expr>  (line("w$") >= line('$') ? "j" : "3\")
noremap <expr>  max([winheight(0) - 2, 1]) ."\".(line('w$') >= line('$') ? "L" : "H")
smap <expr> 	 neosnippet#expandable_or_jumpable() ? "\<Plug>(neosnippet_expand_or_jump)" : (complete_parameter#jumpable(1) ? "\<Plug>(complete_parameter#goto_next_parameter)" : "\	")
nnoremap <silent> 	 :wincmd w
xnoremap 	 >gv
xnoremap <silent>  :call multiple_cursors#new("v", 0)
nnoremap <silent>  :call multiple_cursors#new("n", 1)
nnoremap <silent>  
vnoremap  :w
nnoremap  :w
omap <silent> a% <Plug>(matchup-o_)<Plug>(matchup-a%)
omap <silent> i% <Plug>(matchup-o_)<Plug>(matchup-i%)
omap <silent> z% <Plug>(matchup-o_)<Plug>(matchup-z%)
omap <silent> [% <Plug>(matchup-o_)<Plug>(matchup-[%)
omap <silent> ]% <Plug>(matchup-o_)<Plug>(matchup-]%)
omap <silent> g% <Plug>(matchup-o_)<Plug>(matchup-g%)
omap <silent> % <Plug>(matchup-o_)<Plug>(matchup-%)
nnoremap <silent>  x
noremap <expr>  (line("w0") <= 1         ? "k" : "3\")
vmap   [SPC]
nmap   [SPC]
omap <silent> % <Plug>(matchup-o_)<Plug>(matchup-%)
xmap <silent> % <Plug>(matchup-%)
nmap <silent> % <Plug>(matchup-%)
xmap , [SPC]l
nmap , [SPC]l
nnoremap <silent> ,  :silent! keeppatterns %substitute/\s\+$//e
nnoremap < <<_
xnoremap < <gv
nnoremap > >>_
xnoremap > >gv
imap <expr> ¯ neosnippet#expandable() ? "\<Plug>(neosnippet_expand)" : ""
omap F <Plug>(clever-f-F)
xmap F <Plug>(clever-f-F)
nmap F <Plug>(clever-f-F)
vmap <silent> J <Plug>(jplus)
nmap <silent> J <Plug>(jplus)
xmap S <Plug>VSurround
omap T <Plug>(clever-f-T)
xmap T <Plug>(clever-f-T)
nmap T <Plug>(clever-f-T)
omap <silent> Va% <Plug>(matchup-o_V)<Plug>(matchup-a%)
omap <silent> Vi% <Plug>(matchup-o_V)<Plug>(matchup-i%)
omap <silent> Vz% <Plug>(matchup-o_V)<Plug>(matchup-z%)
omap <silent> V[% <Plug>(matchup-o_V)<Plug>(matchup-[%)
omap <silent> V]% <Plug>(matchup-o_V)<Plug>(matchup-]%)
omap <silent> Vg% <Plug>(matchup-o_V)<Plug>(matchup-g%)
omap <silent> V% <Plug>(matchup-o_V)<Plug>(matchup-%)
xmap V <Plug>(expand_region_shrink)
omap <silent> [% <Plug>(matchup-o_)<Plug>(matchup-[%)
xmap <silent> [% <Plug>(matchup-[%)
nmap <silent> [% <Plug>(matchup-[%)
nnoremap <silent> [SPC]as :Startify | doautocmd WinEnter
nnoremap <silent> [SPC]tmT :if &laststatus == 2 | let &laststatus = 0 | else | let &laststatus = 2 | endif
nnoremap <silent> [SPC]tmp :call SpaceVim#layers#core#statusline#toggle_section("cursorpos")
nnoremap <silent> [SPC]tmt :call SpaceVim#layers#core#statusline#toggle_section("time")
nnoremap <silent> [SPC]tmd :call SpaceVim#layers#core#statusline#toggle_section("date")
nnoremap <silent> [SPC]tmb :call SpaceVim#layers#core#statusline#toggle_section("battery status")
nnoremap <silent> [SPC]tmM :call SpaceVim#layers#core#statusline#toggle_section("major mode")
nnoremap <silent> [SPC]tmm :call SpaceVim#layers#core#statusline#toggle_section("minor mode lighters")
nmap <silent> [SPC]; <Plug>CommentOperator
xmap <silent> [SPC]cT <Plug>CommentToLineInvert
nmap <silent> [SPC]cT <Plug>CommentToLineInvert
xmap <silent> [SPC]ct <Plug>CommentToLine
nmap <silent> [SPC]ct <Plug>CommentToLine
xmap <silent> [SPC]cP vip<Plug>NERDCommenterInvert
nmap <silent> [SPC]cP vip<Plug>NERDCommenterInvert
xmap <silent> [SPC]cp vip<Plug>NERDCommenterComment
nmap <silent> [SPC]cp vip<Plug>NERDCommenterComment
xmap <silent> [SPC]cv <Plug>NERDCommenterInvertgv
nmap <silent> [SPC]cv <Plug>NERDCommenterInvertgv
xmap <silent> [SPC]cL <Plug>NERDCommenterInvert
nmap <silent> [SPC]cL <Plug>NERDCommenterInvert
xmap <silent> [SPC]cl <Plug>NERDCommenterInvert
nmap <silent> [SPC]cl <Plug>NERDCommenterInvert
nnoremap <silent> [SPC]qt :tabclose!
nnoremap <silent> [SPC]qr :
nnoremap <silent> [SPC]qR :
nnoremap <silent> [SPC]qQ :qa!
nnoremap <silent> [SPC]qq :qa
nnoremap <silent> [SPC]p/ :Grepper
nnoremap <silent> [SPC]pp :call SpaceVim#plugins#projectmanager#list()
nnoremap <silent> [SPC]pk :call SpaceVim#plugins#projectmanager#kill_project()
nnoremap <silent> [SPC]pt :call SpaceVim#plugins#projectmanager#current_root()
nnoremap <silent> [SPC]fvd :SPConfig
nnoremap <silent> [SPC]fvv :let @+=g:spacevim_version | echo g:spacevim_version
nnoremap <silent> [SPC]fy :call zvim#util#CopyToClipboard()
nnoremap <silent> [SPC]bt :VimFilerBufferDir -no-toggle
nnoremap <silent> [SPC]fo :VimFiler -find
nnoremap <silent> [SPC]fT :VimFiler -no-toggle
nnoremap <silent> [SPC]ft :VimFiler
nnoremap <silent> [SPC]fF :normal! gf
nnoremap <silent> [SPC]fCu :update | e ++ff=dos | setlocal ff=unix | w
nnoremap <silent> [SPC]fCd :update | e ++ff=dos | w
nnoremap <silent> [SPC]fb :BookmarkShowAll
nnoremap <silent> [SPC]bNn :enew
nnoremap <silent> [SPC]bNl :rightbelow vertical new
nnoremap <silent> [SPC]bNk :new
nnoremap <silent> [SPC]bNj :rightbelow new
nnoremap <silent> [SPC]bNh :topleft vertical new
nnoremap <silent> [SPC]bw :setl readonly!
nnoremap <silent> [SPC]bY :normal! ggVG"+y``
nnoremap <silent> [SPC]bP :normal! ggdG"+P
nnoremap <silent> [SPC]bh :Startify
nnoremap <silent> [SPC]bc :call SpaceVim#mapping#clear_saved_buffers()
nnoremap <silent> [SPC]b :call SpaceVim#mapping#clearBuffers()
nnoremap <silent> [SPC]bD :call SpaceVim#mapping#kill_visible_buffer_choosewin()
nnoremap <silent> [SPC]bd :call SpaceVim#mapping#close_current_buffer()
nnoremap <silent> [SPC]	 :try | b# | catch | endtry
nnoremap <silent> [SPC]jo ik$
nnoremap <silent> [SPC]jn i
nmap <silent> [SPC]jq <Plug>(easymotion-overwin-line)
nmap <silent> [SPC]jw <Plug>(easymotion-overwin-w)
nmap <silent> [SPC]jv <Plug>(easymotion-overwin-line)
nmap <silent> [SPC]jl <Plug>(easymotion-overwin-line)
nnoremap <silent> [SPC]jk j==
nmap <silent> [SPC]jJ <Plug>(easymotion-overwin-f2)
nmap <silent> [SPC]jj <Plug>(easymotion-overwin-f)
nnoremap <silent> [SPC]jD :VimFiler
nnoremap <silent> [SPC]jd :VimFiler -no-split
nnoremap <silent> [SPC]jf 	
nnoremap <silent> [SPC]jb 
nnoremap <silent> [SPC]j$ m`g_
nnoremap <silent> [SPC]j0 m`^
nnoremap <silent> [SPC]h[SPC] :Unite help -input=SpaceVim
nnoremap <silent> [SPC]hk :LeaderGuide "[KEYs]"
nnoremap <silent> [SPC]hm :Unite manpage
nnoremap <silent> [SPC]hL :SPRuntimeLog
nnoremap <silent> [SPC]hl :SPLayer -l
nnoremap <silent> [SPC]hI :call SpaceVim#issue#report()
nnoremap <silent> [SPC]fS :wall
nnoremap <silent> [SPC]fs :write
nnoremap <silent> [p P
nnoremap <silent> [t :tabprevious
nnoremap <silent> [l :lprevious
nnoremap <silent> [b :bN | stopinsert
nnoremap <silent> [e :execute 'move -1-'. v:count1
nnoremap <silent> [  :put! =repeat(nr2char(10), v:count1)
nnoremap <silent> [SPC]TF <F11>
nnoremap <silent> [SPC]thc :set cursorcolumn!
nnoremap <silent> [SPC]thh :set cursorline!
nnoremap <silent> [SPC]tt :call SpaceVim#plugins#tabmanager#open()
nnoremap <silent> [SPC]tb :call ToggleBG()
nnoremap <silent> [SPC]iu :Unite unicode
nnoremap <silent> [SPC]xdw :StripWhitespace
nnoremap <silent> [SPC]xa| :Tabularize /|
nnoremap <silent> [SPC]xa¦ :Tabularize /¦
nnoremap <silent> [SPC]xa= :Tabularize /=
nnoremap <silent> [SPC]xa; :Tabularize /;
nnoremap <silent> [SPC]xa: :Tabularize /:
nnoremap <silent> [SPC]xa. :Tabularize /.
nnoremap <silent> [SPC]xa, :Tabularize /,
nnoremap <silent> [SPC]xa} :Tabularize /}
nnoremap <silent> [SPC]xa{ :Tabularize /{
nnoremap <silent> [SPC]xa] :Tabularize /]
nnoremap <silent> [SPC]xa[ :Tabularize /[
nnoremap <silent> [SPC]xa) :Tabularize /)
nnoremap <silent> [SPC]xa( :Tabularize /(
nnoremap <silent> [SPC]xa& :Tabularize /&
xmap <silent> [SPC]xc <Plug>CountSelectionRegion
nmap <silent> [SPC]xc <Plug>CountSelectionRegion
nnoremap <silent> [SPC]bf :Neoformat
nnoremap <silent> [SPC]eN :lNext
nnoremap <silent> [SPC]ep :lprevious
nnoremap <silent> [SPC]eL :lopen
nnoremap <silent> [SPC]el :lopen | wincmd w
nnoremap <silent> [SPC]en :lnext
nnoremap <silent> [SPC]eh :
nnoremap <silent> [SPC]is :Unite neosnippet
nnoremap <silent> [SPC]hdk :call SpaceVim#plugins#help#describe_key()
nnoremap <silent> [SPC]hdb :call SpaceVim#plugins#help#describe_bindings()
nnoremap <silent> [SPC]sh :call SpaceVim#plugins#highlight#start()
xmap <silent> [SPC]se <Plug>SpaceVim-plugin-iedit
nmap <silent> [SPC]se <Plug>SpaceVim-plugin-iedit
nnoremap <silent> [SPC]sc :noh
nnoremap <silent> [SPC]s/ :call SpaceVim#plugins#flygrep#open({})
nnoremap <silent> [SPC]sgG :call SpaceVim#plugins#flygrep#open({})
nnoremap <silent> [SPC]stJ :call SpaceVim#plugins#searcher#find(expand("<cword>"), "pt")
nnoremap <silent> [SPC]stj :call SpaceVim#plugins#searcher#find("", "pt")
nnoremap <silent> [SPC]stF :call SpaceVim#mapping#search#grep("t", "F")
nnoremap <silent> [SPC]stf :call SpaceVim#mapping#search#grep("t", "f")
nnoremap <silent> [SPC]stP :call SpaceVim#mapping#search#grep("t", "P")
nnoremap <silent> [SPC]stp :call SpaceVim#mapping#search#grep("t", "p")
nnoremap <silent> [SPC]stD :call SpaceVim#mapping#search#grep("t", "D")
nnoremap <silent> [SPC]std :call SpaceVim#mapping#search#grep("t", "d")
nnoremap <silent> [SPC]stB :call SpaceVim#mapping#search#grep("t", "B")
nnoremap <silent> [SPC]stb :call SpaceVim#mapping#search#grep("t", "b")
nnoremap <silent> [SPC]srJ :call SpaceVim#plugins#searcher#find(expand("<cword>"), "rg")
nnoremap <silent> [SPC]srj :call SpaceVim#plugins#searcher#find("", "rg")
nnoremap <silent> [SPC]srF :call SpaceVim#mapping#search#grep("r", "F")
nnoremap <silent> [SPC]srf :call SpaceVim#mapping#search#grep("r", "f")
nnoremap <silent> [SPC]srP :call SpaceVim#mapping#search#grep("r", "P")
nnoremap <silent> [SPC]srp :call SpaceVim#mapping#search#grep("r", "p")
nnoremap <silent> [SPC]srD :call SpaceVim#mapping#search#grep("r", "D")
nnoremap <silent> [SPC]srd :call SpaceVim#mapping#search#grep("r", "d")
nnoremap <silent> [SPC]srB :call SpaceVim#mapping#search#grep("r", "B")
nnoremap <silent> [SPC]srb :call SpaceVim#mapping#search#grep("r", "b")
nnoremap <silent> [SPC]skJ :call SpaceVim#plugins#searcher#find(expand("<cword>"), "ack")
nnoremap <silent> [SPC]skj :call SpaceVim#plugins#searcher#find("", "ack")
nnoremap <silent> [SPC]skF :call SpaceVim#mapping#search#grep("k", "F")
nnoremap <silent> [SPC]skf :call SpaceVim#mapping#search#grep("k", "f")
nnoremap <silent> [SPC]skP :call SpaceVim#mapping#search#grep("k", "P")
nnoremap <silent> [SPC]skp :call SpaceVim#mapping#search#grep("k", "p")
nnoremap <silent> [SPC]skD :call SpaceVim#mapping#search#grep("k", "D")
nnoremap <silent> [SPC]skd :call SpaceVim#mapping#search#grep("k", "d")
nnoremap <silent> [SPC]skB :call SpaceVim#mapping#search#grep("k", "B")
nnoremap <silent> [SPC]skb :call SpaceVim#mapping#search#grep("k", "b")
nnoremap <silent> [SPC]sgJ :call SpaceVim#plugins#searcher#find(expand("<cword>"), "grep")
nnoremap <silent> [SPC]sgj :call SpaceVim#plugins#searcher#find("", "grep")
nnoremap <silent> [SPC]sgF :call SpaceVim#mapping#search#grep("g", "F")
nnoremap <silent> [SPC]sgf :call SpaceVim#mapping#search#grep("g", "f")
nnoremap <silent> [SPC]sgP :call SpaceVim#mapping#search#grep("g", "P")
nnoremap <silent> [SPC]sgp :call SpaceVim#mapping#search#grep("g", "p")
nnoremap <silent> [SPC]sgD :call SpaceVim#mapping#search#grep("g", "D")
nnoremap <silent> [SPC]sgd :call SpaceVim#mapping#search#grep("g", "d")
nnoremap <silent> [SPC]sgB :call SpaceVim#mapping#search#grep("g", "B")
nnoremap <silent> [SPC]sgb :call SpaceVim#mapping#search#grep("g", "b")
nnoremap <silent> [SPC]saJ :call SpaceVim#plugins#searcher#find(expand("<cword>"), "ag")
nnoremap <silent> [SPC]saj :call SpaceVim#plugins#searcher#find("", "ag")
nnoremap <silent> [SPC]saF :call SpaceVim#mapping#search#grep("a", "F")
nnoremap <silent> [SPC]saf :call SpaceVim#mapping#search#grep("a", "f")
nnoremap <silent> [SPC]saP :call SpaceVim#mapping#search#grep("a", "P")
nnoremap <silent> [SPC]sap :call SpaceVim#mapping#search#grep("a", "p")
nnoremap <silent> [SPC]saD :call SpaceVim#mapping#search#grep("a", "D")
nnoremap <silent> [SPC]sad :call SpaceVim#mapping#search#grep("a", "d")
nnoremap <silent> [SPC]saB :call SpaceVim#mapping#search#grep("a", "B")
nnoremap <silent> [SPC]sab :call SpaceVim#mapping#search#grep("a", "b")
nnoremap <silent> [SPC]sl :call SpaceVim#plugins#searcher#list()
nnoremap <silent> [SPC]sJ :call SpaceVim#plugins#searcher#find(expand("<cword>"),SpaceVim#mapping#search#default_tool()[0])
nnoremap <silent> [SPC]sj :call SpaceVim#plugins#searcher#find("", SpaceVim#mapping#search#default_tool()[0])
nnoremap <silent> [SPC]sP :call SpaceVim#plugins#flygrep#open({'input' : expand("<cword>"), 'dir' : get(b:, "rootDir", getcwd())})
nnoremap <silent> [SPC]sp :call SpaceVim#plugins#flygrep#open({'input' : input("grep pattern:"), 'dir' : get(b:, "rootDir", getcwd())})
nnoremap <silent> [SPC]sF :call SpaceVim#plugins#flygrep#open({'input' : expand("<cword>"), 'dir' : input("arbitrary dir:", '', 'dir')})
nnoremap <silent> [SPC]sf :call SpaceVim#plugins#flygrep#open({'input' : input("grep pattern:"), 'dir' : input("arbitrary dir:", '', 'dir')})
nnoremap <silent> [SPC]sD :call SpaceVim#plugins#flygrep#open({'input' : expand("<cword>"), 'dir' : fnamemodify(expand('%'), ':p:h')})
nnoremap <silent> [SPC]sd :call SpaceVim#plugins#flygrep#open({'input' : input("grep pattern:"), 'dir' : fnamemodify(expand('%'), ':p:h')})
nnoremap <silent> [SPC]sB :call SpaceVim#plugins#flygrep#open({'input' : expand("<cword>"), 'files':'@buffers'})
nnoremap <silent> [SPC]sb :call SpaceVim#plugins#flygrep#open({'input' : input("grep pattern:"), 'files':'@buffers'})
nnoremap <silent> [SPC]sS :call SpaceVim#plugins#flygrep#open({'input' : expand("<cword>"), 'files': bufname("%")})
nnoremap <silent> [SPC]ss :call SpaceVim#plugins#flygrep#open({'input' : input("grep pattern:"), 'files': bufname("%")})
nnoremap <silent> [SPC]tn :setlocal nonumber! norelativenumber!
nnoremap <silent> [SPC]bp :bp
nnoremap <silent> [SPC]bn :bnext
nnoremap <silent> [SPC]wU :call SpaceVim#plugins#windowsmanager#RedoQuitWin()
nnoremap <silent> [SPC]wu :call SpaceVim#plugins#windowsmanager#UndoQuitWin()
nnoremap <silent> [SPC]wW :ChooseWin
nnoremap <silent> [SPC]ww :wincmd w
nnoremap <silent> [SPC]w= :wincmd =
nnoremap <silent> [SPC]wV :bel vs
nnoremap <silent> [SPC]w3 :silent only | vs | vs | wincmd H
nnoremap <silent> [SPC]w2 :silent only | vs | wincmd w
nnoremap <silent> [SPC]wS :bel split
nnoremap <silent> [SPC]ws :bel split | wincmd w
nnoremap <silent> [SPC]w- :bel split | wincmd w
nnoremap <silent> [SPC]wv :bel vs | wincmd w
nnoremap <silent> [SPC]w/ :bel vs | wincmd w
nnoremap <silent> [SPC]wo :tabnext
nnoremap <silent> [SPC]wM :ChooseWinSwap
nnoremap <silent> [SPC]wm :only
nnoremap <silent> [SPC]wL :wincmd L
nnoremap <silent> [SPC]wK :wincmd K
nnoremap <silent> [SPC]wJ :wincmd J
nnoremap <silent> [SPC]wH :wincmd H
nnoremap <silent> [SPC]wl :wincmd l
nnoremap <silent> [SPC]wk :wincmd k
nnoremap <silent> [SPC]wj :wincmd j
nnoremap <silent> [SPC]wh :wincmd h
nnoremap <silent> [SPC]wf :tabnew
nnoremap <silent> [SPC]wD :ChooseWin | close | wincmd w
nnoremap <silent> [SPC]wd :close
nnoremap <silent> [SPC]w	 :wincmd w
nnoremap <silent> [SPC]9 :call SpaceVim#layers#core#statusline#jump(9)
nnoremap <silent> [SPC]8 :call SpaceVim#layers#core#statusline#jump(8)
nnoremap <silent> [SPC]7 :call SpaceVim#layers#core#statusline#jump(7)
nnoremap <silent> [SPC]6 :call SpaceVim#layers#core#statusline#jump(6)
nnoremap <silent> [SPC]5 :call SpaceVim#layers#core#statusline#jump(5)
nnoremap <silent> [SPC]4 :call SpaceVim#layers#core#statusline#jump(4)
nnoremap <silent> [SPC]3 :call SpaceVim#layers#core#statusline#jump(3)
nnoremap <silent> [SPC]2 :call SpaceVim#layers#core#statusline#jump(2)
nnoremap <silent> [SPC]1 :call SpaceVim#layers#core#statusline#jump(1)
vnoremap <nowait> <silent> [SPC] :LeaderGuideVisual " "
nnoremap <nowait> <silent> [SPC] :LeaderGuide " "
nnoremap <nowait> <silent> [z] :LeaderGuide "z"
nnoremap <nowait> <silent> [g] :LeaderGuide "g"
nnoremap <silent> [Window]c :call SpaceVim#mapping#clearBuffers()
nnoremap <silent> [Window]q :call SpaceVim#mapping#close_current_buffer()
nnoremap <silent> [Window]Q :close
nnoremap <silent> [Window]\ :b#
nnoremap <silent> [Window]x :call zvim#util#BufferEmpty()
nnoremap <silent> [Window]o :only
nnoremap <silent> [Window]t :tabnew
nnoremap <silent> [Window]g :vsplit
nnoremap <silent> [Window]v :split
nnoremap <silent> [Window]p :vsplit:wincmd w
nnoremap <nowait> <silent> [Window] :LeaderGuide "s"
map \\ <Plug>(easymotion-prefix)
nnoremap <silent> \mt :MinimapToggle
nnoremap <silent> \mc :MinimapClose
nnoremap <silent> \mu :MinimapUpdate
nnoremap <silent> \mm :Minimap
nmap \+ :bnext
nmap \- :bprevious
nmap <silent> \9 :call SpaceVim#layers#core#tabline#jump(9)
nmap <silent> \8 :call SpaceVim#layers#core#tabline#jump(8)
nmap <silent> \7 :call SpaceVim#layers#core#tabline#jump(7)
nmap <silent> \6 :call SpaceVim#layers#core#tabline#jump(6)
nmap <silent> \5 :call SpaceVim#layers#core#tabline#jump(5)
nmap <silent> \4 :call SpaceVim#layers#core#tabline#jump(4)
nmap <silent> \3 :call SpaceVim#layers#core#tabline#jump(3)
nmap <silent> \2 :call SpaceVim#layers#core#tabline#jump(2)
nmap <silent> \1 :call SpaceVim#layers#core#tabline#jump(1)
nnoremap <silent> \lp :Unite -silent -winheight=17 -start-insert menu:AddedPlugins
vnoremap <silent> \ :LeaderGuideVisual get(g:, 'mapleader', '\')
nnoremap <nowait> <silent> \ :LeaderGuide get(g:, 'mapleader', '\')
nnoremap <silent> \qr q
nnoremap \qq :cclose
nnoremap \qk :cprev
nnoremap \qj :cnext
nnoremap \lq :lclose
nnoremap \lk :lprev
nnoremap \lj :lnext
xnoremap \P "+P
xnoremap \p "+p
nnoremap \P "+P
nnoremap \p "+p
xnoremap \d "+d
xnoremap \y "+y
omap <silent> ]% <Plug>(matchup-o_)<Plug>(matchup-]%)
xmap <silent> ]% <Plug>(matchup-]%)
nmap <silent> ]% <Plug>(matchup-]%)
nnoremap <silent> ]p p
nnoremap <silent> ]t :tabnext
nnoremap <silent> ]l :lnext
nnoremap <silent> ]b :bn | stopinsert
nnoremap <silent> ]e :execute 'move +'. v:count1
nnoremap <silent> ]  :put =repeat(nr2char(10), v:count1)
vnoremap <silent> ]<Home> dggP``
vnoremap <silent> ]<End> dGp``
nnoremap <silent> ]<Home> ddggP``
nnoremap <silent> ]<End> ddGp``
omap al <Plug>(textobj-line-a)
xmap al <Plug>(textobj-line-a)
omap ai <Plug>(textobj-indent-a)
xmap ai <Plug>(textobj-indent-a)
omap aI <Plug>(textobj-indent-same-a)
xmap aI <Plug>(textobj-indent-same-a)
omap ae <Plug>(textobj-entire-a)
xmap ae <Plug>(textobj-entire-a)
omap <silent> a% <Plug>(matchup-o_)<Plug>(matchup-a%)
xmap <silent> a% <Plug>(matchup-a%)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
nmap <silent> d<Plug>(easymotion-prefix)l <Plug>(easyoperator-line-delete)
omap f <Plug>(clever-f-f)
xmap f <Plug>(clever-f-f)
nmap f <Plug>(clever-f-f)
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
xmap gS <Plug>VgSurround
omap <silent> g% <Plug>(matchup-o_)<Plug>(matchup-g%)
xmap <silent> g% <Plug>(matchup-g%)
nmap <silent> g% <Plug>(matchup-g%)
xnoremap <silent> gî :call multiple_cursors#select_all("v", 0)
nnoremap <silent> gî :call multiple_cursors#select_all("n", 0)
xnoremap <silent> g :call multiple_cursors#new("v", 0)
nnoremap <silent> g :call multiple_cursors#new("n", 0)
nnoremap <silent> <expr> gp '`['.strpart(getregtype(), 0, 1).'`]'
nnoremap <silent> gd :call SpaceVim#mapping#gd()
nnoremap g g
nnoremap gv gv
nnoremap gs gs
nnoremap go go
nnoremap gm gm
nnoremap gg gg
nnoremap ga ga
nnoremap g~ g~
nnoremap g_ g_
nnoremap g^ g^
nnoremap g] g]
nnoremap gt gt
nnoremap gT gT
nnoremap gR gR
nnoremap gq gq
nnoremap gQ gQ
nnoremap gn gn
nnoremap gN gN
nnoremap gJ gJ
nnoremap gi gi
nnoremap gI gI
nnoremap gh gh
nnoremap gH gH
nnoremap gU gU
nnoremap gE gE
nnoremap gu gu
nnoremap gk gk
nnoremap gj gj
nnoremap gF gF
nnoremap gf gf
nnoremap g< g<
nnoremap ge ge
nnoremap g<Home> g<Home>
nnoremap g<End> g<End>
nnoremap g@ g@
nnoremap g; g;
nnoremap g, g,
nnoremap g- g-
nnoremap g+ g+
nnoremap g` g`
nnoremap g' g'
nnoremap g& g&
nnoremap g g
nmap g [g]
nnoremap <silent> g= :call zvim#format()
nnoremap <silent> gr :tabprevious
nnoremap g$ g$
nnoremap g0 g0
omap il <Plug>(textobj-line-i)
xmap il <Plug>(textobj-line-i)
omap ii <Plug>(textobj-indent-i)
xmap ii <Plug>(textobj-indent-i)
omap iI <Plug>(textobj-indent-same-i)
xmap iI <Plug>(textobj-indent-same-i)
omap ie <Plug>(textobj-entire-i)
xmap ie <Plug>(textobj-entire-i)
omap <silent> i% <Plug>(matchup-o_)<Plug>(matchup-i%)
xmap <silent> i% <Plug>(matchup-i%)
nnoremap <silent> q :call zvim#util#SmartClose()
nmap s [Window]
omap t <Plug>(clever-f-t)
xmap t <Plug>(clever-f-t)
nmap t <Plug>(clever-f-t)
omap <silent> va% <Plug>(matchup-o_v)<Plug>(matchup-a%)
omap <silent> vi% <Plug>(matchup-o_v)<Plug>(matchup-i%)
omap <silent> vz% <Plug>(matchup-o_v)<Plug>(matchup-z%)
omap <silent> v[% <Plug>(matchup-o_v)<Plug>(matchup-[%)
omap <silent> v]% <Plug>(matchup-o_v)<Plug>(matchup-]%)
omap <silent> vg% <Plug>(matchup-o_v)<Plug>(matchup-g%)
omap <silent> v% <Plug>(matchup-o_v)<Plug>(matchup-%)
xmap v <Plug>(expand_region_expand)
map w= :wincmd=
map w| :wincmd|
map w- :wincmd_
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nmap <silent> y<Plug>(easymotion-prefix)l <Plug>(easyoperator-line-yank)
omap <silent> z% <Plug>(matchup-o_)<Plug>(matchup-z%)
xmap <silent> z% <Plug>(matchup-z%)
nmap <silent> z% <Plug>(matchup-z%)
nnoremap zx zx
nnoremap zv zv
nnoremap zt zt
nnoremap zs zs
nnoremap zr zr
nnoremap zo zo
nnoremap zn zn
nnoremap zm zm
nnoremap z<Right> zl
nnoremap zl zl
nnoremap zk zk
nnoremap zj zj
nnoremap zi zi
nnoremap z<Left> zh
nnoremap zh zh
nnoremap zg zg
nnoremap zf zf
nnoremap ze ze
nnoremap zd zd
nnoremap zc zc
nnoremap zb zb
nnoremap za za
nnoremap zX zX
nnoremap zW zW
nnoremap zR zR
nnoremap zO zO
nnoremap zN zN
nnoremap zM zM
nnoremap zL zL
nnoremap zH zH
nnoremap zG zG
nnoremap zF zF
nnoremap zE zE
nnoremap zD zD
nnoremap zC zC
nnoremap zA zA
nnoremap z= z=
nnoremap z. z.
nnoremap z^ z^
nnoremap z- z-
nnoremap z+ z+
nnoremap z z
nmap z [z]
nnoremap zz zz
xnoremap <silent> <Plug>(neosnippet_register_oneshot_snippet) :call neosnippet#mappings#_register_oneshot_snippet()
xnoremap <silent> <Plug>(neosnippet_expand_target) :call neosnippet#mappings#_expand_target()
xnoremap <silent> <Plug>(neosnippet_get_selected_text) :call neosnippet#helpers#get_selected_text(visualmode(), 1)
snoremap <silent> <expr> <Plug>(neosnippet_jump) neosnippet#mappings#jump_impl()
snoremap <silent> <expr> <Plug>(neosnippet_expand) neosnippet#mappings#expand_impl()
snoremap <silent> <expr> <Plug>(neosnippet_jump_or_expand) neosnippet#mappings#jump_or_expand_impl()
snoremap <silent> <expr> <Plug>(neosnippet_expand_or_jump) neosnippet#mappings#expand_or_jump_impl()
nnoremap <silent> <Plug>(vimfiler_simple) :VimFilerSimple
nnoremap <silent> <Plug>(vimfiler_create) :VimFilerCreate
nnoremap <silent> <Plug>(vimfiler_switch) :VimFiler
nnoremap <silent> <Plug>(vimfiler_split_create) :VimFilerSplit
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
nnoremap <silent> <Plug>SurroundRepeat .
nmap <silent> <2-LeftMouse> <Plug>(matchup-double-click)
nnoremap <Plug>(matchup-reload) :MatchupReload
nnoremap <silent> <Plug>(matchup-double-click) :call matchup#text_obj#double_click()
onoremap <silent> <Plug>(matchup-a%) :call matchup#text_obj#delimited(0, 0, 'delim_all')
onoremap <silent> <Plug>(matchup-i%) :call matchup#text_obj#delimited(1, 0, 'delim_all')
xnoremap <silent> <Plug>(matchup-a%) :call matchup#text_obj#delimited(0, 1, 'delim_all')
xnoremap <silent> <Plug>(matchup-i%) :call matchup#text_obj#delimited(1, 1, 'delim_all')
onoremap <silent> <Plug>(matchup-z%) :call matchup#motion#op('z%')
xnoremap <silent> <SNR>134_(matchup-z%) :call matchup#motion#jump_inside(1)
nnoremap <silent> <Plug>(matchup-z%) :call matchup#motion#jump_inside(0)
onoremap <silent> <Plug>(matchup-[%) :call matchup#motion#op('[%')
onoremap <silent> <Plug>(matchup-]%) :call matchup#motion#op(']%')
xnoremap <silent> <SNR>134_(matchup-[%) :call matchup#motion#find_unmatched(1, 0)
xnoremap <silent> <SNR>134_(matchup-]%) :call matchup#motion#find_unmatched(1, 1)
nnoremap <silent> <Plug>(matchup-[%) :call matchup#motion#find_unmatched(0, 0)
nnoremap <silent> <Plug>(matchup-]%) :call matchup#motion#find_unmatched(0, 1)
onoremap <silent> <Plug>(matchup-g%) :call matchup#motion#op('g%')
xnoremap <silent> <SNR>134_(matchup-g%) :call matchup#motion#find_matching_pair(1, 0)
onoremap <silent> <Plug>(matchup-%) :call matchup#motion#op('%')
xnoremap <silent> <SNR>134_(matchup-%) :call matchup#motion#find_matching_pair(1, 1)
nnoremap <silent> <Plug>(matchup-g%) :call matchup#motion#find_matching_pair(0, 0)
nnoremap <silent> <Plug>(matchup-%) :call matchup#motion#find_matching_pair(0, 1)
nnoremap <silent> <expr> <SNR>134_(wise) empty(g:v_motion_force) ? 'v' : g:v_motion_force
nnoremap <silent> <Plug>(matchup-hi-surround) :call matchup#matchparen#highlight_surrounding()
xnoremap <silent> <Plug>(expand_region_shrink) :call expand_region#next('v', '-')
xnoremap <silent> <Plug>(expand_region_expand) :call expand_region#next('v', '+')
nnoremap <silent> <Plug>(expand_region_expand) :call expand_region#next('n', '+')
xmap <silent> <Plug>(easymotion-prefix)l <Plug>(easyoperator-line-select)
omap <silent> <Plug>(easymotion-prefix)l <Plug>(easyoperator-line-select)
nnoremap <Plug>(easyoperator-line-yank) :call easyoperator#line#selectlinesyank()
nnoremap <Plug>(easyoperator-line-delete) :call easyoperator#line#selectlinesdelete()
xnoremap <Plug>(easyoperator-line-select) :call easyoperator#line#selectlines()
onoremap <Plug>(easyoperator-line-select) :call easyoperator#line#selectlines()
nnoremap <Plug>(easyoperator-line-select) :call easyoperator#line#selectlines()
noremap <silent> <expr> <Plug>(clever-f-repeat-back) clever_f#repeat(1)
noremap <silent> <expr> <Plug>(clever-f-repeat-forward) clever_f#repeat(0)
noremap <silent> <expr> <Plug>(clever-f-reset) clever_f#reset()
noremap <silent> <expr> <Plug>(clever-f-T) clever_f#find_with('T')
noremap <silent> <expr> <Plug>(clever-f-t) clever_f#find_with('t')
noremap <silent> <expr> <Plug>(clever-f-F) clever_f#find_with('F')
noremap <silent> <expr> <Plug>(clever-f-f) clever_f#find_with('f')
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
map <silent> <Plug>(easymotion-prefix)N <Plug>(easymotion-N)
map <silent> <Plug>(easymotion-prefix)n <Plug>(easymotion-n)
map <silent> <Plug>(easymotion-prefix)k <Plug>(easymotion-k)
map <silent> <Plug>(easymotion-prefix)j <Plug>(easymotion-j)
map <silent> <Plug>(easymotion-prefix)gE <Plug>(easymotion-gE)
map <silent> <Plug>(easymotion-prefix)ge <Plug>(easymotion-ge)
map <silent> <Plug>(easymotion-prefix)E <Plug>(easymotion-E)
map <silent> <Plug>(easymotion-prefix)e <Plug>(easymotion-e)
map <silent> <Plug>(easymotion-prefix)B <Plug>(easymotion-B)
map <silent> <Plug>(easymotion-prefix)b <Plug>(easymotion-b)
map <silent> <Plug>(easymotion-prefix)W <Plug>(easymotion-W)
map <silent> <Plug>(easymotion-prefix)w <Plug>(easymotion-w)
map <silent> <Plug>(easymotion-prefix)T <Plug>(easymotion-T)
map <silent> <Plug>(easymotion-prefix)t <Plug>(easymotion-t)
map <silent> <Plug>(easymotion-prefix)s <Plug>(easymotion-s)
map <silent> <Plug>(easymotion-prefix)F <Plug>(easymotion-F)
map <silent> <Plug>(easymotion-prefix)f <Plug>(easymotion-f)
xnoremap <silent> <Plug>(easymotion-activate) :call EasyMotion#activate(1)
nnoremap <silent> <Plug>(easymotion-activate) :call EasyMotion#activate(0)
snoremap <silent> <Plug>(easymotion-activate) :call EasyMotion#activate(0)
onoremap <silent> <Plug>(easymotion-activate) :call EasyMotion#activate(0)
noremap <silent> <Plug>(easymotion-dotrepeat) :call EasyMotion#DotRepeat()
xnoremap <silent> <Plug>(easymotion-repeat) :call EasyMotion#Repeat(1)
nnoremap <silent> <Plug>(easymotion-repeat) :call EasyMotion#Repeat(0)
snoremap <silent> <Plug>(easymotion-repeat) :call EasyMotion#Repeat(0)
onoremap <silent> <Plug>(easymotion-repeat) :call EasyMotion#Repeat(0)
xnoremap <silent> <Plug>(easymotion-prev) :call EasyMotion#NextPrevious(1,1)
nnoremap <silent> <Plug>(easymotion-prev) :call EasyMotion#NextPrevious(0,1)
snoremap <silent> <Plug>(easymotion-prev) :call EasyMotion#NextPrevious(0,1)
onoremap <silent> <Plug>(easymotion-prev) :call EasyMotion#NextPrevious(0,1)
xnoremap <silent> <Plug>(easymotion-next) :call EasyMotion#NextPrevious(1,0)
nnoremap <silent> <Plug>(easymotion-next) :call EasyMotion#NextPrevious(0,0)
snoremap <silent> <Plug>(easymotion-next) :call EasyMotion#NextPrevious(0,0)
onoremap <silent> <Plug>(easymotion-next) :call EasyMotion#NextPrevious(0,0)
xnoremap <silent> <Plug>(easymotion-wl) :call EasyMotion#WBL(1,0)
nnoremap <silent> <Plug>(easymotion-wl) :call EasyMotion#WBL(0,0)
snoremap <silent> <Plug>(easymotion-wl) :call EasyMotion#WBL(0,0)
onoremap <silent> <Plug>(easymotion-wl) :call EasyMotion#WBL(0,0)
xnoremap <silent> <Plug>(easymotion-lineforward) :call EasyMotion#LineAnywhere(1,0)
nnoremap <silent> <Plug>(easymotion-lineforward) :call EasyMotion#LineAnywhere(0,0)
snoremap <silent> <Plug>(easymotion-lineforward) :call EasyMotion#LineAnywhere(0,0)
onoremap <silent> <Plug>(easymotion-lineforward) :call EasyMotion#LineAnywhere(0,0)
xnoremap <silent> <Plug>(easymotion-lineanywhere) :call EasyMotion#LineAnywhere(1,2)
nnoremap <silent> <Plug>(easymotion-lineanywhere) :call EasyMotion#LineAnywhere(0,2)
snoremap <silent> <Plug>(easymotion-lineanywhere) :call EasyMotion#LineAnywhere(0,2)
onoremap <silent> <Plug>(easymotion-lineanywhere) :call EasyMotion#LineAnywhere(0,2)
xnoremap <silent> <Plug>(easymotion-bd-wl) :call EasyMotion#WBL(1,2)
nnoremap <silent> <Plug>(easymotion-bd-wl) :call EasyMotion#WBL(0,2)
snoremap <silent> <Plug>(easymotion-bd-wl) :call EasyMotion#WBL(0,2)
onoremap <silent> <Plug>(easymotion-bd-wl) :call EasyMotion#WBL(0,2)
xnoremap <silent> <Plug>(easymotion-linebackward) :call EasyMotion#LineAnywhere(1,1)
nnoremap <silent> <Plug>(easymotion-linebackward) :call EasyMotion#LineAnywhere(0,1)
snoremap <silent> <Plug>(easymotion-linebackward) :call EasyMotion#LineAnywhere(0,1)
onoremap <silent> <Plug>(easymotion-linebackward) :call EasyMotion#LineAnywhere(0,1)
xnoremap <silent> <Plug>(easymotion-bl) :call EasyMotion#WBL(1,1)
nnoremap <silent> <Plug>(easymotion-bl) :call EasyMotion#WBL(0,1)
snoremap <silent> <Plug>(easymotion-bl) :call EasyMotion#WBL(0,1)
onoremap <silent> <Plug>(easymotion-bl) :call EasyMotion#WBL(0,1)
xnoremap <silent> <Plug>(easymotion-el) :call EasyMotion#EL(1,0)
nnoremap <silent> <Plug>(easymotion-el) :call EasyMotion#EL(0,0)
snoremap <silent> <Plug>(easymotion-el) :call EasyMotion#EL(0,0)
onoremap <silent> <Plug>(easymotion-el) :call EasyMotion#EL(0,0)
xnoremap <silent> <Plug>(easymotion-gel) :call EasyMotion#EL(1,1)
nnoremap <silent> <Plug>(easymotion-gel) :call EasyMotion#EL(0,1)
snoremap <silent> <Plug>(easymotion-gel) :call EasyMotion#EL(0,1)
onoremap <silent> <Plug>(easymotion-gel) :call EasyMotion#EL(0,1)
xnoremap <silent> <Plug>(easymotion-bd-el) :call EasyMotion#EL(1,2)
nnoremap <silent> <Plug>(easymotion-bd-el) :call EasyMotion#EL(0,2)
snoremap <silent> <Plug>(easymotion-bd-el) :call EasyMotion#EL(0,2)
onoremap <silent> <Plug>(easymotion-bd-el) :call EasyMotion#EL(0,2)
xnoremap <silent> <Plug>(easymotion-jumptoanywhere) :call EasyMotion#JumpToAnywhere(1,2)
nnoremap <silent> <Plug>(easymotion-jumptoanywhere) :call EasyMotion#JumpToAnywhere(0,2)
snoremap <silent> <Plug>(easymotion-jumptoanywhere) :call EasyMotion#JumpToAnywhere(0,2)
onoremap <silent> <Plug>(easymotion-jumptoanywhere) :call EasyMotion#JumpToAnywhere(0,2)
xnoremap <silent> <Plug>(easymotion-vim-n) :call EasyMotion#Search(1,0,1)
nnoremap <silent> <Plug>(easymotion-vim-n) :call EasyMotion#Search(0,0,1)
snoremap <silent> <Plug>(easymotion-vim-n) :call EasyMotion#Search(0,0,1)
onoremap <silent> <Plug>(easymotion-vim-n) :call EasyMotion#Search(0,0,1)
xnoremap <silent> <Plug>(easymotion-n) :call EasyMotion#Search(1,0,0)
nnoremap <silent> <Plug>(easymotion-n) :call EasyMotion#Search(0,0,0)
snoremap <silent> <Plug>(easymotion-n) :call EasyMotion#Search(0,0,0)
onoremap <silent> <Plug>(easymotion-n) :call EasyMotion#Search(0,0,0)
xnoremap <silent> <Plug>(easymotion-bd-n) :call EasyMotion#Search(1,2,0)
nnoremap <silent> <Plug>(easymotion-bd-n) :call EasyMotion#Search(0,2,0)
snoremap <silent> <Plug>(easymotion-bd-n) :call EasyMotion#Search(0,2,0)
onoremap <silent> <Plug>(easymotion-bd-n) :call EasyMotion#Search(0,2,0)
xnoremap <silent> <Plug>(easymotion-vim-N) :call EasyMotion#Search(1,1,1)
nnoremap <silent> <Plug>(easymotion-vim-N) :call EasyMotion#Search(0,1,1)
snoremap <silent> <Plug>(easymotion-vim-N) :call EasyMotion#Search(0,1,1)
onoremap <silent> <Plug>(easymotion-vim-N) :call EasyMotion#Search(0,1,1)
xnoremap <silent> <Plug>(easymotion-N) :call EasyMotion#Search(1,1,0)
nnoremap <silent> <Plug>(easymotion-N) :call EasyMotion#Search(0,1,0)
snoremap <silent> <Plug>(easymotion-N) :call EasyMotion#Search(0,1,0)
onoremap <silent> <Plug>(easymotion-N) :call EasyMotion#Search(0,1,0)
xnoremap <silent> <Plug>(easymotion-eol-j) :call EasyMotion#Eol(1,0)
nnoremap <silent> <Plug>(easymotion-eol-j) :call EasyMotion#Eol(0,0)
snoremap <silent> <Plug>(easymotion-eol-j) :call EasyMotion#Eol(0,0)
onoremap <silent> <Plug>(easymotion-eol-j) :call EasyMotion#Eol(0,0)
xnoremap <silent> <Plug>(easymotion-sol-k) :call EasyMotion#Sol(1,1)
nnoremap <silent> <Plug>(easymotion-sol-k) :call EasyMotion#Sol(0,1)
snoremap <silent> <Plug>(easymotion-sol-k) :call EasyMotion#Sol(0,1)
onoremap <silent> <Plug>(easymotion-sol-k) :call EasyMotion#Sol(0,1)
xnoremap <silent> <Plug>(easymotion-sol-j) :call EasyMotion#Sol(1,0)
nnoremap <silent> <Plug>(easymotion-sol-j) :call EasyMotion#Sol(0,0)
snoremap <silent> <Plug>(easymotion-sol-j) :call EasyMotion#Sol(0,0)
onoremap <silent> <Plug>(easymotion-sol-j) :call EasyMotion#Sol(0,0)
xnoremap <silent> <Plug>(easymotion-k) :call EasyMotion#JK(1,1)
nnoremap <silent> <Plug>(easymotion-k) :call EasyMotion#JK(0,1)
snoremap <silent> <Plug>(easymotion-k) :call EasyMotion#JK(0,1)
onoremap <silent> <Plug>(easymotion-k) :call EasyMotion#JK(0,1)
xnoremap <silent> <Plug>(easymotion-j) :call EasyMotion#JK(1,0)
nnoremap <silent> <Plug>(easymotion-j) :call EasyMotion#JK(0,0)
snoremap <silent> <Plug>(easymotion-j) :call EasyMotion#JK(0,0)
onoremap <silent> <Plug>(easymotion-j) :call EasyMotion#JK(0,0)
xnoremap <silent> <Plug>(easymotion-bd-jk) :call EasyMotion#JK(1,2)
nnoremap <silent> <Plug>(easymotion-bd-jk) :call EasyMotion#JK(0,2)
snoremap <silent> <Plug>(easymotion-bd-jk) :call EasyMotion#JK(0,2)
onoremap <silent> <Plug>(easymotion-bd-jk) :call EasyMotion#JK(0,2)
xnoremap <silent> <Plug>(easymotion-eol-bd-jk) :call EasyMotion#Eol(1,2)
nnoremap <silent> <Plug>(easymotion-eol-bd-jk) :call EasyMotion#Eol(0,2)
snoremap <silent> <Plug>(easymotion-eol-bd-jk) :call EasyMotion#Eol(0,2)
onoremap <silent> <Plug>(easymotion-eol-bd-jk) :call EasyMotion#Eol(0,2)
xnoremap <silent> <Plug>(easymotion-sol-bd-jk) :call EasyMotion#Sol(1,2)
nnoremap <silent> <Plug>(easymotion-sol-bd-jk) :call EasyMotion#Sol(0,2)
snoremap <silent> <Plug>(easymotion-sol-bd-jk) :call EasyMotion#Sol(0,2)
onoremap <silent> <Plug>(easymotion-sol-bd-jk) :call EasyMotion#Sol(0,2)
xnoremap <silent> <Plug>(easymotion-eol-k) :call EasyMotion#Eol(1,1)
nnoremap <silent> <Plug>(easymotion-eol-k) :call EasyMotion#Eol(0,1)
snoremap <silent> <Plug>(easymotion-eol-k) :call EasyMotion#Eol(0,1)
onoremap <silent> <Plug>(easymotion-eol-k) :call EasyMotion#Eol(0,1)
xnoremap <silent> <Plug>(easymotion-iskeyword-ge) :call EasyMotion#EK(1,1)
nnoremap <silent> <Plug>(easymotion-iskeyword-ge) :call EasyMotion#EK(0,1)
snoremap <silent> <Plug>(easymotion-iskeyword-ge) :call EasyMotion#EK(0,1)
onoremap <silent> <Plug>(easymotion-iskeyword-ge) :call EasyMotion#EK(0,1)
xnoremap <silent> <Plug>(easymotion-w) :call EasyMotion#WB(1,0)
nnoremap <silent> <Plug>(easymotion-w) :call EasyMotion#WB(0,0)
snoremap <silent> <Plug>(easymotion-w) :call EasyMotion#WB(0,0)
onoremap <silent> <Plug>(easymotion-w) :call EasyMotion#WB(0,0)
xnoremap <silent> <Plug>(easymotion-bd-W) :call EasyMotion#WBW(1,2)
nnoremap <silent> <Plug>(easymotion-bd-W) :call EasyMotion#WBW(0,2)
snoremap <silent> <Plug>(easymotion-bd-W) :call EasyMotion#WBW(0,2)
onoremap <silent> <Plug>(easymotion-bd-W) :call EasyMotion#WBW(0,2)
xnoremap <silent> <Plug>(easymotion-iskeyword-w) :call EasyMotion#WBK(1,0)
nnoremap <silent> <Plug>(easymotion-iskeyword-w) :call EasyMotion#WBK(0,0)
snoremap <silent> <Plug>(easymotion-iskeyword-w) :call EasyMotion#WBK(0,0)
onoremap <silent> <Plug>(easymotion-iskeyword-w) :call EasyMotion#WBK(0,0)
xnoremap <silent> <Plug>(easymotion-gE) :call EasyMotion#EW(1,1)
nnoremap <silent> <Plug>(easymotion-gE) :call EasyMotion#EW(0,1)
snoremap <silent> <Plug>(easymotion-gE) :call EasyMotion#EW(0,1)
onoremap <silent> <Plug>(easymotion-gE) :call EasyMotion#EW(0,1)
xnoremap <silent> <Plug>(easymotion-e) :call EasyMotion#E(1,0)
nnoremap <silent> <Plug>(easymotion-e) :call EasyMotion#E(0,0)
snoremap <silent> <Plug>(easymotion-e) :call EasyMotion#E(0,0)
onoremap <silent> <Plug>(easymotion-e) :call EasyMotion#E(0,0)
xnoremap <silent> <Plug>(easymotion-bd-E) :call EasyMotion#EW(1,2)
nnoremap <silent> <Plug>(easymotion-bd-E) :call EasyMotion#EW(0,2)
snoremap <silent> <Plug>(easymotion-bd-E) :call EasyMotion#EW(0,2)
onoremap <silent> <Plug>(easymotion-bd-E) :call EasyMotion#EW(0,2)
xnoremap <silent> <Plug>(easymotion-iskeyword-e) :call EasyMotion#EK(1,0)
nnoremap <silent> <Plug>(easymotion-iskeyword-e) :call EasyMotion#EK(0,0)
snoremap <silent> <Plug>(easymotion-iskeyword-e) :call EasyMotion#EK(0,0)
onoremap <silent> <Plug>(easymotion-iskeyword-e) :call EasyMotion#EK(0,0)
xnoremap <silent> <Plug>(easymotion-b) :call EasyMotion#WB(1,1)
nnoremap <silent> <Plug>(easymotion-b) :call EasyMotion#WB(0,1)
snoremap <silent> <Plug>(easymotion-b) :call EasyMotion#WB(0,1)
onoremap <silent> <Plug>(easymotion-b) :call EasyMotion#WB(0,1)
xnoremap <silent> <Plug>(easymotion-iskeyword-b) :call EasyMotion#WBK(1,1)
nnoremap <silent> <Plug>(easymotion-iskeyword-b) :call EasyMotion#WBK(0,1)
snoremap <silent> <Plug>(easymotion-iskeyword-b) :call EasyMotion#WBK(0,1)
onoremap <silent> <Plug>(easymotion-iskeyword-b) :call EasyMotion#WBK(0,1)
xnoremap <silent> <Plug>(easymotion-iskeyword-bd-w) :call EasyMotion#WBK(1,2)
nnoremap <silent> <Plug>(easymotion-iskeyword-bd-w) :call EasyMotion#WBK(0,2)
snoremap <silent> <Plug>(easymotion-iskeyword-bd-w) :call EasyMotion#WBK(0,2)
onoremap <silent> <Plug>(easymotion-iskeyword-bd-w) :call EasyMotion#WBK(0,2)
xnoremap <silent> <Plug>(easymotion-W) :call EasyMotion#WBW(1,0)
nnoremap <silent> <Plug>(easymotion-W) :call EasyMotion#WBW(0,0)
snoremap <silent> <Plug>(easymotion-W) :call EasyMotion#WBW(0,0)
onoremap <silent> <Plug>(easymotion-W) :call EasyMotion#WBW(0,0)
xnoremap <silent> <Plug>(easymotion-bd-w) :call EasyMotion#WB(1,2)
nnoremap <silent> <Plug>(easymotion-bd-w) :call EasyMotion#WB(0,2)
snoremap <silent> <Plug>(easymotion-bd-w) :call EasyMotion#WB(0,2)
onoremap <silent> <Plug>(easymotion-bd-w) :call EasyMotion#WB(0,2)
xnoremap <silent> <Plug>(easymotion-iskeyword-bd-e) :call EasyMotion#EK(1,2)
nnoremap <silent> <Plug>(easymotion-iskeyword-bd-e) :call EasyMotion#EK(0,2)
snoremap <silent> <Plug>(easymotion-iskeyword-bd-e) :call EasyMotion#EK(0,2)
onoremap <silent> <Plug>(easymotion-iskeyword-bd-e) :call EasyMotion#EK(0,2)
xnoremap <silent> <Plug>(easymotion-ge) :call EasyMotion#E(1,1)
nnoremap <silent> <Plug>(easymotion-ge) :call EasyMotion#E(0,1)
snoremap <silent> <Plug>(easymotion-ge) :call EasyMotion#E(0,1)
onoremap <silent> <Plug>(easymotion-ge) :call EasyMotion#E(0,1)
xnoremap <silent> <Plug>(easymotion-E) :call EasyMotion#EW(1,0)
nnoremap <silent> <Plug>(easymotion-E) :call EasyMotion#EW(0,0)
snoremap <silent> <Plug>(easymotion-E) :call EasyMotion#EW(0,0)
onoremap <silent> <Plug>(easymotion-E) :call EasyMotion#EW(0,0)
xnoremap <silent> <Plug>(easymotion-bd-e) :call EasyMotion#E(1,2)
nnoremap <silent> <Plug>(easymotion-bd-e) :call EasyMotion#E(0,2)
snoremap <silent> <Plug>(easymotion-bd-e) :call EasyMotion#E(0,2)
onoremap <silent> <Plug>(easymotion-bd-e) :call EasyMotion#E(0,2)
xnoremap <silent> <Plug>(easymotion-B) :call EasyMotion#WBW(1,1)
nnoremap <silent> <Plug>(easymotion-B) :call EasyMotion#WBW(0,1)
snoremap <silent> <Plug>(easymotion-B) :call EasyMotion#WBW(0,1)
onoremap <silent> <Plug>(easymotion-B) :call EasyMotion#WBW(0,1)
nnoremap <silent> <Plug>(easymotion-overwin-w) :call EasyMotion#overwin#w()
nnoremap <silent> <Plug>(easymotion-overwin-line) :call EasyMotion#overwin#line()
nnoremap <silent> <Plug>(easymotion-overwin-f2) :call EasyMotion#OverwinF(2)
nnoremap <silent> <Plug>(easymotion-overwin-f) :call EasyMotion#OverwinF(1)
xnoremap <silent> <Plug>(easymotion-Tln) :call EasyMotion#TL(-1,1,1)
nnoremap <silent> <Plug>(easymotion-Tln) :call EasyMotion#TL(-1,0,1)
snoremap <silent> <Plug>(easymotion-Tln) :call EasyMotion#TL(-1,0,1)
onoremap <silent> <Plug>(easymotion-Tln) :call EasyMotion#TL(-1,0,1)
xnoremap <silent> <Plug>(easymotion-t2) :call EasyMotion#T(2,1,0)
nnoremap <silent> <Plug>(easymotion-t2) :call EasyMotion#T(2,0,0)
snoremap <silent> <Plug>(easymotion-t2) :call EasyMotion#T(2,0,0)
onoremap <silent> <Plug>(easymotion-t2) :call EasyMotion#T(2,0,0)
xnoremap <silent> <Plug>(easymotion-t) :call EasyMotion#T(1,1,0)
nnoremap <silent> <Plug>(easymotion-t) :call EasyMotion#T(1,0,0)
snoremap <silent> <Plug>(easymotion-t) :call EasyMotion#T(1,0,0)
onoremap <silent> <Plug>(easymotion-t) :call EasyMotion#T(1,0,0)
xnoremap <silent> <Plug>(easymotion-s) :call EasyMotion#S(1,1,2)
nnoremap <silent> <Plug>(easymotion-s) :call EasyMotion#S(1,0,2)
snoremap <silent> <Plug>(easymotion-s) :call EasyMotion#S(1,0,2)
onoremap <silent> <Plug>(easymotion-s) :call EasyMotion#S(1,0,2)
xnoremap <silent> <Plug>(easymotion-tn) :call EasyMotion#T(-1,1,0)
nnoremap <silent> <Plug>(easymotion-tn) :call EasyMotion#T(-1,0,0)
snoremap <silent> <Plug>(easymotion-tn) :call EasyMotion#T(-1,0,0)
onoremap <silent> <Plug>(easymotion-tn) :call EasyMotion#T(-1,0,0)
xnoremap <silent> <Plug>(easymotion-bd-t2) :call EasyMotion#T(2,1,2)
nnoremap <silent> <Plug>(easymotion-bd-t2) :call EasyMotion#T(2,0,2)
snoremap <silent> <Plug>(easymotion-bd-t2) :call EasyMotion#T(2,0,2)
onoremap <silent> <Plug>(easymotion-bd-t2) :call EasyMotion#T(2,0,2)
xnoremap <silent> <Plug>(easymotion-tl) :call EasyMotion#TL(1,1,0)
nnoremap <silent> <Plug>(easymotion-tl) :call EasyMotion#TL(1,0,0)
snoremap <silent> <Plug>(easymotion-tl) :call EasyMotion#TL(1,0,0)
onoremap <silent> <Plug>(easymotion-tl) :call EasyMotion#TL(1,0,0)
xnoremap <silent> <Plug>(easymotion-bd-tn) :call EasyMotion#T(-1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-tn) :call EasyMotion#T(-1,0,2)
snoremap <silent> <Plug>(easymotion-bd-tn) :call EasyMotion#T(-1,0,2)
onoremap <silent> <Plug>(easymotion-bd-tn) :call EasyMotion#T(-1,0,2)
xnoremap <silent> <Plug>(easymotion-fn) :call EasyMotion#S(-1,1,0)
nnoremap <silent> <Plug>(easymotion-fn) :call EasyMotion#S(-1,0,0)
snoremap <silent> <Plug>(easymotion-fn) :call EasyMotion#S(-1,0,0)
onoremap <silent> <Plug>(easymotion-fn) :call EasyMotion#S(-1,0,0)
xnoremap <silent> <Plug>(easymotion-bd-tl) :call EasyMotion#TL(1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-tl) :call EasyMotion#TL(1,0,2)
snoremap <silent> <Plug>(easymotion-bd-tl) :call EasyMotion#TL(1,0,2)
onoremap <silent> <Plug>(easymotion-bd-tl) :call EasyMotion#TL(1,0,2)
xnoremap <silent> <Plug>(easymotion-fl) :call EasyMotion#SL(1,1,0)
nnoremap <silent> <Plug>(easymotion-fl) :call EasyMotion#SL(1,0,0)
snoremap <silent> <Plug>(easymotion-fl) :call EasyMotion#SL(1,0,0)
onoremap <silent> <Plug>(easymotion-fl) :call EasyMotion#SL(1,0,0)
xnoremap <silent> <Plug>(easymotion-bd-tl2) :call EasyMotion#TL(2,1,2)
nnoremap <silent> <Plug>(easymotion-bd-tl2) :call EasyMotion#TL(2,0,2)
snoremap <silent> <Plug>(easymotion-bd-tl2) :call EasyMotion#TL(2,0,2)
onoremap <silent> <Plug>(easymotion-bd-tl2) :call EasyMotion#TL(2,0,2)
xnoremap <silent> <Plug>(easymotion-bd-fn) :call EasyMotion#S(-1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-fn) :call EasyMotion#S(-1,0,2)
snoremap <silent> <Plug>(easymotion-bd-fn) :call EasyMotion#S(-1,0,2)
onoremap <silent> <Plug>(easymotion-bd-fn) :call EasyMotion#S(-1,0,2)
xnoremap <silent> <Plug>(easymotion-f) :call EasyMotion#S(1,1,0)
nnoremap <silent> <Plug>(easymotion-f) :call EasyMotion#S(1,0,0)
snoremap <silent> <Plug>(easymotion-f) :call EasyMotion#S(1,0,0)
onoremap <silent> <Plug>(easymotion-f) :call EasyMotion#S(1,0,0)
xnoremap <silent> <Plug>(easymotion-bd-fl) :call EasyMotion#SL(1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-fl) :call EasyMotion#SL(1,0,2)
snoremap <silent> <Plug>(easymotion-bd-fl) :call EasyMotion#SL(1,0,2)
onoremap <silent> <Plug>(easymotion-bd-fl) :call EasyMotion#SL(1,0,2)
xnoremap <silent> <Plug>(easymotion-Fl2) :call EasyMotion#SL(2,1,1)
nnoremap <silent> <Plug>(easymotion-Fl2) :call EasyMotion#SL(2,0,1)
snoremap <silent> <Plug>(easymotion-Fl2) :call EasyMotion#SL(2,0,1)
onoremap <silent> <Plug>(easymotion-Fl2) :call EasyMotion#SL(2,0,1)
xnoremap <silent> <Plug>(easymotion-tl2) :call EasyMotion#TL(2,1,0)
nnoremap <silent> <Plug>(easymotion-tl2) :call EasyMotion#TL(2,0,0)
snoremap <silent> <Plug>(easymotion-tl2) :call EasyMotion#TL(2,0,0)
onoremap <silent> <Plug>(easymotion-tl2) :call EasyMotion#TL(2,0,0)
xnoremap <silent> <Plug>(easymotion-f2) :call EasyMotion#S(2,1,0)
nnoremap <silent> <Plug>(easymotion-f2) :call EasyMotion#S(2,0,0)
snoremap <silent> <Plug>(easymotion-f2) :call EasyMotion#S(2,0,0)
onoremap <silent> <Plug>(easymotion-f2) :call EasyMotion#S(2,0,0)
xnoremap <silent> <Plug>(easymotion-Fln) :call EasyMotion#SL(-1,1,1)
nnoremap <silent> <Plug>(easymotion-Fln) :call EasyMotion#SL(-1,0,1)
snoremap <silent> <Plug>(easymotion-Fln) :call EasyMotion#SL(-1,0,1)
onoremap <silent> <Plug>(easymotion-Fln) :call EasyMotion#SL(-1,0,1)
xnoremap <silent> <Plug>(easymotion-sln) :call EasyMotion#SL(-1,1,2)
nnoremap <silent> <Plug>(easymotion-sln) :call EasyMotion#SL(-1,0,2)
snoremap <silent> <Plug>(easymotion-sln) :call EasyMotion#SL(-1,0,2)
onoremap <silent> <Plug>(easymotion-sln) :call EasyMotion#SL(-1,0,2)
xnoremap <silent> <Plug>(easymotion-tln) :call EasyMotion#TL(-1,1,0)
nnoremap <silent> <Plug>(easymotion-tln) :call EasyMotion#TL(-1,0,0)
snoremap <silent> <Plug>(easymotion-tln) :call EasyMotion#TL(-1,0,0)
onoremap <silent> <Plug>(easymotion-tln) :call EasyMotion#TL(-1,0,0)
xnoremap <silent> <Plug>(easymotion-fl2) :call EasyMotion#SL(2,1,0)
nnoremap <silent> <Plug>(easymotion-fl2) :call EasyMotion#SL(2,0,0)
snoremap <silent> <Plug>(easymotion-fl2) :call EasyMotion#SL(2,0,0)
onoremap <silent> <Plug>(easymotion-fl2) :call EasyMotion#SL(2,0,0)
xnoremap <silent> <Plug>(easymotion-bd-fl2) :call EasyMotion#SL(2,1,2)
nnoremap <silent> <Plug>(easymotion-bd-fl2) :call EasyMotion#SL(2,0,2)
snoremap <silent> <Plug>(easymotion-bd-fl2) :call EasyMotion#SL(2,0,2)
onoremap <silent> <Plug>(easymotion-bd-fl2) :call EasyMotion#SL(2,0,2)
xnoremap <silent> <Plug>(easymotion-T2) :call EasyMotion#T(2,1,1)
nnoremap <silent> <Plug>(easymotion-T2) :call EasyMotion#T(2,0,1)
snoremap <silent> <Plug>(easymotion-T2) :call EasyMotion#T(2,0,1)
onoremap <silent> <Plug>(easymotion-T2) :call EasyMotion#T(2,0,1)
xnoremap <silent> <Plug>(easymotion-bd-tln) :call EasyMotion#TL(-1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-tln) :call EasyMotion#TL(-1,0,2)
snoremap <silent> <Plug>(easymotion-bd-tln) :call EasyMotion#TL(-1,0,2)
onoremap <silent> <Plug>(easymotion-bd-tln) :call EasyMotion#TL(-1,0,2)
xnoremap <silent> <Plug>(easymotion-T) :call EasyMotion#T(1,1,1)
nnoremap <silent> <Plug>(easymotion-T) :call EasyMotion#T(1,0,1)
snoremap <silent> <Plug>(easymotion-T) :call EasyMotion#T(1,0,1)
onoremap <silent> <Plug>(easymotion-T) :call EasyMotion#T(1,0,1)
xnoremap <silent> <Plug>(easymotion-bd-t) :call EasyMotion#T(1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-t) :call EasyMotion#T(1,0,2)
snoremap <silent> <Plug>(easymotion-bd-t) :call EasyMotion#T(1,0,2)
onoremap <silent> <Plug>(easymotion-bd-t) :call EasyMotion#T(1,0,2)
xnoremap <silent> <Plug>(easymotion-Tn) :call EasyMotion#T(-1,1,1)
nnoremap <silent> <Plug>(easymotion-Tn) :call EasyMotion#T(-1,0,1)
snoremap <silent> <Plug>(easymotion-Tn) :call EasyMotion#T(-1,0,1)
onoremap <silent> <Plug>(easymotion-Tn) :call EasyMotion#T(-1,0,1)
xnoremap <silent> <Plug>(easymotion-s2) :call EasyMotion#S(2,1,2)
nnoremap <silent> <Plug>(easymotion-s2) :call EasyMotion#S(2,0,2)
snoremap <silent> <Plug>(easymotion-s2) :call EasyMotion#S(2,0,2)
onoremap <silent> <Plug>(easymotion-s2) :call EasyMotion#S(2,0,2)
xnoremap <silent> <Plug>(easymotion-Tl) :call EasyMotion#TL(1,1,1)
nnoremap <silent> <Plug>(easymotion-Tl) :call EasyMotion#TL(1,0,1)
snoremap <silent> <Plug>(easymotion-Tl) :call EasyMotion#TL(1,0,1)
onoremap <silent> <Plug>(easymotion-Tl) :call EasyMotion#TL(1,0,1)
xnoremap <silent> <Plug>(easymotion-sn) :call EasyMotion#S(-1,1,2)
nnoremap <silent> <Plug>(easymotion-sn) :call EasyMotion#S(-1,0,2)
snoremap <silent> <Plug>(easymotion-sn) :call EasyMotion#S(-1,0,2)
onoremap <silent> <Plug>(easymotion-sn) :call EasyMotion#S(-1,0,2)
xnoremap <silent> <Plug>(easymotion-Fn) :call EasyMotion#S(-1,1,1)
nnoremap <silent> <Plug>(easymotion-Fn) :call EasyMotion#S(-1,0,1)
snoremap <silent> <Plug>(easymotion-Fn) :call EasyMotion#S(-1,0,1)
onoremap <silent> <Plug>(easymotion-Fn) :call EasyMotion#S(-1,0,1)
xnoremap <silent> <Plug>(easymotion-sl) :call EasyMotion#SL(1,1,2)
nnoremap <silent> <Plug>(easymotion-sl) :call EasyMotion#SL(1,0,2)
snoremap <silent> <Plug>(easymotion-sl) :call EasyMotion#SL(1,0,2)
onoremap <silent> <Plug>(easymotion-sl) :call EasyMotion#SL(1,0,2)
xnoremap <silent> <Plug>(easymotion-Fl) :call EasyMotion#SL(1,1,1)
nnoremap <silent> <Plug>(easymotion-Fl) :call EasyMotion#SL(1,0,1)
snoremap <silent> <Plug>(easymotion-Fl) :call EasyMotion#SL(1,0,1)
onoremap <silent> <Plug>(easymotion-Fl) :call EasyMotion#SL(1,0,1)
xnoremap <silent> <Plug>(easymotion-sl2) :call EasyMotion#SL(2,1,2)
nnoremap <silent> <Plug>(easymotion-sl2) :call EasyMotion#SL(2,0,2)
snoremap <silent> <Plug>(easymotion-sl2) :call EasyMotion#SL(2,0,2)
onoremap <silent> <Plug>(easymotion-sl2) :call EasyMotion#SL(2,0,2)
xnoremap <silent> <Plug>(easymotion-bd-fln) :call EasyMotion#SL(-1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-fln) :call EasyMotion#SL(-1,0,2)
snoremap <silent> <Plug>(easymotion-bd-fln) :call EasyMotion#SL(-1,0,2)
onoremap <silent> <Plug>(easymotion-bd-fln) :call EasyMotion#SL(-1,0,2)
xnoremap <silent> <Plug>(easymotion-F) :call EasyMotion#S(1,1,1)
nnoremap <silent> <Plug>(easymotion-F) :call EasyMotion#S(1,0,1)
snoremap <silent> <Plug>(easymotion-F) :call EasyMotion#S(1,0,1)
onoremap <silent> <Plug>(easymotion-F) :call EasyMotion#S(1,0,1)
xnoremap <silent> <Plug>(easymotion-bd-f) :call EasyMotion#S(1,1,2)
nnoremap <silent> <Plug>(easymotion-bd-f) :call EasyMotion#S(1,0,2)
snoremap <silent> <Plug>(easymotion-bd-f) :call EasyMotion#S(1,0,2)
onoremap <silent> <Plug>(easymotion-bd-f) :call EasyMotion#S(1,0,2)
xnoremap <silent> <Plug>(easymotion-F2) :call EasyMotion#S(2,1,1)
nnoremap <silent> <Plug>(easymotion-F2) :call EasyMotion#S(2,0,1)
snoremap <silent> <Plug>(easymotion-F2) :call EasyMotion#S(2,0,1)
onoremap <silent> <Plug>(easymotion-F2) :call EasyMotion#S(2,0,1)
xnoremap <silent> <Plug>(easymotion-bd-f2) :call EasyMotion#S(2,1,2)
nnoremap <silent> <Plug>(easymotion-bd-f2) :call EasyMotion#S(2,0,2)
snoremap <silent> <Plug>(easymotion-bd-f2) :call EasyMotion#S(2,0,2)
onoremap <silent> <Plug>(easymotion-bd-f2) :call EasyMotion#S(2,0,2)
xnoremap <silent> <Plug>(easymotion-Tl2) :call EasyMotion#TL(2,1,1)
nnoremap <silent> <Plug>(easymotion-Tl2) :call EasyMotion#TL(2,0,1)
snoremap <silent> <Plug>(easymotion-Tl2) :call EasyMotion#TL(2,0,1)
onoremap <silent> <Plug>(easymotion-Tl2) :call EasyMotion#TL(2,0,1)
xnoremap <silent> <Plug>(easymotion-fln) :call EasyMotion#SL(-1,1,0)
nnoremap <silent> <Plug>(easymotion-fln) :call EasyMotion#SL(-1,0,0)
snoremap <silent> <Plug>(easymotion-fln) :call EasyMotion#SL(-1,0,0)
onoremap <silent> <Plug>(easymotion-fln) :call EasyMotion#SL(-1,0,0)
nnoremap <silent> <Plug>(startify-open-buffers) :call startify#open_buffers()
nnoremap <silent> <Plug>(choosewin) :call choosewin#start(range(1, winnr('$')))
snoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
nnoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
snoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
nnoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
snoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
nnoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
snoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
nnoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
xnoremap <silent> <Plug>(openbrowser- :call dein#autoload#_on_map('<Plug>(openbrowser-', 'open-browser.vim','x')
nnoremap <silent> <Plug>(openbrowser- :call dein#autoload#_on_map('<Plug>(openbrowser-', 'open-browser.vim','n')
noremap <silent> <F2> :silent TagbarToggle
vnoremap <C-Space> <Plug>(wildfire-water)
xnoremap <silent> <Plug>(jplus :call dein#autoload#_on_map('<Plug>(jplus', 'vim-jplus','x')
nnoremap <silent> <Plug>(jplus :call dein#autoload#_on_map('<Plug>(jplus', 'vim-jplus','n')
xnoremap <silent> <Plug>(wildfire- :call dein#autoload#_on_map('<Plug>(wildfire-', 'wildfire.vim','x')
nnoremap <silent> <Plug>(wildfire- :call dein#autoload#_on_map('<Plug>(wildfire-', 'wildfire.vim','n')
xnoremap <silent> <Plug>SpaceVim-plugin-iedit :call SpaceVim#plugins#iedit#start(1)
nnoremap <silent> <Plug>SpaceVim-plugin-iedit :call SpaceVim#plugins#iedit#start()
nnoremap <silent> <S-Tab> :wincmd p
nnoremap <silent> <Up> gk
nnoremap <silent> <Down> gj
xnoremap <S-Tab> <gv
nnoremap <F11> :call libcallnr("gvimfullscreen.dll", "ToggleFullScreen", 0)
vnoremap <silent> <C-S-Up> :m '<-2gv=gv
vnoremap <silent> <C-S-Down> :m '>+1gv=gv
nnoremap <silent> <C-S-Up> :m .-2==
nnoremap <silent> <C-S-Down> :m .+1==
nnoremap <silent> <C-Down> :wincmd j
nnoremap <silent> <C-Up> :wincmd k
nnoremap <silent> <C-Left> :wincmd h
nnoremap <silent> <C-Right> :wincmd l
cnoremap  <Home>
cnoremap  <Left>
inoremap <expr>  neocomplete#cancel_popup()
cnoremap  <Right>
imap S <Plug>ISurround
imap s <Plug>Isurround
imap <silent> % <Plug>(matchup-c_g%)
inoremap <expr>  neocomplete#smart_close_popup()."\"
imap <silent> <expr> 	 SpaceVim#mapping#tab()
imap <silent> <expr>  pumvisible() ? "\" : "\"
imap  <Plug>Isurround
cnoremap  w
inoremap <expr>  neocomplete#close_popup()
imap <expr> ( pumvisible() ? complete_parameter#pre_complete("()") : (len(maparg('<Plug>delimitMate(', 'i')) == 0) ? "\<Plug>delimitMate(" : '('
xnoremap <silent> î :call multiple_cursors#select_all("v", 0)
nnoremap <silent> î :call multiple_cursors#select_all("n", 1)
nnoremap <silent> ã :call chat#chatting#OpenMsgWin()
nnoremap <silent> ÷ :call chat#weixin#OpenMsgWin()
nnoremap <silent> ø :call chat#qq#OpenMsgWin()
inoremap <silent> \	 =MyLeaderTabfunc()
inoremap jk 
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set background=dark
set backspace=indent,eol,start
set backup
set backupdir=~/.cache/SpaceVim/backup
set cindent
set comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,f://
set complete=.,w,b,u,t
set completeopt=menuone
set cpoptions=aABceFsd
set directory=~/.cache/SpaceVim/swap
set display=lastline
set expandtab
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set fillchars=vert:│,fold:·
set helplang=en
set hidden
set hlsearch
set incsearch
set laststatus=2
set listchars=tab:→\ ,eol:↵,trail:·,extends:↷,precedes:↶
set matchtime=0
set nomodeline
set mouse=nv
set nrformats=bin,hex
set pumheight=15
set pyxversion=3
set ruler
set runtimepath=~/.SpaceVim.d,~/.vim,/usr/share/vim/vimfiles,~/.cache/vimfiles/repos/github.com/Yggdroot/indentLine,~/.cache/vimfiles/repos/github.com/neomake/neomake,~/.cache/vimfiles/repos/github.com/Shougo/neosnippet-snippets,~/.cache/vimfiles/repos/github.com/morhetz/gruvbox,~/.cache/vimfiles/repos/github.com/tenfyzhong/CompleteParameter.vim,~/.cache/vimfiles/repos/github.com/Shougo/unite.vim,~/.cache/vimfiles/repos/github.com/editorconfig/editorconfig-vim,~/.cache/vimfiles/repos/github.com/Raimondi/delimitMate,~/.cache/vimfiles/repos/github.com/t9md/vim-choosewin,~/.cache/vimfiles/repos/github.com/Shougo/vimproc.vim,~/.cache/vimfiles/repos/github.com/severin-lemaignan/vim-minimap,~/.cache/vimfiles/repos/github.com/tenfyzhong/tagbar-proto.vim,~/.cache/vimfiles/repos/github.com/mhinz/vim-startify,~/.cache/vimfiles/repos/github.com/tenfyzhong/tagbar-makefile.vim,~/.cache/vimfiles/repos/github.com/Shougo/dein.vim,~/.cache/vimfiles/repos/github.com/sbdchd/neoformat,~/.cache/vimfiles/repos/github.com/terryma/vim-multiple-cursors,~/.cache/vimfiles/repos/github.com/Shougo/vimfiler.vim,~/.cache/vimfiles/repos/github.com/Shougo/neocomplete,~/.cache/vimfiles/repos/github.com/Shougo/neosnippet.vim,~/.cache/vimfiles/repos/github.com/Shougo/neopairs.vim,~/.cache/vimfiles/repos/github.com/Shougo/neoinclude.vim,~/.cache/vimfiles/repos/github.com/Shougo/context_filetype.vim,~/.cache/vimfiles/repos/github.com/ujihisa/neco-look,~/.cache/vimfiles/repos/github.com/Shougo/neco-syntax,~/.cache/vimfiles/repos/github.com/honza/vim-snippets,~/.cache/vimfiles/repos/github.com/Shougo/echodoc.vim,~/.cache/vimfiles/.cache/vimrc/.dein,/usr/share/vim/vim81,~/.cache/vimfiles/repos/github.com/Yggdroot/indentLine/after,~/.cache/vimfiles/repos/github.com/tenfyzhong/CompleteParameter.vim/after,~/.cache/vimfiles/.cache/vimrc/.dein/after,/usr/share/vim/vimfiles/after,~/.vim/after,~/.cache/vimfiles/repos/github.com/Shougo/dein.vim
set scrolloff=1
set noshelltemp
set shiftwidth=2
set shortmess=filnxtToOcsF
set showmatch
set noshowmode
set showtabline=2
set sidescrolloff=5
set smartindent
set smarttab
set softtabstop=2
set suffixes=.bak,~,.o,.info,.swp,.aux,.bbl,.blg,.brf,.cb,.dvi,.idx,.ilg,.ind,.inx,.jpg,.log,.out,.png,.toc
set noswapfile
set tabline=%!SpaceVim#layers#core#tabline#get()
set tabstop=2
set termencoding=utf-8
set termguicolors
set ttimeout
set ttimeoutlen=50
set undodir=~/.cache/SpaceVim/undofile
set undofile
set wildignore=*/tmp/*,*.so,*.swp,*.zip,*.class,tags,*.jpg,*.ttf,*.TTF,*.png,*/target/*,.git,.svn,.hg,.DS_Store,*.svg
set wildignorecase
set wildmenu
set window=82
set nowritebackup
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/local/CGRA350/assignment3/ass3-local
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +96 srctree/src/a3.cpp
badd +7 srctree/src/cgra/mesh.hpp
badd +202 srctree/src/main.cpp
badd +33 srctree/src/a3_dogui.cpp
badd +68 srctree/src/a3.hpp
badd +13 srctree/src/a3_inevents.cpp
badd +15 srctree/src/CMakeLists.txt
badd +103 srctree/src/a3_kfwin.cpp
badd +95 srctree/src/app_renderer.cpp
badd +13 srctree/src/app_renderer.hpp
badd +1 \[1m/home/shelly/local/CGRA350/assignment3/ass3-local/srctree/src/asf.hpp
badd +27 srctree/res/shaders/pick.fs.glsl
badd +175 srctree/include/skeleton/skeleton.cpp
badd +179 srctree/src/asf.cpp
badd +0 srctree/res/shaders/simple.fs.glsl
badd +51 srctree/src/splineMath.cpp
badd +5 srctree/src/splineMath.hpp
argglobal
silent! argdel *
$argadd .
tabnew
tabnew
tabnew
tabnew
tabnew
tabnext -5
edit srctree/src/a3.cpp
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
exe '1resize ' . ((&lines * 69 + 41) / 83)
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe '2resize ' . ((&lines * 10 + 41) / 83)
exe 'vert 2resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 3resize ' . ((&columns * 175 + 144) / 288)
argglobal
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 29\ ?\ \"\"\ :\ (\"\ 5.1k\ a3.cpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 37\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 51\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 169 - ((54 * winheight(0) + 34) / 69)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
169
normal! 02|
wincmd w
argglobal
enew
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
nnoremap <buffer> <silent> q :cclose:lclose
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=wipe
setlocal nobuflisted
setlocal buftype=quickfix
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,f://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'qf'
setlocal filetype=qf
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal nomodifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 25\ ?\ \"\"\ :\ (\"\ No\ Name\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 32\ ?\ \"\"\ :\ (\"\ \ qf\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 46\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'qf'
setlocal syntax=qf
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal winfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
wincmd w
argglobal
if bufexists('srctree/src/a3.hpp') | buffer srctree/src/a3.hpp | else | edit srctree/src/a3.hpp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 29\ ?\ \"\"\ :\ (\"\ 3.6k\ a3.hpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 37\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 51\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 40 - ((23 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
40
normal! 03|
wincmd w
exe '1resize ' . ((&lines * 69 + 41) / 83)
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe '2resize ' . ((&lines * 10 + 41) / 83)
exe 'vert 2resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 3resize ' . ((&columns * 175 + 144) / 288)
tabnext
edit srctree/src/a3_inevents.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 38\ ?\ \"\"\ :\ (\"\ 6.7k\ a3_inevents.cpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 46\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 60\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 30 - ((29 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
30
normal! 03|
tabnext
edit srctree/src/splineMath.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 144 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 143 + 144) / 288)
argglobal
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_a#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_a_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ &modified\ ?\ '\ *\ '\ :\ '\ -\ '}1.4k\ splineMath.cpp\ %#SpaceVim_statusline_b_SpaceVim_statusline_c#%#SpaceVim_statusline_c#%{empty(&ft)?\ \"\"\ :\ \"\ \"\ .\ &ft\ .\ \"\ \"}%#SpaceVim_statusline_c_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%#SpaceVim_statusline_warn#\ ●\ 6\ %#SpaceVim_statusline_b_SpaceVim_statusline_c#%#SpaceVim_statusline_c#\ ❖\ ⓢ\ \ %#SpaceVim_statusline_c_SpaceVim_statusline_b#%#SpaceVim_statusline_c_SpaceVim_statusline_z#%#SpaceVim_statusline_z#%=%#SpaceVim_statusline_z#%{SpaceVim#layers#core#statusline#_current_tag()}%#SpaceVim_statusline_b_SpaceVim_statusline_z#%#SpaceVim_statusline_b#%{\"\ \"\ .\ g:_spacevim_statusline_fileformat\ .\ \"\ |\ \"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}%#SpaceVim_statusline_c_SpaceVim_statusline_b#%#SpaceVim_statusline_c#\ %l:%c\ %#SpaceVim_statusline_b_SpaceVim_statusline_c#%#SpaceVim_statusline_b#\ %P\ %#SpaceVim_statusline_c_SpaceVim_statusline_b#
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 51 - ((50 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
51
normal! 05|
wincmd w
argglobal
if bufexists('srctree/src/splineMath.hpp') | buffer srctree/src/splineMath.hpp | else | edit srctree/src/splineMath.hpp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 42\ ?\ \"\"\ :\ (\"\ 444\ bytes\ splineMath.hpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 50\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 64\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 4 - ((3 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
4
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 144 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 143 + 144) / 288)
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
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 35\ ?\ \"\"\ :\ (\"\ 4.0k\ a3_dogui.cpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 43\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 57\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 33 - ((32 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
33
normal! 063|
tabnext
edit srctree/res/shaders/pick.fs.glsl
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 175 + 144) / 288)
argglobal
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=:#
setlocal commentstring=#\ %s
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'conf'
setlocal filetype=conf
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 40\ ?\ \"\"\ :\ (\"\ 504\ bytes\ pick.fs.glsl\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 49\ ?\ \"\"\ :\ (\"\ \ conf\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 63\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'conf'
setlocal syntax=conf
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 27 - ((26 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
27
normal! 04|
wincmd w
argglobal
if bufexists('srctree/res/shaders/simple.fs.glsl') | buffer srctree/res/shaders/simple.fs.glsl | else | edit srctree/res/shaders/simple.fs.glsl | endif
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=:#
setlocal commentstring=#\ %s
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'conf'
setlocal filetype=conf
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 42\ ?\ \"\"\ :\ (\"\ 864\ bytes\ simple.fs.glsl\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 51\ ?\ \"\"\ :\ (\"\ \ conf\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 65\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'conf'
setlocal syntax=conf
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 40 - ((39 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
40
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 175 + 144) / 288)
tabnext
edit srctree/src/app_renderer.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 175 + 144) / 288)
argglobal
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 39\ ?\ \"\"\ :\ (\"\ 2.7k\ app_renderer.cpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 47\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 61\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 6 - ((5 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
6
normal! 0
wincmd w
argglobal
if bufexists('srctree/src/app_renderer.hpp') | buffer srctree/src/app_renderer.hpp | else | edit srctree/src/app_renderer.hpp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <buffer> <S-BS> <Plug>delimitMateS-BS
imap <buffer> <silent> g <Plug>delimitMateJumpMany
imap <buffer> " <Plug>delimitMate"
imap <buffer> ' <Plug>delimitMate'
imap <buffer> ) <Plug>delimitMate)
imap <buffer> [ <Plug>delimitMate[
imap <buffer> ] <Plug>delimitMate]
imap <buffer> ` <Plug>delimitMate`
imap <buffer> { <Plug>delimitMate{
imap <buffer> } <Plug>delimitMate}
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t
setlocal concealcursor=niv
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
set foldtext=SpaceVim#default#Customfoldtext()
setlocal foldtext=SpaceVim#default#Customfoldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=bin,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=2
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%#SpaceVim_statusline_ia#%{SpaceVim#layers#core#statusline#mode(mode())}\ %{\ SpaceVim#layers#core#statusline#winnr(get(w:,\ \"winid\",\ winnr()))\ }\ %#SpaceVim_statusline_ia_SpaceVim_statusline_b#%#SpaceVim_statusline_b#%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 44\ ?\ \"\"\ :\ (\"\ 845\ bytes\ app_renderer.hpp\ \ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 52\ ?\ \"\"\ :\ (\"\ \ cpp\ \")}%{\ get(w:,\ \"winwidth\",\ 150)\ <\ 66\ ?\ \"\"\ :\ (\"\ \ ❖\ ⓢ\ \ \ \")}%=%{\"\ \"\ .\ &ff\ .\ \"|\"\ .\ (&fenc!=\"\"?&fenc:&enc)\ .\ \"\ \"}\ %P\ 
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal undofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal nowinfixheight
setlocal nowinfixwidth
set nowrap
setlocal nowrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 40) / 80)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 112 + 144) / 288)
exe 'vert 2resize ' . ((&columns * 175 + 144) / 288)
tabnext 3
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
