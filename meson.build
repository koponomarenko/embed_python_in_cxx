project('embed_python_in_cxx', 'cpp',
        default_options: ['cpp_std=c++17'],
        version: '0.1.0')

thread_dep = dependency('threads')
boost_dep = dependency('boost', static: true, required: true,
                        modules: ['python3'])

python = import('python').find_installation('python3')
python_dep = python.dependency(required: true, embed: true)

executable('embed_python_in_cxx', 'main.cpp',
    dependencies: [
        thread_dep,
        boost_dep,
        python_dep,
    ],
#    cpp_args: ['-v'],
)
