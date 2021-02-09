
project('myapp', 'cpp')

zen_proj = subproject('zen', default_options: ['namespace=myapp::zen'])
zen_dep = zen_proj.get_variable('zen_dep')

executable('myapp', 'src/main.cc', dependencies: zen_dep)

