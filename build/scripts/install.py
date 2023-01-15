import setuptools

setuptools.setup(
  	name='rexpy',
    version='0.0.1',
    author='Nick De Breuck',
    author_email='nick.debreuck@outlook.com',
    description='Python framework used with Rex Engine',
    url='https://github.com/Dyronix/Rex',
    packages=setuptools.find_packages(),
    classifiers=[
      # https://pypi.org/classifiers/
      "Programming Language :: Python :: 3",
      "License :: OSI Approved :: MIT License",
      "Operating System :: OS Independent",
    ],
    python_requires='>=3.7',
    install_requires=["requests", "termcolor"],
)