project('runline', ['cpp'], version : '0.1.0', default_options : ['cpp_std=c++11'])

qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets'])
qt5 = import('qt5')

source_root = meson.source_root()
source_dir = include_directories('source/')
resource_dir = 'resource/'

runline_source = [
    'source/main.cpp',
    'source/styles.h',
    'source/mainwindow.h',
    'source/mainwindow.cpp',
    'source/orientbutton.h',
    'source/orientbutton.cpp'
]

runline_resource = [
    qt5.preprocess(
    moc_headers : 'source/mainwindow.h',
    ui_files : 'resource/mainwindow.ui',
    dependencies: [qt5_dep])
]

executable('runline',
    [runline_source, runline_resource],
    include_directories : [source_dir, resource_dir],
    dependencies : [qt5_dep]
)
