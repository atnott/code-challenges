from setuptools import setup, find_packages

setup(
    name='useful_utils',
    version='1.0.0',
    packages=find_packages(),
    description='Utils to make life easier',
    author='Anton Krotov',
    author_email='twinkidr@gmail.com',
    url='https://github.com/anton-krotov/code-challenges/open-source-practice/my-library',
    install_requires=[
        'pytest'
    ],
    python_requires='>=3'
)