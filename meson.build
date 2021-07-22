project('zadaca2', 'cpp', default_options : ['cpp_std=c++14', 'buildtype=release'])

inc = include_directories('include', 'resources')


project_source_files = [
    'src/attack.cpp',
    'src/bishop.cpp',
    'src/chessboard.cpp',
    'src/game.cpp',
    'src/king.cpp',
    'src/knight.cpp',
    'src/main.cpp',
    'src/material.cpp',
    'src/pawn.cpp',
    'src/queen.cpp',
    'src/rook.cpp',
    'src/square.cpp'
]

testexe = executable('zadaca2', project_source_files, include_directories : inc)
