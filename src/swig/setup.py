from setuptools import setup, find_packages
print(find_packages())
if __name__ == "__main__":
    setup(
        name='hough',
        version='0.1',
        packages=find_packages(),
        include_package_data=True
    )



# try this: https://stackoverflow.com/a/56694024/8591914