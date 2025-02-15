#!/usr/bin/zsh
#SBATCH --job-name=io500-beeond
#SBATCH --beeond
#SBATCH --exclusive
#SBATCH --time=01:59:00
#SBATCH --ntasks=16
#SBATCH --nodes=1
#SBATCH --account=thes1876
#SBATCH --output=/hpcwork/ph077533/io500-beeond/io500-beeond_%j.out

ml purge
ml load iimpi
ml load HDF5
cp $HPCWORK/io500-claix-2023/io500 $BEEOND
cp $HPCWORK/io500-claix-2023/config-beeond-mpi.ini $BEEOND

cd $BEEOND
ls -l
file io500
file config-beeond-mpi.ini

$MPIEXEC ./io500 config-beeond-mpi.ini
