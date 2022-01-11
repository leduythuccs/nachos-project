# Nachos-project
Not Another Completely Heuristic Operating System

This is our course-work for the OS course in HCMUS.

Nashos version: 4.0

## Installation

To install: run `bash full_install.sh`. In case of error, you might want to run the installation step by step via:
```bash
# Install building tools like make, g++
bash install_building_tools.sh

# Build the nachos
bash build_nachos.sh

# Build the coff2noff translator
bash coff2noff.sh

# Build & run tests in code/test folder
bash build_test.sh
```

You can read the full building instruction [here](https://www.fit.hcmus.edu.vn/~ntquan/os/setup_nachos.html) if you want to (believe me, you don't want to read it :) ).


## CI/CD

I've set up the GitHub workflow, it will automatically build & test the nachos when you make a commit.

Please make sure that you passed all the workflows before creating a pull request.
