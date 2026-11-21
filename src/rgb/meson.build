progs = [
    'linear',
    'sine',
    'rainbow',
]

foreach prog : progs
    executable(
        prog,
        sources: [
            prog + '.cpp',
        ],
        dependencies: [
            libapp,
            libcolor,
        ],
    )
endforeach
