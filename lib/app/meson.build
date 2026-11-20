sdl = dependency('sdl3')

impl = static_library(
    import('fs').name(meson.current_source_dir()),
    sources: [
        'app_base.cpp',
        'app_dumb.cpp',
    ],
    dependencies: [
        libcolor,
        sdl,
    ],
)

libapp = declare_dependency(
    link_with: impl,
    include_directories: include_directories('.'),
    dependencies: [
        libcolor,
    ],
)
