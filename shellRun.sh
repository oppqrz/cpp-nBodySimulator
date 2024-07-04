g++ sim.C -Ofast -march=native -flto -Ofast -march=native -flto -fno-signed-zeros -fno-trapping-math -fopenmp -D_GLIBCXX_PARALLEL -o run
time ./run