let project_dir = $GIT . '/predictor2/'
let build_dir = project_dir . 'build/'

exe 'CMakeProjectDir' project_dir
exe 'CMakeBuildLocation' build_dir
exe 'MakeFile' build_dir .'Makefile'
exe 'MakeCmdlineArgs -j4'

let command = project_dir . 'build/bin/predictor'
exe "nnoremap <leader>t :!" . command . " <CR>"
