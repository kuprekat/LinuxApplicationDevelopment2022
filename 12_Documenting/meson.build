project('src/num-game', 'c')
executable('num-game', sources : 'src/num-game.c')
subdir('po')


run_target('clean_generates', command: ['rm', '-rf', '../po/ru.pot', 'build.ninja', 'compile_commands.json', '.gitignore', '.hgignore', 'meson-info', 'meson-logs', 'meson-private', '.ninja_deps', '.ninja_log', 'num-game', 'num-game.p', 'po'])
