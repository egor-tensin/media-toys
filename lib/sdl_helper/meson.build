actual_sdl = dependency('sdl3')

impl = static_library(
    import('fs').name(meson.current_source_dir()),
    sources: [
        'sdl_helper.cpp',
    ],
    dependencies: [
        actual_sdl,
        libcolor,
    ],
)

libsdl_helper = declare_dependency(
    link_with: impl,
    include_directories: include_directories('.'),
    dependencies: [
        libcolor,
    ],
)
