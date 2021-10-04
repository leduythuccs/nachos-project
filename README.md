# Nachos-project1

## Installation

As a teammate, I've already created the script to install, build the nachos for you :).
You can still read the full building instruction [here](https://www.fit.hcmus.edu.vn/~ntquan/os/setup_nachos.html) if you want to (believe me, you don't want to read it).

To install: run `bash full_install.sh`. In case of error, you might want to run the installation step by step via:
```bash
# Install building tools like make, g++
bash install_building_tools.sh

# Build the nash os + run it
bash build_nash_os.sh

# Build the coff2noff translator
bash coff2noff.sh

# Build & run tests in code/test folder
bash build_test.sh
```

## Github workflow

I've setted up the github workflow, it will automatically run the building script to make sure everything is okay.

Please make sure that you passed all the workflows before create a pull request.
