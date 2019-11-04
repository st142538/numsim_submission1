#!/bin/bash
# Do not forget to select a proper partition if the default
# one is no fit for the job! You can do that either in the sbatch
# command line or here with the other settings.
#SBATCH --job-name=numsim
#SBATCH --output=output.txt
#SBATCH --mail-user=finkdl@ipvs.uni-stuttgart.de
#SBATCH --nodes=1
#SBATCH --tasks-per-node=1
#SBATCH --time=00:10:00
# Never forget that! Strange happenings ensue otherwise.
#SBATCH --export=NONE

set -e # Good Idea to stop operation on first error.

echo "SLURM_JOBID="$SLURM_JOBID
echo "SLURM_JOB_NODELIST"=$SLURM_JOB_NODELIST
echo "SLURM_NNODES"=$SLURM_NNODES
echo "SLURMTMPDIR="$SLURMTMPDIR

echo "working directory = "$SLURM_SUBMIT_DIR

# source /sw/batch/init.sh

# Load environment modules for your application here.
module use /usr/local.nfs/sgs/modulefiles
module load vtk/8.2
module load gcc/8.2
module load cmake/cmake-3.12.3

# Compile
mkdir -p build
cd build
cmake ..
make install

# Start working
./numsim parameters.txt
