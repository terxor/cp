nnoremap <leader>c :call Compile()<CR>
nnoremap <leader>v :call Run()<CR>

nnoremap <leader>1 :call LoadTemplate("cpp/template.cc")<CR>
nnoremap <leader>2 :call LoadTemplate("cpp/template-ext.cc")<CR>

" Normal paste in inline terminal
tmap <C-v> <C-w>"+

" Utility
let g:utilDir = $CP_UTILS

function! LoadTemplate(t)
	let s = ":0r " . g:utilDir . "/" . a:t 
	" Delete first
	execute ":normal ggdG"
	execute s
endfunction

function! ExecCommand(cmd)
  execute ":vertical belowright term " . a:cmd
endfunction

function! Compile()
  execute ":w"
  call ExecCommand("python.exe " . g:utilDir . "/cp.py % compile")
endfunction

function! Run()
  call ExecCommand("python.exe " . g:utilDir . "/cp.py % run")
endfunction