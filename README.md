# GreenScreenWiper

Piss shrimple Computer Vision project that takes a green-screen image as input and outputs a PNG with the green-screen removed.

## Usage

```bash
git clone https://github.com/masroof-maindak/GreenScreenWiper.git
cd GreenScreenWiper
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. # Or 'Debug' if you want to hack away.
cmake --build .
./gsw <fpath>
```

## Dependencies

- OpenCV
- QT6
- VTK
- HDF5

#### Arch Linux

```bash
sudo pacman -S opencv qt6-base vtk hdf5
```
