#!/usr/bin/zsh
#SBATCH --job-name=io500-beeond
#SBATCH --beeond
#SBATCH --exclusive
#SBATCH --time=01:59:00
#SBATCH --ntasks=16
#SBATCH --nodes=1


ml purge
ml load iimpi
ml load HDF5

cp -r $HPCWORK/io500-claix-2023/io500 $BEEOND
cp -r $HPCWORK/io500-claix-2023/config-beeond-mpi.ini $BEEOND
$MPIEXEC ./io500 config-beeond-mpi.ini
