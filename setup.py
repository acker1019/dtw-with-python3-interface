from setuptools import Extension, setup

setup(
    name='pydtw',
    version='1.0',
    description='Python Package of DTW C++ Extension',
    ext_modules=[
        Extension('pydtw',
            sources=['pydtw.cpp', 'dtw.cpp'],
            py_limited_api=True,
            language='c++',
            extra_compile_args=['-std=c++17']
    )]
)

# python setup.py build
