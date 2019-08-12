from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy as np

setup(
	name="krnnt_utils",
	version="1.0.0",
	install_requires=["Cython"],
    ext_modules = cythonize(Extension("krnnt_utils", sources=["krnnt_utils.pyx"], include_dirs=[np.get_include()]), annotate=True)
)