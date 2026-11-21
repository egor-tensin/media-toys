progs = [
    'linear',
    'sine',
    'rainbow',
    'blackwhite',
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
