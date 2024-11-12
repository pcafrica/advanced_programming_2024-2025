# Configure [GSL](https://www.gnu.org/software/gsl/)
```bash
./configure --enable-shared --enable-static --prefix=/opt/gsl
make -j<N>
sudo make install
```

# Static linkage
```bash
g++ example_gsl.cpp -I/opt/gsl/include /opt/gsl/lib/libgsl.a -lopenblas -o main
```

# Dynamic linkage
```bash
g++ example_gsl.cpp -I/opt/gsl/include -L/opt/gsl/lib -lgsl -lopenblas -o main # Precedence to shared libraries.
```
