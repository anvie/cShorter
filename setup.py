from distutils.core import setup, Extension
 
module1 = Extension('shorter', sources = ['shorter.c'])
 
setup (name = 'Shorter',
        version = '1.0',
        description = 'This is a test',
        ext_modules = [module1])

